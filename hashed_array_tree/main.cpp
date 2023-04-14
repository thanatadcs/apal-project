#include <iostream>

#include "list.hpp"
#include "sitarski-hat.hpp"
#include "brodnik-hat-a-brd.hpp"
#include "brodnik-hat-b.hpp"

using namespace std;

int main(void)
{
	SitarskiHat sh;
	BrodnikHatA bha;
	BrodnikHatB bhb;
	//for (int i=0;i<100;i++)
	//	bhb.append(i);
	//bhb.print();
	//for (int i=0;i<51;i++)
	//	cout << bhb.get(i) << endl;
	for (int i=0;i<100;i++)
		bhb.append(i);
	for (int i=0;i<100;i++)
		cout << bhb.get(i) << " ";
}
