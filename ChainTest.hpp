#pragma once
#include "Chain.hpp"
#include <iostream>
using namespace std;
class ChainTest
{
public:
	static void t01()
	{
		Chain<int> c;
		for (int i = 0; i < 100; ++i)
			c.push_back(i + 1);
		for (auto& e : c)
			cout << e.m_element << " ";
		cout << endl;
		c.clear();
		cout << c.size() << endl;
	}

	static void tErase()
	{
		Chain<char> c;
		c.push_back('a');
		c.push_back('b');
		c.push_back('c');
		c.push_back('d');
		c.push_back('e');
		for (auto& e : c)
			cout << e.m_element << " ";
		cout << endl;

		c.insert(0, 'f');
		for (auto& e : c)
			cout << e.m_element << " ";
		cout << endl;

		c.insert(3, 'g');
		for (auto& e : c)
			cout << e.m_element << " ";
		cout << endl;

		c.insert(7,'h');
		for (auto& e : c)
			cout << e.m_element << " ";
		cout << endl;
		
		c.erase(0);
		for (auto& e : c)
			cout << e.m_element << " ";
		cout << endl;

		c.erase(6);
		for (auto& e : c)
			cout << e.m_element << " ";
		cout << endl;
	}

	static void tSetSize() 
	{
		Chain<char> c;
		c.push_back('a');
		c.push_back('b');
		c.push_back('c');
		c.push_back('d');
		c.push_back('e');
		for (auto& e : c)
			cout << e.m_element << " ";
		cout << endl;
		c.setSize(3);
		for (auto& e : c)
			cout << e.m_element << " ";
		cout << endl;
		c.setSize(0);
		for (auto& e : c)
			cout << e.m_element << " ";
	}

	static void tSet()
	{
		Chain<char> c;
		c.push_back('a');
		c.push_back('b');
		c.push_back('c');
		c.push_back('d');
		c.push_back('e');
		for (auto& e : c)
			cout << e.m_element << " ";
		cout << endl;

		c.set(0, 'p');
		for (auto& e : c)
			cout << e.m_element << " ";
		cout << endl;
		c.set(4, 'p');
		for (auto& e : c)
			cout << e.m_element << " ";
		cout << endl;
	}

	static void tRemoveRange()
	{
		Chain<int> c;
		
		for (int i = 1; i <= 10; ++i)
			c.push_back(i);
		c.removeRange(1, 10);
		c.push(111);
		for (auto& e : c)
			cout << e.m_element << " ";
		
		cout << endl;
		//c.removeRange(8, 9);
		//for (auto& e : c)
		//	cout << e.m_element << " ";
		//cout << endl;
		//c.removeRange(7, 8);
		//for (auto& e : c)
		//	cout << e.m_element << " ";
		//cout << endl;
		//c.removeRange(6, 7);
		//for (auto& e : c)
		//	cout << e.m_element << " ";
		//cout << endl;
		//c.removeRange(5, 6);
		//for (auto& e : c)
		//	cout << e.m_element << " ";
		//cout << endl;
		//c.removeRange(4, 5);
		//for (auto& e : c)
		//	cout << e.m_element << " ";
		//cout << endl;
		//c.removeRange(3, 4);
		//for (auto& e : c)
		//	cout << e.m_element << " ";
		//cout << endl;
		//c.removeRange(2, 3);
		//for (auto& e : c)
		//	cout << e.m_element << " ";
		//cout << endl;
		//c.removeRange(1, 2);
		//for (auto& e : c)
		//	cout << e.m_element << " ";
		//cout << endl;
		//c.removeRange(0, 1);
		//for (auto& e : c)
		//	cout << e.m_element << " ";
		//cout << endl;
	}

	static void tLastIndexof()
	{
		Chain<int> c;

		for (int i = 1; i <= 10; ++i)
			c.push_back(i);

		for (int i = 0; i < 10; ++i)
		{
			cout << c[i] << " ";
		}
		c.removeRange(0, 10);
		c.push_back(1);
		c.push_back(2);
		c.push_back(3);
		c.push_back(1);
		c.push_back(3);
		c.push_back(2);
		c.push_back(3);
		c.push_back(3);
		cout << endl;
		cout << c.lastIndexOf(3) << endl;
		cout << c.lastIndexOf(1) << endl;
		cout << c.lastIndexOf(2) << endl;
		cout << endl;
	}

	static void tLeftShift()
	{
		Chain<int> c;

		for (int i = 1; i <= 10; ++i)
			c.push_back(i);
		c.leftShift(10);
		for (auto& e : c)
			cout << e.m_element << " ";
	}

	static void tReverse()
	{
		Chain<int> c;

		for (int i = 1; i <= 100; ++i)
			c.push_back(i);
		c.reverse();
		for (auto& e : c)
			cout << e.m_element << " ";
	}

	//1 2 3 4 5 6 7，利用成员方法进行逆序
	template<class T>
	static void myreverse(Chain<T>& _chain)
	{
		//链表长度大于1才有意义
		if (_chain.size() > 1)
		{
			auto sz = _chain.size();
			for (int i = 1; i < sz; ++i)
			{
				auto first = _chain.get(i);
				_chain.removeRange(i, i+1);
				_chain.push(first);
			}
		}
	}

	static void tMyreverse()
	{
		Chain<int> c;

		for (int i = 1; i <= 100; ++i)
			c.push_back(i);
		myreverse(c);
		for (auto& e : c)
			cout << e.m_element << " ";
	}
};