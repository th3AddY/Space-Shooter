#pragma once

#include "LoadingState.h"
#include "SpaceCraft.h"
#include "Human.h"
#include "Bot.h"
#include "SpaceCraftBuilder.h"
#include "ObstacleBuilder.h"

#include <osg/ShapeDrawable>
#include <osgParticle/ParticleSystem>
#include <osgParticle/ParticleSystemUpdater>
#include <osgParticle/ModularEmitter>
#include <osgParticle/MultiSegmentPlacer>
#include <osgParticle/ModularProgram>
#include <osgParticle/AccelOperator>
#include <osgParticle/SinkOperator>

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

		void createTestParticleSystem(Group* root);
	};
}