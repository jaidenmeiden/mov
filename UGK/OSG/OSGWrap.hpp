#ifndef OSG_WRAP
#define OSG_WRAP 1

#include <osgViewer/Viewer>
#include "GenericNode.hpp"

template <class T>
class __declspec(dllexport) OSGWrap
{
public:
	OSGWrap() : root() {}
	OSGWrap(T data) : root(data) {}
	OSGWrap(const OSGWrap& copy)
	{
		this.root = copy.getRoot();
	}

	GenericNode<T> getRoot() { return root; }

	bool addChildFromUri(const std::string& uri)
	{
		return root.addChildFromUri(uri);
	}

	int startViewer()
	{
		osgViewer::Viewer viewer;
		osg::ref_ptr<CNode<T>> osgNode = root.getNode();
		viewer.setSceneData(osgNode.get());
		return viewer.run();
	}

private:

	GenericNode<T> root;
};


#endif