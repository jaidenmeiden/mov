#ifndef OSG_GENERICNODE
#define OSG_GENERICNODE 1

#include <iostream>
#include <osg/Group>
#include "CNode.hpp"
#include <algorithm>
#include <vector>

template <class T>
class __declspec(dllexport) GenericNode
{
public:
	typedef std::function<void(T data)>		functionDelegate;
	GenericNode() : node() {}
	GenericNode(T data) : node(data) {}
//	GenericNode(const GenericNode& copy)
//	{
//		this.data = copy.getData();
//	}
	T getData() { return data; }
	void setData(T newData) { data = newData; }
	bool addChildFromData(T newData)
	{
		return node.addChildFromData(newData);
	}
	bool insertChildFromData(unsigned int index, T newData)
	{
		return node.insertChildFromData(index, newData);
	}
	void addTraverseDelegate(functionDelegate delegate)
	{
		node.addTraverseDelegate(delegate);
	}
	bool addChildFromUri(const std::string& uri)
	{
		return node.addChildFromUri(uri);
	}
	CNode<T>* getNode()
	{
		return &node;
	}

private:
	CNode<T> node;
	T data;
};


#endif