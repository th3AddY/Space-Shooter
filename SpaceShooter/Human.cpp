#include "Human.h"

using namespace Shooter;

void Human::control()
{
	m_spaceCraft->controlDirection(Vec2(double(-m_inputState.mouseXspeed) * 0.0005, double(m_inputState.mouseYspeed) * 0.0015));


	if (m_inputState.keydown[97])
		m_spaceCraft->controlLateral(-0.1f);

	if (m_inputState.keydown[100])
		m_spaceCraft->controlLateral(0.1f);

	if (m_inputState.keydown[119])
		m_spaceCraft->accelerate();

	if (m_inputState.keydown[115])
		m_spaceCraft->retard();

}

void Human::useInputStateStamp(InputStateStamp stamp)
{
	m_inputState = stamp;
}
