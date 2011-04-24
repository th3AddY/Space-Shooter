#include "Universe.h"

using namespace Shooter;

Universe::Universe()
	: Group(),
	  m_skyboxDirectory(""),
	  m_built(false),
	  m_humanPlayer(0)
{
	m_sceneGroup = new Group();
	m_menuGroup = new Group();

	addChild(m_menuGroup);
}

Universe::~Universe()
{
	m_sceneGroup.release();
	m_menuGroup.release();
}

void Universe::addSkybox(char *dir)
{
	m_skyboxDirectory = dir;
}

void Universe::addPlayer(Player* player)
{
	m_players.push_back(player);

	try
	{
		Human* human = static_cast<Human*>(player);
		m_humanPlayer = human;
	} catch(int)
	{
	}
}

void Universe::addSpaceCraft(SpaceCraft* spaceCraft)
{
	m_spaceCrafts.push_back(spaceCraft);
}

Player* Universe::getPlayer(unsigned int i)
{
	return m_players[i];
}

unsigned int Universe::getPlayerCount()
{
	return m_players.size();
}

Human* Universe::getHumanPlayer()
{
	if (m_humanPlayer != 0)
		return m_humanPlayer;

	return 0;
}

Group* Universe::getSceneGroup()
{
	return m_sceneGroup;
}

Group* Universe::getMenuGroup()
{
	return m_menuGroup;
}

void Universe::useSceneGroup()
{
	removeChild(m_menuGroup);
	addChild(m_sceneGroup);

	for (unsigned int i=0; i<m_spaceCrafts.size(); i++)
	{
		m_spaceCrafts[i]->prepare();
		m_spaceCrafts[i]->setUpdateCallback(new MatterCallback());
	}
}

void Universe::useMenuGroup()
{
	removeChild(m_sceneGroup);
	addChild(m_menuGroup);
}

int Universe::build()
{
	if (m_built==false) {

		// build skybox
		m_skyboxTransform = new PositionAttitudeTransform();
		if (m_skyboxDirectory) {
			Geode* skybox = createSkyboxGeode(m_skyboxDirectory);

			m_skyboxTransform->addChild(skybox);
			m_sceneGroup->addChild(m_skyboxTransform);
		}

		// setup lights
		LightSource* ls = new LightSource();
		ls->getLight()->setPosition(Vec4(0,-1,0,0));
		ls->getLight()->setAmbient(Vec4(0.1f, 0.1f, 0.1f, 1.0f));
		ls->getLight()->setDiffuse(Vec4(0.4f, 0.4f, 0.4f, 1.0f));
		ls->getLight()->setSpecular(Vec4(1.0f, 1.0f, 1.0f, 1.0f));

		m_sceneGroup->addChild(ls);
		//////////////

		// setup root stateset
		m_sceneGroup->getOrCreateStateSet()->setMode(GL_CULL_FACE, StateAttribute::ON);
		m_sceneGroup->getStateSet()->setMode(GL_NORMALIZE, StateAttribute::ON);
		m_sceneGroup->getStateSet()->setMode(GL_DEPTH_TEST, StateAttribute::ON);
		m_sceneGroup->getStateSet()->setMode(GL_LIGHTING, StateAttribute::ON);
		m_sceneGroup->getStateSet()->setMode(GL_LIGHT0, StateAttribute::ON);

		LightModel* lm = new LightModel();
		lm->setAmbientIntensity(Vec4(0.7f, 0.7f, 0.7f, 1.0f));
		m_sceneGroup->getStateSet()->setAttribute(lm, StateAttribute::ON);
		//////////////

		for (unsigned int i=0; i<m_spaceCrafts.size(); i++)
			m_sceneGroup->addChild(m_spaceCrafts[i]);

		m_built=true;
		return 0;
	} else
		return 1;
}

void Universe::destruct()
{
	if (m_skyboxDirectory!="")
	{
		removeChild(m_skyboxTransform);
		m_skyboxDirectory = "";
	}

	for (unsigned int i=0; i<m_spaceCrafts.size(); i++)
		m_sceneGroup->removeChild(m_spaceCrafts[i]);

	for (unsigned int i=0; i<m_players.size(); i++)
		delete m_players[i];
}

void Universe::updateSkybox(Follower* follower)
{
	m_skyboxTransform->setPosition(follower->getPosition());
}

bool Universe::isRunning()
{
	return true;
}