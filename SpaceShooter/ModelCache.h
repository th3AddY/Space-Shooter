#pragma once

#include <vector>

#include <osg/Node>
#include <osgDB/ReadFile>

#include "Misc.h"

using namespace std;
using namespace osg;
using namespace osgDB;

namespace Shooter
{
	typedef struct _modelCacheData
	{
		char* filename;
		ref_ptr<Node> node;
	} ModelCacheData;

	class ModelCache
	{
	public:
		static ModelCache* get();
		void clear();

		Node* fromFile(char* filename);
	private:
		ModelCacheData* findCache(char* filename);

		static ModelCache* m_instance;

		vector<ModelCacheData*> m_cachedModels;
	};
}