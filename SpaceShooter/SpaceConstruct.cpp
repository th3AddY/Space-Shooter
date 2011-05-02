#include "SpaceConstruct.h"

using namespace Shooter;

SpaceConstruct::SpaceConstruct()
	: m_prevSimTime(0),
	  m_currentState(0),
	  m_cursorTime(0),
	  m_ignoreSimTime(false)
{
	initializeXerces();
	initializeGraphicsMode();

	m_universe = new Universe();
	m_follower = new Follower();
}

SpaceConstruct::~SpaceConstruct()
{
	MeshCache::get().clear();
	ModelCache::get().clear();
	SpaceCraftBuilder::get().clear();
	ObstacleBuilder::get().clear();

	XMLPlatformUtils::Terminate();

	GraphicsContext::getWindowingSystemInterface()->
		setScreenResolution(0, m_nativeResolution[0], m_nativeResolution[1]);
}

bool SpaceConstruct::initializeXerces()
{
	try 
	{
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& e)
	{
		std::cout << "Xerces failed to load." << std::endl;
		std::cout << e.getMessage() << std::endl;

		return false;
	}

	return true;
}

void SpaceConstruct::setState(SpaceState* state)
{
	if (m_currentState != 0)
	{
		m_ignoreSimTime = m_currentState->isLoadingState();

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

void SpaceConstruct::preRender()
{
	if (m_ignoreSimTime)
		m_universe->useSceneGroup();

	recalcSimTime();
	updateCursor();
}

int SpaceConstruct::run()
{
	m_viewer.setSceneData(m_universe);
	m_viewer.setCamera(m_follower);

	m_viewer.realize();

	setUpCursor();

	m_prevSimTime = m_viewer.getFrameStamp()->getSimulationTime();
	while(m_universe->isRunning() && !m_viewer.done())
		m_viewer.frame();

	return 0;
}

void SpaceConstruct::recalcSimTime()
{
	m_currSimTime = m_viewer.getFrameStamp()->getSimulationTime();

	if (m_ignoreSimTime == true)
	{
		m_simTimeDiff = 0;
		m_ignoreSimTime = false;
	}
	else
	{
		m_simTimeDiff = m_currSimTime - m_prevSimTime;
	}

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

	if (m_currSimTime - m_cursorTime >= 0.02)
	{
		osgViewer::Viewer::Windows windows;
		m_viewer.getWindows(windows);

		(*windows.begin())->requestWarpPointer(m_gameResolution[0]/2, m_gameResolution[1]/2);
		m_currentState->updateMousePosition(m_gameResolution[0]/2, m_gameResolution[1]/2);
		m_cursorTime = m_currSimTime;
	}
}

void SpaceConstruct::setUpCursor()
{
	osgViewer::Viewer::Windows windows;
	m_viewer.getWindows(windows);

	(*windows.begin())->setCursor(osgViewer::GraphicsWindow::NoCursor);
}