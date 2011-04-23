#include "MeshCache.h"

using namespace Shooter;

CacheContainer* MeshCache::load(char* filename)
{
	CacheContainer* container = new CacheContainer();
	container->node = readNodeFile(filename);

	return container;
}