#include "Universe.h"

using namespace Shooter;

Universe::Universe()
	: Group(),
	  m_skyboxDirectory(""),
	  m_built(false),
	  m_humanPlayer(0)
{
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
		Human* human = dynamic_cast<Human*>(player);
		m_humanPlayer = human;
	} catch(int)
	{
	}
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

int Universe::build()
{
	if (m_built==false) {

		// build skybox
		m_skyboxTransform = new PositionAttitudeTransform();
		if (m_skyboxDirectory) {
			Geode* skybox = createSkyboxGeode(m_skyboxDirectory);

			m_skyboxTransform->addChild(skybox);
			addChild(m_skyboxTransform);
		}

		// setup lights
		LightSource* ls = new LightSource();
		ls->getLight()->setPosition(Vec4(0,-1,0,0));
		ls->getLight()->setAmbient(Vec4(0.1f, 0.1f, 0.1f, 1.0f));
		ls->getLight()->setDiffuse(Vec4(0.4f, 0.4f, 0.4f, 1.0f));
		ls->getLight()->setSpecular(Vec4(1.0f, 1.0f, 1.0f, 1.0f));

		addChild(ls);
		//////////////

		// setup root stateset
		getOrCreateStateSet()->setMode(GL_CULL_FACE, StateAttribute::ON);
		getStateSet()->setMode(GL_NORMALIZE, StateAttribute::ON);
		getStateSet()->setMode(GL_DEPTH_TEST, StateAttribute::ON);
		getStateSet()->setMode(GL_LIGHTING, StateAttribute::ON);
		getStateSet()->setMode(GL_LIGHT0, StateAttribute::ON);

		LightModel* lm = new LightModel();
		lm->setAmbientIntensity(Vec4(0.5f, 0.5f, 0.5f, 1.0f));
		getStateSet()->setAttribute(lm, StateAttribute::ON);
		//////////////

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

}

void Universe::updateSkybox(Follower* follower)
{
	m_skyboxTransform->setPosition(follower->getPosition());
}

bool Universe::isRunning()
{
	return true;
}