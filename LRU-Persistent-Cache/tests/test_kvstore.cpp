#include <catch2/catch_test_macros.hpp>
#include "KVstore.h"

TEST_CASE("SET and GET basic value", "[kvstore]") {
	KVstore store;
	store.set("a", "1");
	auto result = store.get("a");
	REQUIRE(result.has_value());
	REQUIRE(*result == "1");
}

TEST_CASE("GET on missing key returns nullopt", "[kvstore]") {
	KVstore store;
	auto result = store.get("testmissing");
	REQUIRE_FALSE(result.has_value());
}

TEST_CASE("SET overwrites existing key", "[lvstore]") {
	KVstore store;
	store.set("a", "1");
	store.set("a", "2");
	auto result = store.get("a");
	REQUIRE(result.has_value());
	REQUIRE(*result == "2");
}

TEST_CASE("DEL removes existing key", "[kvstore]") {
	KVstore store;
	store.set("a", "1");
	bool deleted = store.del("a");
	REQUIRE(deleted == true);
	REQUIRE_FALSE(store.get("a").has_value());
}
TEST_CASE("DEL on missing key returns false", "[kvstore]") {
	KVstore store;
	bool deleted = store.del("missing");
	REQUIRE(deleted == false);
}

TEST_CASE("SET -> DEL -> SET", "[kvstore]") {
	KVstore store;
	store.set("a", "1");

	bool deleted = store.del("a");
	REQUIRE(deleted == true);
	REQUIRE_FALSE(store.get("a").has_value());  

	store.set("a", "2");
	auto result = store.get("a");                 
	REQUIRE(result.has_value());
	REQUIRE(*result == "2");                       
}