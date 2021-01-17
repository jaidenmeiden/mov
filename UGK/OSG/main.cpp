#include <iostream>
#include <windows.h>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include "SceneGraph.hpp"
#include "CNode.hpp"
#include "GenericNode.hpp"
#include "OSGWrap.hpp"

int main(int argc, char *argv[])
{
	std::cout << "Hello world";

	//GenericNode<int> *otherNode = new GenericNode<int>(1);

	OSGWrap<int> *osgWrap = new OSGWrap<int>(2);
	osgWrap->addChildFromUri("cow.osg");
	osgWrap->startViewer();
	
	/*osg::ref_ptr<CNode<int>> cplain = new CNode<int>(1);
	cplain->addChild(osgDB::readNodeFile("cow.osg"));

	osg::ref_ptr<osg::Node> plain = osgDB::readNodeFile("cessna.osg");
	cplain->addChild(plain.get());

	cplain->addChildFromData(5);

	//funcion delegada para ejecutarse en el traverse
	cplain->addTraverseDelegate([](int data){
		std::cout << "Node data: " << data << std::endl;
	});

	SceneGraph *root = &SceneGraph::instance(); // cache instance pointer
	root->addChild(cplain.get());

	osgViewer::Viewer viewer;
	viewer.setSceneData(root->getRootNode().get());
	return viewer.run();*/
}