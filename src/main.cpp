#include <iostream>
#include <tuple>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <cstdint> // uint64_t 

#ifndef MEMO_SIZE_LIMIT
#define MEMO_SIZE_LIMIT 1000000 // limited to * entries.
#endif

#ifndef USE_MAP_INSTEAD_OF_VECTOR
#endif

#ifndef MEMO_SIZE_LIMITING_ENABLED
#endif

#ifndef USE_BRANCH_OPTIM
#endif

using LargeInt = uint64_t;

#ifdef USE_MAP_INSTEAD_OF_VECTOR
using MemoContainer = std::map<std::pair<LargeInt, LargeInt>, LargeInt>;
#else
using MemoContainer = std::vector<std::tuple<LargeInt, LargeInt, LargeInt>>;
#endif

inline void putIntoContainer(LargeInt m, LargeInt n, LargeInt result, MemoContainer& memo) {
#ifdef MEMO_SIZE_LIMITING_ENABLED
        if (memo.size() < MEMO_SIZE_LIMIT)
#endif
#ifdef USE_MAP_INSTEAD_OF_VECTOR
            memo.emplace(std::make_pair(std::make_pair(m, n), result));
#else
    	    memo.emplace_back(m, n, result);
#endif
}

LargeInt Ackermann(LargeInt m, LargeInt n, MemoContainer& memo) {
	auto it = std::find_if(memo.begin(), memo.end(), [m, n] (auto t) {
	    #ifdef USE_MAP_INSTEAD_OF_VECTOR
	        return (t.first.first == m) && (t.first.second == n);
	    #else    
	        return (std::get<0>(t) == m) && (std::get<1>(t) == n); 
	    #endif
	    });
	// huh, that was long.
	if (
#ifdef USE_BRANCH_OPTIM
	__builtin_expect(	
#endif
		it != memo.end()
#ifdef USE_BRANCH_OPTIM
		, 0)
#endif
	   )
#ifdef USE_MAP_INSTEAD_OF_VECTOR
        return it->second;
#else
	    return std::get<2>(*it);
#endif
	else {
	    // ackermann function implementation.
	    LargeInt result;
	    if (m == 0)
	        result = n + 1;
	    else if (/* m > 0 && */ n == 0 )
	        result = Ackermann(m - 1, 1, memo);
	    else /* if (m > 0 && n > 0) */ {
	        result = Ackermann(m, n - 1, memo);
	        result = Ackermann(m - 1, result, memo);
	    }
	    
	    putIntoContainer(m, n, result, memo);
	    
	    return result;
	}
}

int main(int argc, char *argv[]) {
    bool inputAcquired = false;
    LargeInt m, n;
    MemoContainer memo;
    
    #ifndef USE_MAP_INSTEAD_OF_VECTOR
    memo.reserve(MEMO_SIZE_LIMIT);
    #endif
    
    if (argc > 2) {
        try
        {
        m = std::atoll(argv[1]);
        n = std::atoll(argv[2]);
        inputAcquired = true;
        } 
        catch (std::exception ex) 
        {
            std::cerr << ex.what() << std::endl;
            return -1;
        }
    }
    
    if (!inputAcquired) {
        std::cerr << "one should\'ve passed positive integers as m and n\n";
        std::cout << "enter m & n manually pleez: ";
        std::cin >> m >> n;
    }
    
    // here, both m and n should be set.
    LargeInt result = Ackermann(m, n, memo);
    std::cout << "ack(" << m << ", " << n << ") = " << result 
		<< "\ntailIdx at the end: " << memo.size()
		<< "\nMemory utilization: " << double(100 * memo.size()) / MEMO_SIZE_LIMIT
		<< std::endl;
    
    //std::ofstream outfile("nanocube.txt", std::ios::out | std::ios::binary);
    //outfile.write(&memo[0], memo.size() * sizeof(memo[0]));
    
    return 0;
}
