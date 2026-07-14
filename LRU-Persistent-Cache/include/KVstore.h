#pragma once
#include <string>
#include <unordered_map>
#include <optional>

class KVstore {
public:
	void set(std::string key, std::string value);
	std::optional<std::string> get(std::string_view key) const;
	bool del(std::string_view key);	
private:
	std::unordered_map<std::string, std::string> data_;
};