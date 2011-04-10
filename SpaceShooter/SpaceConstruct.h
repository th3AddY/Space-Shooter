#pragma once

#include "SpaceState.h"
#include "SpaceViewer.h"
#include "Universe.h"
#include "Follower.h"

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

		int run();
		void recalcSimTime();
		void updateCursor();
	private:
		void initializeGraphicsMode();

		SpaceState* m_currentState;

		SpaceViewer m_viewer;
		Follower* m_follower;
		Universe* m_universe;

		double m_currSimTime;
		double m_prevSimTime;
		double m_simTimeDiff;

		unsigned int m_nativeResolution[2];
		unsigned int m_gameResolution[2];
	};

}