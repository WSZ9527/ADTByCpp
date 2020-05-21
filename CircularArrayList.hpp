#pragma once
#include <iterator>

template <class T>
class CircularArrayList
{
protected:
	enum {DEFAULT_STEP = 7};
	enum { DEFAULT_CAPATITY = 10, MIN_INCREASE = 1 };
		//公式中的步长
	int m_first;
		//线性表首元素
	int m_last;
		//线性表尾元素
	int m_step;
		//公式中的步长

	T* m_element;
	//一维数组
	int m_arrayLength;
	//一维数组的容量
	int m_listsize;
	//线性表的元素个数
	int m_increase;
	//线性表长度增长因子，默认为0，如果为0，扩容时容量翻倍，否则每次扩容增长因子个内存空间
	void createList()
	{
		this->m_element = new T[this->m_arrayLength];
		this->m_first = m_step % this->m_arrayLength;
		this->m_last = (m_step + 1) % this->m_arrayLength;
	}
public:
	using Iterator = typename CircularArrayList<T>::Iterator;
	class Iterator
	{
	protected:
		T* m_position;
	public:
		//双向迭代器标签
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = const T*;
		using reference = const T&;
		inline Iterator(T* _position)
			: m_position(_position) {}

		inline Iterator(const Iterator& _iter)
		{
			this->m_position = _iter.m_position;
		}

		inline Iterator& operator=(const Iterator& _iter)
		{
			if(&_iter != this)
				this->m_position = _iter.m_position;
		}

		inline T& operator*()
		{
			return *this->m_position;
		}

		inline const T& operator*()const
		{
			return *this->m_position;
		}

		inline T* operator->()
		{
			return this->m_position;
		}
	};
	inline CircularArrayList()
		:m_step(this->DEFAULT_STEP)
	{
		this->m_arrayLength = this->DEFAULT_CAPATITY;
		createList();
	}

	inline CircularArrayList(int _initCapacity, int _increase = 0, int _step = 0)
	{
		this->m_arrayLength = _initCapacity > this->DEFAULT_CAPATITY ? _initCapacity : this->DEFAULT_CAPATITY;
		this->m_increase = _increase > this->MIN_INCREASE ? _increase : this->MIN_INCREASE;
		this->m_step = _step > 0 ? _step : this->DEFAULT_STEP;

		createList();
	}

	virtual ~CircularArrayList() 
	{
		delete[] this->m_element;
	}

	virtual bool operator ==(const ArrayList<T>& _list) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual bool operator !=(const ArrayList<T>& _list) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual bool operator <(const ArrayList<T>& _list) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual const T& operator [](int _index) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual T& operator [](int _index) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual bool empty() const override
	{
		return this->m_first == this->m_last - 1s;
	}

	//index = (index + step) % length ,,last = (step + size) % length
	virtual int size() const override
	{
		if (this->m_last == this->m_first)
			return 0;
		else if (this->m_last > this->m_first)
			return this->m_last - this->m_first;
		else
			return this->m_last + this->m_step + 1;
	}


	virtual T& get(int _index) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual const T& get(int _index) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual int indexOf(const T& _element) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void erase(int _index) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void insert(int _index, const T& _element) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual inline int capacity() const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void push_back(const T& _element) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void pop_back() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void swap(ArrayList<T>& _list) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void reserve(int _capacity) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual T& set(int _index, const T& _element) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void clear() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void removeRange(Iterator _begin, Iterator _end) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void removeRange(Iterator _begin) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual int lastIndexOf(const T& _element) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void reverse() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void leftShift(int _shift) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void circularShift(int _shift) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void half() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void trimToSize() override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual bool equal(const ArrayList<T>& _list) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual Iterator begin() const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual Iterator end() const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual ArrayList<T>& meld(const ArrayList<T>& _leftList, const ArrayList<T>& _rightList) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual ArrayList<T>& merge(const ArrayList<T>& _leftList, const ArrayList<T>& _rightList) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void split(ArrayList<T>& _leftList, ArrayList<T>& _rightList) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void setSize(int _capacity) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

protected:
	virtual void changeLength(T*& _arr, int& _oldLength, int _newLength) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void checkIndex(int _index) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void iterSwap(Iterator& _leftIter, Iterator _rightIter) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

};
