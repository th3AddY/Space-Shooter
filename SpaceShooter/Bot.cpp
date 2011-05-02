#include "Bot.h"

using namespace Shooter;

void Bot::control()
{
	m_spaceCraft->controlDirection(Vec2(double(0.0005), 0));
}