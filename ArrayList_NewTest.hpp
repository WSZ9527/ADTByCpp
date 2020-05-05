#pragma once
#include "ArrayList_New.hpp"
#include <iostream>
#include <vector>
using namespace std;
struct ArrayList_NewTest
{
	void tErase()
	{
		ArrayList_New<int> arr;
		for (int i = 0; i < 20; ++i)
		{
			arr.push_back(i + 1);
		}
		cout << arr << endl;
		for (int i = 0; i < 20; ++i)
		{
			arr.erase(i%arr.size());
			cout << arr << endl;
		}

	}

	void tPopBack()
	{
		ArrayList_New<int> arr;
		for (int i = 0; i < 20; ++i)
		{
			arr.push_back(i + 1);
		}

		cout << arr << endl;

		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;
		arr.pop_back();
		cout << arr << endl;

		for (int i = 0; i < 11; ++i)
		{
			arr.push_back(i + 1);
		}
		cout << arr << endl;
		for (int i = 0; i < 10; ++i)
		{
			arr.pop_back();
			cout << arr << endl;
		}
	}

	void tRemoveRange()
	{
		ArrayList_New<int> arr;
		for (int i = 0; i < 20; ++i)
		{
			arr.push_back(i + 1);
		}

		cout << arr << endl;

		arr.removeRange(arr.begin(), arr.end());
		cout << arr << endl;
	}
};