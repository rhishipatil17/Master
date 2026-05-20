#include <gtest/gtest.h>
#include <string>
#include "lru_cache.hpp"

namespace rp_test {

    // 1. Test basic addition and successful retrieval
    TEST(LRUCacheTest, BasicAddAndGet) {
        rp::LRU_Cache<int, std::string> cache(2);
        
        cache.addData(1, "One");
        
        std::string val;
        bool found = cache.getData(1, val);
        
        EXPECT_TRUE(found);
        EXPECT_EQ(val, "One");
    }

    // 2. Test cache miss (retrieving a key that doesn't exist)
    TEST(LRUCacheTest, CacheMiss) {
        rp::LRU_Cache<int, int> cache(2);
        cache.addData(1, 10);
        
        int val = 0;
        bool found = cache.getData(2, val); // Key 2 does not exist
        
        EXPECT_FALSE(found);
        EXPECT_EQ(val, 0); // Value should remain unmodified
    }

    // 3. Test the eviction policy when capacity is exceeded
    TEST(LRUCacheTest, EvictionPolicy) {
        rp::LRU_Cache<int, int> cache(2);
        
        cache.addData(1, 10);
        cache.addData(2, 20);
        
        // Cache is now full. Adding a 3rd element should evict the LRU (Key 1)
        cache.addData(3, 30); 
        
        int val;
        EXPECT_FALSE(cache.getData(1, val)) << "Key 1 should have been evicted.";
        
        EXPECT_TRUE(cache.getData(2, val));
        EXPECT_EQ(val, 20);
        
        EXPECT_TRUE(cache.getData(3, val));
        EXPECT_EQ(val, 30);
    }

    // 4. Test if MRU and LRU references update correctly upon reads
    TEST(LRUCacheTest, MRUAndLRUTrackingOnRead) {
        rp::LRU_Cache<int, int> cache(3);
        
        cache.addData(1, 100);
        cache.addData(2, 200);
        cache.addData(3, 300);
        
        // Initial state: 3 is MRU, 1 is LRU
        EXPECT_EQ(cache.getMRU().first, 3);
        EXPECT_EQ(cache.getLRU().first, 1);
        
        // Accessing Key 2 should move it to the MRU position
        int val;
        cache.getData(2, val);
        
        EXPECT_EQ(cache.getMRU().first, 2) << "Key 2 should now be the MRU.";
        EXPECT_EQ(cache.getLRU().first, 1) << "Key 1 should still be the LRU.";
    }

} // namespace
