#include <catch2/catch_test_macros.hpp>
#include "KVstore.h"
#include <filesystem>

TEST_CASE("Snapshot round-trip preserves data", "[snapshot]") {
    const std::string path = "test_snapshot_roundtrip.dat";
    std::filesystem::remove(path);

    {
        KVstore store(10);
        store.set("a", "1");
        store.set("b", "2");
        store.set("c", "3");
        REQUIRE(store.saveSnapshot(path));
    }

    KVstore restored(10);
    REQUIRE(restored.loadSnapshot(path));

    REQUIRE(restored.get("a").has_value());
    REQUIRE(*restored.get("a") == "1");
    REQUIRE(restored.get("b").has_value());
    REQUIRE(*restored.get("b") == "2");
    REQUIRE(restored.get("c").has_value());
    REQUIRE(*restored.get("c") == "3");

    std::filesystem::remove(path);
}

TEST_CASE("loadSnapshot on missing file returns true and leaves store empty", "[snapshot]") {
    const std::string path = "test_snapshot_missing.dat";
    std::filesystem::remove(path);

    KVstore store(10);
    REQUIRE(store.loadSnapshot(path));
    REQUIRE_FALSE(store.get("anything").has_value());
}

TEST_CASE("saveSnapshot does not leave a .tmp file behind", "[snapshot]") {
    const std::string path = "test_snapshot_tmp_check.dat";
    std::filesystem::remove(path);
    std::filesystem::remove(path + ".tmp");

    KVstore store(10);
    store.set("x", "1");
    REQUIRE(store.saveSnapshot(path));

    REQUIRE(std::filesystem::exists(path));
    REQUIRE_FALSE(std::filesystem::exists(path + ".tmp"));

    std::filesystem::remove(path);
}