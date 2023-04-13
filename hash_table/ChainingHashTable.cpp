#include <string>
#include <stdexcept>
#include <iostream>
#include "ChainingHashTable.hpp"

template <typename Key, typename Value>
ChainingHashTable<Key, Value>::ChainingHashTable(size_t capacity, double load_factor)
        : table_(capacity), size_(0), load_factor_(load_factor), capacity_(capacity), hasher_() {}

template <typename Key, typename Value>
ChainingHashTable<Key, Value>::~ChainingHashTable() {
    for (auto& list : table_) {
        list.clear();
    }
    size_ = 0;
}

template <typename Key, typename Value>
void ChainingHashTable<Key, Value>::insert(const Key& key, const Value& value) {
    if ((double)size_ / capacity_ >= load_factor_)
        rehash_();

    auto& list = table_[hasher_(key) % capacity_];
    for (auto& pair : list) {
        if (pair.key == key) {
            pair.value = value;
            return;
        }
    }
    list.push_back({ key, value });
    size_++;
}

template <typename Key, typename Value>
bool ChainingHashTable<Key, Value>::contains(const Key& key) const {
    const auto& list = table_[hasher_(key) % capacity_];
    for (const auto& pair : list) {
        if (pair.key == key) {
            return true;
        }
    }
    return false;
}

template <typename Key, typename Value>
bool ChainingHashTable<Key, Value>::remove(const Key& key) {
    auto& list = table_[hasher_(key) % capacity_];
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (it->key == key) {
            list.erase(it);
            size_--;
            return true;
        }
    }
    return false;
}

template <typename Key, typename Value>
void ChainingHashTable<Key, Value>::print() const {
    for (size_t i = 0; i < capacity_; i++) {
        const auto& list = table_[i];
        std::cout << "[" << i << "]: ";
        for (const auto& pair : list) {
            std::cout << "(" << pair.key << ", " << pair.value << ") -> ";
        }
        std::cout << "nullptr" << std::endl;
    }
}

template <typename Key, typename Value>
void ChainingHashTable<Key, Value>::rehash_() {
    std::vector<std::list<KeyValuePair>> new_table(capacity_ * 2);
    for (const auto& list : table_) {
        for (const auto& pair : list) {
            auto& new_list = new_table[hasher_(pair.key) % (capacity_ * 2)];
            new_list.push_back(pair);
        }
    }
    table_ = std::move(new_table);
    capacity_ *= 2;
}

template <typename Key, typename Value>
size_t ChainingHashTable<Key, Value>::size() const {
    return size_;
}

template <typename Key, typename Value>
size_t ChainingHashTable<Key, Value>::capacity() const {
    return capacity_;
}

template <typename Key, typename Value>
Value ChainingHashTable<Key, Value>::get(const Key& key) const {
    const auto& list = table_[hasher_(key) % capacity_];
    for (const auto& pair : list) {
        if (pair.key == key) {
            return pair.value;
        }
    }
    throw std::out_of_range("Key not found");
}

// Explicit instantiations for common types
template class ChainingHashTable<int, int>;
template class ChainingHashTable<std::string, int>;