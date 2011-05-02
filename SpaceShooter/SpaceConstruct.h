#pragma once

#include <xercesc\util\PlatformUtils.hpp>

#include "SpaceState.h"
#include "SpaceViewer.h"
#include "Universe.h"
#include "Follower.h"
#include "SpaceCraftBuilder.h"
#include "ObstacleBuilder.h"

using namespace xercesc;

namespace Shooter
{

	class SpaceConstruct
	{
	public:
		SpaceConstruct();
		~SpaceConstruct();

		void setState(SpaceState* state);
		void setUpdater(NodeCallback* callback);

		SpaceState* getCurrentState();

		void preRender();
		int run();
	private:
		void recalcSimTime();
		void updateCursor();

		bool initializeXerces();
		void initializeGraphicsMode();
		void setUpCursor();

		SpaceState* m_currentState;

		SpaceViewer m_viewer;
		Follower* m_follower;
		Universe* m_universe;

		double m_currSimTime;
		double m_prevSimTime;
		double m_simTimeDiff;

		double m_cursorTime;

		unsigned int m_nativeResolution[2];
		unsigned int m_gameResolution[2];

		bool m_ignoreSimTime;
	};

}