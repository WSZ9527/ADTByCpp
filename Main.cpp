#include <iostream>
#include "ArrayList.hpp"
#include "ArrayListTest.hpp"
#include "ArrayList_NewTest.hpp"
#include <vector>
#include <deque>
#include "CircularArrayList.hpp"
using namespace std;

ArrayListTest t;
ArrayList_NewTest tt;
ArrayList<int> arr;
int main()
{
	using size_type = typename CircularArrayList<int>::size_type;
	int j = 0;
	CircularArrayList<int> arr;
	arr.push_back(111);
	for (int i = 0; i < 100; ++i)
		arr.insert(1, i+i);
	
	cout << arr << endl;
	return 0;
}
