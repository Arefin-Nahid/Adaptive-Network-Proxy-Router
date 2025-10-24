#ifndef MODULES_HELPERS_H_
#define MODULES_HELPERS_H_

#include <omnetpp.h>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace omnetpp;
using namespace std;

// DHCP Message Types
enum {
    DHCP_DISCOVER=10, DHCP_OFFER=11, DHCP_REQUEST=12, DHCP_ACK=13
};

// HTTP Message Types
enum {
    HTTP_REQUEST=20, HTTP_RESPONSE=21
};

// Cache Management
enum {
    CACHE_QUERY=30, CACHE_RESPONSE=31, CACHE_STORE=32, CACHE_EVICT=33
};

// Adaptive TTL
enum {
    TTL_UPDATE=40, TTL_QUERY=41
};

// Learning Router
enum {
    ROUTE_UPDATE=50, ROUTE_QUERY=51, ROUTE_RESPONSE=52
};

// Security/Attack
enum {
    POISON_ATTEMPT=60, SECURITY_ALERT=61, THREAT_DETECTION=62
};

// Network Statistics
enum {
    NETWORK_STATS=70, PERFORMANCE_METRICS=71
};

// Helper functions for message creation
static cPacket* mk(const char* name, int kind, long src, long dst) {
    auto *m = new cPacket(name, kind);
    m->addPar("src").setLongValue(src);
    m->addPar("dst").setLongValue(dst);
    m->addPar("timestamp").setDoubleValue(simTime().dbl());
    m->setByteLength(64); // Default packet size
    return m;
}

static inline long SRC(cMessage* m){ return m->par("src").longValue(); }
static inline long DST(cMessage* m){ return m->par("dst").longValue(); }
static inline double TIMESTAMP(cMessage* m){ return m->par("timestamp").doubleValue(); }

// Cache key generation
static string generateCacheKey(const string& url, const string& params = "") {
    return "cache_" + to_string(hash<string>{}(url + params));
}

// TTL calculation helpers
static double calculateAdaptiveTTL(double baseTTL, double hitRate, double accessFreq) {
    double multiplier = 1.0 + (hitRate * 0.5) + (accessFreq * 0.3);
    return baseTTL * multiplier;
}

// Security scoring
static double calculateSecurityScore(const vector<string>& threats) {
    double score = 1.0;
    for (const auto& threat : threats) {
        if (threat == "DHCP_SPOOF") score *= 0.8;
        else if (threat == "CACHE_POISON") score *= 0.7;
        else if (threat == "ROUTE_HIJACK") score *= 0.6;
    }
    return max(0.0, score);
}

// Network performance metrics
struct NetworkMetrics {
    double cacheHitRate = 0.0;
    double averageLatency = 0.0;
    double throughput = 0.0;
    int activeConnections = 0;
    double dhcpSuccessRate = 0.0;
    double securityThreats = 0.0;
    double timestamp = 0.0;
};

// Cache entry structure
struct CacheEntry {
    string key;
    string contentHash;
    double ttl;
    double size;
    string url;
    double timestamp;
    int accessCount = 0;
    double lastAccess = 0.0;
    int priority = 0;
};

// Route entry structure
struct RouteEntry {
    string destination;
    string nextHop;
    int hopCount;
    double cost;
    double timestamp;
    bool isLearned;
    double confidence = 1.0;
};

#endif /* MODULES_HELPERS_H_ */
