#include "../ChainingHashTable.cpp"
#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int getRandInt(int lo, int hi)
{

	int range = hi - lo + 1;
	int randomInt = rand() % range + lo;
	
	return randomInt;
}

uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

void insertTime(ChainingHashTable<int, int> &t, int size, vector<int> &v)
{
	ofstream outfile;
	outfile.open("chaining_insert_time.txt", ios::out | ios::trunc);
	uint64_t start, end, time_elapsed;
	int r;
	for (int i=0;i<size;i++)
	{
		r = getRandInt(0, 100 * size);
		v.push_back(r);
		start = rdtsc();
		t.insert(r, r);
		end = rdtsc();
		time_elapsed = end - start;
		outfile << i + 1 << "," << time_elapsed << endl;
	}
	outfile.close();
}

void getTime(ChainingHashTable<int, int> &t, int size, vector<int> &v)
{
	ofstream outfile;
	outfile.open("chaining_get_time.txt", ios::out | ios::trunc);
	uint64_t start, end, time_elapsed;
	// Get elements
	for (int i=0;i<v.size();i++)
	{
		start = rdtsc();
		t.get(v.at(i));
		end = rdtsc();
		time_elapsed = end - start;
		outfile << i + 1 << "," << time_elapsed << endl;
	}
	outfile.close();
}


void scanTime(ChainingHashTable<int, int> &t, int n, vector<int> &v)
{
	ofstream outfile;
	outfile.open("chaining_scan_time.txt", ios::out | ios::trunc);
	uint64_t start, end, time_elapsed;
	// Get elements
	for (int iter=0;iter<n;iter++)
	{
		start = rdtsc();
		for (int i=0;i<v.size();i++)
			t.get(v.at(i));
		end = rdtsc();
		time_elapsed = end - start;
		outfile << time_elapsed << endl;
	}
	outfile.close();
}

void overallTime(int size, int iteration)
{
	ofstream outfile;
	outfile.open("chaining_overall_time.txt", ios::out | ios::trunc);
	uint64_t start, end, time_elapsed;
	// Get elements
	int r;
	ChainingHashTable<int, int> *t;
	for (int iter=0;iter<iteration;iter++)
	{
		t = new ChainingHashTable<int, int>;
		start = rdtsc();
		for (int i=0;i<size;i++)
		{
			r = getRandInt(0, 100 * size);
			(*t).insert(r, r);
		}
		end = rdtsc();
		time_elapsed = end - start;
		outfile << time_elapsed << endl;
		delete t;
	}
	outfile.close();
}


int main() {

	srand(time(nullptr));
	vector<int> v;
	int size = 1000;
	int iter = 1000;
	ChainingHashTable<int, int> t;
	//insertTime(t, size, v);
	//getTime(t, size, v);
	//scanTime(t, iter, v);
	overallTime(size, iter);	
}
