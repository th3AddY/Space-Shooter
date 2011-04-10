#include "Player.h"

using namespace Shooter;

bool Player::hasSpaceCraftAssigned()
{
	return (m_spaceCraft != 0);
}

void Player::assignSpaceCraft(SpaceCraft* spaceCraft)
{
	m_spaceCraft = spaceCraft;
}

SpaceCraft* Player::getSpaceCraft()
{
	return m_spaceCraft;
}