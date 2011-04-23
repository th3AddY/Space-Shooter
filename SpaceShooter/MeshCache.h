#pragma once

#include "Cache.h"

using namespace osgDB;

namespace Shooter
{
	class MeshCache : public Cache<MeshCache>
	{
	protected:
		CacheContainer* load(char* filename);
	};
}