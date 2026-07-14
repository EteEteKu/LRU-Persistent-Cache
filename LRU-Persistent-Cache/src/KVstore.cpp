
#include "KVstore.h"
#include <fstream>
#include <iostream>
KVstore::KVstore(size_t limit) : cache_(limit) {}

void KVstore::set(std::string key, std::string value) {
    cache_.put(key,value);
}
std::optional<std::string> KVstore::get(std::string_view key) {
    return cache_.get(key);
}

bool KVstore::del(std::string_view key) {
    return cache_.del(key);
}

bool KVstore::saveSnapshot(const std::filesystem::path& path) {
    std::string temp_file_path = path.string() + ".tmp";
    std::ofstream file(temp_file_path);
    if (!file.is_open()) {
        return false;
    }
    const std::list<std::pair<std::string, std::string>> &items = cache_.items();
    for (const auto& item : items) {
        file << item.first << " " << item.second << std::endl;
    }
    file.close();
    std::error_code ec;
    std::filesystem::rename(temp_file_path, path, ec);
    if (ec) {
        return false;
    }
    return true;
}

bool KVstore::loadSnapshot(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) return true;

    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }
    std::string key, value;
    while (file >> key >> value) {
        cache_.put(key, value);
    }
    return true;
}