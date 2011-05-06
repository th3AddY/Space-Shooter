#pragma once

#include <iostream>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>

#include <osg/PositionAttitudeTransform>

#include "Cache.h"
#include "ModelCache.h"
#include "Misc.h"
#include "Obstacle.h"

using namespace xercesc;
using namespace osg;

namespace Shooter
{
	class ObstacleBuilder : public Cache<ObstacleBuilder>
	{
	public:
		Obstacle* build(char* filename, double* simTimeDiff);
	protected:
		CacheContainer* load(char* filename);
		Node* getNode(CacheContainer* container);

	private:
		Node* parseXML(DOMDocument* doc);
	};
}