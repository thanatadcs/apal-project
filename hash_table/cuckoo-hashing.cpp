#include <iostream>
#include <vector>
#include <stdexcept>
#include <ctime>
#include <cstdlib>

constexpr size_t TABLE_SIZE = 11;

template <typename TKey, typename TValue>
class CuckooHashTable {
public:
    CuckooHashTable()
            : table1(TABLE_SIZE, std::make_pair(TKey(), TValue())),
              table2(TABLE_SIZE, std::make_pair(TKey(), TValue())) {
        srand(time(nullptr));
    }

    void insert(const TKey& key, const TValue& value) {
        size_t i = 0;
        TKey curKey = key;
        TValue curValue = value;
        while (i < TABLE_SIZE) {
            std::pair<TKey, TValue>& pos1 = table1[hash1(curKey)];
            if (pos1.first == TKey()) {
                pos1 = std::make_pair(curKey, curValue);
                return;
            }
            std::swap(curKey, pos1.first);
            std::swap(curValue, pos1.second);

            std::pair<TKey, TValue>& pos2 = table2[hash2(curKey)];
            if (pos2.first == TKey()) {
                pos2 = std::make_pair(curKey, curValue);
                return;
            }
            std::swap(curKey, pos2.first);
            std::swap(curValue, pos2.second);

            i++;
        }
        throw std::runtime_error("Failed to insert: the hash table is too full.");
    }

    TValue find(const TKey& key) const {
        size_t index1 = hash1(key);
        if (table1[index1].first == key) {
            return table1[index1].second;
        }

        size_t index2 = hash2(key);
        if (table2[index2].first == key) {
            return table2[index2].second;
        }

        throw std::runtime_error("Key not found.");
    }

private:
    std::vector<std::pair<TKey, TValue>> table1;
    std::vector<std::pair<TKey, TValue>> table2;

    size_t hash1(const TKey& key) const {
        return std::hash<TKey>{}(key) % TABLE_SIZE;
    }

    size_t hash2(const TKey& key) const {
        return (std::hash<TKey>{}(key) ^ rand()) % TABLE_SIZE;
    }
};

int main() {
    CuckooHashTable<int, std::string> hashTable;
    hashTable.insert(1, "one");
    hashTable.insert(2, "two");
    hashTable.insert(3, "three");

    std::cout << "Value for key 1: " << hashTable.find(1) << std::endl;
    std::cout << "Value for key 2: " << hashTable.find(2) << std::endl;
    std::cout << "Value for key 3: " << hashTable.find(3) << std::endl;

    return 0;
}