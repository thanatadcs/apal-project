#ifndef OPEN_ADDRESSING_HASH_TABLE_HPP
#define OPEN_ADDRESSING_HASH_TABLE_HPP

#include <vector>
#include <functional>

template <typename KeyType, typename ValueType>
class OpenAddressingHashTable {
public:
    explicit OpenAddressingHashTable(std::size_t initial_capacity = 16,
                            double max_load_factor = 0.75,
                            std::function<std::size_t(const KeyType&)> hasher = std::hash<KeyType>());
    ~OpenAddressingHashTable();

    void insert(const KeyType& key, const ValueType& value);
    bool contains(const KeyType& key) const;
    bool remove(const KeyType& key);
    void print() const;

    std::size_t size() const;
    std::size_t capacity() const;

    const ValueType& operator[](const KeyType& key) const;
    ValueType& operator[](const KeyType& key);

private:
    enum class EntryType : char {EMPTY, OCCUPIED, DELETED};

    struct Entry {
        EntryType type;
        KeyType key;
        ValueType value;
    };

    std::vector<Entry> table_;
    std::size_t size_;
    std::size_t capacity_;
    double max_load_factor_;
    std::function<std::size_t(const KeyType&)> hasher_;

    void rehash_();
    std::size_t find_index_(const KeyType& key) const;
    std::size_t probe_distance_(std::size_t index, std::size_t hash) const;
};

#endif
