#include <iostream>

#include "sitarski-hat.hpp"

using namespace std;

SitarskiHat::SitarskiHat(): dataBlockSize(2), logDbs(1), size(0)
{
	name = "hat";
	cap = dataBlockSize << logDbs;
	dataBlocks = new int*[dataBlockSize];
	for (int i=0;i<dataBlockSize;i++)
		dataBlocks[i] = new int[dataBlockSize];
}

SitarskiHat::~SitarskiHat()
{
	for (int i=0;i<dataBlockSize;i++)
		delete[] dataBlocks[i];
	delete[] dataBlocks;
}

void SitarskiHat::resize(int newDataBlockSize)
{
	int **newDataBlocks = new int*[newDataBlockSize];
	for (int i=0;i<newDataBlockSize;i++)
		newDataBlocks[i] = new int[newDataBlockSize];
	int ni = 0, nj = 0;
	for (int i=0;i<dataBlockSize;i++)
	{
		for (int j=0;j<dataBlockSize;j++)
		{
			newDataBlocks[ni][nj++] = dataBlocks[i][j];
			if (nj == newDataBlockSize) 
			{
				nj = 0;
				ni++;
			}
		}
		delete[] dataBlocks[i];
	}
	delete[] dataBlocks;
	dataBlocks = newDataBlocks;
	dataBlockSize = newDataBlockSize;
	logDbs++;
	cap = dataBlockSize << logDbs;
}

void SitarskiHat::append(int n)
{
	if (size == cap)
		resize(dataBlockSize << 1);
	dataBlocks[size >> logDbs][size & ((1 << logDbs) - 1)] = n;
	size++;
}

int SitarskiHat::get(int pos)
{
	if (pos < 0 || pos >= size)
		return 0;
	return dataBlocks[pos >> logDbs][pos & ((1 << logDbs) - 1)];
}

void SitarskiHat::print()
{
	for (int i=0;i<size;i++)
		cout << (*this).get(i) << " ";
	cout << endl;
}

void SitarskiHat::printDes()
{
	cout << "DBS: " << dataBlockSize << endl;
	cout << "logDBS: " << logDbs << endl;
	cout << "size: " << size << endl;
	cout << "cap: " << cap << endl;
}


const std::string &SitarskiHat::getName()
{
	return name;
}

void SitarskiHat::clear()
{
	// Free everything
	for (int i=0;i<dataBlockSize;i++)
		delete[] dataBlocks[i];
	delete[] dataBlocks;
	// Reset fields
	dataBlockSize = 2;
	logDbs = 1;
	size = 0;
	cap = dataBlockSize << logDbs;
	dataBlocks = new int*[dataBlockSize];
	for (int i=0;i<dataBlockSize;i++)
		dataBlocks[i] = new int[dataBlockSize];
}
