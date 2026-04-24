# System Design

## Topics to focus during System Design interviews
- QPS
- CAP theorem
- thnk about large scale
- identify limitations and drawbacks iteratively
- think about geolocation-based load balancing
- breadth-first then deep

## Structure of the typical System Design interview
1. Define Functional (what users can do) requirements, define use cases (__from verbs__) "what can users do?". Often up to five.
2. Define Entities (__from nouns__), that is __objects, relationships/engagement,__ and __ownership__, e.g. __User__ entity is owned by User Service and stored in User Database
2. Define Nonfunctional Requirements/Constraints (performance, latency (caching, precomputing), availability (message queues), scalability (horizontal scaling, load balancers, DB partitioning), durability (DB replication), security) (__from adjectives__)
2. API design - turning functional reqs into API endpoints with clear data types, e.g. 
  ```
  POST /tweet
  Request {"user_id": "string", "content": "string}
  Response {"tweed_id": "string", "status": "string}
  ```
3. High-level architecture design (15-20 min) - turn API endpoints into basic data flow with microservices and databases, step by step. Add API Gateway
4. Apply constaints:
  6. Scalability
    a) __Vertically__
    b) __Horizontally__ (based on traffic patterns)
  7. Load Balancing (with health checks monitoring) right after API Gateway to distribute load equally and reroute traffic from unhealhy instances
  5. Low Latency, Throughput, Caching between DB and service for the latest hot data, with some expiry times or update trigger events predefined
  4. Message queues to prevent from losing data if service experience downtime
  5. Data durability - distributed databases with replicas of their originals (Amazon DynamoDB, Google Cloud Spanner, Cassandra)
8. Security
9. LLD

# High-level Architecture
- __monolithic__
- __microservices__ - scalable stateless services behind the API gateway/load balancer, communicating over REST or gRPC. Technologies: Spring Boot, Node.js

# Storage
- Databases - cold storage and source of truth, normally not being read directly but through Cache first
- __SQL__ - for well structured and linked data, ex. PostgreSQL, MySQL, SQLite (serverless for mobile apps), Amazon RDS. ACID transactions compliant. Ensures data consistency.
  - A - atomic, transactions complete fully or not at all 
  - C - consistent, trancastions move DB from one valid state to another
  - I - isolated, concurrent transcations don't interfere
  - D - durable, commited transactions persist even after crashes
- __NoSQL__ - for dynamic data, e.g. social media (instagram posts), varying for each recods, with new fields added frequently, massive traffic, without complex relationships. Ensures flexibility. Easier for horizontal scalability (more servers).
  - key-value stores (dictionaries, hash-maps), used in: caching, session storage. Examples: Redis, Memcashed
  - document stores (key-object, list of objects, JSON), used in: user profiles, content management. Example: MongoDB
  - column-family (list of rows): time-series data, analytics, high-write workloads like logs. Example: Cassandra (for time-series)
  - graph DB (nodes and edges): social networks, recommendation engines. Example: Neo4j
- __Object Storage__ - large files (photos, videos) stored in buckets under unique keys with their metadata. Handled with REST API. Employs automatic replication, versioning, and lifecycle policies (hot, cold, archive tiers) Example: Amazon S3, Google Cloud Storage, Azure Blob Storage.
- [__Cache__](#cache) - To store frequently read data (e.g. 1000 RPS) and reduce DB queries (each query ~50ms). Reduces example response time from 50ms to 1ms and DB load by 80%, whenever staleness is acceptable.
- [__Content Delivery Network__](#cdn) - cache replications to reduce latency for static large files in different geolocations

# Cache {#cache}
To store frequently read data and reduce DB queries. 

  - Working example:
    1. An app checks cache first.
    2. If data exists, return it (__cache hit__).
    3. If not (__cache miss__), query DB, save result in cache, then return to user.

  - __Writing strategy__
    - __Write-through__ - when app writes data, it updates both cache and DB simultaneously
    - __Write-behind__ - app writes to cache first, DB is synchronized later asyncly
    - __Write-around__ - app writes to DB first, cache is updated only on read operation
    - __Cache-aside__ - app reads from cache first, if cache miss, then read from DB and write data to cache

  - __Maintaining limited cache memory (eviction policies)__
    - Least Recently Used (__LRU__) - get rid off items not used for some long time
    - First In First Out (__FIFO__) - get rid off items written first
    - Least Frequently Used (__LFU__) - get rid off items not used often

  - __Invalidation strategy (keeping data fresh)__
    - Time-to-live (__TTL__) - e.g. 5 minutes for product price
    - Event-based
    - Manual

  - __Location__
    - in-memory (RAM), us to ms latency, volatile
    - disk-based, nonvolatile, for long-term cacheable storage, longer latency, for persistence over speed

  - __Implementation__
    - Redis (in-memory cache, <=us), various data structures, for session storage, leaderboards, general-purpose caching
    - Memcached (in-memory), basic key-value storage
    - Cloudflare (__CDN__)

# CDN - Content Delivery Network {#cdn}
- network of servers around world 
- copy content to CDN servers
- reduces origin server load
- acts like Caching
- stores heavy files/assets (images, videos) in different locations
- reducing latency & preventing high load on origin server
- like Cache, uses TTL
- Implementations: Cloudflare, AWS CloudFront, Akamai

# Message Queues {#message-queues}
- useful for high loads, not blocking the user interface and decoupling services
- producer-consumer idiom
- producer sends data changes to queues
- consumers pull messages, update databases and caches
- consumers send ACK back to queue if processed. If not, the message is not deleted from queue but sends to another consumer (__At least once delivery__)
- messages stored on hard drive in case server crashes
- __dead letter queues__ - failed messages are moved to separate queues for further debugging without freezing other messages.
- __processing order__: 
    - FIFO or 
    - out-of-order processing for higher throughput
- implementations: 
  - P2P (AWS SQS) - single consumer
  - RabbitMQ for complex routing
  - Publisher-Subscriber (Google Pub/Sub, Apache Kafka (event sourcing, real-time analytics, log aggregation)) - multiple consumers

# API gateway
Bridges clients to backend microservices as a single entry point for all API requests
- for security (handling OAuth authorization) and traffic control (rate limiting, e.g. up to 100 RPMs)
- for load balancing (reverse proxy)
- for request aggregation
- logging events and API traffic
- Example: NGINGX API Gateway, AWS API Gateway (for serverless apps and AWS apps)

# Scaling
1. __Decomposition__ - breaking down requirements intro microservices. Instead of one monolithic app architecture we put API Gateway and independent services with their independent databases like inventory, order, and payment service.
2. __Vertical__ - more resources, brute force approach, e.g. Amazon T3 instance to X2gd instance
3. __Horizontal__ - more replicas, running multiple instances of stateless services in parallel after the __Load Balancer__.
4. __Partitioning__ - spliting requests into shards distributing across services and/or DBs, e.g. based on user ID, geolocation, consistent hashing, or other logical key
5. __Caching__ - improving read performance and load by storing frequently accessed data in faster/closer memory storage, e.g. Redis, Memcached
6. __Message queues__ - making sync operation async for I/O bottlenecks, buffers between write services and data storage
7. __Read and write separation__ - adjusting system for read-heavy (social media) or write-heavy (IoT) requirements. 
    For databases replication it involves: 
    - leader(master)-follower(slave) architecture with leader performing write and follower performing read query, and leader-leader replication patterns
    - __CQRS__ - Command Query Responsibility Segregation pattern - split __CRUD__ into write service (CUD, create, update, delete) and read service (R, read) with write- and read-optimized data models. Write DB propagates to Read DB asynchronously
  - __CAP theorem__
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

# Decomposition Framework
  1. Turn verbs to use cases and functional requirements, e.g. CRUD, "Users _post_ tweets".
  2. Turn nouns to entities and owners (data models), e.g. "_Users_ post _tweets_". List all entities and relationships. Define source of truth.
  3. Turn adjectives to constraints and add-ons (non-functional requirements), e.g. "_Highly available_ feed" means replications.
     Other adjectives:
    - __instant/real-time__ - push notifications, websockets, caching, precomputing
    - __reliable__ - retries, dead letter queues, write-ahead logs
    - __highly available__ - replication, stateless services, health checks
    - __auditable/secure__ - encryption, access control, audit logs
    - __scalable__ - partitioning, read replicas, message queues, horizontal scaling

# Useful links
- https://systemdesignschool.io/primer#how-to-prepare
- https://www.geeksforgeeks.org/system-design/system-design-tutorial/
