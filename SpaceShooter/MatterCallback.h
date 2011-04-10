#pragma once

#include <osg/NodeCallback>

#include "Matter.h"

using namespace osg;

namespace Shooter
{
	class MatterCallback : public NodeCallback 
	{
		public:
			virtual void operator()(Node* node, NodeVisitor* nv);
	};
}