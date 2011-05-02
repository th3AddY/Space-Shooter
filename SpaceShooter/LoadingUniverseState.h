#pragma once

#include "LoadingState.h"
#include "SpaceCraft.h"
#include "Human.h"
#include "Bot.h"
#include "SpaceCraftBuilder.h"
#include "ObstacleBuilder.h"

#include <osg/ShapeDrawable>

namespace Shooter
{
	class LoadingUniverseState : public LoadingState
	{
	public:
		LoadingUniverseState(SpaceState* nextState, char* levelFile);

	protected:
		void loadingProcess();

	private:
		char* m_levelFile;
	};
}