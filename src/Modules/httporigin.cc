#include <omnetpp.h>
#include "helpers.h"
#include <map>
#include <sstream>
#include <random>

using namespace omnetpp;
using namespace std;

namespace simple_dns_http {

class HttpOrigin : public cSimpleModule {
  private:
    int addr = 0;
    double serviceTime;
    int pageSizeBytes;
    string contentHash;
    map<string, string> contentCache;
    map<string, double> lastModified;
    random_device rd;
    mt19937 gen;
    
  protected:
    void initialize() override {
        addr = par("address");
        serviceTime = par("serviceTime").doubleValue();
        pageSizeBytes = par("pageSizeBytes").intValue();
        contentHash = par("contentHash").stringValue();
        gen = mt19937(rd());
        
        initializeContent();
        
        EV_INFO << "HttpOrigin " << addr << " initialized with " << pageSizeBytes
                << " bytes, service time " << serviceTime << "s\n";
    }

    void handleMessage(cMessage *msg) override {
        if (msg->isSelfMessage()) {
            handleResponseTimer(msg);
            return;
        }
        
        switch (msg->getKind()) {
            case HTTP_REQUEST: {
                handleHTTPRequest(msg);
                break;
            }
            default:
                EV_WARN << "HttpOrigin " << addr << " unexpected message kind=" << msg->getKind() << "\n";
                delete msg;
        }
    }
    
    void handleHTTPRequest(cMessage *msg) {
        string method = msg->par("method").stringValue();
        string url = msg->par("url").stringValue();
        string host = msg->par("host").stringValue();
        string cacheKey = msg->par("cacheKey").stringValue();
        
        EV_INFO << "HttpOrigin " << addr << " received " << method << " " << url
                << " from " << host << "\n";
        
        // Simulate processing time
        cMessage *responseTimer = new cMessage("http_response");
        responseTimer->addPar("url").setStringValue(url.c_str());
        responseTimer->addPar("cacheKey").setStringValue(cacheKey.c_str());
        responseTimer->addPar("clientAddr").setLongValue(SRC(msg));
        responseTimer->addPar("gateIndex").setLongValue(msg->getArrivalGate()->getIndex());
        
        scheduleAt(simTime() + serviceTime, responseTimer);
        delete msg;
    }
    
    void handleResponseTimer(cMessage *msg) {
        string url = msg->par("url").stringValue();
        string cacheKey = msg->par("cacheKey").stringValue();
        long clientAddr = msg->par("clientAddr").longValue();
        int gateIndex = msg->par("gateIndex").longValue();
        
        // Generate or retrieve content
        string content = generateContent(url);
        string etag = generateETag(content);
        double lastMod = getLastModified(url);
        
        // Create HTTP response
        auto *response = mk("HTTP_RESPONSE", HTTP_RESPONSE, addr, clientAddr);
        response->addPar("statusCode").setLongValue(200);
        response->addPar("contentType").setStringValue("text/html");
        response->addPar("contentLength").setLongValue(content.length());
        response->addPar("etag").setStringValue(etag.c_str());
        response->addPar("lastModified").setDoubleValue(lastMod);
        response->addPar("expires").setDoubleValue(simTime().dbl() + 3600.0);
        response->addPar("cacheControl").setStringValue("public, max-age=3600");
        response->addPar("contentHash").setStringValue(contentHash.c_str());
        response->addPar("fromCache").setBoolValue(false);
        response->addPar("responseTime").setDoubleValue(serviceTime);
        response->addPar("url").setStringValue(url.c_str());
        response->addPar("cacheKey").setStringValue(cacheKey.c_str());
        
        send(response, "ethg$o", gateIndex);
        
        EV_INFO << "HttpOrigin " << addr << " sent HTTP response for " << url
                << " (" << content.length() << " bytes, ETag: " << etag << ")\n";
        
        delete msg;
    }
    
    void initializeContent() {
        contentCache["/"] = "index.html";
        contentCache["/about"] = "about.html";
        contentCache["/contact"] = "contact.html";
        contentCache["/api/data"] = "api_data.json";
        
        double now = simTime().dbl();
        lastModified["/"] = now - 3600;
        lastModified["/about"] = now - 1800;
        lastModified["/contact"] = now - 900;
        lastModified["/api/data"] = now - 300;
    }
    
    string generateContent(const string& url) {
        if (contentCache.find(url) != contentCache.end()) {
            uniform_int_distribution<> dis(0, 100);
            int variation = dis(gen);
            return contentCache[url] + "_v" + to_string(variation);
        }
        return "generated_content_for_" + url;
    }
    
    string generateETag(const string& content) {
        hash<string> hasher;
        size_t hashValue = hasher(content);
        return "\"" + to_string(hashValue) + "\"";
    }
    
    double getLastModified(const string& url) {
        if (lastModified.find(url) != lastModified.end()) {
            return lastModified[url];
        }
        return simTime().dbl();
    }

    void finish() override {
        EV_INFO << "HttpOrigin " << addr << " finished, served " << contentCache.size() << " unique URLs\n";
    }
};

Define_Module(HttpOrigin);

} // namespace simple_dns_http
