#ifndef CHAINING_HASH_TABLE_HPP
#define CHAINING_HASH_TABLE_HPP

#include <vector>
#include <list>
#include <utility>
#include <functional>

template <typename Key, typename Value>
class ChainingHashTable {
public:
    explicit ChainingHashTable(size_t capacity = 10, double load_factor = 0.75);
    ~ChainingHashTable();

    void insert(const Key& key, const Value& value);
    bool contains(const Key& key) const;
    bool remove(const Key& key);
    void print() const;
    size_t size() const;
    size_t capacity() const;
    Value get(const Key& key) const;

private:
    struct KeyValuePair {
        Key key;
        Value value;
    };

    std::vector<std::list<KeyValuePair>> table_;
    size_t size_;
    double load_factor_;
    size_t capacity_;
    std::hash<Key> hasher_;

    void rehash_();
};

#endif
