#pragma once

#include <osg/Node>

using namespace osg;

namespace Shooter
{
	class CacheContainer
	{
	public:
		char* filename;
		ref_ptr<Node> node;

		virtual void release();
	};
}