
#include <locale>
#include <iostream>
#include "KVstore.h"
#include <string>
#include <sstream>

int main() {
	std::setlocale(LC_ALL, "Russian");

	KVstore store(4);
	std::string line;

	store.loadSnapshot("snapshot.dat");
	while (std::getline(std::cin, line)) {
		if (line == "exit") {
			store.saveSnapshot("snapshot.dat");

			break;
		}
		std::istringstream iss(line);
		std::string command;
		iss >> command;
		if (command == "SET") {
			std::string key;
			std::string value;
			iss >> key >> value;
			if (!key.empty() && !value.empty()) {
				store.set(key, value);
				std::cout << "Значение успешно set" << std::endl;
			}
		}
		else if (command == "GET") {
			std::string key;

			iss >> key;
			if (!key.empty()) {
				std::optional<std::string> current_value = store.get(key);
				if (current_value == std::nullopt) {
					std::cout << "Объекта не существует" << std::endl;
				}
				else {
					std::cout << *current_value << std::endl;
				}
			}
		}
		else if (command == "DEL") {
			std::string key;
			iss >> key;
			if (!key.empty()) 
			{
				bool del_value = store.del(key);
				if (!del_value) {
					std::cout << "Такого объекта не существует" << std::endl;
				}
				else {
					std::cout << "Объект удален успешно" << std::endl;
				}
			}
		}

	}

	return 0;
}