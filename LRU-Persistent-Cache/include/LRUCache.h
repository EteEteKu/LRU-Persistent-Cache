#pragma once
#include <string>
#include <unordered_map>
#include <optional>
#include <list>

class LRUcache {
public:
	LRUcache(size_t limit_cache);	
	std::optional<std::string> get(std::string_view key);
	void put(std::string key, std::string value);
	bool del(std::string_view key);
	const std::list<std::pair<std::string, std::string>>& items() const;


private:
	size_t limit_cache_;
	std::list<std::pair<std::string, std::string>> items_;
	std::unordered_map< std::string, std::list<std::pair<std::string, std::string>>::iterator> index_;
	std::optional<std::string>  evict();
};