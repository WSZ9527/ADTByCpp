#pragma once
#include "ArrayList.hpp"
#include <iostream>
#include <vector>
using namespace std;

template <class T>
void mHalf(ArrayList<T>& _list)
{
	auto listSz = _list.size();
	if (listSz <= 1)
		return;

	auto k = listSz % 2 == 0 ? listSz / 2 : (listSz + 1) / 2;
	for (int i = 0; i < k; ++i)
	{
		_list[i] = _list[i + i];
	}

	for (int i = k; i < listSz; ++i)
	{
		_list[i].~T();
	}

	_list.setSize(k);
}
struct ArrayListTest
{

	void tInsertAndErase()
	{
		ArrayList<char> arr;
		cout << arr << endl;
		arr.insert(0, 'f');
		cout << arr << endl;
		arr.insert(3, 'g');
		cout << arr << endl;
		arr.insert(7, 'h');
		cout << arr << endl;
		arr.erase('g');
		cout << arr << endl;
		arr.erase('f');
		cout << arr << endl;
	}

	void tChangeLength()
	{
		ArrayList<int> arr(100,5);
		for (int i = 0; i < 5; ++i)
			(i+1) >> arr;
		cout << arr << endl;


		for (int i = 0; i < 100; ++i)
			(i + 1) >> arr;
		cout << arr << endl;

		for (int i = 0; i < 100; ++i)
			(i + 1) >> arr;
		cout << arr << endl;

		ArrayList<int> arr_1;
		for (int i = 0; i < 5; ++i)
			(i + 1) >> arr_1;
		cout << arr_1 << endl;


		for (int i = 0; i < 100; ++i)
			(i + 1) >> arr_1;
		cout << arr_1 << endl;

		for (int i = 0; i < 100; ++i)
			(i + 1) >> arr_1;
		cout << arr_1 << endl;
	}

 	void tTrimToSize()
	{
		ArrayList<int> arr(100, 5);
		for (int i = 0; i < 5; ++i)
			(i + 1) >> arr;
		cout << arr << endl;
		arr.trimToSize();
		cout << "capacity = " << arr.capacity() << endl;
		for (int i = 0; i < 5; ++i)
			(i + 1) >> arr;
		arr.trimToSize();
		cout << "capacity = " << arr.capacity() << endl;
	}

	void tSetSize()
	{
		ArrayList<int> arr(100, 5);
		for (int i = 0; i < 100; ++i)
			i >> arr;
		arr.setSize(50);
		cout << arr;
	}

	void tEqual()
	{
		ArrayList<int> arr1, arr2(100, 5);
		arr1.push_back(4);
		arr1.push_back(5);
		arr1.push_back(6);

		arr2.push_back(6);
		arr1.push_back(4);
		arr1.push_back(5);

		cout << (arr1 == arr2) << endl;		
	}

	void tPop_back()
	{
		ArrayList<int> arr1;
		
		for (int i = 5; i < 15; ++i)
		{
			arr1.push_back(i);
		}

		while (arr1.size())
		{
			arr1.pop_back();
		}


		cout << arr1 << endl;
	}

	void tSwap()
	{
		ArrayList<int> arr1, arr2(20);

		cout << "arr1：" << arr1 << endl;

		arr2.push_back(1);
		arr2.push_back(2);
		arr2.push_back(3);
		arr2.push_back(4);
		arr2.push_back(5);
		arr2.push_back(6);

		cout << "arr2：" << arr2 << endl;
		arr2.swap(arr1);

		cout << "线性表交换过后" << endl;
		cout << "arr1：" << arr1 << endl;
		cout << "arr2：" << arr2 << endl;
	}

	void tReserve()
	{
		ArrayList<int> arr2;

		cout << "arr2：" << arr2 << endl;

		arr2.push_back(1);
		arr2.push_back(2);
		arr2.push_back(3);
		arr2.push_back(4);
		arr2.push_back(5);
		arr2.push_back(6);

		arr2.reserve(0);
	}

	void tSet()
	{
		ArrayList<int> arr2;

		cout << "arr2：" << arr2 << endl;

		arr2.push_back(1);
		arr2.push_back(2);
		arr2.push_back(3);
		arr2.push_back(4);
		arr2.push_back(5);
		arr2.push_back(6);
		cout << "arr2：" << arr2 << endl;
		auto t =  arr2.set(0, 6);
		t= arr2.set(5, 88);
		t = arr2.set(6, 100);

		cout << "arr2：" << arr2 << endl;
	}

	void tClear()
	{
		ArrayList<int> arr2;

		cout << "arr2：" << arr2 << endl;

		arr2.push_back(1);
		arr2.push_back(2);
		arr2.push_back(3);
		arr2.push_back(4);
		arr2.push_back(5);
		arr2.push_back(6);

		arr2.clear();
		cout << "arr2：" << arr2 << endl;

	}

	void tRemoveRange()
	{
		ArrayList<int> arr2;

		arr2.push_back(1);
		arr2.push_back(2);//begin
		arr2.push_back(3);
		arr2.push_back(4);//end
		arr2.push_back(5);
		arr2.push_back(6);
	
		cout << "arr2：" << arr2 << endl;
		try
		{
			//删除2-3
			arr2.removeRange(arr2.begin() + 1, arr2.begin() + 3);
			cout << "arr2：" << arr2 << endl;

			//删除最后一个元素
			arr2.removeRange(arr2.end() - 1, arr2.end());
			cout << "arr2：" << arr2 << endl;

			//删除4-结尾
			arr2.removeRange(arr2.begin()+1);
			cout << "arr2：" << arr2 << endl;

			//删除全部
			arr2.removeRange(arr2.begin(), arr2.end());
			cout << "arr2：" << arr2 << endl;

			arr2.push_back(1);
			arr2.push_back(2);//begin
			arr2.push_back(3);
			arr2.push_back(4);//end
			arr2.push_back(5);
			arr2.push_back(6);
			cout << "arr2：" << arr2 << endl;

			//删除全部
			arr2.removeRange(arr2.begin());
			cout << "arr2：" << arr2 << endl;
		}
		catch (IllegalParamterValue& e)
		{
			cout << e << endl;
		}
		
	}

	void tLastIndexOf()
	{
		ArrayList<int> arr2;

		

		arr2.push_back(4);
		arr2.push_back(3);
		arr2.push_back(6);
		arr2.push_back(1);
		arr2.push_back(2);
		arr2.push_back(6);
		arr2.push_back(4);
		arr2.push_back(5);
		arr2.push_back(3);
		arr2.push_back(6);
		arr2.push_back(2);
		arr2.push_back(3);
		cout << "arr2：" << arr2 << endl;

		cout << "5 last index = " << arr2.lastIndexOf(5) << endl;
		cout << "1 last index = " << arr2.lastIndexOf(1) << endl;
		cout << "3 last index = " << arr2.lastIndexOf(3) << endl;
		cout << "2 last index = " << arr2.lastIndexOf(2) << endl;
		cout << "6 last index = " << arr2.lastIndexOf(6) << endl;
		cout << "10 last index = " << arr2.lastIndexOf(10) << endl;
		cout << "123 last index = " << arr2.lastIndexOf(123) << endl;
	}

	void tReverse()
	{
		ArrayList<int> arr;

		for (int i = 1; i <= 10000; ++i)
			arr.push_back(i);
		cout << arr << endl;
		arr.reverse();
		cout << arr << endl;
		reverse(arr.begin(), arr.end());
		cout << arr << endl;
	}

	void tLeftShift()
	{
		ArrayList<int> arr;

		for (int i = 1; i <= 20; ++i)
			arr.push_back(i);
		cout << arr << endl;
		arr.leftShift(5);
		cout << arr << endl;
		arr.leftShift(10);
		cout << arr << endl;
		arr.leftShift(3);
		cout << arr << endl;
		arr.leftShift(2);
		cout << arr << endl;
	}

	void tCircularShift()
	{
		ArrayList<int> arr;

		for (int i = 1; i <= 20; ++i)
			arr.push_back(i);
		cout << arr << endl;
		arr.circularShift(21);
		cout << arr << endl;
		arr.circularShift(-10);
		cout << arr << endl;
		arr.circularShift(10);
		cout << arr << endl;
		arr.circularShift(2);
		cout << arr << endl;
	}

	void tHalf()
	{
		ArrayList<int> arr;

		for (int i = 1; i <= 20; ++i)
			arr.push_back(i);
		cout << arr << endl;
		mHalf(arr);
		cout << arr << endl;
		mHalf(arr);
		cout << arr << endl;
		mHalf(arr);
		cout << arr << endl;
		mHalf(arr);
		cout << arr << endl;
		mHalf(arr);
		cout << arr << endl;
		mHalf(arr);
		cout << arr << endl;
	}

	void tIter()
	{
		ArrayList<int> arr;
		arr.push_back(7);
		arr.push_back(1);
		arr.push_back(19);
		arr.push_back(30);
		arr.push_back(88);
		arr.push_back(22);
		arr.push_back(66);
		arr.push_back(99);
		cout << arr << endl;

		std::sort(arr.begin(), arr.end());

		cout << arr << endl;
	
	}

	void tMeld()
	{
		ArrayList<int> arr1,arr2,arr3;
		//arr1.push_back(1);
		//arr1.push_back(2);
		//arr1.push_back(3);
		//arr1.push_back(4);
		//arr1.push_back(5);
		//arr1.push_back(6);
		//arr1.push_back(7);
		//arr1.push_back(8);
	
		arr2.push_back(9);
		//arr2.push_back(10);
		//arr2.push_back(11);
		//arr2.push_back(12);
		arr3.meld(arr1, arr2);
		cout << arr3 << endl;
	}

	void tMerge()
	{
		ArrayList<int> arr1, arr2, arr3;
		arr1.push_back(11);
		arr1.push_back(47);
		arr1.push_back(99);
		arr1.push_back(105);
		arr1.push_back(601);
		arr1.push_back(988);
		arr1.push_back(8118);


		arr2.push_back(9);
		arr2.push_back(15);
		arr2.push_back(33);
		arr2.push_back(77);
		arr2.push_back(99);
		arr2.push_back(100);
		arr3.merge(arr1, arr2);
		cout << arr3 << endl;
	}
};
