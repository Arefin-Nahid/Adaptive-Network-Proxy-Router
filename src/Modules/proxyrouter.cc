#include <omnetpp.h>
#include "helpers.h"
#include <map>
#include <random>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <set>

using namespace omnetpp;
using namespace std;

namespace simple_dns_http {

struct AdaptiveCacheEntry {
    string key;
    string contentHash;
    double ttl;
    double baseTTL;
    double size;
    string url;
    double timestamp;
    int accessCount;
    double lastAccess;
    double avgLatency;
    int hitCount;
    int missCount;
    bool validated;
};

struct LearningRoute {
    long destination;
    int gateIndex;
    double timestamp;
    double confidence;
    int hopCount;
    bool learned;
};

class ProxyRouter : public cSimpleModule {
private:
    int addr;
    int cacheSize;
    double defaultTTL;
    double minTTL;
    double maxTTL;
    bool enableCaching;
    bool enableSecurityFiltering;
    bool enableAdaptiveTTL;
    bool enableLearning;
    bool initialFlooding;
    bool validateResponses;
    double processingDelay;
    double latencyThreshold;
    double congestionThreshold;
    double suspicionThreshold;
    double suspicionDecayRate;

    // Gate mappings (based on NED topology)
    static const int HTTP_ORIGIN_GATE = 0;
    static const int DHCP_LEGIT_GATE = 1;
    static const int DHCP_ROGUE_GATE = 2;
    static const int FIRST_CLIENT_GATE = 3;

    // Caching structures
    map<string, AdaptiveCacheEntry> cache;
    map<string, list<string>::iterator> cacheIndex;
    list<string> lruList;

    // Learning router structures
    map<long, LearningRoute> routingTable;
    map<long, vector<int>> possiblePaths;
    map<int, long> gateToClient;
    map<long, int> clientToGate;

    // DHCP transaction tracking
    map<string, set<int>> dhcpDiscoverGates;
    map<string, int> dhcpRequestSource;
    map<string, int> dhcpOfferSourceGate;  // Track which gate the accepted offer came from

    // Network monitoring
    map<int, double> gateLatency;
    map<int, int> gateLoad;
    double currentCongestion;

    // Security tracking
    map<string, double> suspicionScore;
    map<int, int> rogueDetections;
    int totalRogueDetections;
    map<string, bool> blacklistedServers;

    // Statistics
    double totalHits;
    double totalRequests;
    double totalCachePoisonAttempts;
    double totalBlockedResponses;
    int routingUpdates;

    cMessage *routingUpdateTimer;
    cMessage *cleanupTimer;
    mt19937 gen;
    ofstream logFile;

protected:
    void initialize() override {
        addr = par("address");
        cacheSize = par("cacheSize").intValue();
        defaultTTL = par("defaultTTL").doubleValue();
        minTTL = par("minTTL").doubleValue();
        maxTTL = par("maxTTL").doubleValue();
        enableCaching = par("enableCaching").boolValue();
        enableSecurityFiltering = par("enableSecurityFiltering").boolValue();
        enableAdaptiveTTL = par("enableAdaptiveTTL").boolValue();
        enableLearning = par("enableLearning").boolValue();
        initialFlooding = par("initialFlooding").boolValue();
        validateResponses = par("validateResponses").boolValue();
        processingDelay = par("processingDelay").doubleValue();
        latencyThreshold = par("latencyThreshold").doubleValue();
        congestionThreshold = par("congestionThreshold").doubleValue();
        suspicionThreshold = par("suspicionThreshold").doubleValue();
        suspicionDecayRate = par("suspicionDecayRate").doubleValue();

        totalHits = 0;
        totalRequests = 0;
        totalCachePoisonAttempts = 0;
        totalBlockedResponses = 0;
        totalRogueDetections = 0;
        routingUpdates = 0;
        currentCongestion = 0;

        random_device rd;
        gen = mt19937(rd());

        routingUpdateTimer = new cMessage("routing_update");
        scheduleAt(simTime() + par("routingUpdateInterval").doubleValue(), routingUpdateTimer);

        cleanupTimer = new cMessage("cleanup");
        scheduleAt(simTime() + 60.0, cleanupTimer);

        string logsDir = par("logsDir").stringValue();
        logFile.open(logsDir + "/proxy_" + to_string(addr) + ".log");

        EV_INFO << "ProxyRouter " << addr << " initialized with:\n";
        EV_INFO << "  Adaptive Caching: " << (enableAdaptiveTTL ? "ON" : "OFF") << "\n";
        EV_INFO << "  Learning Router: " << (enableLearning ? "ON" : "OFF") << "\n";
        EV_INFO << "  Security Filtering: " << (enableSecurityFiltering ? "ON" : "OFF") << "\n";
        EV_INFO << "  Cache Size: " << cacheSize << ", TTL: " << minTTL << "-" << maxTTL << "s\n";
    }

    void handleMessage(cMessage *msg) override {
        if (msg->isSelfMessage()) {
            handleTimerMessage(msg);
            return;
        }

        int arrivalGate = msg->getArrivalGate()->getIndex();
        long srcAddr = SRC(msg);

        updateRoutingInfo(srcAddr, arrivalGate);
        updateNetworkMetrics(arrivalGate);

        switch (msg->getKind()) {
            case HTTP_REQUEST:
                handleHTTPRequest(msg, arrivalGate);
                break;
            case HTTP_RESPONSE:
                handleHTTPResponse(msg, arrivalGate);
                break;
            case DHCP_DISCOVER:
            case DHCP_OFFER:
            case DHCP_REQUEST:
            case DHCP_ACK:
                handleDHCPMessage(msg, arrivalGate);
                break;
            case POISON_ATTEMPT:
                handlePoisonAttempt(msg, arrivalGate);
                break;
            default:
                EV_WARN << "ProxyRouter " << addr << " unexpected message kind="
                        << msg->getKind() << "\n";
                delete msg;
        }
    }

    void handleHTTPRequest(cMessage *msg, int arrivalGate) {
        string url = msg->par("url").stringValue();
        string cacheKey = generateCacheKey(url);
        long clientAddr = SRC(msg);
        double requestTime = simTime().dbl();

        totalRequests++;

        EV_INFO << "ProxyRouter " << addr << " received HTTP request for " << url
                << " from client " << clientAddr << "\n";
        logToFile("HTTP_REQUEST", url, clientAddr);

        if (enableCaching && isCacheValid(cacheKey)) {
            AdaptiveCacheEntry &entry = cache[cacheKey];

            totalHits++;
            entry.accessCount++;
            entry.hitCount++;
            entry.lastAccess = requestTime;

            updateLRU(cacheKey);

            double hitRate = (totalRequests > 0) ? (totalHits/totalRequests*100) : 0;
            EV_INFO << "ProxyRouter " << addr << " CACHE HIT for " << url
                    << " (hit rate: " << hitRate << "%)\n";

            sendCachedResponse(msg, entry, arrivalGate);

            if (enableAdaptiveTTL) {
                adaptTTL(cacheKey);
            }

            delete msg;
            return;
        }

        double hitRate = (totalRequests > 0) ? (totalHits/totalRequests*100) : 0;
        EV_INFO << "ProxyRouter " << addr << " CACHE MISS for " << url
                << " (hit rate: " << hitRate << "%)\n";

        if (cache.find(cacheKey) != cache.end()) {
            cache[cacheKey].missCount++;
        }

        if (!msg->hasPar("proxyGate")) {
            msg->addPar("proxyGate").setLongValue(arrivalGate);
        } else {
            msg->par("proxyGate").setLongValue(arrivalGate);
        }

        if (!msg->hasPar("requestTime")) {
            msg->addPar("requestTime").setDoubleValue(requestTime);
        } else {
            msg->par("requestTime").setDoubleValue(requestTime);
        }

        // Forward to HTTP origin server (gate 0)
        forwardToOrigin(msg);
    }

    void handleHTTPResponse(cMessage *msg, int arrivalGate) {
        string url = msg->par("url").stringValue();
        string cacheKey = msg->par("cacheKey").stringValue();
        string contentHash = msg->par("contentHash").stringValue();

        // Get the client address and gate from the stored info
        int clientGate = -1;
        long clientAddr = -1;

        if (msg->hasPar("proxyGate")) {
            clientGate = msg->par("proxyGate").longValue();
        }

        if (msg->hasPar("dst")) {
            clientAddr = msg->par("dst").longValue();
        }

        double requestTime = 0;
        double responseLatency = 0;

        if (msg->hasPar("requestTime")) {
            requestTime = msg->par("requestTime").doubleValue();
            responseLatency = simTime().dbl() - requestTime;
        } else {
            responseLatency = par("processingDelay").doubleValue();
        }

        EV_INFO << "ProxyRouter " << addr << " received HTTP response for " << url
                << " (latency: " << responseLatency << "s)\n";

        if (validateResponses && enableSecurityFiltering) {
            if (!validateResponse(msg, contentHash)) {
                totalBlockedResponses++;
                EV_WARN << "ProxyRouter " << addr << " BLOCKED suspicious response for "
                        << url << " (total blocked: " << totalBlockedResponses << ")\n";
                logToFile("BLOCKED_RESPONSE", url, clientAddr);
                delete msg;
                return;
            }
        }

        if (enableCaching) {
            storeInCache(msg, cacheKey, url, responseLatency);
        }

        // Forward to the client that made the request
        if (clientGate >= FIRST_CLIENT_GATE) {
            send(msg, "ethg$o", clientGate);
            EV_INFO << "ProxyRouter " << addr << " forwarded response to client via gate "
                    << clientGate << "\n";
        } else if (clientAddr != -1) {
            forwardToClient(msg, clientAddr);
        } else {
            EV_WARN << "ProxyRouter " << addr << " cannot determine client for response\n";
            delete msg;
        }
    }

    void handleDHCPMessage(cMessage *msg, int arrivalGate) {
        int kind = msg->getKind();
        long srcAddr = SRC(msg);
        long dstAddr = DST(msg);

        // Security filtering for rogue DHCP
        if (enableSecurityFiltering && (kind == DHCP_OFFER || kind == DHCP_ACK)) {
            if (msg->hasPar("isRogue")) {
                bool isRogue = msg->par("isRogue").boolValue();
                if (isRogue) {
                    totalRogueDetections++;
                    rogueDetections[arrivalGate]++;

                    string serverIP = msg->par("serverIP").stringValue();
                    suspicionScore[serverIP] += 0.3;

                    if (suspicionScore[serverIP] >= suspicionThreshold) {
                        blacklistedServers[serverIP] = true;
                        EV_WARN << "ProxyRouter " << addr << " BLACKLISTED rogue DHCP server "
                                << serverIP << "\n";
                        logToFile("BLACKLIST", serverIP, 0);
                    }

                    EV_WARN << "ProxyRouter " << addr << " DETECTED ROGUE DHCP! "
                            << "Total: " << totalRogueDetections
                            << ", Suspicion: " << suspicionScore[serverIP] << "\n";
                    logToFile("ROGUE_DHCP", serverIP, 0);
                }
            }
        }

        if (kind == DHCP_DISCOVER) {
            string transactionId = msg->par("transactionId").stringValue();
            string clientMac = msg->par("clientMac").stringValue();

            // Store the source gate for this transaction
            dhcpRequestSource[transactionId] = arrivalGate;

            if (dhcpDiscoverGates.find(transactionId) == dhcpDiscoverGates.end()) {
                dhcpDiscoverGates[transactionId] = set<int>();
            }

            // Forward to both DHCP servers (gates 1 and 2)
            simtime_t baseDelay = processingDelay;

            for (int i = DHCP_LEGIT_GATE; i <= DHCP_ROGUE_GATE; i++) {
                if (dhcpDiscoverGates[transactionId].find(i) == dhcpDiscoverGates[transactionId].end()) {
                    cMessage *copy = msg->dup();
                    copy->addPar("forwardGate").setLongValue(i);
                    scheduleAt(simTime() + baseDelay + SimTime((i-1) * 100, SIMTIME_US), copy);
                    dhcpDiscoverGates[transactionId].insert(i);
                }
            }
            delete msg;

        } else if (kind == DHCP_REQUEST) {
            string transactionId = msg->par("transactionId").stringValue();
            string requestedIP = msg->par("requestedIP").stringValue();

            // Store/update the source gate for this transaction
            dhcpRequestSource[transactionId] = arrivalGate;

            EV_INFO << "ProxyRouter " << addr << " received DHCP REQUEST from gate "
                    << arrivalGate << " (transaction: " << transactionId << ")\n";

            // Forward only to the DHCP server gates (1 and 2)
            simtime_t baseDelay = processingDelay;

            for (int i = DHCP_LEGIT_GATE; i <= DHCP_ROGUE_GATE; i++) {
                if (i != arrivalGate) {
                    cMessage *copy = msg->dup();
                    copy->addPar("forwardGate").setLongValue(i);
                    scheduleAt(simTime() + baseDelay + SimTime((i-1) * 100, SIMTIME_US), copy);
                }
            }
            delete msg;

        } else if (kind == DHCP_OFFER || kind == DHCP_ACK) {
            string transactionId = msg->par("transactionId").stringValue();
            string clientMac = msg->par("clientMac").stringValue();

            // Find the original requesting client's gate
            int targetGate = -1;
            if (dhcpRequestSource.find(transactionId) != dhcpRequestSource.end()) {
                targetGate = dhcpRequestSource[transactionId];
            }

            if (targetGate >= FIRST_CLIENT_GATE) {
                // Send only to the specific client that requested it
                scheduleForwardMessage(msg, targetGate);
                EV_INFO << "ProxyRouter " << addr << " forwarded "
                        << (kind == DHCP_OFFER ? "DHCP OFFER" : "DHCP ACK")
                        << " to client at gate " << targetGate
                        << " (MAC: " << clientMac << ")\n";
            } else {
                // Should not happen - but log warning and drop
                EV_WARN << "ProxyRouter " << addr << " no route for "
                        << (kind == DHCP_OFFER ? "DHCP OFFER" : "DHCP ACK")
                        << " (transaction: " << transactionId << ")\n";
                delete msg;
            }
        } else {
            EV_WARN << "ProxyRouter " << addr << " unknown DHCP message kind=" << kind << "\n";
            delete msg;
        }
    }

    void scheduleForwardMessage(cMessage *msg, int targetGate) {
        cGate *outGate = gate("ethg$o", targetGate);
        simtime_t channelFinishTime = simTime();
        if (outGate->getTransmissionChannel() != nullptr) {
            channelFinishTime = outGate->getTransmissionChannel()->getTransmissionFinishTime();
        }

        msg->addPar("forwardGate").setLongValue(targetGate);
        if (channelFinishTime > simTime()) {
            scheduleAt(channelFinishTime + SimTime(10, SIMTIME_US), msg);
        } else {
            scheduleAt(simTime() + processingDelay, msg);
        }
    }

    void handlePoisonAttempt(cMessage *msg, int arrivalGate) {
        totalCachePoisonAttempts++;

        string targetKey = msg->par("targetCacheKey").stringValue();
        string attackerId = msg->par("attackerId").stringValue();

        EV_WARN << "ProxyRouter " << addr << " detected CACHE POISON attempt on "
                << targetKey << " from " << attackerId
                << " (total attempts: " << totalCachePoisonAttempts << ")\n";

        suspicionScore[attackerId] += 0.5;

        if (suspicionScore[attackerId] >= suspicionThreshold) {
            blacklistedServers[attackerId] = true;
            EV_WARN << "ProxyRouter " << addr << " BLACKLISTED attacker " << attackerId << "\n";
        }

        logToFile("POISON_ATTEMPT", targetKey, 0);
        delete msg;
    }

    void handleTimerMessage(cMessage *msg) {
        if (msg->hasPar("forwardGate")) {
            int targetGate = msg->par("forwardGate").longValue();

            cGate *outGate = gate("ethg$o", targetGate);
            if (outGate->getTransmissionChannel() != nullptr) {
                simtime_t finishTime = outGate->getTransmissionChannel()->getTransmissionFinishTime();
                if (finishTime > simTime()) {
                    scheduleAt(finishTime + SimTime(10, SIMTIME_US), msg);
                    return;
                }
            }

            send(msg, "ethg$o", targetGate);
            return;
        }

        if (msg == routingUpdateTimer) {
            updateRoutingTable();
            scheduleAt(simTime() + par("routingUpdateInterval").doubleValue(), msg);
        } else if (msg == cleanupTimer) {
            cleanupCache();
            decaySuspicion();
            cleanupDHCPTracking();
            scheduleAt(simTime() + 60.0, msg);
        } else {
            delete msg;
        }
    }

    // ========== ADAPTIVE CACHING ==========

    void adaptTTL(const string& cacheKey) {
        if (cache.find(cacheKey) == cache.end()) return;

        AdaptiveCacheEntry &entry = cache[cacheKey];

        int totalAccess = entry.hitCount + entry.missCount;
        double hitRate = (totalAccess > 0) ? (double)entry.hitCount / totalAccess : 0.5;

        double timeSinceCreation = simTime().dbl() - entry.timestamp;
        double accessFreq = (timeSinceCreation > 0) ? entry.accessCount / timeSinceCreation : 0;

        double multiplier = 1.0;

        if (hitRate > 0.8) multiplier += 0.5;
        else if (hitRate > 0.6) multiplier += 0.3;
        else if (hitRate > 0.4) multiplier += 0.1;
        else if (hitRate < 0.2) multiplier *= 0.5;

        if (accessFreq > 10.0) multiplier += 0.3;
        else if (accessFreq > 5.0) multiplier += 0.2;
        else if (accessFreq > 1.0) multiplier += 0.1;

        if (entry.avgLatency > latencyThreshold) {
            multiplier += 0.3;
        }

        if (currentCongestion > congestionThreshold) {
            multiplier += 0.2;
        }

        double newTTL = entry.baseTTL * multiplier;
        newTTL = max(minTTL, min(maxTTL, newTTL));

        double oldTTL = entry.ttl;
        entry.ttl = newTTL;

        if (abs(newTTL - oldTTL) > 10.0) {
            EV_INFO << "ProxyRouter " << addr << " adapted TTL for " << entry.url
                    << " from " << oldTTL << "s to " << newTTL << "s "
                    << "(hitRate=" << hitRate << ", freq=" << accessFreq
                    << ", latency=" << entry.avgLatency << "s)\n";
            logToFile("TTL_ADAPT", entry.url + " " + to_string(newTTL), 0);
        }
    }

    bool isCacheValid(const string& cacheKey) {
        if (cache.find(cacheKey) == cache.end()) return false;

        AdaptiveCacheEntry &entry = cache[cacheKey];
        double age = simTime().dbl() - entry.timestamp;

        return (age < entry.ttl && entry.validated);
    }

    void storeInCache(cMessage *msg, const string &cacheKey, const string &url, double latency) {
        AdaptiveCacheEntry entry;
        entry.key = cacheKey;
        entry.url = url;
        entry.contentHash = msg->par("contentHash").stringValue();
        entry.timestamp = simTime().dbl();
        entry.ttl = defaultTTL;
        entry.baseTTL = defaultTTL;
        entry.accessCount = 0;
        entry.hitCount = 0;
        entry.missCount = 0;
        entry.lastAccess = simTime().dbl();
        entry.size = msg->par("contentLength").longValue();
        entry.avgLatency = latency;
        entry.validated = true;

        if (cache.size() >= (size_t)cacheSize) {
            evictLRU();
        }

        cache[cacheKey] = entry;
        lruList.push_front(cacheKey);
        cacheIndex[cacheKey] = lruList.begin();

        EV_INFO << "ProxyRouter " << addr << " stored in cache: " << url
                << " (TTL=" << entry.ttl << "s, latency=" << latency << "s, size="
                << cache.size() << ")\n";
    }

    void evictLRU() {
        if (lruList.empty()) return;

        string oldestKey = lruList.back();
        lruList.pop_back();

        if (cache.find(oldestKey) != cache.end()) {
            EV_INFO << "ProxyRouter " << addr << " evicted LRU entry: "
                    << cache[oldestKey].url << "\n";
            cache.erase(oldestKey);
        }
        cacheIndex.erase(oldestKey);
    }

    void updateLRU(const string& cacheKey) {
        if (cacheIndex.find(cacheKey) != cacheIndex.end()) {
            lruList.erase(cacheIndex[cacheKey]);
        }
        lruList.push_front(cacheKey);
        cacheIndex[cacheKey] = lruList.begin();
    }

    // ========== LEARNING ROUTER ==========

    void updateRoutingInfo(long srcAddr, int arrivalGate) {
        gateToClient[arrivalGate] = srcAddr;
        clientToGate[srcAddr] = arrivalGate;

        if (enableLearning) {
            if (routingTable.find(srcAddr) == routingTable.end()) {
                LearningRoute route;
                route.destination = srcAddr;
                route.gateIndex = arrivalGate;
                route.timestamp = simTime().dbl();
                route.confidence = 1.0;
                route.hopCount = 1;
                route.learned = true;

                routingTable[srcAddr] = route;
                routingUpdates++;

                EV_INFO << "ProxyRouter " << addr << " LEARNED route to " << srcAddr
                        << " via gate " << arrivalGate << " (total routes: "
                        << routingTable.size() << ")\n";
                logToFile("ROUTE_LEARNED", to_string(srcAddr), arrivalGate);
            } else {
                LearningRoute &route = routingTable[srcAddr];
                route.timestamp = simTime().dbl();
                route.confidence = min(1.0, route.confidence + 0.1);
            }
        }
    }

    void updateRoutingTable() {
        double now = simTime().dbl();
        double expiryTime = par("routeExpiryTime").doubleValue();

        vector<long> expiredRoutes;
        for (auto &pair : routingTable) {
            if (now - pair.second.timestamp > expiryTime) {
                expiredRoutes.push_back(pair.first);
            }
        }

        for (long dest : expiredRoutes) {
            EV_INFO << "ProxyRouter " << addr << " expired route to " << dest << "\n";
            routingTable.erase(dest);
        }
    }

    void forwardToClient(cMessage *msg, long clientAddr) {
        if (routingTable.find(clientAddr) != routingTable.end()) {
            int gateIndex = routingTable[clientAddr].gateIndex;
            send(msg, "ethg$o", gateIndex);
            EV_INFO << "ProxyRouter " << addr << " forwarded to client " << clientAddr
                    << " via learned route (gate " << gateIndex << ")\n";
        } else if (clientToGate.find(clientAddr) != clientToGate.end()) {
            int gateIndex = clientToGate[clientAddr];
            send(msg, "ethg$o", gateIndex);
            EV_INFO << "ProxyRouter " << addr << " forwarded to client " << clientAddr
                    << " via cached gate (gate " << gateIndex << ")\n";
        } else {
            if (initialFlooding) {
                EV_INFO << "ProxyRouter " << addr << " flooding to find client " << clientAddr << "\n";
                floodMessage(msg, -1);
            } else {
                EV_WARN << "ProxyRouter " << addr << " no route to client " << clientAddr << "\n";
                delete msg;
            }
        }
    }

    void floodMessage(cMessage *msg, int excludeGate) {
        int numGates = gateSize("ethg");
        simtime_t delay = processingDelay;

        for (int i = FIRST_CLIENT_GATE; i < numGates; i++) {
            if (i != excludeGate) {
                cMessage *copy = msg->dup();
                copy->addPar("forwardGate").setLongValue(i);
                scheduleAt(simTime() + delay + SimTime(i * 100, SIMTIME_US), copy);
            }
        }
        delete msg;
    }

    void forwardToOrigin(cMessage *msg) {
        // Forward to HTTP origin server on gate 0
        send(msg, "ethg$o", HTTP_ORIGIN_GATE);
        EV_INFO << "ProxyRouter " << addr << " forwarded HTTP request to origin server\n";
    }

    // ========== SECURITY ==========

    bool validateResponse(cMessage *msg, const string& contentHash) {
        if (contentHash.empty() || contentHash.find("malicious") != string::npos) {
            return false;
        }

        if (msg->hasPar("serverIP")) {
            string serverIP = msg->par("serverIP").stringValue();
            if (blacklistedServers[serverIP]) {
                return false;
            }
        }

        return true;
    }

    void decaySuspicion() {
        for (auto &pair : suspicionScore) {
            pair.second *= (1.0 - suspicionDecayRate);
            if (pair.second < 0.01) {
                pair.second = 0;
            }
        }
    }

    void cleanupDHCPTracking() {
        // Clean up old DHCP transaction tracking
        dhcpDiscoverGates.clear();
        dhcpRequestSource.clear();
    }

    // ========== NETWORK MONITORING ==========

    void updateNetworkMetrics(int gateIndex) {
        gateLoad[gateIndex]++;

        int totalLoad = 0;
        for (auto &pair : gateLoad) {
            totalLoad += pair.second;
        }
        int numGates = gateSize("ethg");
        currentCongestion = (numGates > 0) ? (double)totalLoad / (numGates * 100.0) : 0;
        currentCongestion = min(1.0, currentCongestion);
    }

    void sendCachedResponse(cMessage *request, AdaptiveCacheEntry &entry, int clientGate) {
        long clientAddr = SRC(request);
        string url = request->par("url").stringValue();

        auto *response = mk("HTTP_RESPONSE_CACHED", HTTP_RESPONSE, addr, clientAddr);
        response->addPar("statusCode").setLongValue(200);
        response->addPar("contentType").setStringValue("text/html");
        response->addPar("contentLength").setLongValue(entry.size);
        response->addPar("etag").setStringValue("cached");
        response->addPar("contentHash").setStringValue(entry.contentHash.c_str());
        response->addPar("fromCache").setBoolValue(true);
        response->addPar("url").setStringValue(url.c_str());
        response->addPar("cacheKey").setStringValue(entry.key.c_str());
        response->addPar("cacheAge").setDoubleValue(simTime().dbl() - entry.timestamp);
        response->addPar("ttl").setDoubleValue(entry.ttl);
        response->addPar("requestTime").setDoubleValue(simTime().dbl());

        send(response, "ethg$o", clientGate);
    }

    void cleanupCache() {
        double now = simTime().dbl();
        vector<string> expiredKeys;

        for (auto &pair : cache) {
            double age = now - pair.second.timestamp;
            if (age > pair.second.ttl) {
                expiredKeys.push_back(pair.first);
            }
        }

        for (const string &key : expiredKeys) {
            EV_INFO << "ProxyRouter " << addr << " cleaned up expired cache entry: "
                    << cache[key].url << "\n";
            cache.erase(key);
            cacheIndex.erase(key);
        }
    }

    void logToFile(const string& event, const string& details, long addr) {
        if (logFile.is_open()) {
            logFile << simTime() << "," << event << "," << details << "," << addr << "\n";
            logFile.flush();
        }
    }

    void finish() override {
        if (routingUpdateTimer != nullptr) {
            cancelAndDelete(routingUpdateTimer);
            routingUpdateTimer = nullptr;
        }
        if (cleanupTimer != nullptr) {
            cancelAndDelete(cleanupTimer);
            cleanupTimer = nullptr;
        }

        double hitRate = (totalRequests > 0) ? (totalHits / totalRequests * 100) : 0;
        double blockRate = (totalRequests > 0) ? (totalBlockedResponses / totalRequests * 100) : 0;

        EV_INFO << "\n========== ProxyRouter " << addr << " Final Statistics ==========\n";
        EV_INFO << "CACHING PERFORMANCE:\n";
        EV_INFO << "  Total HTTP requests: " << totalRequests << "\n";
        EV_INFO << "  Cache hits: " << totalHits << "\n";
        EV_INFO << "  Cache hit rate: " << hitRate << "%\n";
        EV_INFO << "  Final cache size: " << cache.size() << "/" << cacheSize << "\n";

        EV_INFO << "\nROUTING PERFORMANCE:\n";
        EV_INFO << "  Learned routes: " << routingTable.size() << "\n";
        EV_INFO << "  Routing updates: " << routingUpdates << "\n";
        EV_INFO << "  Route convergence time: " << (routingUpdates > 0 ? simTime().dbl() / routingUpdates : 0) << "s\n";

        EV_INFO << "\nSECURITY METRICS:\n";
        EV_INFO << "  Rogue DHCP detections: " << totalRogueDetections << "\n";
        EV_INFO << "  Cache poison attempts: " << totalCachePoisonAttempts << "\n";
        EV_INFO << "  Blocked responses: " << totalBlockedResponses << " (" << blockRate << "%)\n";
        EV_INFO << "  Blacklisted servers: " << blacklistedServers.size() << "\n";
        EV_INFO << "======================================================\n";

        recordScalar("totalRequests", totalRequests);
        recordScalar("cacheHits", totalHits);
        recordScalar("cacheHitRate", hitRate);
        recordScalar("learnedRoutes", routingTable.size());
        recordScalar("routingUpdates", routingUpdates);
        recordScalar("rogueDetections", totalRogueDetections);
        recordScalar("poisonAttempts", totalCachePoisonAttempts);
        recordScalar("blockedResponses", totalBlockedResponses);
        recordScalar("attackDetectionAccuracy",
            (totalRogueDetections + totalCachePoisonAttempts > 0) ?
            ((double)totalRogueDetections / (totalRogueDetections + totalCachePoisonAttempts) * 100) : 100);

        if (logFile.is_open()) {
            logFile.close();
        }
    }
};

Define_Module(ProxyRouter);

} // namespace simple_dns_http
