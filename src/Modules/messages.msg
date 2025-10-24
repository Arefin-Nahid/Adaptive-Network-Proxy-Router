// Unit property declaration
@property(unit,string);

// DHCP Message Types
message DHCPDiscover
{
    string clientMac;
    string transactionId;
    double timestamp @unit(s);
}

message DHCPOffer
{
    string serverMac;
    string clientMac;
    string offeredIP;
    string serverIP;
    double leaseTime @unit(s);
    string transactionId;
    bool isRogue = false;
}

message DHCPRequest
{
    string clientMac;
    string requestedIP;
    string serverIP;
    string transactionId;
    double timestamp @unit(s);
}

message DHCPAck
{
    string serverMac;
    string clientMac;
    string assignedIP;
    string serverIP;
    double leaseTime @unit(s);
    string transactionId;
    bool isRogue = false;
}

// HTTP Message Types
message HTTPRequest
{
    string method; // GET, POST, etc.
    string url;
    string host;
    string userAgent;
    double timestamp @unit(s);
    string cacheKey;
    bool bypassCache = false;
}

message HTTPResponse
{
    int statusCode;
    string contentType;
    int contentLength;
    string etag;
    double lastModified @unit(s);
    double expires @unit(s);
    string cacheControl;
    string contentHash;
    bool fromCache = false;
    double responseTime @unit(s);
}

// Cache Management Messages
message CacheQuery
{
    string cacheKey;
    string url;
    double timestamp @unit(s);
    bool forceRefresh = false;
}

message CacheResponse
{
    string cacheKey;
    bool hit;
    string contentHash;
    double ttl @unit(s);
    double size @unit(bytes);
    double timestamp @unit(s);
}

message CacheStore
{
    string cacheKey;
    string contentHash;
    double ttl @unit(s);
    double size @unit(bytes);
    string url;
    double timestamp @unit(s);
    int priority = 0;
}

message CacheEvict
{
    string cacheKey;
    string reason;
    double timestamp @unit(s);
}

// Adaptive TTL Messages
message TTLUpdate
{
    string cacheKey;
    double newTTL @unit(s);
    double hitRate;
    double accessFrequency;
    double timestamp @unit(s);
}

message TTLQuery
{
    string cacheKey;
    double currentTTL @unit(s);
    double hitCount;
    double missCount;
    double timestamp @unit(s);
}

// Learning Router Messages
message RouteUpdate
{
    string destination;
    string nextHop;
    int hopCount;
    double cost;
    double timestamp @unit(s);
    bool isLearned = true;
}

message RouteQuery
{
    string destination;
    double timestamp @unit(s);
}

message RouteResponse
{
    string destination;
    string nextHop;
    int hopCount;
    double cost;
    bool found;
    double timestamp @unit(s);
}

// Security/Attack Messages
message PoisonAttempt
{
    string targetCacheKey;
    string maliciousContent;
    string attackerId;
    double timestamp @unit(s);
    double successRate;
}

message SecurityAlert
{
    string alertType; // "DHCP_SPOOF", "CACHE_POISON", "ROUTE_HIJACK"
    string source;
    string target;
    double severity; // 0.0 to 1.0
    double timestamp @unit(s);
    string description;
}

message ThreatDetection
{
    string threatType;
    string sourceIP;
    string targetIP;
    double confidence;
    double timestamp @unit(s);
    string mitigation;
}

// Network Statistics Messages
message NetworkStats
{
    double cacheHitRate;
    double averageLatency @unit(s);
    double throughput @unit(bps);
    int activeConnections;
    double dhcpSuccessRate;
    double securityThreats;
    double timestamp @unit(s);
}

message PerformanceMetrics
{
    string componentId;
    double cpuUsage;
    double memoryUsage;
    double diskUsage;
    double networkUsage;
    double timestamp @unit(s);
}
