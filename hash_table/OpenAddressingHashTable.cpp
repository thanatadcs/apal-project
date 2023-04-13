#include "OpenAddressingHashTable.hpp"
#include <stdexcept>
#include <iostream>

template <typename KeyType, typename ValueType>
OpenAddressingHashTable<KeyType, ValueType>::OpenAddressingHashTable(
        std::size_t initial_capacity, double max_load_factor,
        std::function<std::size_t(const KeyType&)> hasher)
        : table_(initial_capacity), size_(0), capacity_(initial_capacity),
          max_load_factor_(max_load_factor), hasher_(hasher) {
}

template <typename KeyType, typename ValueType>
OpenAddressingHashTable<KeyType, ValueType>::~OpenAddressingHashTable()= default;

template <typename KeyType, typename ValueType>
void OpenAddressingHashTable<KeyType, ValueType>::insert(const KeyType& key,
                                                         const ValueType& value) {
    if ((size_ + 1.0) / capacity_ > max_load_factor_) {
        rehash_();
    }
    std::size_t index = find_index_(key);
    if (table_[index].type != EntryType::OCCUPIED) {
        ++size_;
    }
    table_[index].type = EntryType::OCCUPIED;
    table_[index].key = key;
    table_[index].value = value;
}

template <typename KeyType, typename ValueType>
bool OpenAddressingHashTable<KeyType, ValueType>::contains(const KeyType& key) const {
    std::size_t index = find_index_(key);
    return table_[index].type == EntryType::OCCUPIED && table_[index].key == key;
}

template <typename KeyType, typename ValueType>
bool OpenAddressingHashTable<KeyType, ValueType>::remove(const KeyType& key) {
    std::size_t index = find_index_(key);
    if (table_[index].type == EntryType::OCCUPIED && table_[index].key == key) {
        table_[index].type = EntryType::DELETED;
        --size_;
        return true;
    }
    return false;
}

template <typename KeyType, typename ValueType>
void OpenAddressingHashTable<KeyType, ValueType>::print() const {
    for (std::size_t i = 0; i < capacity_; ++i) {
        if (table_[i].type == EntryType::OCCUPIED) {
            std::cout << "Key: " << table_[i].key << ", Value: " << table_[i].value << "\n";
        }
    }
}

template <typename KeyType, typename ValueType>
std::size_t OpenAddressingHashTable<KeyType, ValueType>::size() const {
    return size_;
}

template <typename KeyType, typename ValueType>
std::size_t OpenAddressingHashTable<KeyType, ValueType>::capacity() const {
    return capacity_;
}

template <typename KeyType, typename ValueType>
const ValueType& OpenAddressingHashTable<KeyType, ValueType>::operator[](
        const KeyType& key) const {
    std::size_t index = find_index_(key);
    if (table_[index].type == EntryType::OCCUPIED && table_[index].key == key) {
        return table_[index].value;
    }
    throw std::out_of_range("Key not found");
}

template <typename KeyType, typename ValueType>
ValueType& OpenAddressingHashTable<KeyType, ValueType>::operator[](const KeyType& key) {
    std::size_t index = find_index_(key);
    if (table_[index].type != EntryType::OCCUPIED) {
        if ((size_ + 1.0) / capacity_ > max_load_factor_) {
            rehash_();
            index = find_index_(key);
        }
        ++size_;
        table_[index].type = EntryType::OCCUPIED;
        table_[index].key = key;
    }
    return table_[index].value;
}

template <typename KeyType, typename ValueType>
void OpenAddressingHashTable<KeyType, ValueType>::rehash_() {
    std::vector<Entry> old_table = table_;
    table_.clear();
    table_.resize(capacity_ * 2);
    capacity_ *= 2;
    size_ = 0;
    for (std::size_t i = 0; i < old_table.size(); ++i) {
        if (old_table[i].type == EntryType::OCCUPIED) {
            insert(old_table[i].key, old_table[i].value);
        }
    }
}

template <typename KeyType, typename ValueType>
std::size_t OpenAddressingHashTable<KeyType, ValueType>::find_index_(
        const KeyType& key) const {
    std::size_t hash = hasher_(key);
    std::size_t index = hash % capacity_;
    std::size_t distance = 0;
    while (table_[index].type == EntryType::OCCUPIED && table_[index].key != key) {
        ++distance;
        index = (index + probe_distance_(index, hash)) % capacity_;
    }
    return index;
}

template <typename KeyType, typename ValueType>
std::size_t OpenAddressingHashTable<KeyType, ValueType>::probe_distance_(
        std::size_t index, std::size_t hash) const {
    return (hash % (capacity_ - 1)) + 1;
}