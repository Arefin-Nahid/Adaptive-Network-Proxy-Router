package simple_dns_http;

simple Router
{
    parameters:
        @class(simple_dns_http::Router);
        int address = default(1);
        double processingDelay @unit(s) = default(0.0001s);
        bool enableLearning = default(true);
        double routeConfidenceThreshold = default(0.8);

        @display("i=abstract/router");

    gates:
        inout ethg[];
}