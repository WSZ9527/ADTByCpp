#pragma once
#include <iostream>
//链表节点
template<class T>
struct Node
{
	//数据域
	T* m_data;

	//节点域
	Node<T>* m_next;

	//默认构造
	Node()
		:m_data(nullptr), m_next(nullptr) {}

	//带参构造
	Node(const T& _t, Node<T>* _pnode = nullptr)
		:m_data(new T(_t)), m_next(_pnode) {}

	//拷贝构造函数
	Node(const Node<T>& _node)
	{
		if (_node.m_data != nullptr)
			this->m_data = new T(*_node.m_data);
		this->m_next = _node.m_next;
	}

	//赋值操作符重载
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

	//移动拷贝构造
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

	//移动赋值操作符重载
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

	//全局友元<<函数重载
	friend std::ostream& operator<<(std::ostream& _os, const Node<T>& _node)
	{
		_os << *_node.m_data;
		return _os;
	}

	//析构函数
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
//带头结点的 循环链表
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
	//默认构造函数
	CircularListWithHeader()
		:m_listHeader(new list_t()) 
	{
		this->m_listHeader->m_next = this->m_listHeader;
		this->m_listTail = nullptr;
		this->m_listSize = 0;
	}
	//析构函数
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

	//插入节点x 1 2 3 4 5
	void insert(position_t _pos, const value_t& _value)
	{
		//特殊位置位置是0
		if (_pos == 0)
		{
			this->m_listHeader->m_next = new node_t(_value, this->m_listHeader->m_next);
			//给尾部赋值
			if (this->m_listSize == 0)
			{
				this->m_listTail = this->m_listHeader->m_next;
			}
			//计数+1
			++this->m_listSize;
			return;
		}

		//特殊位置尾部
		if (_pos == this->m_listSize)
		{
			this->m_listTail->m_next = new node_t(_value, this->m_listTail->m_next);
			this->m_listTail = this->m_listTail->m_next;
			//计数+1
			++this->m_listSize;
			return;
		}

		//位置无效
		if (_pos < 0 || _pos > this->m_listSize)
			throw "_pos 无效";

		auto curNode = this->m_listHeader->m_next;
		//迭代至_pos - 1
		for (position_t pos = 0; pos < _pos - 1; ++pos)
		{
			curNode = curNode->m_next;
		}

		//插入节点
		curNode->m_next = new node_t(_value, curNode->m_next);
		//计数+1
		++this->m_listSize;
	}
	
	//头插
	void push(const value_t& _value)
	{
		this->insert(0, _value);
	}

	//尾插
	void push_back(const value_t& _value)
	{
		this->insert(this->m_listSize, _value);
	}

	//查找节点
	position_t indexOf(const value_t& _value) const
	{
		//如果链表为空返回-1
		if (this->m_listSize == 0)
			return -1;
		//将要查找的值放入头结点
		if (this->m_listHeader->m_data == nullptr)
			this->m_listHeader->m_data = new value_t(_value);
		else
			*this->m_listHeader->m_data = _value;

		//当前节点
		auto curNode = this->m_listHeader->m_next;
		position_t pos = 0;
		while (*curNode->m_data != _value)
		{
			//向下迭代
			curNode = curNode->m_next;
			++pos;
		}

		//没找到
		if (curNode == this->m_listHeader)
			return -1;
		else
			return pos;
	}
	
	//获取容量
	inline size_t size() const 
	{
		return this->m_listSize;
	}

	//全局友元<<函数重载
	friend std::ostream& operator<<(std::ostream& _os, const CircularListWithHeader<T>& _cirList)
	{
		auto curNode = _cirList.m_listHeader->m_next;
		//迭代输出
		while (curNode != _cirList.m_listHeader)
		{
			_os << *curNode << " ";
			curNode = curNode->m_next;
		}

		return _os;
	}
protected:
	//表头
	plist_t m_listHeader;
	//表尾部
	plist_t m_listTail;
	//链表大小
	size_t m_listSize;
};