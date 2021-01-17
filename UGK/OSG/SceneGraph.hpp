#ifndef OSG_SCENEGRAPH
#define OSG_SCENEGRAPH 1

#include <iostream>
#include <osg/Group>

class __declspec(dllexport) SceneGraph
{
	static SceneGraph * pInstance;
	SceneGraph() { root = new osg::Group; }
	SceneGraph(const SceneGraph& rs) {
		pInstance = rs.pInstance;
	}
	SceneGraph& operator = (const SceneGraph& rs) {
		if (this != &rs) {
			pInstance = rs.pInstance;
		}

		return *this;
	}
	~SceneGraph() {}

public:	
	static SceneGraph& instance()
	{
		static SceneGraph theInstance;
		pInstance = &theInstance;

		return *pInstance;
	}
	osg::ref_ptr<osg::Group> getRootNode() { return root; }
	bool addChild(osg::ref_ptr<osg::Group> child) { return root->addChild(child.get()); }
	bool insertChild(unsigned int index, osg::ref_ptr<osg::Group> child) { return root->insertChild(index, child.get()); }

protected:
	osg::ref_ptr<osg::Group> root;
};

SceneGraph * SceneGraph::pInstance = nullptr;

#endif