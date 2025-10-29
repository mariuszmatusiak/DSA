# System Design

## Topics to focus on Interviews
- QPS
- CAP theorem
- thnk about large scale
- identify limitations and drawbacks iteratively
- think about geolocation-based load balancing
- breadth-first then deep

## Structure
1. Define Functional (what users can do) and Nonfunctional (performance, latency, availability, scalability, durability, security) Requirements
2. Constraints/limitations
3. High-level architecture design
4. Databases
5. Latency, Throughput, Caching
6. Scalability
  a) _Vertical_
  b) _Horizontal_
7. Load Balancing
8. Security
9. LLD

# Architecture
## monolithic
## microservices 
behind the API gateway, communicating over REST or gRPC
Technologies: Spring Boot, Node.js

# Storage
- _SQL_ - for well structured and linked data, ex. PostgreSQL, MySQL, SQLite (serverless for mobile apps), ACID compliant
- _NoSQL_ - for dynamic data, e.g. social media, massive traffic, without complex relationships
  - key-val stores
  - document stores
  - graph dbs
- Message queue

# Cache
to store frequently read data and reduce DB queries. 
  - Maintaining (eviction policies)
    - Least Recently Used (LRU)
    - First In First Out (FIFO)
    - Least Frequently Used (LFU)
  - Invalidation strategy
    - Time-to-live (TTL)
    - Event-based
    - Manual
  - Write strategy
    - Write-Through - both to cache and to DB
    - Write-Behind - cache first, DB later
    - Write-Around - DB first, cache on read-only operation
  - Location
    - in-memory (RAM), us to ms latency, volatile
    - disk-based, nonvolatile, for long-term cacheable storage, longer latency, for persistence over speed
    
# CDN - Content Delivery Network
- network of servers around world 
- copy content to CDN servers
- acts a bit like Caching
- stores heavy files (images, videos) in different locations
- reducing latency & preventing high load on origin server
- like Cache, uses TTL
- Example: Cloudflare, AWS CloudFront, Akamai

# Message Queues
- producer-consumer idiom
- consumers send ACK
- dead letter queues - msgs on separate queues for debugging
- processing: FIFO or out-of-order processing for higher throughput
- implementations: 
  - P2P (AWS SQS) - single consumer
  - Publisher-Subscriber (Google Pub/Sub, Apache Kafka) - multiple consumers
  
# API gateway
Bridges clients to backend microservices as a single entry point for all API requests
- for security (OAuth authoriztion) and traffic control (rate limiting)
- for load balancing (reverse proxy)
- Example: NGINGX API Gateway, AWS API Gateway

# Scaling
- _Vertical_ - more resources
- _Horizontal_ - more replicas
  - for databases: leader-follower, leader-leader replication patterns
  - CAP theorem
    - Consistency
    - Availability
    - Partition (network)

# Load Balancer
- remote proxy



# Internet
- TCP - low level
  - HTTP - app-layer, request/response, poling
    - REST API - json
    - GraphQL - single request (query) to fetch multiple data
    - gRPC - server 2 server 
  - web socket - support bidirectional communication, for chats
  
# Storage
  -
