#include "../CuckooHashingHashTable.hpp"
#include <iostream>

uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

int main() {
    int size = 10000000;

    // Cuckoo Hash Table
    CuckooHashTable table1(size);

    // Measuring inserting 1 element
    uint64_t start1 = rdtsc();

    table1.insert(1);

    uint64_t end1 = rdtsc();
    std::cout << "Elapsed clock cycles (insert(1)): " << end1 - start1 << std::endl;

    // Measuring deleting 1 element
    uint64_t start2 = rdtsc();

    table1.remove(1);

    uint64_t end2 = rdtsc();
    std::cout << "Elapsed clock cycles (remove(1)): " << end2 - start2 << std::endl;

    unsigned int current_capacity = size;

    // Measuring filling all elements
    uint64_t start3 = rdtsc();

    for (int i = 0; i < current_capacity; i++) {
        table1.insert(i);
    }

    uint64_t end3 = rdtsc();
    std::cout << "Elapsed clock cycles (" << size << " of inserts): " << end3 - start3 << std::endl;



    unsigned long middle_index = (size / 2) - 1;

    // Measuring get all elements
    uint64_t start4 = rdtsc();

    for (int i = 0; i < size; i++) {
        table1.search(i);
    }

    uint64_t end4 = rdtsc();
    std::cout << "Elapsed clock cycles (get()): " << end4 - start4 << std::endl;

    // Measuring scan() with "full" data structure
    uint64_t start5 = rdtsc();

    table1.scan();

    uint64_t end5 = rdtsc();
    std::cout << "Elapsed clock cycles (scan() of size: " << size << "): " << end5 - start5 << std::endl;


    // Measuring deleting all elemeent
    uint64_t start6 = rdtsc();

    for (int i = 0; i < size; i++) {
        table1.remove(i);
    }

    uint64_t end6 = rdtsc();
    std::cout << "Elapsed clock cycles (delete() of size: " << size << "): " << end6 - start6 << std::endl;


    return 0;
}