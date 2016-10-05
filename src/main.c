#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef MEMO_SIZE_LIMIT
#define MEMO_SIZE_LIMIT  1000000
#endif

uint32_t tailIdx = 0;
uint64_t memo[MEMO_SIZE_LIMIT * 3];  // Nth element-> m, n, r

inline
void put(uint64_t m, uint64_t n, uint64_t r) {
    if (tailIdx < MEMO_SIZE_LIMIT) {
    memo[tailIdx++] = m;
    memo[tailIdx++] = n;
    memo[tailIdx++] = r;
    }
}

inline
uint32_t find(uint64_t m, uint64_t n) {
    register uint32_t index = 0;
    do {
        if (memo[index] == m && memo[index + 1] == n)
            return index;
        index += 3;
    } while (index < tailIdx);
    // coming here means we couldn't find it.
    return -1;
}

uint64_t ack(uint64_t m, uint64_t n) {
    uint32_t index;
    uint64_t result;
    
    if ((index = find(m, n)) != -1)
        return memo[index + 2];
        
    if (m == 0)
        result = n + 1;
    else if (n == 0)
        result = ack(m - 1, 1);
    else {
        result = ack(m, n - 1);
        result = ack(m - 1, result);
    }
    
    put(m, n, result);
    
    return result;
}
        
int main(int argc, char *argv[]) {
    int inputAcquired = 0;
    uint64_t m, n;
    
    if (argc > 2) {
        m = atoll(argv[1]);
        n = atoll(argv[2]);
        if (m < 0 || n < 0)
            return -1;
        inputAcquired = 1;
    }
    
    if (!inputAcquired) {
        scanf("%lu %lu", &m, &n);
    }
    
    // here, both m and n should be set.
    uint64_t result = ack(m, n);
    printf("ack(%lu, %lu) = %lu\n", m, n, result);
    printf("tailIdx at the end: %u\nMemory utilization: %3.1f\n", tailIdx, ((double) 100.0 * tailIdx) / MEMO_SIZE_LIMIT);
    
    return 0;
}
