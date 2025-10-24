#include <omnetpp.h>
#include "helpers.h"
#include <map>
#include <vector>

using namespace omnetpp;
using namespace std;

namespace simple_dns_http {

struct RouteEntry {
    long destination;
    int gateIndex;
    double timestamp;
    double confidence;
    int useCount;
};

class Router : public cSimpleModule {
  private:
    int addr;
    double processingDelay;
    map<long, RouteEntry> routingTable;
    map<long, vector<int>> discoveredPaths;
    int totalPackets = 0;
    int floodedPackets = 0;
    int routedPackets = 0;
    bool learningMode = true;

  protected:
    void initialize() override {
        addr = par("address");
        processingDelay = par("processingDelay").doubleValue();

        EV_INFO << "Router " << addr << " initialized with processing delay "
                << processingDelay << "s (Learning Mode: ON)\n";
    }

    void handleMessage(cMessage *msg) override {
        if (msg->isSelfMessage()) {
            // Handle timer message
            cMessage *originalMsg = (cMessage *)msg->par("originalMsg").pointerValue();
            int arrivalGate = msg->par("arrivalGate").longValue();
            long dst = msg->par("dst").longValue();

            delete msg; // Delete timer
            forwardMessage(originalMsg, arrivalGate, dst);
            return;
        }

        int arrivalGate = msg->getArrivalGate()->getIndex();
        long src = SRC(msg);
        long dst = DST(msg);

        totalPackets++;

        // Learn the route back to source
        learnRoute(src, arrivalGate);

        EV_INFO << "Router " << addr << " received " << msg->getName()
                << " (kind=" << msg->getKind() << ") from gate " << arrivalGate
                << " (src=" << src << ", dst=" << dst << ")\n";

        // Simulate processing delay
        if (processingDelay > 0) {
            cMessage *timer = new cMessage("routing_timer");
            timer->addPar("originalMsg").setPointerValue(msg);
            timer->addPar("arrivalGate").setLongValue(arrivalGate);
            timer->addPar("dst").setLongValue(dst);
            scheduleAt(simTime() + processingDelay, timer);
            return;
        }

        forwardMessage(msg, arrivalGate, dst);
    }

    void learnRoute(long destination, int gateIndex) {
        if (routingTable.find(destination) == routingTable.end()) {
            // New route discovered
            RouteEntry entry;
            entry.destination = destination;
            entry.gateIndex = gateIndex;
            entry.timestamp = simTime().dbl();
            entry.confidence = 0.8;
            entry.useCount = 0;

            routingTable[destination] = entry;

            EV_INFO << "Router " << addr << " LEARNED new route to " << destination
                    << " via gate " << gateIndex << " (total routes: "
                    << routingTable.size() << ")\n";
        } else {
            // Update existing route
            RouteEntry &entry = routingTable[destination];
            if (entry.gateIndex == gateIndex) {
                // Strengthen confidence
                entry.confidence = min(1.0, entry.confidence + 0.1);
                entry.timestamp = simTime().dbl();
            } else {
                // Different path discovered - track it
                if (discoveredPaths[destination].empty() ||
                    find(discoveredPaths[destination].begin(),
                         discoveredPaths[destination].end(),
                         gateIndex) == discoveredPaths[destination].end()) {
                    discoveredPaths[destination].push_back(gateIndex);
                    EV_INFO << "Router " << addr << " discovered alternate path to "
                            << destination << " via gate " << gateIndex << "\n";
                }
            }
        }
    }

    void forwardMessage(cMessage *msg, int arrivalGate, long dst) {
        int numGates = gateSize("ethg");

        if (numGates <= 1) {
            // Only one gate - just send back (or drop if same gate)
            if (arrivalGate == 0) {
                EV_INFO << "Router " << addr << " only has one gate, forwarding back\n";
                send(msg, "ethg$o", 0);
            } else {
                EV_WARN << "Router " << addr << " has only " << numGates
                        << " gate(s), dropping message\n";
                delete msg;
            }
            return;
        }

        // Check if we have a learned route
        if (routingTable.find(dst) != routingTable.end()) {
            RouteEntry &entry = routingTable[dst];
            entry.useCount++;
            routedPackets++;

            // Use learned route
            cMessage *copy = msg->dup();
            send(copy, "ethg$o", entry.gateIndex);

            EV_INFO << "Router " << addr << " forwarded via LEARNED ROUTE to gate "
                    << entry.gateIndex << " (confidence=" << entry.confidence
                    << ", uses=" << entry.useCount << ")\n";

            delete msg;
            return;
        }

        // No learned route - flood the packet
        floodedPackets++;
        EV_INFO << "Router " << addr << " FLOODING packet (no learned route to "
                << dst << ")\n";

        for (int i = 0; i < numGates; i++) {
            if (i != arrivalGate) {
                cMessage *copy = msg->dup();
                send(copy, "ethg$o", i);
            }
        }
        delete msg;
    }

    void finish() override {
        double routingEfficiency = (totalPackets > 0) ?
            ((double)routedPackets / totalPackets * 100) : 0;

        EV_INFO << "\n========== Router " << addr << " Statistics ==========\n";
        EV_INFO << "Total packets: " << totalPackets << "\n";
        EV_INFO << "Routed packets: " << routedPackets << "\n";
        EV_INFO << "Flooded packets: " << floodedPackets << "\n";
        EV_INFO << "Routing efficiency: " << routingEfficiency << "%\n";
        EV_INFO << "Learned routes: " << routingTable.size() << "\n";
        EV_INFO << "Alternate paths discovered: " << discoveredPaths.size() << "\n";

        // Print routing table
        EV_INFO << "\nRouting Table:\n";
        for (const auto &pair : routingTable) {
            EV_INFO << "  Destination " << pair.first << " -> Gate "
                    << pair.second.gateIndex << " (confidence="
                    << pair.second.confidence << ", uses="
                    << pair.second.useCount << ")\n";
        }
        EV_INFO << "===================================================\n";

        recordScalar("totalPackets", totalPackets);
        recordScalar("routedPackets", routedPackets);
        recordScalar("floodedPackets", floodedPackets);
        recordScalar("routingEfficiency", routingEfficiency);
        recordScalar("learnedRoutes", routingTable.size());
    }
};

Define_Module(Router);

} // namespace simple_dns_http
