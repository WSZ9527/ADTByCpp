#pragma once
#include "ChainNode.hpp"
#include "LinearList.hpp"
#include "IllegalParamterValue.hpp"
#include <iostream>
template<class T>
class Chain : public LinearList<T>
{
public:
	using capacity_type = unsigned int;
	using node_type = typename ChainNode<T>;
	using header_type = node_type*;
	using value_ytpe = typename T;
	using reference = value_ytpe&;
	using const_reference = const value_ytpe&;
	using pointer = value_ytpe*;
	using const_pointer = const value_ytpe*;
	using size_type =  int;
	using position_type =  int;
	//Ĭ�Ϲ��캯��
	Chain() = default;
	//�������캯��
	Chain(const Chain<T>& _chain)
	{
		this->m_header = new node_type(_chain.m_header->m_element, nullptr);
		auto header = this->m_header;
		for (auto iter = _chain.m_header->m_next; iter != nullptr; iter = iter->m_next)
		{
			header->m_next = new node_type(iter->m_element, nullptr);
			header = header->m_next;
		}
		this->m_listsize = _chain.m_listsize;
	}
	//��������
	virtual~Chain()
	{
		while (m_header!=nullptr)
		{
			auto delNode = m_header;
			m_header = m_header->m_next;
			delete delNode;
		}
	}
	//�ж������Ƿ�Ϊ��
	virtual bool empty() const override
	{
		return this->m_listsize == 0;
	}
	//��ȡ������
	virtual size_type size() const override
	{
		return this->m_listsize;
	}
	//����������ȡ����Ԫ��
	virtual reference get(int _index) override
	{
		this->checkIndex(_index);
		auto header = this->m_header;
		for (auto i{ 0 }; i < _index; ++i)
		{
			header = header->m_next;
		}

		return header->m_element;
	}
	//����������ȡ����Ԫ�� const�汾
	virtual const_reference& get(position_type _index) const override
	{
		this->checkIndex(_index);
		auto header = this->m_header;
		for (auto i{ 0 }; i <= _index; ++i)
		{
			header = header->m_next;
		}

		return header->m_element;
	}
	//������������
	virtual void setSize(size_type _size)
	{
		
		if (this->m_listsize > _size)
		{
			if (_size == 0)
			{
				for (int i = 0; i < this->m_listsize; i++)
				{
					auto del = this->m_header;
					this->m_header = this->m_header->m_next;
					delete del;
				}
				return;
			}
			auto list = this->m_header;
			for (size_type i = 0; i < _size-1; ++i)
			{
				list = list->m_next;
			}
			auto tmp = list->m_next;
			list->m_next = nullptr;
			
			
			for (size_type i = _size; i < this->m_listsize; ++i)
			{
				auto del = tmp;
				tmp = tmp->m_next;
				delete del;
			}

			this->m_listsize = _size;
		}
	}
	//������������Ԫ�ص�ֵ
	virtual void set(position_type _position, const_reference _element)
	{
		this->checkIndex(_position);
		auto list = this->m_header;
		for (int i = 0; i < _position; ++i)
		{
			list = list->m_next;
		}
		list->m_element = _element;
	}
	//��ȡ��ӦԪ�ص�����
	virtual int indexOf(const_reference _element) const override
	{
		auto index{ -1 };
		if (this->empty())
			return index;
		
		auto i{ -1 };
		for (auto iter = this->m_header; iter != nullptr; iter = iter->m_next)
		{
			++i;
			if (iter->m_element == _element)
			{
				index = i;
				break;
			}
		}

		return index;
	}
	//��������ɾ��Ԫ��
	virtual void erase(position_type _index) override
	{
		checkIndex(_index);
		if (_index == 0)
		{
			auto delNode = this->m_header;
			this->m_header = this->m_header->m_next;
			delete delNode;
		}

		auto i{ 0 };
		for (auto iter = this->m_header; iter != nullptr; iter = iter->m_next)
		{
			++i;
			if (i == _index )
			{
				auto delNode = iter->m_next;
				iter->m_next = delNode->m_next;
				delete delNode;
			}
		}

		--this->m_listsize;
	}
	//������������Ԫ��
	virtual void insert(position_type _index, const_reference _element) override
	{
		if (_index == 0)
		{
			auto newNode = new node_type(_element);
			if (this->m_listsize == 0)
			{
				this->m_header = newNode;
			} 
			else
			{
				newNode->m_next = this->m_header;
				this->m_header = newNode;
			}

		}
		else
		{
			this->checkIndex(_index);
			auto newNode = new node_type(_element);
			auto header = this->m_header;
			for (auto i{ 0 }; i < _index-1; ++i)
			{
				header = header->m_next;
			}

			newNode->m_next = header->m_next;
			header->m_next = newNode;
		}

		++this->m_listsize;
	}
	//������β������Ԫ��
	virtual void push_back(const_reference _element)
	{
		this->insert(this->m_listsize, _element);
	}
	//��Ա�������
	class _Const_Iterator 
	{
		header_type m_header;
		void checkPointer(header_type _header) const
		{
			if (m_header == nullptr)
				throw IllegalParamterValue("null pointer");
		}
	public:
		_Const_Iterator(header_type _header)
			:m_header(_header) {}
		~_Const_Iterator() {}

		virtual const ChainNode<T> operator*() const
		{
			return this->m_header->m_element;
		}

		virtual const ChainNode<T>* operator->() const
		{
			return this->m_header;
		}
		virtual _Const_Iterator& operator++()
		{
			this->checkPointer(m_header);
			m_header = m_header->m_next;
			return *this;
		}
		virtual _Const_Iterator operator++(int) 
		{
			this->checkPointer(this->m_header);
			auto tmp = *this;
			this->m_header = m_header->m_next;
			return tmp;
		}
		virtual bool operator!=(const _Const_Iterator& _rightIter) const
		{
			return this->m_header != _rightIter.m_header;
		}
		virtual bool operator==(const _Const_Iterator& _rightIter) const
		{
			return this->m_header == _rightIter.m_header;
		}
		virtual bool operator >(const _Const_Iterator& _rightIter) const 
		{
			return this->m_header > _rightIter.m_header;
		}
	};
	using Iterator = typename Chain<T>::_Const_Iterator;
	//��ȡͷ��������
	Iterator begin()const { return Iterator(this->m_header); }
	//��ȡβ��������
	Iterator end()const { return Iterator(nullptr); }
	//��������ɾ��һ����Χ��Ԫ��
	virtual void removeRange(int _beginIndex, int _endIndex)
	{
		if (this->m_listsize == 0)
			throw IllegalParamterValue("the list is empty");
		if (_endIndex <= _beginIndex)
			throw IllegalParamterValue("_endIndex must be > _beginIndex");
		if(_endIndex - _beginIndex > this->m_listsize)
			throw IllegalParamterValue("_endIndex and _beginIndex not in the list range");
		

		//��0��ʼ
		if (_beginIndex == 0)
		{
			for (int i = 0; i < _endIndex -_beginIndex; ++i)
			{
				auto del = this->m_header;
				this->m_header = del->m_next;
				delete del;
				--this->m_listsize;
			}

			return;
		}

		//���Ǵ�0��ʼ��������Ҫ��ʼɾ����������ǰһ��
		auto list = this->m_header;
		for (int i = 1; i < _beginIndex; ++i)
		{
			list = list->m_next;
		}

		//1 2 3 4 5 6 x
		auto pre = list;
		list = list->m_next;
		for (int i = _beginIndex; i < _endIndex; ++i)
		{
			auto del = list;
			list = del->m_next;
			delete del;
			--this->m_listsize;
		}
		pre->m_next = list;
	}
	//�������
	virtual void clear()
	{
		while (this->m_listsize>0)
		{
			auto del = this->m_header;
			this->m_header = this->m_header->m_next;
			delete del;
			--this->m_listsize;
		}
	}
	//��ͷ������Ԫ��
	virtual void push(const T& _t)
	{
		this->insert(0, _t);
	}
	//��ȡĳһԪ�������ֵ�����
	virtual int lastIndexOf(const T& _element) const
	{
		auto list = this->m_header;
		int i = 0;
		int last = -1;
		while (list!=nullptr)
		{
			if (list->m_element == _element)
			{
				last = i;
			}
			++i;
			list = list->m_next;
		}

		return last;
	}
	//���������±������
	virtual T& operator[](int _index) 
	{
		if (_index < 0 || _index >= this->m_listsize)
			throw IllegalParamterValue("_index is not in list range");
		auto list = this->m_header;
		for (int i = 0; i < _index; ++i)
		{
			list = list->m_next;
		}

		return list->m_element;
	}
	//���������±������ const�汾
	virtual const T& operator[](int _index) const
	{
		if (_index < 0 || _index >= this->m_listsize)
			throw IllegalParamterValue("_index is not in list range");
		auto list = this->m_header;
		for (int i = 0; i < _index; ++i)
		{
			list = list->m_next;
		}

		return list->m_element;
	}
	//�ж����������Ƿ����
	virtual bool equal(const Chain<T>& _rightChain) const 
	{
		if (this->m_listsize != _rightChain.m_listsize)
			return false;
		auto left = this->m_header;
		auto right = _rightChain.m_header;
		
		while (left && right)
		{
			if (left->m_element != right->m_element)
				return false;
			left = left->m_next;
			right = right->m_next;
		}

		return true;
	}
	virtual bool less(const Chain<T>& _rightChain)const
	{
		auto left = this->m_header;
		auto right = _rightChain.m_header;

		while (left && right)
		{
			if(left->m_element<right->m_element)
				continue;
			return false;
		}

		return true;
	}
	//����==������,�ж����������Ƿ����
	virtual bool operator==(const Chain<T>& _rightChain) const
	{
		return this->equal(_rightChain);
	}
	//����!=������,�ж����������Ƿ����
	virtual bool operator!=(const Chain<T>& _rightChain) const
	{
		return this->equal(_rightChain) == true ? false : true;
	}
	//����<������
	virtual bool operator<(const Chain<T>& _rightChain) const
	{
		return this->less(_rightChain);
	}
	//����2������
	virtual void swap(Chain<T>& _rightChain)
	{
		auto tmpSize = this->m_listsize;
		auto tmpHeader = this->m_header;
		this->m_listsize = _rightChain.m_listsize;
		this->m_header = _rightChain.m_header;
		_rightChain.m_listsize = tmpSize;
		_rightChain.m_header = tmpHeader;
	}
	//����
	virtual void leftShift(int _step)
	{
		if (_step < 0 || _step > this->m_listsize)
			throw IllegalParamterValue("_step must be valid");
		this->removeRange(0, _step);
	}
	//��������
	virtual void reverse()
	{
		//1 2 3 4 5 6
		if (this->m_listsize == 0)
			throw IllegalParamterValue("the list is empty");
		//ֻ��һ��ֱ���˳�
		if (this->m_listsize == 1)
			return;

		auto list = this->m_header;
		//ͷ��
		header_type newHeader = nullptr;
		while (list != nullptr)
		{
			if (newHeader == nullptr)
			{
				newHeader = list;
				list = list->m_next;
				newHeader->m_next = nullptr;
			}
			else
			{
				auto tmp = list->m_next;
				list->m_next = newHeader;
				newHeader = list;
				list = tmp;
			}
		}

		this->m_header = newHeader;
	}
protected:
	header_type m_header = nullptr;
	size_type m_listsize = 0;
	size_type m_thesize = 0;
	void checkIndex(position_type _index) const
	{
		if (_index < 0 || _index > this->m_listsize)
			throw IllegalParamterValue("_index is no in range");
	}
};