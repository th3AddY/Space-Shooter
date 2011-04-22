#pragma once

#include <vector>
#include <iostream>

#include <osg/Node>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>

#include "SpaceCraft.h"
#include "ModelCache.h"
#include "Misc.h"

using namespace osg;
using namespace std;
using namespace xercesc;

namespace Shooter
{
	typedef struct _spaceCraftData
	{
		char* filename;
		char* modelFilename;

		Vec3 position;
		Vec3 scale;
		Quat attitude;

		ref_ptr<Node> node;
		SpaceCraftParams params;
	} SpaceCraftData;

	class SpaceCraftBuilder
	{
	public:
		static SpaceCraftBuilder* get();
		void clear();

		SpaceCraft* fromFile(char* filename, double* simTimeDiff);

	private:
		SpaceCraftData* findCache(char* filename);
		SpaceCraftData* parseXML(DOMDocument* doc);
		void buildSpaceCraftNode(SpaceCraftData* data);

		static SpaceCraftBuilder* m_instance;

		vector<SpaceCraftData*> m_spaceCraftCache;
	};
}