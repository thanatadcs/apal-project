#include <iostream>
#include <vector>
#include <stdexcept>
#include <random>

class CuckooHashTable {
public:
    CuckooHashTable(size_t size) : table1(size, -1), table2(size, -1), size(size) {}

    void insert(int key) {
        int max_iterations = size;
        while (max_iterations--) {
            int h1 = hash1(key);
            if (table1[h1] == -1) {
                table1[h1] = key;
                return;
            }
            std::swap(key, table1[h1]);

            int h2 = hash2(key);
            if (table2[h2] == -1) {
                table2[h2] = key;
                return;
            }
            std::swap(key, table2[h2]);
        }

        regenerateHashFunctions();
        insert(key);
    }

    void remove(int key) {
        int h1 = hash1(key);
        if (table1[h1] == key) {
            table1[h1] = -1;
            return;
        }

        int h2 = hash2(key);
        if (table2[h2] == key) {
            table2[h2] = -1;
            return;
        }
    }

    bool search(int key) {
        return table1[hash1(key)] == key || table2[hash2(key)] == key;
    }

    void scan() {
        for (const auto& value : table1) {
            if (value != -1) {
                std::cout << value << " ";
            }
        }
        for (const auto& value : table2) {
            if (value != -1) {
                std::cout << value << " ";
            }
        }
        std::cout << std::endl;
    }

    void print() {
        std::cout << "Table 1:" << std::endl;
        for (const auto& value : table1) {
            std::cout << value << " ";
        }
        std::cout << std::endl;

        std::cout << "Table 2:" << std::endl;
        for (const auto& value : table2) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector<int> table1, table2;
    size_t size;
    int seed1 = 42, seed2 = 97;

    int hash1(int key) {
        std::hash<int> h;
        return (h(key) ^ seed1) % size;
    }

    int hash2(int key) {
        std::hash<int> h;
        return (h(key) ^ seed2) % size;
    }

    void regenerateHashFunctions() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);

        seed1 = dis(gen);
        seed2 = dis(gen);
    }
};
