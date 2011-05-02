#include "LoadingUniverseState.h"

using namespace Shooter;

LoadingUniverseState::LoadingUniverseState(SpaceState* nextState, char* levelFile)
	: LoadingState(nextState),
	  m_levelFile(levelFile)
{
}

void LoadingUniverseState::loadingProcess()
{
	m_universe->loadFromFile(m_levelFile);

	/* PositionAttitudeTransform* transform;
	Geode* geode;
	for (int i=0; i<300; i++)
	{
		transform = new PositionAttitudeTransform();
		geode = new Geode();
		geode->addDrawable(new ShapeDrawable(new Sphere()));
		transform->addChild(geode);
		m_universe->getSceneGroup()->addChild(transform);
		transform->setPosition(Vec3(rand() % 200 - 100, rand() % 200 + 10, rand() % 200 - 100));
	} */
	PositionAttitudeTransform* transform = new PositionAttitudeTransform();
	transform->setScale(Vec3(10, 10, 10));
	transform->setPosition(Vec3(20, 20, 20));

	Geode* geode = new Geode();

	m_universe->getSceneGroup()->addChild(transform);
	transform->addChild(geode);
	geode->addDrawable(new ShapeDrawable(new Sphere()));

	Material* material = new Material();
	material->setAmbient(Material::FRONT_AND_BACK, Vec4(0.1, 0.1, 0.1, 1));
	material->setDiffuse(Material::FRONT_AND_BACK, Vec4(0.6, 0.6, 0.6, 1));
	material->setSpecular(Material::FRONT_AND_BACK, Vec4(0.2, 0.2, 0.2, 1));
	material->setShininess(Material::FRONT_AND_BACK, 64);

	transform->getOrCreateStateSet()->setAttribute(material, StateAttribute::ON);


	SpaceCraft* fighter = SpaceCraftBuilder::get().build("GameData/SpaceCrafts/Fighter.xml", m_simTimeDiff);
	SpaceCraft* cruiser = SpaceCraftBuilder::get().build("GameData/SpaceCrafts/Cruiser.xml", m_simTimeDiff);
	SpaceCraft* corsair = SpaceCraftBuilder::get().build("GameData/SpaceCrafts/Corsair.xml", m_simTimeDiff);
	SpaceCraft* frigate = SpaceCraftBuilder::get().build("GameData/SpaceCrafts/Frigate.xml", m_simTimeDiff);

	// Node* spaceshipstation = ObstacleBuilder::get().fromFile("GameData/Obstacles/Spaceshipstation.xml");
	// m_universe->getSceneGroup()->addChild(spaceshipstation);

	Node* spacestation = ObstacleBuilder::get().fromFile("GameData/Obstacles/Spacestation.xml");
	m_universe->getSceneGroup()->addChild(spacestation);


	frigate->setPosition(Vec3(0, -200, 0));

	corsair->setPosition(Vec3(0, 200, 0));
	corsair->setAttitude(getQuatFromEuler(0, 0, 3.141));

	fighter->setPosition(Vec3(-200, 0, 0));
	fighter->setAttitude(getQuatFromEuler(0, -3.141/2, 0));

	cruiser->setPosition(Vec3(200, 0, 0));
	cruiser->setAttitude(getQuatFromEuler(0, 3.141/2, 0));

	fighter->prepare();
	cruiser->prepare();
	corsair->prepare();
	frigate->prepare();

	m_universe->addSpaceCraft(fighter);
	m_universe->addSpaceCraft(cruiser);
	m_universe->addSpaceCraft(corsair);
	m_universe->addSpaceCraft(frigate);

	Bot* bot1 = new Bot();
	bot1->assignSpaceCraft(cruiser);

	Bot* bot2 = new Bot();
	bot2->assignSpaceCraft(corsair);

	Bot* bot3 = new Bot();
	bot3->assignSpaceCraft(fighter);

	Human* human = new Human();
	human->assignSpaceCraft(frigate);

	m_universe->addPlayer(bot1);
	m_universe->addPlayer(bot2);
	m_universe->addPlayer(bot3);
	m_universe->addPlayer(human);


	m_universe->build();
}