#pragma once

#include <vector>
#include <iostream>

#include <osg/Node>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>

#include "Cache.h"
#include "MeshCache.h"
#include "SpaceCraftContainer.h"
#include "Misc.h"

using namespace osg;
using namespace std;
using namespace xercesc;

namespace Shooter
{
	class SpaceCraftBuilder : public Cache<SpaceCraftBuilder>
	{
	public:
		SpaceCraft* build(char* filename, double* simTimeDiff);

	protected:
		CacheContainer* load(char* filename);
		Node* getNode(CacheContainer* container);

	private:
		SpaceCraftContainer* parseXML(DOMDocument* doc);
		
		void buildSpaceCraftNode(SpaceCraftContainer* container);
	};
}