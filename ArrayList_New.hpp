#pragma once
#include "ArrayList.hpp"

template <class T>
class ArrayList_New : public ArrayList<T>
{
public:
	using Iterator = ArrayList<T>::Iterator;
	inline ArrayList_New()
		:ArrayList<T>() {}

	inline ArrayList_New(int _initCapacity, int _increase = 0)
		:ArrayList<T>(_initCapacity, _increase) {}
	
	virtual ~ArrayList_New() {}

	virtual void erase(int _index) override
	{
		this->checkIndex(_index);
		
		if ((this->m_listsize - 1) < (this->m_arrayLength / 4) && (this->m_arrayLength / 2) >= this->DEFAULT_CAPATITY)
		{
			auto newArrayLength = this->m_arrayLength / 2;
			auto newArray = new T[newArrayLength];
			
			//����ǰ��Ĳ���
			std::copy(this->m_element, this->m_element + _index, newArray);
			//���ƺ���Ĳ���
			std::copy(this->m_element + _index + 1, this->m_element + this->m_listsize, newArray + _index );
			//�ͷžɵĵ������ڴ�
			delete[] this->m_element;
			this->m_element = newArray;
			--this->m_listsize;
			this->m_arrayLength = newArrayLength;
		}
		else
		{
			std::copy(this->m_element + _index + 1, this->m_element + this->m_listsize, this->m_element + _index);
			this->m_element[--this->m_listsize].~T();
		}
	}

	virtual void pop_back() override
	{
		if (this->m_listsize == 0)
			throw IllegalParamterValue("list size = 0, size must be > 0");
		if ((this->m_listsize - 1) < (this->m_arrayLength / 4) && (this->m_arrayLength / 2) >= this->DEFAULT_CAPATITY)
		{
			auto newArrayLength = this->m_arrayLength / 2;
			auto newArray = new T[newArrayLength];
			//���Ƴ������һ��Ԫ�أ����µ����Ա���
			std::copy(this->m_element, this->m_element + this->m_listsize - 1, newArray);
			//�ͷžɵĵ������ڴ�
			delete[] this->m_element;
			this->m_element = newArray;
			--this->m_listsize;
			this->m_arrayLength = newArrayLength;
		}
		else
		{
			this->m_element[this->m_listsize - 1].~T();
			--this->m_listsize;
		}
	}


	virtual void removeRange(Iterator _begin, Iterator _end) override
	{
		if (_end < _begin)
			throw IllegalParamterValue("_end must be > _begin");
		if (_begin < this->begin() || _begin > this->end() || _end > this->end())
			throw IllegalParamterValue("_end Iterator must be in the list range");

		if ((_end - _begin) == this->m_listsize && (this->m_arrayLength / 2) >= this->DEFAULT_CAPATITY)
		{
			//�ͷžɵĵ������ڴ�
			delete[] this->m_element;
			this->m_element = new T[this->m_arrayLength];
			this->m_listsize = 0;
		}
		else if ((this->m_listsize - (_end - _begin)) < (this->m_arrayLength / 4) && (this->m_arrayLength / 2) >= this->DEFAULT_CAPATITY)
		{
			auto newArrayLength = this->m_arrayLength / 2;
			auto newArray = new T[newArrayLength];
			//���Ƴ������һ��Ԫ�أ����µ����Ա���
			std::copy(this->m_element, this->m_element + this->m_listsize - 1, newArray);
			//�ͷžɵĵ������ڴ�
			delete[] this->m_element;
			this->m_element = newArray;
			--this->m_listsize;
			this->m_arrayLength = newArrayLength;
		}
		else
		{
			auto it_end = this->end();
			//���Ա�������ƶ�
			std::copy(_end, it_end, _begin);
			auto removeLength = _end - _begin;
			//�����������Ա�Ԫ��
			while (_end != it_end)
			{
				(*_end++).~T();
			}

			this->m_listsize -= removeLength;
		}
	}


	virtual void removeRange(Iterator _begin) override
	{
		if (this->begin() > _begin)
			throw IllegalParamterValue("_begin must be >= begin Iterator");
		if (this->end() < _begin)
			throw IllegalParamterValue("_begin must be < end Iterator");

		if ((this->m_arrayLength / 2) >= this->DEFAULT_CAPATITY)
		{
			auto newArrayLength = this->m_arrayLength / 2;
			auto newArray = new T[newArrayLength];
			//���Ƴ������һ��Ԫ�أ����µ����Ա���
			std::copy(this->m_element, this->m_element + this->m_listsize - 1, newArray);
			//�ͷžɵĵ������ڴ�
			delete[] this->m_element;
			this->m_element = newArray;
			--this->m_listsize;
			this->m_arrayLength = newArrayLength;
		}
		else
		{
			//�����������Ա�Ԫ��
			auto it_end = this->end();
			auto removeLength = it_end - _begin;
			while (_begin != it_end)
			{
				(*_begin++).~T();
			}

			this->m_listsize -= removeLength;
		}
	}

};