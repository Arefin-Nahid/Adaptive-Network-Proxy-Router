package simple_dns_http;

simple DHCPClient
{
    parameters:
        @class(simple_dns_http::DHCPClient);
        int address = default(100);
        double requestInterval @unit(s) = default(30s);
        bool autoRenew = default(true);
        double httpRequestInterval @unit(s) = default(10s);
        bool sendHttpRequests = default(true);
        double offerTimeoutMs @unit(ms) = default(1000ms);
        double requestTimeoutMs @unit(ms) = default(1000ms);
        string acceptPolicy = default("accept-first");

        @display("i=abstract/pc");

    gates:
        inout ethg[];
}