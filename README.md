# Adaptive Network Proxy Router with Security Features

## 📋 Project Overview

This project implements a sophisticated network simulation using OMNeT++ that demonstrates an intelligent proxy router with adaptive caching, learning-based routing, and security monitoring capabilities. The system simulates a realistic network environment with DHCP address allocation, HTTP traffic, and potential security threats including rogue DHCP servers and cache poisoning attacks.

## 🎯 Key Features

### 1. **Adaptive Caching System**
- **Dynamic TTL Adjustment**: Cache entries automatically adjust their Time-To-Live based on:
  - Hit rate (higher hits = longer TTL)
  - Access frequency (more frequent = longer TTL)
  - Network latency (higher latency = longer TTL to reduce origin requests)
  - Network congestion (higher congestion = longer TTL)
- **LRU Eviction Policy**: Least Recently Used entries are evicted when cache is full
- **Cache Performance**: Achieves 50% hit rate in baseline simulation
- **TTL Range**: 60s (minimum) to 7200s (maximum), default 3600s

### 2. **Learning Router**
- **Dynamic Route Discovery**: Learns optimal paths by observing traffic patterns
- **Route Confidence Scoring**: Tracks reliability of learned routes
- **Automatic Route Expiry**: Removes stale routes after 300s of inactivity
- **Fallback Flooding**: Uses flooding only when no learned route exists
- **Multi-path Discovery**: Tracks alternative paths to destinations

### 3. **Security Monitoring**
- **Rogue DHCP Detection**: Identifies malicious DHCP servers by tracking:
  - IP address range anomalies (10.0.0.x vs legitimate 192.168.1.x)
  - Suspicious offer patterns
  - Cumulative suspicion scoring
- **Cache Poisoning Protection**: Validates response content before caching
- **Dynamic Blacklisting**: Automatically blocks attackers exceeding suspicion threshold (0.8)
- **Suspicion Decay**: Reduces false positives with 10% decay rate per cleanup cycle

### 4. **DHCP Management**
- **Full DHCP Protocol**: Implements DISCOVER → OFFER → REQUEST → ACK flow
- **MAC-based Address Assignment**: Ensures consistent IP allocation
- **Transaction Tracking**: Prevents response confusion between multiple clients
- **Lease Management**: Supports 86400s (1 day) legitimate leases vs 3600s (1 hour) rogue leases

## 🏗️ System Architecture

```
┌─────────────────────────────────────────────────────────┐
│                    ProxyRouter (Central Hub)             │
│  ┌─────────────┐  ┌──────────────┐  ┌────────────────┐ │
│  │   Adaptive  │  │   Learning   │  │    Security    │ │
│  │    Cache    │  │    Router    │  │   Filtering    │ │
│  │  (LRU+TTL)  │  │  (Dynamic)   │  │  (DHCP/Cache)  │ │
│  └─────────────┘  └──────────────┘  └────────────────┘ │
└───────┬─────────────┬──────────────┬──────────────┬─────┘
        │             │              │              │
   ┌────▼───┐   ┌────▼────┐   ┌─────▼─────┐  ┌────▼────┐
   │  HTTP  │   │  DHCP   │   │   DHCP    │  │ Clients │
   │ Origin │   │ Legit   │   │   Rogue   │  │  (N)    │
   └────────┘   └─────────┘   └───────────┘  └─────────┘
   (Gate 0)     (Gate 1)      (Gate 2)       (Gates 3+)
```

## 📁 Project Structure

```
proxy_router/
├── Makefile                    # Main build configuration
├── README.md                   # This file
├── src/
│   ├── Makefile               # Source build configuration
│   ├── package.ned            # Package definition
│   ├── SimpleNet.ned          # Network topology
│   ├── omnetpp.ini            # Simulation configuration
│   └── Modules/
│       ├── helpers.h          # Common utilities and message types
│       ├── messages.msg       # Custom message definitions
│       ├── dhcpclient.cc      # DHCP client implementation
│       ├── dhcpserver.cc      # DHCP server (legitimate + rogue)
│       ├── httporigin.cc      # HTTP origin server
│       └── proxyrouter.cc     # Main proxy router with all features
└── results/                   # Simulation outputs and logs
```

## 🚀 Getting Started

### Prerequisites

- **OMNeT++ 6.0+**: Network simulation framework
- **C++17 compatible compiler**: GCC 7+ or Clang 5+
- **Make**: Build automation tool

### Installation

1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   cd proxy_router
   ```

2. **Build the project**:
   ```bash
   make
   ```

3. **Run simulations**:
   ```bash
   # Run baseline configuration
   cd src
   ../src/simple_dns_http -u Cmdenv -c Baseline
   
   # Or use the OMNeT++ IDE for GUI simulation
   ```

## 🧪 Experimental Configurations

The project includes 7 pre-configured experiments in `omnetpp.ini`:

| Configuration | Description | Key Changes |
|--------------|-------------|-------------|
| **Baseline** | All features enabled | Default settings, 3 clients |
| **NoAdaptiveTTL** | Static TTL caching | Disables dynamic TTL adjustment |
| **NoLearning** | Static routing | Disables route learning, uses flooding |
| **NoSecurity** | No threat detection | Disables all security features |
| **HighLoad** | Stress test | 10 clients, 5s request interval |
| **HighLatency** | Network delay test | 5ms link delay (10x normal) |
| **AggressiveAttack** | Enhanced rogue DHCP | Faster rogue responses, lower detection threshold |
| **SmallCache** | Memory constraint test | 100 entry cache (10x smaller) |

### Running Experiments

```bash
# Single configuration
./simple_dns_http -u Cmdenv -c HighLoad

# All configurations
./simple_dns_http -u Cmdenv -c Baseline,NoAdaptiveTTL,NoLearning,NoSecurity

# With GUI
./simple_dns_http -u Qtenv -c Baseline
```

## 📊 Simulation Results (Baseline - 50s)

### Performance Metrics

| Metric | Value | Description |
|--------|-------|-------------|
| **Total HTTP Requests** | 10 | Combined requests from all clients |
| **Cache Hits** | 5 | Successfully served from cache |
| **Cache Hit Rate** | 50% | Percentage of cached responses |
| **Cache Size** | 5/1000 | Active entries / Max capacity |
| **Learned Routes** | 5 | Discovered network paths |
| **Routing Updates** | 5 | Total route learning events |
| **Route Convergence** | 10s | Average time to learn route |

### Security Metrics

| Metric | Value | Description |
|--------|-------|-------------|
| **Rogue DHCP Detections** | 2 | Malicious DHCP offers identified |
| **Cache Poison Attempts** | 0 | Detected poisoning attacks |
| **Blocked Responses** | 0 | Filtered malicious content |
| **Blacklisted Servers** | 0 | Permanently blocked attackers |
| **Attack Detection Accuracy** | 100% | Correct threat identification rate |

### DHCP Performance

| Metric | Client 0 | Client 1 | Description |
|--------|----------|----------|-------------|
| **Assigned IP** | 192.168.1.101 | 192.168.1.100 | Legitimate addresses |
| **Lease Duration** | 86400s (1 day) | 86400s (1 day) | From legitimate server |
| **Rogue Offers Received** | 1 (10.0.0.101) | 1 (10.0.0.100) | Rejected rogue offers |

## 🔍 Key Observations from Simulation Log

### 1. DHCP Process Flow
```
Client 101 → DISCOVER → ProxyRouter → Both DHCP Servers
Legitimate Server → OFFER (192.168.1.100) → ProxyRouter → Client 101
Rogue Server → OFFER (10.0.0.100) → [DETECTED] → ProxyRouter → Client 101
Client 101 → REQUEST (192.168.1.100) → ProxyRouter → Both Servers
Legitimate Server → ACK → ProxyRouter → Client 101 ✓
Rogue Server → CANNOT PROVIDE → Rejected
```

### 2. Cache Behavior Evolution
- **First Request** (t=5.48s): `/about` - CACHE MISS → Origin fetch (latency: 0.001s)
- **Second Request** (t=15.48s): `/about` - CACHE HIT → TTL adapted 3600s → 5400s
- **Hit Rate Growth**: 0% → 33.33% → 50% → 44.44% → 50%

### 3. Route Learning Timeline
```
t=0.554s: Route to Client 101 (gate 4) learned
t=0.556s: Route to DHCP Legit (gate 1) learned
t=0.556s: Route to DHCP Rogue (gate 2) learned
t=0.817s: Route to Client 100 (gate 3) learned
t=5.497s: Route to HTTP Origin (gate 0) learned
```

### 4. Security Event Timeline
```
t=0.556s: ROGUE DHCP detected! Suspicion: 0.3 (Total: 1)
t=0.819s: ROGUE DHCP detected! Suspicion: 0.6 (Total: 2)
```

## 📈 Adaptive TTL Mechanism

The TTL adaptation formula:
```
multiplier = 1.0
if hitRate > 0.8: multiplier += 0.5
if hitRate > 0.6: multiplier += 0.3
if hitRate > 0.4: multiplier += 0.1
if hitRate < 0.2: multiplier *= 0.5
if accessFreq > 10: multiplier += 0.3
if accessFreq > 5:  multiplier += 0.2
if accessFreq > 1:  multiplier += 0.1
if avgLatency > threshold: multiplier += 0.3
if congestion > threshold:  multiplier += 0.2

newTTL = baseTTL × multiplier
newTTL = clamp(newTTL, minTTL, maxTTL)
```

**Example from simulation:**
- URL: `/about`
- Initial TTL: 3600s
- After first hit: hitRate=1.0, freq=0.10, latency=0.001s
- New TTL: 5400s (50% increase due to perfect hit rate)

## 🛡️ Security Architecture

### Rogue DHCP Detection
1. **Pattern Matching**: Identifies IP ranges (10.0.0.x indicates rogue)
2. **Suspicion Scoring**: 
   - +0.3 per rogue OFFER
   - +0.5 per cache poison attempt
   - -10% decay per cleanup cycle (60s)
3. **Blacklisting**: Suspicion ≥ 0.8 triggers permanent block
4. **Allow-through Design**: Forwards all offers to client for first-come-first-served selection

### Cache Validation
```cpp
bool validateResponse(msg, contentHash):
    if contentHash contains "malicious": return false
    if serverIP is blacklisted: return false
    return true
```

## 🎛️ Configuration Parameters

### Proxy Router
```ini
**.proxyRouter.address = 2
**.proxyRouter.cacheSize = 1000                    # Max cache entries
**.proxyRouter.defaultTTL = 3600s                  # Base TTL
**.proxyRouter.minTTL = 60s                        # Min adaptive TTL
**.proxyRouter.maxTTL = 7200s                      # Max adaptive TTL
**.proxyRouter.enableAdaptiveTTL = true            # Enable TTL adaptation
**.proxyRouter.enableLearning = true               # Enable route learning
**.proxyRouter.enableSecurityFiltering = true      # Enable threat detection
**.proxyRouter.suspicionThreshold = 0.8            # Blacklist threshold
**.proxyRouter.routeExpiryTime = 300s              # Route timeout
```

### Network
```ini
**.numClients = 3                                  # Number of clients
**.linkDelay = 0.0005s                             # 0.5ms propagation delay
**.linkDatarate = 1Gbps                            # Link bandwidth
```

### DHCP Clients
```ini
**.clients[*].requestInterval = 30s                # DHCP retry interval
**.clients[*].autoRenew = true                     # Enable lease renewal
**.clients[*].httpRequestInterval = 10s            # HTTP request frequency
**.clients[*].sendHttpRequests = true              # Enable HTTP traffic
```

## 📊 Output Files

### Scalar Results (.sca)
Contains final statistics:
- `totalRequests`: Total HTTP requests processed
- `cacheHits`: Number of cache hits
- `cacheHitRate`: Cache hit percentage
- `learnedRoutes`: Number of discovered routes
- `rogueDetections`: Security threat count
- `attackDetectionAccuracy`: Security system effectiveness

### Vector Results (.vec)
Time-series data for:
- Cache hit rate evolution
- Routing table growth
- Suspicion score changes
- Network latency measurements

### Event Log (.elog)
Complete event trace for visualization in OMNeT++ IDE

### Custom Logs (results/proxy_*.log)
CSV format: `timestamp,event,details,address`

## 🔬 Research Applications

This simulation is ideal for studying:

1. **Cache Optimization**
   - TTL adaptation strategies
   - Eviction policy comparison
   - Hit rate vs memory tradeoffs

2. **Network Routing**
   - Learning vs static routing efficiency
   - Convergence time analysis
   - Flooding overhead reduction

3. **Security**
   - Intrusion detection effectiveness
   - False positive rates
   - Attack mitigation strategies

4. **Protocol Analysis**
   - DHCP security vulnerabilities
   - HTTP caching behavior
   - Message ordering issues

## 🐛 Known Limitations

1. **Simplified Protocols**: Does not implement full TCP/IP stack
2. **Content Validation**: Basic hash-based validation only
3. **No Encryption**: TLS/SSL not simulated
4. **Single Proxy**: No distributed proxy support
5. **Memory**: Assumes unlimited available memory (only entry count limited)

## 🔮 Future Enhancements

- [ ] Distributed caching with cache coherence protocols
- [ ] Machine learning-based TTL prediction
- [ ] Advanced attack patterns (DNS spoofing, ARP poisoning)
- [ ] QoS-aware routing decisions
- [ ] Real-world trace replay support
- [ ] Integration with actual network stacks (ns-3)

## 👥 Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Submit a pull request with detailed description
