#pragma once
#include <iostream>
#include <string>

class HashTable {
public:
	HashTable(int size);
	~HashTable();
	bool insert(const std::string& key, const std::string& value);
	bool remove(const std::string& key);
	std::pair<std::string, std::string>* get_all(int& count);
	std::string get(const std::string& key);

private:
	struct Slot {
		std::string key;
		std::string value;
		bool deleted;
	};

	int size;
	int count;
	Slot* data;

	int hash(const std::string& key);
};