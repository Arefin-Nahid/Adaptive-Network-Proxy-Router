package simple_dns_http;

import simple_dns_http.ProxyRouter;
import simple_dns_http.HttpOrigin;
import simple_dns_http.DHCPServer;
import simple_dns_http.DHCPClient;

// Simplified Topology: ProxyRouter as central hub (no separate gateway)
network SimpleNet
{
    parameters:
        int numClients = default(20);
        double linkDelay @unit(s) = default(0.0005s);
        double linkDatarate @unit(bps) = default(1Gbps);

    submodules:
        // Central proxy router (acts as both proxy and gateway)
        proxyRouter: ProxyRouter {
            @display("p=300,300");
        }

        // HTTP origin server
        httpOrigin: HttpOrigin {
            @display("p=300,120");
        }

        // DHCP servers
        dhcpServerLegit: DHCPServer {
            parameters:
                address = 10;
                isRogue = false;
                @display("p=100,300");
        }

        dhcpServerRogue: DHCPServer {
            parameters:
                address = 11;
                isRogue = true;
                @display("p=100,199");
        }

        // DHCP clients
        clients[numClients]: DHCPClient {
            @display("p=500,120,row,60");
        }

    connections allowunconnected:
        // ProxyRouter <-> HttpOrigin (gate 0)
        proxyRouter.ethg++ <--> { delay = parent.linkDelay; datarate = parent.linkDatarate; } <--> httpOrigin.ethg++;

        // ProxyRouter <-> DHCP Servers (gates 1-2)
        proxyRouter.ethg++ <--> { delay = parent.linkDelay; datarate = parent.linkDatarate; } <--> dhcpServerLegit.ethg++;
        proxyRouter.ethg++ <--> { delay = parent.linkDelay; datarate = parent.linkDatarate; } <--> dhcpServerRogue.ethg++;

        // ProxyRouter <-> Clients (gates 3+)
        for i=0..numClients-1 {
            proxyRouter.ethg++ <--> { delay = parent.linkDelay; datarate = parent.linkDatarate; } <--> clients[i].ethg++;
        }
}