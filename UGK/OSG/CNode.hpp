#ifndef OSG_CNODE
#define OSG_CNODE 1

#include <iostream>
#include <osgDB/ReadFile>
#include <osg/Group>
#include <osg/NodeVisitor>
#include <algorithm>
#include <vector>

template <class T>
class CNode : public osg::Group
{
public:
	typedef std::function<void(T data)>		functionDelegate;

	CNode() : osg::Group(), data() {}
	CNode(T data) : osg::Group(), data(data) {}
//	CNode(const CNode& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY)
//	{
//		this.data = copy.getData();
//	}

	T getData() { return data; }

	void setData(T newData) { data = newData; }

	bool addChild(Node *child)
	{
		return this->insertChild(_children.size(), child);
	}

	bool addChildFromData(T newData) 
	{
		osg::ref_ptr<CNode<T>> child = new CNode<T>(newData);
		return this->addChild(child);
	}

	bool insertChildFromData(unsigned int index, T newData)
	{
		osg::ref_ptr<CNode<T>> child = new CNode<T>(newData);
		return this->insertChild(index, child);
	}

	bool addChildFromUri(const std::string& uri)
	{
		osg::ref_ptr<osg::Node> child = osgDB::readNodeFile(uri);
		return this->addChild(child);
	}

	void addTraverseDelegate(functionDelegate delegate)
	{
		traverseDelegate.push_back(delegate);
	}

	void traverse(osg::NodeVisitor& nv)
	{
		for (osg::NodeList::iterator itr = _children.begin();
			itr != _children.end();
			++itr)
		{
			(*itr)->accept(nv);
		}

		std::for_each(std::begin(traverseDelegate), std::end(traverseDelegate),
			[&](functionDelegate& delegate) {delegate(data); });
	}
private:
	T data;
	std::vector<functionDelegate>		traverseDelegate;
};

#endif