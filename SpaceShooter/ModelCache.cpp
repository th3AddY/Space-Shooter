#include "ModelCache.h"

using namespace Shooter;

ModelCache* ModelCache::m_instance = 0;

ModelCache* ModelCache::get()
{
	if (m_instance == 0)
		m_instance = new ModelCache();

	return m_instance;
}

void ModelCache::clear()
{
	for (unsigned int i=0; i<m_cachedModels.size(); i++)
	{
		m_cachedModels[i]->node.release();
		delete m_cachedModels[i];
	}

	m_cachedModels.clear();

	delete m_instance;
}

Node* ModelCache::fromFile(char* filename)
{
	ModelCacheData* result = findCache(filename);

	if (result == 0)
	{
		result = new ModelCacheData();
		result->filename = filename;
		result->node = readNodeFile(filename);

		m_cachedModels.push_back(result);
	}

	return result->node;
}

ModelCacheData* ModelCache::findCache(char* filename)
{
	for (unsigned int i=0; i<m_cachedModels.size(); i++)
		if (getLower(m_cachedModels[i]->filename) == getLower(filename))
			return m_cachedModels[i];

	return 0;
}