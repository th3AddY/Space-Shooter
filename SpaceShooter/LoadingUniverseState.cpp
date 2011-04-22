#include "LoadingUniverseState.h"

using namespace Shooter;

LoadingUniverseState::LoadingUniverseState(SpaceState* nextState)
	: LoadingState(nextState)
{
}

void LoadingUniverseState::loadingProcess()
{
	m_universe->destruct();

	m_universe->addSkybox("skybox/Skycube02");




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




	SpaceCraft* fighter = SpaceCraftBuilder::get()->fromFile("GameData/SpaceCrafts/Fighter.xml", m_simTimeDiff);
	SpaceCraft* cruiser = SpaceCraftBuilder::get()->fromFile("GameData/SpaceCrafts/Cruiser.xml", m_simTimeDiff);
	SpaceCraft* corsair = SpaceCraftBuilder::get()->fromFile("GameData/SpaceCrafts/Corsair.xml", m_simTimeDiff);
	SpaceCraft* frigate = SpaceCraftBuilder::get()->fromFile("GameData/SpaceCrafts/Frigate.xml", m_simTimeDiff);

	fighter->setPosition(Vec3(0, -200, 0));

	corsair->setPosition(Vec3(0, 200, 0));
	corsair->setAttitude(getQuatFromEuler(0, 0, 3.141));

	frigate->setPosition(Vec3(-200, 0, 0));
	frigate->setAttitude(getQuatFromEuler(0, -3.141/2, 0));

	cruiser->setPosition(Vec3(200, 0, 0));
	cruiser->setAttitude(getQuatFromEuler(0, 3.141/2, 0));



	m_universe->addChild(fighter);
	m_universe->addChild(cruiser);
	m_universe->addChild(corsair);
	m_universe->addChild(frigate);

	Human* human = new Human();
	human->assignSpaceCraft(fighter);

	m_universe->addPlayer(human);

	m_universe->build();
}