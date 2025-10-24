package simple_dns_http;

simple HttpOrigin
{
    parameters:
        @class(simple_dns_http::HttpOrigin);
        int address = default(2);
        double serviceTime @unit(s) = default(0.01s);
        int pageSizeBytes = default(4096);
        string contentHash = default("origin-content-hash");

        @display("i=device/server");

    gates:
        inout ethg[];
}