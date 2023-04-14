chaining:
	g++ benchmark_chaining.cpp ../ChainingHashTable.cpp -o benchmark_chaining

open-addressing:
	g++ benchmark_open_addressing.cpp ../OpenAddressingHashTable.cpp -o benchmark_open_addressing

cuckoo:
	g++ benchmark_cuckoo_hashing.cpp ../CuckooHashingHashTable.hpp -o benchmark_cuckoo_hashing

all: chaining open-addressing cuckoo

clean:
	rm benchmark_chaining benchmark_open_addressing benchmark_cuckoo_hashing
