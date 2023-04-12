#ifndef HAT_H
# define HAT_H

#include "list.h"

class Hat: public List
{
	private:
		int **dataBlocks;
		int dataBlockSize;
		int logDbs;
		int	size;
		int	cap;
		std::string name;

		void resize(int newSize);


	public:
		Hat();
		~Hat();

		void append(int n);
		int get(int pos);
		void print();
		void printDes();
		const std::string &getName();
		void clear();
};

#endif
