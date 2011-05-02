#pragma once

#include <iostream>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>

#include <osg/PositionAttitudeTransform>

#include "Cache.h"
#include "ModelCache.h"
#include "Misc.h"

using namespace xercesc;
using namespace osg;

namespace Shooter
{
	class ObstacleBuilder : public Cache<ObstacleBuilder>
	{
	protected:
		CacheContainer* load(char* filename);

	private:
		Node* parseXML(DOMDocument* doc);
	};
}