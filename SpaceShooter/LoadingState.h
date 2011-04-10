#pragma once

#include <boost/thread/thread.hpp>

#include "SpaceState.h"

namespace Shooter
{
	class LoadingState : public SpaceState
	{
	public:
		LoadingState(SpaceState* nextState);

		void initialize();
		SpaceState* update();

		void setNextState(SpaceState* nextState);
	protected:
		virtual void loadingProcess() {}

		SpaceState* m_nextState;
	};
}