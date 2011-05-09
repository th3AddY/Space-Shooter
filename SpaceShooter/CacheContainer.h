#pragma once

#include <osg/Node>

using namespace osg;

namespace Shooter
{
	class CacheContainer
	{
	public:
		const char* filename;
		ref_ptr<Referenced> referenced;

		virtual void release();
	};
}