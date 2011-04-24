#include "LoadingUniverseState.h"

using namespace Shooter;

LoadingUniverseState::LoadingUniverseState(SpaceState* nextState)
	: LoadingState(nextState)
{
}

void LoadingUniverseState::loadingProcess()
{
	m_universe->addSkybox("skybox/Skycube02");

	PositionAttitudeTransform* transform;
	Geode* geode;
	for (int i=0; i<300; i++)
	{
		transform = new PositionAttitudeTransform();
		geode = new Geode();
		geode->addDrawable(new ShapeDrawable(new Sphere()));
		transform->addChild(geode);
		m_universe->getSceneGroup()->addChild(transform);
		transform->setPosition(Vec3(rand() % 200 - 100, rand() % 200 + 10, rand() % 200 - 100));
	}

	SpaceCraft* fighter = SpaceCraftBuilder::get().build("GameData/SpaceCrafts/Fighter.xml", m_simTimeDiff);
	SpaceCraft* cruiser = SpaceCraftBuilder::get().build("GameData/SpaceCrafts/Cruiser.xml", m_simTimeDiff);
	SpaceCraft* corsair = SpaceCraftBuilder::get().build("GameData/SpaceCrafts/Corsair.xml", m_simTimeDiff);
	SpaceCraft* frigate = SpaceCraftBuilder::get().build("GameData/SpaceCrafts/Frigate.xml", m_simTimeDiff);

	fighter->setPosition(Vec3(0, -200, 0));

	corsair->setPosition(Vec3(0, 200, 0));
	corsair->setAttitude(getQuatFromEuler(0, 0, 3.141));

	frigate->setPosition(Vec3(-200, 0, 0));
	frigate->setAttitude(getQuatFromEuler(0, -3.141/2, 0));

	cruiser->setPosition(Vec3(200, 0, 0));
	cruiser->setAttitude(getQuatFromEuler(0, 3.141/2, 0));

	m_universe->addSpaceCraft(fighter);
	m_universe->addSpaceCraft(cruiser);
	m_universe->addSpaceCraft(corsair);
	m_universe->addSpaceCraft(frigate);

	Human* human = new Human();
	human->assignSpaceCraft(fighter);

	m_universe->addPlayer(human);

	m_universe->build();
}