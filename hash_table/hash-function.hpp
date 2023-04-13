#ifndef HASH_FUNCTION_HPP
#define HASH_FUNCTION_HPP

#include <cstddef>
#include <limits>

std::size_t hash_function(int key, std::size_t table_size) {
    return key % table_size;
}


//template <typename T>
//inline int hash_function(const T& value) {
//    const std::size_t value_size = sizeof(value);
//    const char* data = reinterpret_cast<const char*>(&value);
//    unsigned int hash_value = 0;
//    for (std::size_t i = 0; i < value_size; ++i) {
//        hash_value += static_cast<unsigned char>(data[i]);
//        hash_value += (hash_value << 10);
//        hash_value ^= (hash_value >> 6);
//    }
//    hash_value += (hash_value << 3);
//    hash_value ^= (hash_value >> 11);
//    hash_value += (hash_value << 15);
//    const int max_int = std::numeric_limits<int>::max();
//    return static_cast<int>(hash_value % static_cast<unsigned int>(max_int)) ;
//}

#endif
