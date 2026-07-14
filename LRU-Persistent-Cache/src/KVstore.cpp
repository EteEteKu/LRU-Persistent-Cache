
#include "KVstore.h"


void KVstore::set(std::string key, std::string value) {
	data_.insert_or_assign(key, value);
}
std::optional<std::string> KVstore::get(std::string_view key) const {
    auto it = data_.find(std::string(key));  
    if (it != data_.end()) {
        return it->second;
    }
    return std::nullopt;
}

bool KVstore::del(std::string_view key) {
    auto it = data_.find(std::string(key));
    if (it != data_.end()) {
        data_.erase(it);
        return true;
    }
    return false;   
}