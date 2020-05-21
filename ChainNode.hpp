#pragma once
template <class T>
struct ChainNode
{
	T m_element;
	ChainNode<T>* m_next=nullptr;
	ChainNode() = default;
	ChainNode(const ChainNode<T>& _node)
	{
		this->m_element = _node.m_element;
		this->m_next = _node.m_next;
	}

	ChainNode(const T& _element, ChainNode<T>* _next =nullptr)
		:m_element(_element), m_next(_next) {}
};