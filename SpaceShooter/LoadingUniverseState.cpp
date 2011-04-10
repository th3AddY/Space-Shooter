#include "LoadingUniverseState.h"

using namespace Shooter;

LoadingUniverseState::LoadingUniverseState(SpaceState* nextState)
	: LoadingState(nextState)
{
}

void LoadingUniverseState::loadingProcess()
{
	m_universe->destruct();

	m_universe->addSkybox("skybox/cosmo02");




	PositionAttitudeTransform* transform;
	Geode* geode;
	for (int i=0; i<300; i++)
	{
		transform = new PositionAttitudeTransform();
		geode = new Geode();
		geode->addDrawable(new ShapeDrawable(new Sphere()));
		transform->addChild(geode);
		m_universe->addChild(transform);
		transform->setPosition(Vec3(rand() % 200 - 100, rand() % 200 + 10, rand() % 200 - 100));
	}




	SpaceCraft* spaceCraft = new SpaceCraft(m_simTimeDiff);
	SpaceCraft* spaceCraft2 = new SpaceCraft(m_simTimeDiff);

	m_universe->addChild(spaceCraft);
	m_universe->addChild(spaceCraft2);

	spaceCraft2->setPosition(Vec3(-20,50, 0));
	spaceCraft2->setAttitude(getQuatFromEuler(0, - 3.1415962 / 2, 0));


	Human* human = new Human();
	human->assignSpaceCraft(spaceCraft);

	m_universe->addPlayer(human);

	m_universe->build();
}