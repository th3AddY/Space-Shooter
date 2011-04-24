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
			~Universe();

			void addSkybox(char* dir);

			int build();
			void destruct();

			void updateSkybox(Follower* follower);
			bool isRunning();

			void addPlayer(Player* player);
			Player* getPlayer(unsigned int i);
			unsigned int getPlayerCount();

			void addSpaceCraft(SpaceCraft* spaceCraft);

			Human* getHumanPlayer();

			Group* getSceneGroup();
			Group* getMenuGroup();

			void useSceneGroup();
			void useMenuGroup();
		private:
			char* m_skyboxDirectory;
			PositionAttitudeTransform* m_skyboxTransform;

			bool m_built;

			vector<Player*> m_players;
			vector<SpaceCraft*> m_spaceCrafts;

			Human* m_humanPlayer;

			ref_ptr<Group> m_menuGroup;
			ref_ptr<Group> m_sceneGroup;
	};

}