#include "Human.h"

using namespace Shooter;

void Human::control()
{
	m_spaceCraft->controlDirection(Vec3(0, double(-m_inputState.mouseXspeed) * 0.00003, double(m_inputState.mouseYspeed) * 0.0001));


	if (m_inputState.keydown[97])
		m_spaceCraft->controlDirection(Vec3(-0.0002, 0, 0));

	if (m_inputState.keydown[100])
		m_spaceCraft->controlDirection(Vec3(0.0002, 0, 0));
}

void Human::useInputStateStamp(InputStateStamp stamp)
{
	m_inputState = stamp;
}
