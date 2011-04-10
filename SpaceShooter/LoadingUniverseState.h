#pragma once

#include "LoadingState.h"
#include "SpaceCraft.h"
#include "Human.h"

#include <osg/ShapeDrawable>

namespace Shooter
{
	class LoadingUniverseState : public LoadingState
	{
	public:
		LoadingUniverseState(SpaceState* nextState);

	protected:
		void loadingProcess();
	};
}