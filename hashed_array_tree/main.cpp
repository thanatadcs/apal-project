#include <iostream>

#include "list.hpp"
#include "sitarski-hat.hpp"
#include "brodnik-hat-a-brd.hpp"
#include "brodnik-hat-b-brd.hpp"

using namespace std;

uint64_t rdtsc() {
    uint32_t lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

int main(void)
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	SitarskiHat sh;
	BrodnikHatA bha;
	BrodnikHatB bhb;
	for (int i=0;i<100;i++)
	{
		bhb.append(i);
	}
	uint64_t t1 = rdtsc();
	bhb.get(2);
    	uint64_t t2 = rdtsc();
    	uint64_t cycles = t2 - t1;
    	std::cout << "Elapsed CPU cycles: " << cycles << std::endl;
}
