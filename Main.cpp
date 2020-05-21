#include <iostream>
#include "ArrayList.hpp"
#include "ArrayListTest.hpp"
#include "ArrayList_NewTest.hpp"
#include "CircularListWithHeader.hpp"
#include <vector>
using namespace std;

ArrayListTest t;
ArrayList_NewTest tt;
int main()
{
	CircularListWithHeader<int> list;
	for (int i = 0; i < 100; ++i)
		list.push_back(i + 1);
	cout << list << endl;
	return 0;
}
