#include "LRUCache.h"
#include <optional>
LRUcache::LRUcache(size_t limit_cache) 
	:limit_cache_(limit_cache) {

}
std::optional<std::string> LRUcache::get(std::string_view key) {
	auto result = index_.find(std::string(key));
	if (result == index_.end()) return std::nullopt;
	items_.splice(items_.begin(), items_, result->second);
	return items_.begin()->second;
}
void LRUcache::put(std::string key, std::string value) {
	auto it = index_.find(key);
	if (it != index_.end()) {
		it->second->second = value;
		items_.splice(items_.begin(), items_,it->second);
	}
	else {
		if (limit_cache_ <= items_.size()) {
			evict();
		}
		items_.push_front(std::make_pair(key, value));
		index_.insert(std::make_pair(key, items_.begin()));
	}
}
std::optional<std::string> LRUcache::evict() {
	if (items_.empty()) {
		return std::nullopt;
	}
	auto delete_key = items_.back();
	items_.pop_back();
	index_.erase(delete_key.first);
	return delete_key.first;
}