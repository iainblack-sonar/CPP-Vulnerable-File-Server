#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <ctime>

// RELIABILITY: Global mutable state
static std::map<std::string, char*> cache;
static std::map<std::string, time_t> cacheExpiry;
static int cacheHits = 0;
static int cacheMisses = 0;

class CacheModule {
public:
    CacheModule() {
        maxSize = 1000;
        // RELIABILITY: currentSize not initialized
    }
    
    ~CacheModule() {
        // RELIABILITY: Memory leak - cache entries not freed
        // for (auto& pair : cache) {
        //     delete[] pair.second;
        // }
    }
    
    // RELIABILITY: Memory leak on cache update
    void put(const std::string& key, const char* value, int ttl) {
        // BUG: If key exists, old value is not freed
        char* copy = new char[strlen(value) + 1];
        strcpy(copy, value);
        
        cache[key] = copy;
        cacheExpiry[key] = time(nullptr) + ttl;
        currentSize++;
    }
    
    // RELIABILITY: Use after free potential
    char* get(const std::string& key) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            cacheMisses++;
            return nullptr;
        }
        
        // Check expiry
        if (time(nullptr) > cacheExpiry[key]) {
            // RELIABILITY: Returning pointer then deleting it
            char* expired = it->second;
            cache.erase(it);
            delete[] expired;  // BUG: Should not delete if returning
            return nullptr;
        }
        
        cacheHits++;
        return it->second;  // Caller might use freed memory
    }
    
    // RELIABILITY: Double free potential
    void remove(const std::string& key) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            delete[] it->second;
            cache.erase(it);
        }
        // BUG: If called twice, double free
    }
    
    // RELIABILITY: Integer overflow
    double getHitRate() {
        // BUG: Division by zero if no accesses
        return (double)cacheHits / (cacheHits + cacheMisses) * 100;
    }
    
    // RELIABILITY: Buffer overflow
    void copyToBuffer(const std::string& key, char* buffer, int bufferSize) {
        char* value = get(key);
        if (value != nullptr) {
            // BUG: No bounds checking - buffer overflow
            strcpy(buffer, value);
        }
    }

private:
    int maxSize;
    int currentSize;  // RELIABILITY: Uninitialized
};

// ============================================
// DUPLICATED CACHE OPERATIONS
// ============================================

// DUPLICATED: Serialize cache entry v1
std::string serializeCacheEntry_v1(const std::string& key, const char* value, time_t expiry) {
    std::string result;
    result += key;
    result += "|";
    result += value;
    result += "|";
    result += std::to_string(expiry);
    return result;
}

// DUPLICATED: Serialize cache entry v2 (copy)
std::string serializeCacheEntry_v2(const std::string& key, const char* value, time_t expiry) {
    std::string result;
    result += key;
    result += "|";
    result += value;
    result += "|";
    result += std::to_string(expiry);
    return result;
}

// DUPLICATED: Serialize cache entry v3 (another copy)
std::string serializeCacheEntry_v3(const std::string& key, const char* value, time_t expiry) {
    std::string result;
    result += key;
    result += "|";
    result += value;
    result += "|";
    result += std::to_string(expiry);
    return result;
}

// ============================================
// DUPLICATED KEY GENERATION
// ============================================

// DUPLICATED: Generate cache key v1
std::string generateCacheKey_v1(const std::string& prefix, int id, const std::string& suffix) {
    std::string key;
    key += prefix;
    key += "_";
    key += std::to_string(id);
    key += "_";
    key += suffix;
    return key;
}

// DUPLICATED: Generate cache key v2 (copy)
std::string generateCacheKey_v2(const std::string& prefix, int id, const std::string& suffix) {
    std::string key;
    key += prefix;
    key += "_";
    key += std::to_string(id);
    key += "_";
    key += suffix;
    return key;
}

// DUPLICATED: Generate cache key v3 (another copy)
std::string generateCacheKey_v3(const std::string& prefix, int id, const std::string& suffix) {
    std::string key;
    key += prefix;
    key += "_";
    key += std::to_string(id);
    key += "_";
    key += suffix;
    return key;
}

// ============================================
// RELIABILITY ISSUES
// ============================================

// RELIABILITY: Null pointer dereference
void processCacheValue(const char* value) {
    // BUG: No null check
    int len = strlen(value);
    std::cout << "Value length: " << len << std::endl;
}

// RELIABILITY: Array out of bounds
int getCacheStats(int index) {
    int stats[5] = {cacheHits, cacheMisses, 0, 0, 0};
    // BUG: No bounds checking
    return stats[index];
}

// RELIABILITY: Resource leak
char* loadFromDisk(const std::string& filename) {
    FILE* f = fopen(filename.c_str(), "r");
    if (f == nullptr) {
        return nullptr;
    }
    
    char* buffer = new char[4096];
    fread(buffer, 1, 4096, f);
    
    // BUG: File handle not closed
    // fclose(f);
    
    return buffer;
}

// RELIABILITY: Infinite loop potential  
void waitForCacheReady() {
    bool ready = false;
    // BUG: ready is never set to true - infinite loop
    while (!ready) {
        // Busy wait
    }
}

// MAINTAINABILITY: High complexity function
int calculateCachePolicy(int size, int age, int frequency, int priority,
                         bool isCompressed, bool isEncrypted, int userTier) {
    int score = 0;
    
    if (size < 1024) {
        if (age < 60) {
            score = 100;
        } else if (age < 300) {
            score = 80;
        } else if (age < 600) {
            score = 60;
        } else {
            score = 40;
        }
    } else if (size < 10240) {
        if (age < 60) {
            score = 90;
        } else if (age < 300) {
            score = 70;
        } else {
            score = 50;
        }
    } else {
        if (age < 60) {
            score = 70;
        } else {
            score = 30;
        }
    }
    
    if (frequency > 100) {
        score += 20;
    } else if (frequency > 50) {
        score += 10;
    }
    
    if (priority > 5) {
        score += 15;
    }
    
    if (isCompressed) {
        score += 5;
    }
    
    if (isEncrypted) {
        score -= 10;
    }
    
    if (userTier == 1) {
        score += 30;
    } else if (userTier == 2) {
        score += 20;
    } else if (userTier == 3) {
        score += 10;
    }
    
    return score;
}

