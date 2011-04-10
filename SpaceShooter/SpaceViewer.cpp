#include "SpaceViewer.h"

using namespace Shooter;

void SpaceViewer::removeEventHandler(GUIEventHandler* eventHandler)
{
	osgViewer::View::EventHandlers::iterator it = std::find(_eventHandlers.begin(), _eventHandlers.end(), eventHandler);
	if (it != _eventHandlers.end())
		_eventHandlers.erase(it);
}