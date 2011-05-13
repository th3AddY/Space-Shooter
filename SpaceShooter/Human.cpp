#include "Human.h"

using namespace Shooter;

void Human::control()
{

	if (m_inputState.mousedown[MOUSE_MIDDLE])
	{
		if (m_inputState.mousedown[MOUSE_LEFT])
			m_spaceCraft->accelerate();

		if (m_inputState.mousedown[MOUSE_RIGHT])
			m_spaceCraft->retard();

		m_spaceCraft->controlDirection(Vec2(0, double(m_inputState.mouseYspeed) * 0.0015));
		m_spaceCraft->controlLateral(float(m_inputState.mouseXspeed) * 0.005);
	}
	else
	{
		m_spaceCraft->controlDirection(Vec2(double(-m_inputState.mouseXspeed) * 0.0005, double(m_inputState.mouseYspeed) * 0.0015));
		m_spaceCraft->controlLateral(float(m_inputState.mouseXspeed) * 0.0005);
	}

	if (m_inputState.keydown[KEY_A])
		m_spaceCraft->controlLateral(-0.1f);

	if (m_inputState.keydown[KEY_D])
		m_spaceCraft->controlLateral(0.1f);

	if (m_inputState.keydown[KEY_W])
		m_spaceCraft->accelerate();

	if (m_inputState.keydown[KEY_S])
		m_spaceCraft->retard();
	
	// checkKeysAndMouse(&m_inputState.keydown[0], &m_inputState.mousedown[0]);
}

void Human::useInputStateStamp(InputStateStamp stamp)
{
	m_inputState = stamp;
}
