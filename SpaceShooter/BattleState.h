#pragma once

#include "SpaceState.h"

namespace Shooter
{
	class BattleState : public SpaceState
	{
	public:
		void initialize();
		SpaceState* update();
	};
}