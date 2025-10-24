package simple_dns_http;

simple ProxyRouter
{
    parameters:
        @class(simple_dns_http::ProxyRouter);
        int address = default(2);
        double processingDelay @unit(s) = default(0.001s);

        // Caching parameters
        bool enableCaching = default(true);
        int cacheSize = default(1000);
        double defaultTTL @unit(s) = default(3600s);
        string cachePolicy = default("LRU");

        // Adaptive TTL parameters
        bool enableAdaptiveTTL = default(true);
        double minTTL @unit(s) = default(60s);
        double maxTTL @unit(s) = default(7200s);
        double latencyThreshold @unit(s) = default(0.1s);
        double congestionThreshold = default(0.7);

        // Security parameters
        bool enableSecurityFiltering = default(true);
        bool validateResponses = default(true);
        double suspicionThreshold = default(0.8);
        double suspicionDecayRate = default(0.1);
        int maxRogueDetections = default(10);

        // Learning router parameters
        bool enableLearning = default(true);
        bool initialFlooding = default(true);
        double routingUpdateInterval @unit(s) = default(10s);
        double routeExpiryTime @unit(s) = default(300s);

        string logsDir = default("results");
        bool verboseMode = default(false);

        @display("i=abstract/router");

    gates:
        inout ethg[];
}