#pragma once
#include <iostream>
//����ڵ�
template<class T>
struct Node
{
	//������
	T* m_data;

	//�ڵ���
	Node<T>* m_next;

	//Ĭ�Ϲ���
	Node()
		:m_data(nullptr), m_next(nullptr) {}

	//���ι���
	Node(const T& _t, Node<T>* _pnode = nullptr)
		:m_data(new T(_t)), m_next(_pnode) {}

	//�������캯��
	Node(const Node<T>& _node)
	{
		if (_node.m_data != nullptr)
			this->m_data = new T(*_node.m_data);
		this->m_next = _node.m_next;
	}

	//��ֵ����������
	Node& operator=(const Node<T>& _node)
	{
		if (this != &_node)
		{
			if (_node.m_data != nullptr)
				this->m_data = new T(*_node.m_data);
			this->m_next = _node.m_next;
		}
		else
		{
			this->m_data = nullptr;
			this->m_next = nullptr;
		}

		return *this;
	}

	//�ƶ���������
	Node(Node<T>&& _node)
	{
		if (_node.m_data != nullptr)
		{
			this->m_data = _node.m_data;
			_node.m_data = nullptr;
		}
		this->m_next = _node.m_next;
		_node.m_next = nullptr;
	}

	//�ƶ���ֵ����������
	Node& operator=(Node<T>&& _node)
	{
		if (this != &_node)
		{
			if (_node.m_data != nullptr)
			{
				this->m_data = _node.m_data;
				_node.m_data = nullptr;
			}
			this->m_next = _node.m_next;
			_node.m_next = nullptr;
		}
		else
		{
			this->m_data = nullptr;
			this->m_next = nullptr;
		}

		return *this;
	}

	//ȫ����Ԫ<<��������
	friend std::ostream& operator<<(std::ostream& _os, const Node<T>& _node)
	{
		_os << *_node.m_data;
		return _os;
	}

	//��������
	virtual ~Node()
	{
		if (this->m_data != nullptr)
		{
			delete this->m_data;
			this->m_data = nullptr;
		}
		if (this->m_next != nullptr)
			this->m_next = nullptr;
	}
};
//��ͷ���� ѭ������
template<class T>
class CircularListWithHeader
{
public:
	using value_t = typename T;
	using node_t = typename Node<T>;
	using pnode_t = node_t*;
	using list_t = node_t;
	using plist_t = pnode_t;
	using size_t = int;
	using position_t = int;
	//Ĭ�Ϲ��캯��
	CircularListWithHeader()
		:m_listHeader(new list_t()) 
	{
		this->m_listHeader->m_next = this->m_listHeader;
		this->m_listTail = nullptr;
		this->m_listSize = 0;
	}
	//��������
	virtual ~CircularListWithHeader()
	{
		auto curNode = this->m_listHeader->m_next;
		while (curNode!= this->m_listHeader)
		{
			auto delNode = curNode;
			curNode = curNode->m_next;
			delete delNode;
		}

		delete this->m_listHeader;
	}

	//����ڵ�x 1 2 3 4 5
	void insert(position_t _pos, const value_t& _value)
	{
		//����λ��λ����0
		if (_pos == 0)
		{
			this->m_listHeader->m_next = new node_t(_value, this->m_listHeader->m_next);
			//��β����ֵ
			if (this->m_listSize == 0)
			{
				this->m_listTail = this->m_listHeader->m_next;
			}
			//����+1
			++this->m_listSize;
			return;
		}

		//����λ��β��
		if (_pos == this->m_listSize)
		{
			this->m_listTail->m_next = new node_t(_value, this->m_listTail->m_next);
			this->m_listTail = this->m_listTail->m_next;
			//����+1
			++this->m_listSize;
			return;
		}

		//λ����Ч
		if (_pos < 0 || _pos > this->m_listSize)
			throw "_pos ��Ч";

		auto curNode = this->m_listHeader->m_next;
		//������_pos - 1
		for (position_t pos = 0; pos < _pos - 1; ++pos)
		{
			curNode = curNode->m_next;
		}

		//����ڵ�
		curNode->m_next = new node_t(_value, curNode->m_next);
		//����+1
		++this->m_listSize;
	}
	
	//ͷ��
	void push(const value_t& _value)
	{
		this->insert(0, _value);
	}

	//β��
	void push_back(const value_t& _value)
	{
		this->insert(this->m_listSize, _value);
	}

	//���ҽڵ�
	position_t indexOf(const value_t& _value) const
	{
		//�������Ϊ�շ���-1
		if (this->m_listSize == 0)
			return -1;
		//��Ҫ���ҵ�ֵ����ͷ���
		if (this->m_listHeader->m_data == nullptr)
			this->m_listHeader->m_data = new value_t(_value);
		else
			*this->m_listHeader->m_data = _value;

		//��ǰ�ڵ�
		auto curNode = this->m_listHeader->m_next;
		position_t pos = 0;
		while (*curNode->m_data != _value)
		{
			//���µ���
			curNode = curNode->m_next;
			++pos;
		}

		//û�ҵ�
		if (curNode == this->m_listHeader)
			return -1;
		else
			return pos;
	}
	
	//��ȡ����
	inline size_t size() const 
	{
		return this->m_listSize;
	}

	//ȫ����Ԫ<<��������
	friend std::ostream& operator<<(std::ostream& _os, const CircularListWithHeader<T>& _cirList)
	{
		auto curNode = _cirList.m_listHeader->m_next;
		//�������
		while (curNode != _cirList.m_listHeader)
		{
			_os << *curNode << " ";
			curNode = curNode->m_next;
		}

		return _os;
	}
protected:
	//��ͷ
	plist_t m_listHeader;
	//��β��
	plist_t m_listTail;
	//�����С
	size_t m_listSize;
};