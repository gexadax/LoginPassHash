#include "hash_table.h"

const int PRIME = 31;
const int MAX_LOAD_FACTOR = 2;

HashTable::HashTable(int size) : size(size), count(0) {
    data = new Slot[size];
    for (int i = 0; i < size; ++i) {
        data[i].deleted = true;
    }
}

HashTable::~HashTable() {
    delete[] data;
}

int HashTable::hash(const std::string& key) {
    const double A = 0.7;
    double result = 0;
    for (char c : key) {
        result = fmod(result * PRIME + c, INT_MAX);
    }
    return static_cast<int>(floor(size * fmod(result * A, 1)));
}

bool HashTable::insert(const std::string& key, const std::string& value) {
    if (count >= size * MAX_LOAD_FACTOR) {
        // Warning for resize the hash table.
        std::cout << "Warning: load factor above " << MAX_LOAD_FACTOR
            << ". Resizing hash table.\n";
        return false;
    }

    int h = hash(key);
    for (int i = 0; i < size; ++i) {
        int j = (h + i * i) % size;
        if (data[j].deleted || data[j].key == key) {
            data[j].key = key;
            data[j].value = value;
            data[j].deleted = false;
            ++count;
            return true;
        }
    }

    // Unable to insert into hash table.
    return false;
}

bool HashTable::remove(const std::string& key) {
    int h = hash(key);
    for (int i = 0; i < size; ++i) {
        int j = (h + i * i) % size;
        if (!data[j].deleted && data[j].key == key) {
            data[j].deleted = true;
            --count;
            return true;
        }
    }
    return false;
}

std::string HashTable::get(const std::string& key) {
    int h = hash(key);
    for (int i = 0; i < size; ++i) {
        int j = (h + i * i) % size;
        if (!data[j].deleted && data[j].key == key) {
            return data[j].value;
        }
    }
    return "";
}

std::pair<std::string, std::string>* HashTable::get_all(int& count) {
    std::pair<std::string, std::string>* all_entries = new std::pair<std::string, std::string>[this->count]();
    count = 0;
    for (int i = 0; i < size; ++i) {
        if (!data[i].deleted) {
            all_entries[count++] = std::make_pair(data[i].key, data[i].value);
        }
    }
    return all_entries;
}