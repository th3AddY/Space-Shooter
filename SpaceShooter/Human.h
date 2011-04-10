#pragma once

#include "Player.h"
#include "Misc.h"

namespace Shooter
{
	class Human : public Player
	{
	public:
		void control();

		void useInputStateStamp(InputStateStamp stamp);

	private:
		InputStateStamp m_inputState;
	};
}