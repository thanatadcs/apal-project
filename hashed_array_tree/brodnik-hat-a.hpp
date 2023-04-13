#ifndef BRODNIK_HAT_A_H 
# define BRODNIK_HAT_A_H

#include "list.hpp"

class BrodnikHatA: public List
{
	private:
		int **pointerBlock;
		int dataBlockSize;
		int pointerBlockSize;
		int	size;
		int	cap;
		std::string name;

		void resize(int newSize);


	public:
		BrodnikHatA();
		~BrodnikHatA();

		void append(int n);
		int get(int pos);
		void print();
		void printDes();
		const std::string &getName();
		void clear();
};

#endif
