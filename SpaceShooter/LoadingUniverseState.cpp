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

	Obstacle* spaceshipstation = ObstacleBuilder::get().build("GameData/Obstacles/Spaceshipstation.xml", m_simTimeDiff);
	spaceshipstation->setPosition(Vec3(200, 0, 200));
	m_universe->getSceneGroup()->addChild(spaceshipstation);

	Obstacle* spacestation = ObstacleBuilder::get().build("GameData/Obstacles/Spacestation.xml", m_simTimeDiff);
	spacestation->setPosition(Vec3(-100, 0, -100));
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
	bot3->assignSpaceCraft(frigate);

	Human* human = new Human();
	human->assignSpaceCraft(fighter);

	m_universe->addPlayer(bot1);
	m_universe->addPlayer(bot2);
	m_universe->addPlayer(bot3);
	m_universe->addPlayer(human);

	createTestParticleSystem(m_universe->getSceneGroup());


	m_universe->build();
}

void LoadingUniverseState::createTestParticleSystem(Group* root)
{
	// Create and initialize a particle system
 /* osgParticle::ParticleSystem *dustParticleSystem = new osgParticle::ParticleSystem;

 // Set the attributes 'texture', 'emmisive' and 'lighting'
 dustParticleSystem->setDefaultAttributes(
    "test/particle.tga", 
    true, false);

 // Since the particle system is derived from the class Drawable, we can create
 // add it to the scene as a child of a geode 
 osg::Geode *geode = new osg::Geode; 
 geode->addDrawable(dustParticleSystem);

// Add an 'updater' to help per-frame management
 osgParticle::ParticleSystemUpdater *dustSystemUpdater = new osgParticle::ParticleSystemUpdater;
 // Associate this updater with our particle system 
 dustSystemUpdater->addParticleSystem(dustParticleSystem);
 // add the updater node to the scene graph
 root->addChild(geode);
 root->addChild(dustSystemUpdater);

 // Create a partical to be used by our particle system and define a few
 // of its properties
 osgParticle::Particle smokeParticle; 
 smokeParticle.setSizeRange(osgParticle::rangef(0.1,20.0)); // meters
 smokeParticle.setLifeTime(4); // seconds
 smokeParticle.setMass(0.0); // in kilograms
 // Make this our particle system's default particle 
 dustParticleSystem->setDefaultParticleTemplate(smokeParticle);

 // Create a modular emitter (this contains default counter, placer and shooter.)
 osgParticle::ModularEmitter *emitter = new osgParticle::ModularEmitter;
 // Associate this emitter with the particle system 
 emitter->setParticleSystem(dustParticleSystem);

 // Get a handle to the emitter's counter and adjust the number of new particles
 // that will be added each frame
 osgParticle::RandomRateCounter *dustRate = 
    static_cast<osgParticle::RandomRateCounter *>(emitter->getCounter());
 dustRate->setRateRange(5, 10); // generate 5 to 10 particles per second

 // To customize the placer, create and initialize a multi-segment placer 
 osgParticle::MultiSegmentPlacer* lineSegment = new osgParticle::MultiSegmentPlacer();
 // Add vertices to our placer. This defines line seqments along which our particles will
 // originate. (If we co-locate a tank and this emitter, this will result in dust particles
 // originating from a line extending below and behind the tank model.) 
 lineSegment->addVertex(0,0,-2);
 lineSegment->addVertex(0,-2,-2);
 lineSegment->addVertex(0,-16,0);
 // Use this placer for our emitter 
 emitter->setPlacer(lineSegment);

 // To customize the shooter, create and initialize a radial shooter 
 osgParticle::RadialShooter* smokeShooter = new osgParticle::RadialShooter();
 // Set properties of this shooter 
 smokeShooter->setThetaRange(0.0, 3.14159/4); // radians, relative to Z axis.
 smokeShooter->setInitialSpeedRange(50,100); // meters/second
 // Use this shooter for our emitter
 emitter->setShooter(smokeShooter);

 root->addChild(emitter);

     // Create a modular program and attach it to our particle system
    osgParticle::ModularProgram *moveDustInAir = new osgParticle::ModularProgram;
    moveDustInAir->setParticleSystem(dustParticleSystem);

    // Create an operator that simulates gravity, adjust it and add it to our program
    osgParticle::AccelOperator *accelUp = new osgParticle::AccelOperator;
    accelUp->setToGravity(-0.5); // scale factor for normal acceleration due to gravity. 
    moveDustInAir->addOperator(accelUp);

    // Add an operator to our program to calculate the friction of air.
    osgParticle::SinkOperator *airFriction = new osgParticle::SinkOperator;
    // airFriction->setSinkStrategy( //->setFluidToAir();

    moveDustInAir->addOperator(airFriction);

    // Finally, add the program to the scene 
    root->addChild(moveDustInAir); */

}