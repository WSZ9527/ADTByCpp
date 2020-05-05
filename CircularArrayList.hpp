#pragma once
#include <iterator>
#include <iostream>
#include "IllegalParamterValue.hpp"
template <class T>
class CircularArrayList
{
public:
	using value_type = T;
	using reference = value_type&;
	using const_reference = const T&;
	using pointer = T*;
	using const_pointer = const T*;
	using size_type = unsigned int;
	using difference_type = unsigned int;
	using position_type = unsigned int;
	CircularArrayList() 
	{
		this->m_container =  this->allocator(this->m_capacity);
	}

	explicit CircularArrayList(size_type _capacity)
	{
		if (_capacity > this->DEFAULT_CAPACITY)
			this->m_capacity = _capacity;
		this->m_container = this->allocator(this->m_capacity);
	}

	//全局友元输出流符号重载
	friend std::ostream& operator<<(ostream& _out, const CircularArrayList<T>& _list)
	{
		for (auto& e : _list)
			_out << e << " ";
		return _out;
	}

	//双向迭代器
	class _CircularArrayList_Const_Iterator
	{
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = typename CircularArrayList<T>::value_type;
		using const_reference = typename CircularArrayList<T>::const_reference;
		using pointer = typename CircularArrayList<T>::pointer;
		using const_pointer = typename CircularArrayList<T>::const_pointer;
		using size_type = typename CircularArrayList<T>::size_type;
		using difference_type = typename CircularArrayList<T>::difference_type;
		using position_type = typename CircularArrayList<T>::position_type;

		_CircularArrayList_Const_Iterator(pointer _pointer, position_type _position,difference_type _step, size_type _capacity)
			:m_pointer(_pointer), m_step(_step),m_position(_position), m_capacity(_capacity) {}

		virtual ~_CircularArrayList_Const_Iterator() {}

		//重载*取值操作符
		const_reference operator*() const 
		{
			this->checkPosition(this->m_position);
			return this->m_pointer[this->getRealPosition()];
		}
		//重载指针操作符
		const_pointer operator->() const 
		{
			this->checkPosition(this->m_position);
			return this->m_pointer + this->getRealPosition();
		}

		//重载前置自加操作符
		_CircularArrayList_Const_Iterator& operator++()
		{
			this->checkPosition(++this->m_position);
			return *this;
		}

		//重载前置减减操作符
		_CircularArrayList_Const_Iterator& operator--()
		{
			this->checkPosition(--this->m_position);
			return *this;
		}

		_CircularArrayList_Const_Iterator operator-(difference_type _step) const
		{
			return _CircularArrayList_Const_Iterator(this->m_pointer, this->m_position - _step, this->m_step, this->m_capacity);
		}

		_CircularArrayList_Const_Iterator operator+(difference_type _step) const
		{
			return _CircularArrayList_Const_Iterator(this->m_pointer, this->m_position + _step, this->m_step, this->m_capacity);
		}

		bool operator>(const _CircularArrayList_Const_Iterator& _rightIter) const
		{
			this->checkIter(_rightIter);
			return this->m_position > _rightIter.m_position;
		}

		bool operator>=(const _CircularArrayList_Const_Iterator& _rightIter) const
		{
			this->checkIter(_rightIter);
			return this->m_position >= _rightIter.m_position;
		}

		bool operator<(const _CircularArrayList_Const_Iterator& _rightIter) const
		{
			this->checkIter(_rightIter);
			return this->m_position < _rightIter.m_position;
		}

		bool operator<=(const _CircularArrayList_Const_Iterator& _rightIter) const
		{
			this->checkIter(_rightIter);
			return this->m_position <= _rightIter.m_position;
		}

		bool operator!=(const _CircularArrayList_Const_Iterator& _rightIter) const
		{
			this->checkIter(_rightIter);
			return this->m_position != _rightIter.m_position;
		}

		bool operator==(const _CircularArrayList_Const_Iterator& _rightIter) const
		{
			this->checkIter(_rightIter);
			return this->m_position == _rightIter.m_position;
		}

	protected:
		pointer m_pointer;
		difference_type m_step;
		size_type m_capacity;
		position_type m_position;

		inline void checkPosition(position_type _position) const
		{
			if (_position < 0 || _position >= this->m_capacity)
				throw IllegalParamterValue("iterator is falied");
			//else if (_position > this->size())
				//throw IllegalParamterValue("the _position must be in the list range");
		}

		inline position_type getRealPosition() const
		{
			return this->getRealPosition(this->m_position);
		}

		inline position_type getRealPosition(position_type _position) const
		{
			return this->getRealPosition(_position, this->m_step, this->m_capacity);
		}

		inline position_type getRealPosition(position_type _position, difference_type _step, size_type _capacity) const
		{
			//checkPosition(_position);
			return (_position + _step) % _capacity;
		}

		inline void checkIter(const _CircularArrayList_Const_Iterator& _rightIter) const
		{
			if (this->m_pointer != _rightIter.m_pointer || this->m_step != _rightIter.m_step || this->m_capacity != _rightIter.m_capacity)
				throw IllegalParamterValue("iterator is falied");
		}		
	};
	using Iterator = typename CircularArrayList<T>::_CircularArrayList_Const_Iterator;
	//根据索引将元素插入线性表中
	virtual void insert(position_type _position, const_reference _element)
	{
		
		if (this->size() == this->m_capacity)
		{
			//扩容
			increaseMemroySpace();
		}

		this->checkPosition(_position);


		++this->m_listsize;
		this->m_last = (this->m_listsize + this->m_step + 1) % this->m_capacity;
		//策略选择线性表元素移动方向
		auto realPosition = this->getRealPosition(_position);
		auto lastStep = this->dabs(realPosition - this->m_last);
		auto firstStep = this->dabs(realPosition - this->m_first);
		if (lastStep > firstStep)
		{
			//离头部比较近，左移
			auto iter = this->getIterator(_position);
			auto iterEnd = this->getIterator(_position + lastStep);
			auto desIter = this->getIterator();
		}
		else
		{
			//离尾部比较近，右移
			auto iter = this->getIterator(_position + lastStep); 
			auto iterEnd = this->getIterator(_position);
			auto desIter = this->getIterator();

		}
		//if(realPosition)
		this->m_container[this->getRealPosition(_position)] = _element;
	}
	//在线性表的尾部插入元素
	virtual void push_back(const_reference _element)
	{
		this->insert(this->m_listsize, _element);
	}
	//根据索引获取线性表元素的引用
	virtual reference indexOf(position_type _position) const
	{
		this->checkPosition(_position);
		return this->m_container[this->getRealPosition(_position)];
	}
	//重载数组操作符，方便遍历线性表元素
	reference operator[](position_type _position) const
	{
		return this->indexOf(_position);
	}
	//获取线性表元素个数
	virtual size_type size() const
	{
		//return this->m_last == this->m_first ? this->m_capacity:
			//this->m_last < this->m_first ? (this->m_capacity - this->m_first + this->m_last + 1) : (this->m_last - this->m_first - 1);
		return this->m_listsize;
	}
	//获取线性表在内存中的实际分配的大小
	virtual size_type capacity() const
	{
		return this->m_capacity;
	}
	//获取首迭代器
	virtual Iterator begin() const
	{
		return this->getIterator();
	}
	//获取尾迭代器
	virtual Iterator end() const
	{
		return this->getIterator(this->m_listsize);
	}
	virtual ~CircularArrayList() {}
protected:
	//一些默认属性
	enum 
	{
		DEFAULT_CAPACITY = 10,
		DEFAULT_STEP = 7,
		DEFAULT_CONDITION = 5
	};
	
	size_type m_capacity = this->DEFAULT_CAPACITY;
	size_type m_listsize = 0;
	size_type m_condition = 0;
	position_type m_last = this->DEFAULT_STEP + 1;
	position_type m_first = this->DEFAULT_STEP;
	difference_type m_step = this->DEFAULT_STEP;
	pointer m_container;

	inline Iterator getIterator(position_type _position = 0) const
	{
		return Iterator(this->m_container, _position, this->m_step, this->m_capacity);
	}

	inline void allocatorCapacityVerify(size_type _size)
	{
		if (_size < 0)
			throw IllegalParamterValue("the size must be > 0");
	}

	inline pointer allocator(size_type _capaticy)
	{
		this->allocatorCapacityVerify(_capaticy);
		return new value_type[_capaticy];
	}

	inline void checkPosition(position_type _position) const
	{
		if (_position < 0)
			throw IllegalParamterValue("the _position must be > 0");
		else if(_position > this->size())
			throw IllegalParamterValue("the _position must be in the list range");
	}

	inline position_type getRealPosition(position_type _position) const
	{
		return this->getRealPosition(_position, this->m_step, this->m_capacity);
	}

	inline position_type getRealPosition(position_type _position, difference_type _step, size_type _capacity) const
	{
		checkPosition(_position);
		return (_position + _step) % _capacity;
	}

	//重新分配内存
	void reAllocator(size_type _capaticy)
	{
		this->allocatorCapacityVerify(_capaticy);
		_capaticy = _capaticy > this->DEFAULT_CAPACITY ? _capaticy : this->DEFAULT_CAPACITY;

		auto newContainer = allocator(_capaticy);
		for (position_type i = 0; i < this->size(); ++i)
		{
			newContainer[this->getRealPosition(i, this->m_step, _capaticy)] = this->m_container[this->getRealPosition(i)];
		}

		delete[]this->m_container;
		this->m_container = newContainer;
	}

	//拓展内存
	void increaseMemroySpace()
	{
		size_type newCapacity = this->m_capacity + (this->m_capacity >> 1);
		if (this->m_condition >= this->DEFAULT_CONDITION)
			newCapacity = this->m_capacity + this->m_condition;
		this->reAllocator(newCapacity);

		this->m_capacity = newCapacity;
	}

	void iterSwap(Iterator& _leftIter, Iterator& _rightIter)
	{
		std::swap(const_cast<reference>(*_leftIter), const_cast<reference>(*_rightIter));
	}

	//取绝对值
	inline difference_type dabs(int _step) const 
	{
		return _step > 0 ? _step : -_step;
	}
};