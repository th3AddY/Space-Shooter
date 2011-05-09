#pragma once

#include "Cache.h"

using namespace osgDB;

namespace Shooter
{
	class MeshCache : public Cache<MeshCache>
	{
	public:
		Node* loadMesh(const char* filename);
	protected:
		CacheContainer* load(const char* filename);
	};
}