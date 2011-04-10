#include "SpaceState.h"

using namespace Shooter;

SpaceState::SpaceState()
	: GUIEventHandler()
{
	for (int i=0; i<256; i++) {
		if (i<8) {
			m_input.inputState.mousedown[i] = false;
			m_input.inputState.mousehit[i] = false;
		}

		m_input.inputState.keydown[i] = false;
		m_input.inputState.keyhit[i] = false;
	}

	m_input.mouseX = m_input.mouseXold = 0;
	m_input.mouseY = m_input.mouseYold = 0;
	m_input.inputState.mouseXspeed = m_input.mouseXspeed_ret = 0;
	m_input.inputState.mouseYspeed = m_input.mouseYspeed_ret = 0;
}

void SpaceState::setGameData(GameData data)
{
	m_universe = data.universe;
	m_follower = data.follower;
	m_simTime = data.simTime;
	m_simTimeDiff = data.simTimeDiff;
}

bool SpaceState::keyDown(int key)
{
	return m_input.inputState.keydown[key];
}

bool SpaceState::keyHit(int key)
{
	bool res = m_input.inputState.keyhit[key];
	m_input.inputState.keyhit[key] = false;
	return res;
}

bool SpaceState::mouseDown(int button)
{
	return m_input.inputState.mousedown[button];
}

bool SpaceState::mouseHit(int button)
{
	bool res = m_input.inputState.mousehit[button];
	m_input.inputState.mousehit[button] = false;
	return res;
}

int SpaceState::getMouseXspeed()
{
	return m_input.inputState.mouseXspeed;
}

int SpaceState::getMouseYspeed()
{
	return m_input.inputState.mouseYspeed;
}

void SpaceState::updateMouseMotion()
{
	m_input.inputState.mouseXspeed = m_input.mouseXspeed_ret;
	m_input.inputState.mouseYspeed = m_input.mouseYspeed_ret;
	m_input.mouseXspeed_ret = 0;
	m_input.mouseYspeed_ret = 0;
}

void SpaceState::updateMousePosition(unsigned int x, unsigned int y)
{
	m_input.mouseXold = x;
	m_input.mouseYold = y;
}

void SpaceState::assignInputState(SpaceState* state)
{
	m_input = state->getInputData();
}

void SpaceState::flushEvents()
{
	for (int i=0; i<256; i++)
	{
		if (i<8)
			m_input.inputState.mousehit[i] = false;

		m_input.inputState.keyhit[i] = false;
	}
}

InputData SpaceState::getInputData()
{
	return m_input;
}

InputStateStamp SpaceState::getInputStateStamp()
{
	return m_input.inputState;
}

bool SpaceState::handle(const GUIEventAdapter& ea, GUIActionAdapter&)
{
	switch(ea.getEventType())
	{
		case(GUIEventAdapter::PUSH):
		{
			int button = ea.getButton();
			if (button >= 0 && button < 8)
				m_input.inputState.mousedown[button] = true;

			return false;
		}
		case(GUIEventAdapter::RELEASE):
		{
			int button = ea.getButton();
			if (button >= 0 && button < 8) {
				m_input.inputState.mousedown[button] = false;
				m_input.inputState.mousehit[button] = true;
			}

			return false;
		}
		case(GUIEventAdapter::KEYDOWN):
		{
			int key = ea.getKey();
			if (key >= 0 && key < 256)
				m_input.inputState.keydown[key] = true;

			return false;
		}
		case(GUIEventAdapter::KEYUP):
		{
			int key = ea.getKey();
			if (key >= 0 && key < 256) {
				m_input.inputState.keydown[key] = false;
				m_input.inputState.keyhit[key] = true;
			}

			return false;
		}
		case(GUIEventAdapter::DRAG):;
		case(GUIEventAdapter::MOVE):
		{
			m_input.mouseX = ea.getX();
			m_input.mouseY = ea.getY();
			m_input.mouseXspeed_ret = m_input.mouseX - m_input.mouseXold;
			m_input.mouseYspeed_ret = m_input.mouseY - m_input.mouseYold;
			m_input.mouseXold = m_input.mouseX;
			m_input.mouseYold = m_input.mouseY;

			return false;
		}
		default:
			return false;
	}
}