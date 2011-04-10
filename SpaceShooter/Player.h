#pragma once

#include "SpaceCraft.h"

namespace Shooter
{
	class Player
	{
	public:
		bool hasSpaceCraftAssigned();
		virtual void control() {}

		void assignSpaceCraft(SpaceCraft* spaceCraft);
		SpaceCraft* getSpaceCraft();
	protected:
		SpaceCraft* m_spaceCraft;
	};
}