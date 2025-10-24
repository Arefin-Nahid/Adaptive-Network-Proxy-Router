package simple_dns_http;

simple SimpleSwitch
{
    parameters:

        @class(simple_dns_http::SimpleSwitch);
        int numPorts = default(8);
        double agingTime @unit(s) = default(300s);
        @display("i=abstract/switch");

    gates:
        inout ethg[numPorts];
}
