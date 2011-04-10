#pragma once

#include <osgViewer/Viewer>
#include <osgGA/GUIEventHandler>

using namespace osgViewer;
using namespace osgGA;

namespace Shooter
{

	class SpaceViewer : public Viewer
	{
		public:
			void removeEventHandler(GUIEventHandler* eventHandler);
	};

}