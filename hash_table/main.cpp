#include <iostream>
#include <string>
#include "ChainingHashTable.cpp"
#include "OpenAddressingHashTable.cpp"


int main() {
    ChainingHashTable<int, std::string> hash_table(5, 0.75);
    hash_table.insert(1, "one");
    hash_table.insert(2, "two");
    hash_table.insert(3, "three");
    hash_table.insert(6, "six");

    // Attempt to insert a key that collides with an existing key
    hash_table.insert(11, "eleven");
    hash_table.insert(16, "sixteen");

    hash_table.print();

    std::cout << "-----------------------------------------------------------------\n";
    // --------------------------------------------------------------------------

    OpenAddressingHashTable<int, int> hash_table_two(2, 0.5);

    // Insert two key-value pairs with the same hash value
    hash_table_two.insert(1, 1);
    hash_table_two.insert(3, 3);

    // Check that both key-value pairs are present in the hash table
    if (!hash_table_two.contains(1)) {
        std::cerr << "Error: key 1 not found in hash table\n";
        return 1;
    }
    if (!hash_table_two.contains(3)) {
        std::cerr << "Error: key 3 not found in hash table\n";
        return 1;
    }

    // Insert another key-value pair that has the same hash value as the first two
    hash_table_two.insert(5, 5);

    // Check that all three key-value pairs are present in the hash table
    if (!hash_table_two.contains(1)) {
        std::cerr << "Error: key 1 not found in hash table\n";
        return 1;
    }
    if (!hash_table_two.contains(3)) {
        std::cerr << "Error: key 3 not found in hash table\n";
        return 1;
    }
    if (!hash_table_two.contains(5)) {
        std::cerr << "Error: key 5 not found in hash table\n";
        return 1;
    }

    // Remove the second key-value pair and check that it is no longer present in the hash table
    if (!hash_table_two.remove(3)) {
        std::cerr << "Error: failed to remove key 3 from hash table\n";
        return 1;
    }
    if (hash_table_two.contains(3)) {
        std::cerr << "Error: key 3 still found in hash table after removal\n";
        return 1;
    }

    // Test the operator[] method
    hash_table_two[1] = 2;
    if (hash_table_two[1] != 2) {
        std::cerr << "Error: operator[] method not working correctly\n";
        return 1;
    }

    std::cout << "All tests passed!\n";

    hash_table_two.print();

    return 0;
}