#include <omnetpp.h>
#include "helpers.h"
#include <map>
#include <sstream>
#include <random>
#include <iomanip>

using namespace omnetpp;
using namespace std;

namespace simple_dns_http {

class DHCPServer : public cSimpleModule {
  private:
    int addr = 0;
    bool isRogue = false;
    string poolStart;
    string poolEnd;
    double leaseTime;
    map<string, string> macToIP;  // MAC -> IP mapping
    map<string, double> leaseExpiry;
    map<string, string> ipToMac;  // IP -> MAC reverse mapping (to prevent duplicate IPs)
    random_device rd;
    mt19937 gen;
    int gateIndex = 0;
    int nextIPSuffix = 100;
    
  protected:
    void initialize() override {
        addr = par("address");

        if (hasPar("isRogue")) {
            isRogue = par("isRogue").boolValue();
        } else if (hasPar("mode")) {
            string mode = par("mode").stringValue();
            isRogue = (mode == "rogue");
        }

        poolStart = par("poolStart").stringValue();
        poolEnd = par("poolEnd").stringValue();
        leaseTime = par("leaseTime").doubleValue();
        gen = mt19937(rd());
        
        nextIPSuffix = 100;

        EV_INFO << "DHCPServer " << addr << " initialized";
        if (isRogue) EV_INFO << " [ROGUE SERVER]";
        EV_INFO << " pool: " << poolStart << "-" << poolEnd << " lease: " << leaseTime << "s\n";
    }

    void handleMessage(cMessage *msg) override {
        gateIndex = msg->getArrivalGate()->getIndex();

        switch (msg->getKind()) {
            case DHCP_DISCOVER: {
                handleDHCPDiscover(msg);
                break;
            }
            case DHCP_REQUEST: {
                handleDHCPRequest(msg);
                break;
            }
            default:
                EV_WARN << "DHCPServer " << addr << " unexpected message kind=" << msg->getKind() << "\n";
        }
        delete msg;
    }
    
    void handleDHCPDiscover(cMessage *msg) {
        string clientMac = msg->par("clientMac").stringValue();
        string transactionId = msg->par("transactionId").stringValue();
        
        EV_INFO << "DHCPServer " << addr << " received DHCP DISCOVER from " << clientMac << "\n";
        
        // Check if this MAC already has a lease
        if (macToIP.find(clientMac) != macToIP.end()) {
            string existingIP = macToIP[clientMac];
            EV_INFO << "DHCPServer " << addr << " found existing lease for " << clientMac
                    << ": " << existingIP << "\n";
            sendDHCPOffer(clientMac, existingIP, transactionId);
        } else {
            // Allocate new unique IP for this MAC
            string offeredIP = allocateNewIP(clientMac);
            if (!offeredIP.empty()) {
                macToIP[clientMac] = offeredIP;
                ipToMac[offeredIP] = clientMac;
                leaseExpiry[clientMac] = simTime().dbl() + leaseTime;

                EV_INFO << "DHCPServer " << addr << " allocated NEW IP " << offeredIP
                        << " for MAC " << clientMac << "\n";

                sendDHCPOffer(clientMac, offeredIP, transactionId);
            } else {
                EV_WARN << "DHCPServer " << addr << " no IPs available in pool\n";
            }
        }
    }
    
    void handleDHCPRequest(cMessage *msg) {
        string clientMac = msg->par("clientMac").stringValue();
        string requestedIP = msg->par("requestedIP").stringValue();
        string transactionId = msg->par("transactionId").stringValue();
        
        EV_INFO << "DHCPServer " << addr << " received DHCP REQUEST from " << clientMac
                << " for " << requestedIP << "\n";
        
        // Check if this server can provide the requested IP to this client
        if (macToIP.find(clientMac) != macToIP.end() && macToIP[clientMac] == requestedIP) {
            // This server offered this IP to this MAC
            leaseExpiry[clientMac] = simTime().dbl() + leaseTime;
            sendDHCPAck(clientMac, requestedIP, transactionId);
        } else {
            EV_WARN << "DHCPServer " << addr << " cannot provide requested IP " << requestedIP << "\n";
        }
    }
    
    void sendDHCPOffer(string clientMac, string offeredIP, string transactionId) {
        auto *offer = mk("DHCP_OFFER", DHCP_OFFER, addr, -1);
        offer->addPar("serverMac").setStringValue(getServerMac().c_str());
        offer->addPar("clientMac").setStringValue(clientMac.c_str());
        offer->addPar("offeredIP").setStringValue(offeredIP.c_str());
        offer->addPar("serverIP").setStringValue(getServerIP().c_str());
        offer->addPar("leaseTime").setDoubleValue(leaseTime);
        offer->addPar("transactionId").setStringValue(transactionId.c_str());
        offer->addPar("isRogue").setBoolValue(isRogue);
        
        send(offer, "ethg$o", gateIndex);
        
        EV_INFO << "DHCPServer " << addr << " sent DHCP OFFER: " << offeredIP
                << " to " << clientMac;
        if (isRogue) EV_INFO << " [ROGUE OFFER]";
        EV_INFO << "\n";
    }
    
    void sendDHCPAck(string clientMac, string assignedIP, string transactionId) {
        auto *ack = mk("DHCP_ACK", DHCP_ACK, addr, -1);
        ack->addPar("serverMac").setStringValue(getServerMac().c_str());
        ack->addPar("clientMac").setStringValue(clientMac.c_str());
        ack->addPar("assignedIP").setStringValue(assignedIP.c_str());
        ack->addPar("serverIP").setStringValue(getServerIP().c_str());
        ack->addPar("leaseTime").setDoubleValue(leaseTime);
        ack->addPar("transactionId").setStringValue(transactionId.c_str());
        ack->addPar("isRogue").setBoolValue(isRogue);
        
        send(ack, "ethg$o", gateIndex);
        
        EV_INFO << "DHCPServer " << addr << " sent DHCP ACK: " << assignedIP
                << " to " << clientMac;
        if (isRogue) EV_INFO << " [ROGUE ACK - SECURITY THREAT!]";
        EV_INFO << "\n";
    }
    
    string allocateNewIP(const string& clientMac) {
        string baseIP = isRogue ? "10.0.0." : "192.168.1.";
        int maxAttempts = 100;

        for (int attempt = 0; attempt < maxAttempts; attempt++) {
            string candidateIP = baseIP + to_string(nextIPSuffix);
            nextIPSuffix++;

            if (nextIPSuffix > 199) {
                nextIPSuffix = 100;
            }

            // Check if this IP is not already allocated to another MAC
            if (ipToMac.find(candidateIP) == ipToMac.end()) {
                return candidateIP;
            }
        }

        return "";  // No IPs available
    }
    
    string getServerMac() {
        stringstream ss;
        ss << hex << setfill('0');
        ss << setw(2) << 0 << ":" << setw(2) << 11 << ":" << setw(2) << 22
           << ":" << setw(2) << 33 << ":" << setw(2) << 44 << ":" << setw(2) << addr;
        return ss.str();
    }
    
    string getServerIP() {
        if (isRogue) {
            return "10.0.0.1";
        } else {
            return "192.168.1.10";
        }
    }

    void finish() override {
        EV_INFO << "DHCPServer " << addr << " finished with " << macToIP.size() << " active leases\n";

        recordScalar("activeLeases", macToIP.size());
        recordScalar("isRogue", isRogue ? 1 : 0);
    }
};

Define_Module(DHCPServer);

} // namespace simple_dns_http
