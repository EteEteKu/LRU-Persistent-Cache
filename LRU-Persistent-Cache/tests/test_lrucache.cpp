#include <catch2/catch_test_macros.hpp>
#include "LRUCache.h"


TEST_CASE("Eviction removes least recently used key", "[lrucache]") {
	LRUcache cache = LRUcache(2);
	cache.put("a", "1");
	cache.put("b", "2");
	cache.put("c", "3");
	REQUIRE(cache.get("a") == std::nullopt);   
	REQUIRE(cache.get("b").has_value());        
	REQUIRE(*cache.get("b") == "2");
	REQUIRE(cache.get("c").has_value());        
	REQUIRE(*cache.get("c") == "3");
}
TEST_CASE("Recently accessed key survives eviction", "[lrucache]") {
	LRUcache cache = LRUcache(2);
	cache.put("a", "1");
	cache.put("b", "2");
	cache.get("a");
	cache.put("c", "3");
	REQUIRE(*cache.get("a") == "1");
	REQUIRE(cache.get("b") == std::nullopt);
	REQUIRE_FALSE(cache.get("c") == std::nullopt);
	REQUIRE(*cache.get("c") == "3");
}

TEST_CASE("Updating existing key does not increase cache size", "[lrucache]") {
	LRUcache cache = LRUcache(2);
	cache.put("a", "1");
	cache.put("b", "2");
	cache.put("a", "4");
	cache.put("c", "3");
	REQUIRE(cache.get("b") == std::nullopt);
	REQUIRE_FALSE(cache.get("a") == std::nullopt);
	REQUIRE(*cache.get("a") == "4");
	REQUIRE_FALSE(cache.get("c") == std::nullopt);
	REQUIRE(*cache.get("c") == "3");

}