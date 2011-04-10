#include "SpaceConstruct.h"

using namespace Shooter;

SpaceConstruct::SpaceConstruct()
	: m_prevSimTime(0),
	  m_currentState(0)
{
	initializeGraphicsMode();

	m_universe = new Universe();
	m_follower = new Follower();
}

SpaceConstruct::~SpaceConstruct()
{
	GraphicsContext::getWindowingSystemInterface()->
		setScreenResolution(0, m_nativeResolution[0], m_nativeResolution[1]);
}

void SpaceConstruct::setState(SpaceState* state)
{
	if (m_currentState != 0)
	{
		state->assignInputState(m_currentState);
		state->flushEvents();
		m_viewer.removeEventHandler(m_currentState);
	}

	m_currentState = state;

	GameData data;
	data.universe = m_universe;
	data.follower = m_follower;
	data.simTime = &m_currSimTime;
	data.simTimeDiff = &m_simTimeDiff;

	m_currentState->setGameData(data);
	m_viewer.addEventHandler(m_currentState);

	m_currentState->initialize();
}

void SpaceConstruct::setUpdater(NodeCallback* callback)
{
	m_universe->setUpdateCallback(callback);
}

SpaceState* SpaceConstruct::getCurrentState()
{
	return m_currentState;
}

int SpaceConstruct::run()
{
	m_viewer.setSceneData(m_universe);
	m_viewer.setCamera(m_follower);

	m_viewer.realize();

	m_prevSimTime = m_viewer.getFrameStamp()->getSimulationTime();
	while(m_universe->isRunning() && !m_viewer.done())
		m_viewer.frame();

	return 0;
}

void SpaceConstruct::recalcSimTime()
{
	m_currSimTime = m_viewer.getFrameStamp()->getSimulationTime();
	m_simTimeDiff = m_currSimTime - m_prevSimTime;
    m_prevSimTime = m_currSimTime;
}

void SpaceConstruct::initializeGraphicsMode()
{
	GraphicsContext::getWindowingSystemInterface()->
		getScreenResolution(0, m_nativeResolution[0], m_nativeResolution[1]);

	// Soll später aus config.xml gelesen werden
	m_gameResolution[0] = m_nativeResolution[0]; // 1024;
	m_gameResolution[1] = m_nativeResolution[1]; // 768;

	GraphicsContext::getWindowingSystemInterface()->
		setScreenResolution(0, m_gameResolution[0], m_gameResolution[1]);
}

void SpaceConstruct::updateCursor()
{
	m_currentState->updateMouseMotion();
}