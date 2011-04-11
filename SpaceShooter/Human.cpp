#include "Human.h"

using namespace Shooter;

void Human::control()
{
	m_spaceCraft->controlDirection(Vec3(0, double(-m_inputState.mouseXspeed) * 0.00001, double(m_inputState.mouseYspeed) * 0.00003));


	if (m_inputState.keydown[97])
		m_spaceCraft->controlDirection(Vec3(-0.0002, 0, 0));

	if (m_inputState.keydown[100])
		m_spaceCraft->controlDirection(Vec3(0.0002, 0, 0));

	if (m_inputState.keydown[119])
		m_spaceCraft->accelerate();

	if (m_inputState.keydown[115])
		m_spaceCraft->retard();

}

void Human::useInputStateStamp(InputStateStamp stamp)
{
	m_inputState = stamp;
}
