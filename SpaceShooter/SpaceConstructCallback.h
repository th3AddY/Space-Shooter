#pragma once

#include "SpaceConstruct.h"
#include "SpaceState.h"

using namespace osg;

namespace Shooter {

	class SpaceConstructCallback : public NodeCallback 
	{
		public:
			SpaceConstructCallback(SpaceConstruct* c);

			virtual void operator()(Node* node, NodeVisitor* nv);
		private:
			SpaceConstruct* m_spaceConstruct;
	};

}