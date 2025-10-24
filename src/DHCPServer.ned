package simple_dns_http;

simple DHCPServer
{
    parameters:
        @class(simple_dns_http::DHCPServer);
        int address = default(10);
        bool isRogue = default(false);
        string poolStart = default("192.168.1.100");
        string poolEnd = default("192.168.1.200");
        double leaseTime @unit(s) = default(86400s);  // 24 hours
        string serverIP = default("192.168.1.10");
        string routerIP = default("192.168.1.1");
        string dnsIP = default("8.8.8.8");
        string subnetMask = default("255.255.255.0");
        double offerDelayMs @unit(ms) = default(50ms);
        string logsDir = default("results");

        @display("i=abstract/server");

    gates:
        inout ethg[];
}