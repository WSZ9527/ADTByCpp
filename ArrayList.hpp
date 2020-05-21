#pragma once
#include "linearList.hpp"
#include "IllegalParamterValue.hpp"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
template <class T>
class ArrayList : public LinearList<T>
{
protected:
	enum{DEFAULT_CAPATITY = 10, MIN_INCREASE = 1};
	T* m_element;
	//一维数组
	int m_arrayLength;
	//一维数组的容量
	int m_listsize;
	//线性表的元素个数
	int m_increase;
	//线性表长度增长因子，默认为0，如果为0，扩容时容量翻倍，否则每次扩容增长因子个内存空间
public:
	//随机访问迭代器类
	class _ArrayList_Const_Iterator
	{
	public:
		using iterator_concept = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = const value_type*;
		using reference = const value_type&;
		inline _ArrayList_Const_Iterator(pointer _position)
			:m_position(_position) {}

		inline reference operator*() const { return *this->m_position; }

		inline pointer operator->() const { return this->m_position; }

		//迭代器向后，前置++
		inline _ArrayList_Const_Iterator& operator++()
		{
			++this->m_position;
			return *this;
		}
		//迭代器向后，后置++
		inline _ArrayList_Const_Iterator operator++(int)
		{
			Iterator old = *this;
			++this->m_position;
			return old;
		}

		//迭代器向前，前置--
		inline _ArrayList_Const_Iterator& operator--()
		{
			--this->m_position;
			return *this;
		}
		//迭代器向前，后置--
		inline _ArrayList_Const_Iterator operator--(int)
		{
			Iterator old = *this;
			--this->m_position;
			return old;
		}
		
		//重载-操作运算符，支持向前随机迭代
		_ArrayList_Const_Iterator operator-(int _length) const
		{
			if (_length < 0)
			{
				std::ostringstream os;
				os << "_length = " << _length << " must be >= 0";
				throw IllegalParamterValue(os);
			}

			return _ArrayList_Const_Iterator(this->m_position - _length);
		}

		//重载+操作运算符，支持向后随机迭代
		_ArrayList_Const_Iterator operator+(int _length) const
		{
			if (_length < 0)
			{
				std::ostringstream os;
				os << "_length = " << _length << " must be >= 0";
				throw IllegalParamterValue(os);
			}

			return _ArrayList_Const_Iterator(this->m_position + _length);
		}

		//重载-操作运算符，计算2迭代器之间的距离
		inline difference_type operator-(const _ArrayList_Const_Iterator& _it) const
		{
			return ((int)(this->m_position - _it.m_position));
		}

		//重载数组操作符，支持随机访问
		reference operator[](int _index) const
		{
			if (_index < 0)
			{
				std::ostringstream os;
				os << "_index = " << _index << " _index must be >= 0";
				throw IllegalParamterValue(os);
			}
			return this->m_position[_index];
		}

		//重载<操作运算符
		inline bool operator<(const _ArrayList_Const_Iterator& _it) const { return this->m_position < _it.m_position; }

		//重载>操作运算符
		inline bool operator>(const _ArrayList_Const_Iterator& _it) const { return this->m_position > _it.m_position; }


		//重载=<操作运算符
		inline bool operator<=(const _ArrayList_Const_Iterator& _it) const { return this->m_position <= _it.m_position; }

		//重载>=操作运算符
		inline bool operator>=(const _ArrayList_Const_Iterator& _it) const { return this->m_position >= _it.m_position; }

		//重载!=操作运算符
		inline bool operator!=(const _ArrayList_Const_Iterator& _it)const { return this->m_position != _it.m_position; }

		//重载==操作运算符
		inline bool operator==(const _ArrayList_Const_Iterator& _it)const { return this->m_position == _it.m_position; }

		protected:
			pointer m_position;
		};

	class _ArrayList_Iterator : _ArrayList_Const_Iterator
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = value_type*;
		using reference = value_type&;
		using _Mybase = _ArrayList_Const_Iterator;
		inline _ArrayList_Iterator(T* _position)
			:_Mybase(_position) {}
		inline reference operator*() const { return const_cast<reference>(_Mybase::operator*()); }

		inline pointer operator->() const { return const_cast<pointer>(_Mybase::operator->()); }
	
		void swap(_ArrayList_Iterator& _right) const
		{
			auto tmpIt = _right;
			_right->m_position = this->m_position;
			this->m_position = tmpIt.m_position;
		}

		//迭代器向后，前置++
		inline _ArrayList_Iterator& operator++()
		{
			_Mybase::operator++();
			return *this;
		}
		//迭代器向后，后置++
		inline _ArrayList_Iterator operator++(int)
		{
			Iterator old = *this;
			_Mybase::operator++();
			return old;
		}

		//迭代器向前，前置--
		inline _ArrayList_Iterator& operator--()
		{
			_Mybase::operator--();
			return *this;
		}
		//迭代器向前，后置--
		inline _ArrayList_Iterator operator--(int)
		{
			auto old = *this;
			_Mybase::operator--();
			return old;
		}

		//重载-操作运算符，支持向前随机迭代
		_ArrayList_Iterator operator-(int _length) const
		{
			_Mybase::operator-(_length);
			return *this;
		}

		//重载+操作运算符，支持向后随机迭代
		_ArrayList_Iterator operator+(int _length) const
		{
			_Mybase::operator+(_length);
			return *this;
		}

		//重载-操作运算符，计算2迭代器之间的距离
		inline difference_type operator-(const _ArrayList_Iterator& _it) const
		{
			return _Mybase::operator-(_it);
		}

		//重载数组操作符，支持随机访问
		reference operator[](int _index) const
		{
			return const_cast<reference>(_Mybase::operator [](_index));
		}

		//重载<操作运算符
		inline bool operator<(const _ArrayList_Iterator& _it) const
		{  
			return _Mybase::operator<(_it);
		}

		//重载>操作运算符
		inline bool operator>(const _ArrayList_Iterator& _it) const { return _Mybase::operator>(_it); }


		//重载=<操作运算符
		inline bool operator<=(const _ArrayList_Iterator& _it) const { return _Mybase::operator<=(_it); }

		//重载>=操作运算符
		inline bool operator>=(const _ArrayList_Iterator& _it) const { return _Mybase::operator>=(_it); }

		//重载!=操作运算符
		inline bool operator!=(const _ArrayList_Iterator& _it)const { return _Mybase::operator!=(_it); }

		//重载==操作运算符
		inline bool operator==(const _ArrayList_Iterator& _it)const { return _Mybase::operator==(_it); }
	};

	using Iterator = typename ArrayList<T>::_ArrayList_Iterator;
	using Const_Iterator = typename ArrayList<T>::_ArrayList_Const_Iterator;
	ArrayList()
		:m_arrayLength(DEFAULT_CAPATITY), m_increase(0)
	{
		this->m_element = new T[this->m_arrayLength];
		this->m_listsize = 0;
	}

	ArrayList(int _initCapacity, int _increase = 0)
	{
		if (_initCapacity < 1)
		{
			std::ostringstream os;
			os << "_initCapacity = " << _initCapacity << " must be >= 1";
			throw IllegalParamterValue(os);
		}
		

		_initCapacity < this->DEFAULT_CAPATITY ? this->m_arrayLength = this->DEFAULT_CAPATITY : this->m_arrayLength = _initCapacity;
		_increase > this->MIN_INCREASE ? this->m_increase = _increase : this->m_increase = 0;
		this->m_element = new T[this->m_arrayLength];
		this->m_listsize = 0;
	}

	ArrayList(const ArrayList<T>& _list)
	{
		this->m_arrayLength = _list.m_arrayLength;
		this->m_listsize = _list.m_listsize;
		this->m_element = new T[this->m_arrayLength];
		this->m_increase = _list.m_increase;
		std::copy(_list.m_element, _list.m_element + _list.m_listsize, this->m_element);
	}

	ArrayList<T>& operator=(const ArrayList<T>& _list)
	{
		if (&_list == this)
			return *this;
		delete[] this->m_element;
		this->m_arrayLength = _list.m_arrayLength;
		this->m_listsize = _list.m_listsize;
		this->m_element = new T[this->m_arrayLength];
		this->m_increase = _list.m_increase;
		std::copy(_list.m_element, _list.m_element + _list.m_listsize, this->m_element);
	}

	friend std::ostream& operator<<(std::ostream& _out, const ArrayList<T>& _list)
	{
		_out << "capacity = " << _list.capacity() << " list size = " << _list.size() << " ";
		for (auto it = _list.begin(), it_end = _list.end(); it != it_end; ++it)
		{
			_out << *it << " ";
		}

		return _out;
	}

	friend void operator>>(const T& _element, ArrayList<T>& _list)
	{
		_list.push_back(_element);
	}

	friend std::istream& operator>>(std::istream& _in, ArrayList<T>& _list)
	{
		T t;
		_in >> t;
		_list.push_back(t);
		return _in;
	}

	//重载等号操作符
	virtual bool operator==(const ArrayList<T>& _list) const
	{
		return this->equal(_list);
	}

	//重载不等号操作符
	virtual bool operator!=(const ArrayList<T>& _list) const
	{
		if (this->m_listsize != _list.m_listsize || this->m_listsize == 0)
			return true;
		for (int i = 0; i < this->m_listsize; ++i)
		{
			if (this->m_element[i] != _list.m_element[i])
				return true;
		}

		return false;
	}

	//重载小于符号
	virtual bool operator<(const ArrayList<T>& _list) const
	{
		if (_list.m_listsize == 0)
			return false;
		else if (this->m_listsize == 0)
			return true;

		for (int i = 0; i < this->m_listsize && i < _list.m_listsize; ++i)
		{
			if (this->m_element[i] > _list.m_element[i])
				return false;
		}

		return true;
	}

	//重载数组符号，索引无效抛出异常
	virtual T& operator[](int _index)
	{
		return this->get(_index);
	}

	//重载数组符号，索引无效抛出异常 const
	virtual const T& operator[](int _index) const
	{
		return this->get(_index);
	}


	virtual ~ArrayList()
	{
		delete[] this->m_element;
	}

	//判断线性表是否为空
	virtual bool empty() const override
	{
		return this->m_listsize == 0;
	}

	//获取线性表大小
	virtual int size() const override
	{
		return this->m_listsize;
	}

	//根据索引获取线性表元素，索引无效抛出异常
	virtual T& get(int _index) override
	{
		this->checkIndex(_index);
		return this->m_element[_index];
	}

	//返回线性表元素个数 const
	virtual const T& get(int _index) const
	{
		this->checkIndex(_index);
		return this->m_element[_index];
	}

	//根据元素获取该元素在线性表中的索引，没有找到返回-1
	virtual int indexOf(const T& _element) const override
	{
		int index =  (int)(std::find(this->m_element, this->m_element + this->m_listsize, _element) - this->m_element);
		if (index == this->m_listsize)
			return -1;
		else
			return index;
	}

	//根据索引删除线性表中的元素，索引无效抛出异常
	virtual void erase(int _index) override
	{
		this->checkIndex(_index);
		std::copy(this->m_element + _index + 1, this->m_element + this->m_listsize, this->m_element + _index);
		this->m_element[--this->m_listsize].~T();
	}

	//根据索引在线性表中插入元素，索引无效抛出异常
	virtual void insert(int _index, const T& _element) override
	{
		if (_index < 0 || _index > this->m_listsize)
		{
			std::ostringstream os;
			os << "_index = " << _index << " size = " << this->m_listsize;
			throw IllegalParamterValue(os);
		}
		
		//判断是否需要扩容
		if (this->m_listsize == this->m_arrayLength)
			this->changeLength(this->m_element, this->m_arrayLength, (this->m_increase == 0 ? this->m_arrayLength * 2 : this->m_arrayLength + this->m_increase));
		std::copy_backward(this->m_element + _index, this->m_element + this->m_listsize, this->m_element + this->m_listsize + 1);
		this->m_element[_index] = _element;
		++this->m_listsize;
	}

	//获取线性表在内存中分配的大小
	virtual inline int capacity() const { return this->m_arrayLength; }
	
	//将元素插入线性表的右端
	virtual void push_back(const T& _element)
	{
		//判断是否需要扩容
		if (this->m_listsize == this->m_arrayLength)
			this->changeLength(this->m_element, this->m_arrayLength, (this->m_increase == 0 ? this->m_arrayLength * 2 : this->m_arrayLength + this->m_increase));
		this->m_element[this->m_listsize++] = _element;
	}

	//删除线性表右端元素
	virtual void pop_back()
	{
		if (this->m_listsize == 0)
			throw IllegalParamterValue("list size = 0, size must be > 0");
		this->m_element[this->m_listsize - 1].~T();	
		--this->m_listsize;
	}

	//交换线性表
	virtual void swap(ArrayList<T>& _list)
	{
		//备份
		auto tmpLength = this->m_arrayLength;
		auto tmpListSize = this->m_listsize;
		auto tmpIncrease = this->m_increase;
		auto temElement = this->m_element;
		
		//开始交换
		this->m_arrayLength = _list.m_arrayLength;
		this->m_listsize = _list.m_listsize;
		this->m_increase = _list.m_increase;
		this->m_element = _list.m_element;

		_list.m_arrayLength = tmpLength;
		_list.m_listsize = tmpListSize;
		_list.m_increase = tmpIncrease;
		_list.m_element = temElement;

	}

	//改变容量，用比较大的_capacity
	virtual void reserve(int _capacity)
	{
		if (_capacity < 1)
		{
			std::ostringstream os;
			os << "_capacity = " << _capacity << " must be >= 1";
			throw IllegalParamterValue(os);
		}
		else if (_capacity < this->m_arrayLength)
			return;

		changeLength(this->m_element, this->m_arrayLength, _capacity);
	}

	//根据索引修改线性表元素，如果索引不在范围，则抛出异常
	virtual T& set(int _index, const T& _element)
	{
		checkIndex(_index);
		return (this->m_element[_index] = _element);
	}

	//清空线性表
	virtual void clear()
	{
		for (int i = 0; i < this->m_listsize; ++i)
		{
			this->m_element[i].~T();
		}

		this->m_listsize = 0;
	}

	//删除线性表内一个范围的元素，根据首尾迭代器
	virtual void removeRange(Iterator _begin, Iterator _end)
	{
		if (_end < _begin)
			throw IllegalParamterValue("_end must be > _begin");
		if (_begin < this->begin() || _begin > this->end() || _end > this->end())
			throw IllegalParamterValue("_end Iterator must be in the list range");
		
		if ((_end - _begin) == this->m_listsize)
		{
			while (_begin != _end)
			{
				(*_begin++).~T();
			}

			this->m_listsize = 0;
		}
		else
		{		
			auto it_end = this->end();
			//线性表向左边移动
			std::copy(_end, it_end, _begin);
			auto removeLength = _end - _begin;
			//迭代析构线性表元素
			while (_end != it_end)
			{
				(*_end++).~T();
			}

			this->m_listsize -= removeLength;
		}
	}

	//删除线性表内一个范围的元素，根据首迭代器
	virtual void removeRange(Iterator _begin)
	{
		if(this->begin() > _begin)
			throw IllegalParamterValue("_begin must be >= begin Iterator");
		if(this->end() < _begin)
			throw IllegalParamterValue("_begin must be < end Iterator");

		//迭代析构线性表元素
		auto it_end = this->end();
		auto removeLength = it_end - _begin;
		while (_begin != it_end)
		{
			(*_begin++).~T();
		}

		this->m_listsize -= removeLength;
	}

	//返回指定元素最后一次出现在线性表中的索引
	virtual int lastIndexOf(const T& _element) const
	{
		int lastIndex = -1;
		if (this->m_listsize == 0)
			return lastIndex;

		for (int i = 0; i < this->m_listsize; ++i)
		{
			if (this->m_element[i] == _element)
				lastIndex = i;
		}

		return lastIndex;
	}

	//原地颠倒顺序
	virtual void reverse()
	{
		//std::reverse()
		if (this->m_listsize == 0)
			throw IllegalParamterValue("list is empty");
		auto it_begin = this->begin();
		auto it_end = this->end();
		//1 2 3 4 5 s
		for (;it_begin != it_end && it_begin != --it_end;++it_begin)
		{
			this->iterSwap(it_begin, it_end);
		}
	}
	
	//原地颠倒顺序,友元函数
	friend void reverse(Iterator& _firstIter, Iterator& _lastIter)
	{
		if (_lastIter <= _firstIter)
			throw IllegalParamterValue("_lastIter must be > _firstIter");
		if (_lastIter == _firstIter)
			return;

		T t;
		for (; _firstIter != _lastIter && _firstIter != --_lastIter; ++_firstIter)
		{
			t = *_firstIter;
			*_firstIter = *_lastIter;
			*_lastIter = t;
		}
	}

	//线性表向左移动xx位
	virtual void leftShift(int _shift)
	{
		if (_shift <= 0 || _shift >= m_listsize)
		{
			std::ostringstream os;
			os << "_shift = " << _shift << " must be < list size = " << this->m_listsize << " and > 0";
			throw IllegalParamterValue(os);
		}

		for (auto it_begin = this->begin() + _shift, it_end = this->end(); it_begin != it_end; ++it_begin)
		{
			*(it_begin - _shift) = *it_begin;
		}

		for (auto it_begin = this->end() - _shift, it_end = this->end(); it_begin != it_end; ++it_begin)
		{
			(*it_begin).~T();
		}

		this->m_listsize -= _shift;
	}

	//线性循环移动
	virtual void circularShift(int _shift)
	{
		//if (m_listsize == 0)
		//	throw IllegalParamterValue("list size must be > 0");
		//_shift %= this->m_listsize;

		//if (_shift == 0)
		//{
		//	std::ostringstream os;
		//	os << "_shift  %"<< this->m_listsize << " = " << _shift << " must be != 0";
		//	throw IllegalParamterValue(os);
		//}

		if (m_listsize == 0)
			return;
		_shift %= this->m_listsize;

		if (_shift == 0)
			return;
		//逆时针移动
		if (_shift < 0)
			_shift = this->m_listsize + _shift;

		//顺时针循环移动 
		for (auto it_begin = this->begin(), it_end = this->end(); it_begin != it_end; ++it_begin)
		{
			if (it_begin == (it_end - 1))
			{
				this->iterSwap(it_begin, it_end - 1);
				break;
			}
			this->iterSwap(it_begin, it_begin + (_shift % (it_end - it_begin)));
		}
		
	}

	//将线性表的元素隔一个删除一个
	virtual void half()
	{
		if (this->m_listsize <= 1)
			return;

		auto k = this->m_listsize % 2 == 0 ? this->m_listsize / 2 : (this->m_listsize + 1) / 2;
		for (int i = 0; i < k ; ++i)
		{
			this->m_element[i] = this->m_element[i + i];
		}

		for (int i = k; i < this->m_listsize; ++i)
		{
			this->m_element[i].~T();
		}

		this->m_listsize = k;
	}

	//将线性表在内存中分配的大小裁剪为线性表大小
	virtual void trimToSize()
	{
		if (this->m_arrayLength > this->m_listsize && this->m_listsize != 0)
		{
			changeLength(this->m_element, this->m_arrayLength, this->m_listsize);
		}
	}

	//判断线性表是否相等
	virtual bool equal(const ArrayList<T>& _list) const
	{
		if (this->m_listsize != _list.m_listsize || this->m_listsize == 0)
			return false;
		for (int i = 0; i < this->m_listsize; ++i)
		{
			if (this->m_element[i] != _list.m_element[i])
				return false;
		}

		return true;
	}

	//获取首迭代器
	virtual Iterator begin() const { return Iterator(this->m_element); }

	//获取尾迭代器
	virtual Iterator end() const { return Iterator(this->m_element + this->m_listsize); }


	//获取首迭代器
	virtual Const_Iterator cbegin() const { return Const_Iterator(this->m_element); }

	//获取尾迭代器
	virtual Const_Iterator cend() const { return Const_Iterator(this->m_element + this->m_listsize); }

	//交替合并2个表的元素
	virtual ArrayList<T>& meld(const ArrayList<T>& _leftList, const ArrayList<T>& _rightList)
	{
		auto leftSize = _leftList.m_listsize;
		auto rightSize = _rightList.m_listsize;
		delete[] this->m_element;
		this->m_arrayLength = _leftList.m_arrayLength + _rightList.m_arrayLength;
		this->m_element = new T[this->m_arrayLength];
		this->m_listsize = leftSize + rightSize;
		if (this->m_listsize == 0)
			return  *this;
		if (leftSize != 0 && rightSize != 0)
		{
			if (leftSize == rightSize)
			{
				for (int i = 0; i < leftSize; ++i)
				{
					this->m_element[2*i] = _leftList[i];
					this->m_element[2*(i+1) -1] = _rightList[i];
				}
			}
			else if (leftSize < rightSize)
			{
				for (int i = 0; i < leftSize; ++i)
				{
					this->m_element[i + i] = _leftList[i];
					this->m_element[2 * (i + 1) - 1] = _rightList[i];
				}

				for (int i = 0; i < rightSize - leftSize; ++i)
				{
					this->m_element[i + 2*leftSize] = _rightList[i + leftSize];
				}
			}
			else if (leftSize > rightSize)
			{
				for (int i = 0; i < rightSize; ++i)
				{
					this->m_element[i + i] = _leftList[i]; 
					this->m_element[2 * (i + 1) - 1] = _rightList[i];
				}

				for (int i = 0; i < leftSize - rightSize; ++i)
				{
					this->m_element[i + 2*rightSize] = _leftList[i + rightSize];
				}
			}
		}
		else if (leftSize != 0)
		{
			for (int i = 0; i < leftSize; ++i)
			{
				this->m_element[i] = _leftList[i];
			}
		}
		else if(rightSize != 0)
		{
			for (int i = 0; i < rightSize; ++i)
			{
				this->m_element[i] = _rightList[i];
			}
		}

		return *this;
	}

	//合并2个有序非递减线性表
	virtual ArrayList<T>& merge(const ArrayList<T>& _leftList, const ArrayList<T>& _rightList)
	{
		auto leftSize = _leftList.m_listsize;
		auto rightSize = _rightList.m_listsize;
		delete[] this->m_element;
		this->m_arrayLength = _leftList.m_arrayLength + _rightList.m_arrayLength;
		this->m_element = new T[this->m_arrayLength];
		this->m_listsize = leftSize + rightSize;

		if (this->m_listsize == 0)
			return  *this;
		if (leftSize != 0 && rightSize != 0)
		{
			int leftIndex = 0, rightIndex = 0;
			for (int i = 0; i < this->m_listsize && leftIndex < leftSize && rightIndex < rightSize; ++i)
			{
				this->m_element[i] = _leftList[leftIndex] < _rightList[rightIndex] ? _leftList[leftIndex++] : _rightList[rightIndex++];
			}

			if (leftIndex == leftSize)
			{
				for (int i = rightIndex; i < rightSize; ++i)
				{
					this->m_element[leftSize + i] = _rightList[i];
				}
			}
			else if (rightIndex == rightSize)
			{
				for (int i = leftIndex; i < leftSize; ++i)
				{
					this->m_element[rightSize + i] = _leftList[i];
				}
			}
		}
		else if (leftSize != 0)
		{
			for (int i = 0; i < leftSize; ++i)
			{
				this->m_element[i] = _leftList[i];
			}
		}
		else if (rightSize != 0)
		{
			for (int i = 0; i < rightSize; ++i)
			{
				this->m_element[i] = _rightList[i];
			}
		}

		return *this;

	}

	//split将线性表拆分为2个表 _leftList包含索引为偶数的元素,_rightList包含其他元素
	virtual void split(ArrayList<T>& _leftList, ArrayList<T>& _rightList) const 
	{
		int i = 0;
		for (auto it = this->begin(), it_end = this->end(); it != it_end; ++it)
		{
			if (i % 2 == 0)
				_leftList.push_back(*it);
			else
				_rightList.push_back(*it);
		}
	}
	//设置线性表在内存中分配的大小
	virtual void setSize(int _capacity)
	{
		if (_capacity < 0)
		{
			std::ostringstream os;
			os << "_capacity = " << _capacity << " must be >= 0";
			throw IllegalParamterValue(os);
		}

		changeLength(this->m_element, this->m_arrayLength, _capacity);
		this->m_listsize = _capacity;
	}
protected:
	virtual void changeLength(T*& _arr, int& _oldLength, int _newLength)
	{//改变数组的长度
		if (_newLength < 0)
			throw IllegalParamterValue("_newLength must be >= 0");
		T* newArray = new T[_newLength];				//新数组
		int number = std::min(_oldLength, _newLength);	//需要复制的个数
		std::copy(_arr, _arr + number, newArray);
		delete[]_arr;									//释放旧的空间
		_arr = newArray;
		_oldLength = _newLength;
	}

	virtual void checkIndex(int _index) const
	{
		if (_index < 0 || _index >= this->m_listsize)
		{
			std::ostringstream os;
			os << "_index = " << _index << " size = " << this->m_listsize << " _index must be >= 0 and < size";
			throw IllegalParamterValue(os);
		}
	}

	virtual void iterSwap(Iterator& _leftIter, Iterator _rightIter)
	{
		std::swap(*_leftIter, *_rightIter);
	}
};
