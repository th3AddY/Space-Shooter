#include "MeshCache.h"

using namespace Shooter;

Node* MeshCache::loadMesh(const char* filename)
{
	return static_cast<Node*>(fromFile(filename));
}

CacheContainer* MeshCache::load(const char* filename)
{
	CacheContainer* container = new CacheContainer();
	container->referenced = readNodeFile(filename);

	return container;
}