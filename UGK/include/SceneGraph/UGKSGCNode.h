#ifndef UGKSGOSG_CNODE
#define UGKSGOSG_CNODE

#include <iostream>
#include <osgDB/ReadFile>
#include <osg/Group>
#include <osg/NodeVisitor>
#include <algorithm>
#include <vector>
#include <UGKCharacter.h>

namespace UGK
{

	class OSGCNode : public osg::Group
	{
		CCharacter* character;
	public:

		OSGCNode() : osg::Group() {}
		OSGCNode(const OSGCNode& copy, const osg::CopyOp& copyop = osg::CopyOp::SHALLOW_COPY) {}
		OSGCNode(CCharacter* Char) { 
			character = Char;
			osg::ref_ptr<osg::Node> osgNode = character->getMesh()->getMesh();
			this->addChild(osgNode);
		}

		CCharacter* getCharacter() { return character; }

		bool addChild(Node *child)
		{
			return this->insertChild(_children.size(), child);
		}

		bool addChildFromUri(const std::string& uri)
		{
			osg::ref_ptr<osg::Node> child = osgDB::readNodeFile(uri);
			return this->addChild(child);
		}

		void traverse(osg::NodeVisitor& nv)
		{
			for (osg::NodeList::iterator itr = _children.begin();
				itr != _children.end();
				++itr)
			{
				(*itr)->accept(nv);
			}
		}
	};
}
#endif