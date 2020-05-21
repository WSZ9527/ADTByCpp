#pragma once
template <class T>
class LinearList
{
	virtual bool empty() const = 0;
		//返回true,说明线性表为空
	virtual int size() const = 0;
		//返回线性表元素个数
	virtual T& get(int _index) = 0;
	virtual const T& get(int _index) const = 0;
		//根据索引返回线性表元素 const
	virtual int indexOf(const T& _element) const = 0;
		//返回元素theElement元素在线性表第一次出现的位置
	virtual void erase(int _index) = 0;
		//根据索引删除一个元素
	virtual void insert(int _index, const T& _element) = 0;
};
