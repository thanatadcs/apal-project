#include <cstdint>
#include <ctime>
#include <fstream>
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

void listAppendTime(List &list, int size)
{
	ofstream outfile;
	outfile.open(list.getName() + "_append_time.txt", ios::out | ios::trunc);
	uint64_t start, end, time_elapsed;
	// Append elements
	for (int i=0;i<size;i++)
	{
		start = rdtsc();
		list.append(i);
		end = rdtsc();
		time_elapsed = end - start;
		outfile << i + 1 << "," << time_elapsed << endl;
	}
	outfile.close();
}

void listGetTime(List &list, int size, int n)
{
	ofstream outfile;
	outfile.open(list.getName() + "_get_time.txt", ios::out | ios::trunc);
	uint64_t start, end, time_elapsed;
	// Append elements
	for (int i=0;i<size;i++)
		list.append(i);
	// Get elements
	for (int i=0;i<n;i++)
	{
		start = rdtsc();
		list.get(i);
		end = rdtsc();
		time_elapsed = end - start;
		outfile << i + 1 << "," << time_elapsed << endl;
	}
	outfile.close();
}

void listScanime(List &list, int size, int n)
{
	ofstream outfile;
	outfile.open(list.getName() + "_scan_time.txt", ios::out | ios::trunc);
	uint64_t start, end, time_elapsed;
	// Append elements
	for (int i=0;i<size;i++)
		list.append(i);
	// Scan all elements
	for (int iter=0;iter<n;iter++)
	{
		start = rdtsc();
		for (int i=0;i<size;i++)
			list.get(i);
		end = rdtsc();
		time_elapsed = end - start;
		outfile << time_elapsed << endl;
	}
	outfile.close();
}

void listOverallAppendTime(List &list, int size, int iteration)
{
	ofstream outfile;
	outfile.open(list.getName() + "_overall_append_time.txt", ios::out | ios::trunc);
	uint64_t start, end, time_elapsed;
	for (int iter=0;iter<iteration;iter++)
	{
		start = rdtsc();
		for (int i=0;i<size;i++)
			list.append(i);
		end = rdtsc();
		time_elapsed = end - start;
		outfile << time_elapsed << endl;
		list.clear();
	}
	outfile.close();
}

int main(void)
{
	SitarskiHat sh;
	BrodnikHatA bha;
	BrodnikHatB bhb;
	int size = 10000000;
	//listAppendTime(sh, size);
	listAppendTime(bha, size);
	//listAppendTime(bhb, size);
}
