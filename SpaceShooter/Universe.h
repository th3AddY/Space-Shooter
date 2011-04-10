#pragma once

#include <vector>

#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/LightSource>
#include <osg/LightModel>

#include "Follower.h"
#include "Misc.h"
#include "Human.h"

using namespace osg;
using namespace std;

namespace Shooter
{

	class Universe : public Group
	{
		public:
			Universe();

			void addSkybox(char* dir);

			int build();
			void destruct();

			void updateSkybox(Follower* follower);
			bool isRunning();

			void addPlayer(Player* player);
			Player* getPlayer(unsigned int i);
			unsigned int getPlayerCount();

			Human* getHumanPlayer();
		private:
			char* m_skyboxDirectory;
			PositionAttitudeTransform* m_skyboxTransform;

			bool m_built;

			vector<Player*> m_players;
			Human* m_humanPlayer;
	};

}