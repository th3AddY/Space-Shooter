#include "BattleState.h"

using namespace Shooter;

void BattleState::initialize()
{
	
}

SpaceState* BattleState::update()
{
	Human* human;
	Player* player;

	unsigned int playerCount = m_universe->getPlayerCount();


	// assign Input state to human player to control the spacecraft
	if ((human = m_universe->getHumanPlayer()) != 0)
	{
		InputStateStamp stamp = getInputStateStamp();
		human->useInputStateStamp(stamp);
	}
	

	// controll spacecrafts
	for (unsigned int i=0; i<playerCount; i++)
	{
		player = m_universe->getPlayer(i);

		if (player->hasSpaceCraftAssigned())
			player->control();
	}


	// set follower behind human spacecraft
	if (human!=0)
	{
		SpaceCraft* humanSpaceCraft;

		if ((humanSpaceCraft = human->getSpaceCraft()) != 0)
			humanSpaceCraft->setFollowerPosition(m_follower);
	}


	m_follower->updateLookAtMatrix();
	m_universe->updateSkybox(m_follower);

	return 0;
}