# EFlightPM
An Efficient and Friendly Lightweight Persistent Memory System

## Step-by-step building for EFlightPM

1. Pre-allocate a large Memory Chunk for user (page-continuous), like 1~128GB.
2. Partition the large memory using finer grain, like 1KB, 2KB or 4KB.
3. Use tricky method to allocate memory efficiently, like hash-allocate.

