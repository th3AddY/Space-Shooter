#include "LoadingState.h"

using namespace Shooter;
using namespace boost;

LoadingState::LoadingState(SpaceState* nextState)
	: SpaceState(),
	  m_nextState(nextState)
{
}

void LoadingState::initialize()
{
	m_universe->destruct();
	m_universe->useMenuGroup();
}

SpaceState* LoadingState::update()
{
	//thread loadingThread(bind(&LoadingState::loadingProcess, this));

	//if (!loadingThread.joinable())
	//	return 0;
	// while(!loadingThread.joinable()); // busy wait, später Ladebildschirm rendern
	//loadingThread.join();
	loadingProcess();


	return m_nextState;
}

void LoadingState::setNextState(SpaceState* nextState)
{
	m_nextState = nextState;
}

bool LoadingState::isLoadingState()
{
	return true;
}