#pragma once

#include <xercesc/dom/DOM.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>

#include <osg/PositionAttitudeTransform>

#include "Cache.h"
#include "MeshCache.h"

using namespace osg;

namespace Shooter
{
	class ModelCache : public Cache<ModelCache>
	{
	protected:
		CacheContainer* load(char* filename);

	private:
		CacheContainer* parseXML(DOMDocument* doc);
	};
}