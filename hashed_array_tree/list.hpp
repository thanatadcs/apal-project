#ifndef LIST_H
# define LIST_H

#include <string>

class List
{
	public:
		virtual void append(int n) = 0;
		virtual int get(int pos) = 0;
		virtual const std::string &getName() = 0;
		virtual void clear() = 0;
};

#endif
