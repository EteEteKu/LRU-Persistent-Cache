#pragma once
#include <string>
#include <optional>
#include "LRUCache.h"
#include <filesystem>
class KVstore {
public:
    explicit KVstore(size_t limit);
    void set(std::string key, std::string value);
    std::optional<std::string> get(std::string_view key);
    bool del(std::string_view key);
    bool saveSnapshot(const std::filesystem::path& path);
    bool loadSnapshot(const std::filesystem::path& path);
private:
    LRUcache cache_;
};