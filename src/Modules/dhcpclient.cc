#include <omnetpp.h>
#include "helpers.h"
#include <map>
#include <sstream>
#include <random>
#include <iomanip>
#include <vector>

using namespace omnetpp;
using namespace std;

namespace simple_dns_http {

class DHCPClient : public cSimpleModule {
  private:
    int addr = 0;
    string clientMac;
    string assignedIP;
    string serverIP;
    double leaseTime = 0.0;
    cMessage *requestTimer = nullptr;
    cMessage *renewTimer = nullptr;
    cMessage *httpTimer = nullptr;
    bool hasValidLease = false;
    double requestInterval;
    double httpRequestInterval;
    bool autoRenew;
    bool sendHttpRequests;
    random_device rd;
    mt19937 gen;
    int serverGateIndex = 0;
    int totalHttpRequests = 0;
    int totalHttpResponses = 0;
    bool dhcpRequestPending = false;
    string currentTransactionId;
    
    vector<string> sampleUrls = {
        "/", "/about", "/contact", "/api/data", "/products", "/services"
    };

  protected:
    void initialize() override {
        int clientIndex = getIndex();
        addr = 100 + clientIndex;

        requestInterval = par("requestInterval").doubleValue();
        autoRenew = par("autoRenew").boolValue();

        httpRequestInterval = hasPar("httpRequestInterval") ?
            par("httpRequestInterval").doubleValue() : 10.0;
        sendHttpRequests = hasPar("sendHttpRequests") ?
            par("sendHttpRequests").boolValue() : true;

        gen = mt19937(rd());
        
        // Generate unique random MAC address per client
        uniform_int_distribution<> dis(0, 255);
        stringstream mac;
        mac << hex << setfill('0');
        for (int i = 0; i < 6; i++) {
            if (i > 0) mac << ":";
            mac << setw(2) << dis(gen);
        }
        clientMac = mac.str();
        
        // Start DHCP discovery with slight offset per client to avoid simultaneous sends
        requestTimer = new cMessage("dhcp_request");
        double dhcpStartTime = uniform(0.1, 1.0) + (clientIndex * 0.1);
        scheduleAt(simTime() + dhcpStartTime, requestTimer);
        
        // Schedule HTTP requests if enabled (but they won't send until DHCP completes)
        if (sendHttpRequests) {
            httpTimer = new cMessage("http_request");
            scheduleAt(simTime() + uniform(5.0, 10.0), httpTimer);
        }

        EV_INFO << "DHCPClient " << addr << " (ID " << getId() << ", Index " << clientIndex
                << ") starting with MAC " << clientMac << "\n";
    }

    void handleMessage(cMessage *msg) override {
        if (msg->isSelfMessage()) {
            if (msg == requestTimer) {
                if (!hasValidLease && !dhcpRequestPending) {
                    sendDHCPDiscover();
                }
                scheduleAt(simTime() + requestInterval, requestTimer);
                return;
            } else if (msg == renewTimer) {
                if (hasValidLease && autoRenew) {
                    sendDHCPRequest();
                    scheduleAt(simTime() + leaseTime * 0.5, renewTimer);
                }
                return;
            } else if (msg == httpTimer) {
                if (hasValidLease && sendHttpRequests) {
                    sendHTTPRequest();
                }
                scheduleAt(simTime() + httpRequestInterval, httpTimer);
                return;
            } else {
                delete msg;
            }
            return;
        }

        serverGateIndex = msg->getArrivalGate()->getIndex();

        switch (msg->getKind()) {
            case DHCP_OFFER:
                handleDHCPOffer(msg);
                break;
            case DHCP_ACK:
                handleDHCPAck(msg);
                break;
            case HTTP_RESPONSE:
                handleHTTPResponse(msg);
                break;
            case DHCP_DISCOVER:
            case DHCP_REQUEST:
                EV_DEBUG << "DHCPClient " << addr << " ignoring DHCP message from another client\n";
                break;
            default:
                EV_WARN << "DHCPClient " << addr << " unexpected message kind="
                        << msg->getKind() << "\n";
        }
        delete msg;
    }

    void sendDHCPDiscover() {
        auto *discover = mk("DHCP_DISCOVER", DHCP_DISCOVER, addr, -1);
        discover->addPar("clientMac").setStringValue(clientMac.c_str());
        discover->addPar("transactionId").setStringValue(generateTransactionId().c_str());

        send(discover, "ethg$o", 0);
        dhcpRequestPending = true;

        EV_INFO << "DHCPClient " << addr << " sent DHCP DISCOVER\n";
    }

    void sendDHCPRequest() {
        if (assignedIP.empty()) return;

        auto *request = mk("DHCP_REQUEST", DHCP_REQUEST, addr, -1);
        request->addPar("clientMac").setStringValue(clientMac.c_str());
        request->addPar("requestedIP").setStringValue(assignedIP.c_str());
        request->addPar("serverIP").setStringValue(serverIP.c_str());
        request->addPar("transactionId").setStringValue(generateTransactionId().c_str());

        send(request, "ethg$o", serverGateIndex);

        EV_INFO << "DHCPClient " << addr << " sent DHCP REQUEST for " << assignedIP << "\n";
    }

    void sendHTTPRequest() {
        if (!hasValidLease) {
            EV_DEBUG << "DHCPClient " << addr << " skipping HTTP request (no valid DHCP lease)\n";
            return;
        }

        uniform_int_distribution<> dis(0, sampleUrls.size() - 1);
        string url = sampleUrls[dis(gen)];

        totalHttpRequests++;

        auto *request = mk("HTTP_REQUEST", HTTP_REQUEST, addr, -1);
        request->addPar("method").setStringValue("GET");
        request->addPar("url").setStringValue(url.c_str());
        request->addPar("host").setStringValue("example.com");
        request->addPar("cacheKey").setStringValue(generateCacheKey(url).c_str());
        request->addPar("bypassCache").setBoolValue(false);
        request->addPar("clientIP").setStringValue(assignedIP.c_str());

        send(request, "ethg$o", 0);

        EV_INFO << "DHCPClient " << addr << " sent HTTP request for " << url
                << " (total: " << totalHttpRequests << ")\n";
    }

    void handleDHCPOffer(cMessage *msg) {
        // Verify this offer is for our MAC address
        string offerMac = msg->par("clientMac").stringValue();
        if (offerMac != clientMac) {
            EV_DEBUG << "DHCPClient " << addr << " ignoring DHCP OFFER for different MAC "
                     << offerMac << "\n";
            return;
        }

        string offeredIP = msg->par("offeredIP").stringValue();
        string srvIP = msg->par("serverIP").stringValue();
        double lease = msg->par("leaseTime").doubleValue();
        bool isRogue = msg->par("isRogue").boolValue();

        EV_INFO << "DHCPClient " << addr << " received DHCP OFFER: " << offeredIP
                << " from " << srvIP << " (lease: " << lease << "s)";
        if (isRogue) EV_INFO << " [ROGUE SERVER]";
        EV_INFO << "\n";

        // Only accept the first offer (first come, first served)
        if (assignedIP.empty()) {
            this->assignedIP = offeredIP;
            this->serverIP = srvIP;
            this->leaseTime = lease;
            sendDHCPRequest();
        }
    }

    void handleDHCPAck(cMessage *msg) {
        // Verify this ACK is for our MAC address
        string ackMac = msg->par("clientMac").stringValue();
        if (ackMac != clientMac) {
            EV_DEBUG << "DHCPClient " << addr << " ignoring DHCP ACK for different MAC "
                     << ackMac << "\n";
            return;
        }

        string assignedIP = msg->par("assignedIP").stringValue();
        string srvIP = msg->par("serverIP").stringValue();
        double lease = msg->par("leaseTime").doubleValue();
        bool isRogue = msg->par("isRogue").boolValue();

        this->assignedIP = assignedIP;
        this->serverIP = srvIP;
        this->leaseTime = lease;
        hasValidLease = true;
        dhcpRequestPending = false;

        EV_INFO << "DHCPClient " << addr << " received DHCP ACK: " << assignedIP
                << " from " << srvIP << " (lease: " << lease << "s)";
        if (isRogue) EV_INFO << " [ROGUE SERVER - SECURITY ALERT!]";
        EV_INFO << "\n";

        if (autoRenew) {
            if (renewTimer != nullptr) {
                cancelEvent(renewTimer);
            } else {
                renewTimer = new cMessage("dhcp_renew");
            }
            scheduleAt(simTime() + lease * 0.5, renewTimer);
        }
    }

    void handleHTTPResponse(cMessage *msg) {
        totalHttpResponses++;

        string url = msg->par("url").stringValue();
        int statusCode = msg->par("statusCode").longValue();
        bool fromCache = msg->par("fromCache").boolValue();

        EV_INFO << "DHCPClient " << addr << " received HTTP response for " << url
                << " (status: " << statusCode << ", from cache: " << (fromCache ? "YES" : "NO")
                << ", total: " << totalHttpResponses << ")\n";
    }

    string generateTransactionId() {
        uniform_int_distribution<> dis(10000, 99999);
        return to_string(addr) + "-" + to_string(dis(gen));
    }

    double uniform(double min, double max) {
        uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }

    void finish() override {
        if (requestTimer != nullptr) {
            cancelAndDelete(requestTimer);
            requestTimer = nullptr;
        }
        if (renewTimer != nullptr) {
            cancelAndDelete(renewTimer);
            renewTimer = nullptr;
        }
        if (httpTimer != nullptr) {
            cancelAndDelete(httpTimer);
            httpTimer = nullptr;
        }

        EV_INFO << "DHCPClient " << addr << " finished";
        if (hasValidLease) {
            EV_INFO << " with IP " << assignedIP;
        }
        EV_INFO << " HTTP requests: " << totalHttpRequests
                << ", responses: " << totalHttpResponses << "\n";

        recordScalar("hasValidLease", hasValidLease ? 1 : 0);
        recordScalar("totalHttpRequests", totalHttpRequests);
        recordScalar("totalHttpResponses", totalHttpResponses);
    }
};

Define_Module(DHCPClient);

} // namespace simple_dns_http
