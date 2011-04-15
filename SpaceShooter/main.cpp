#include <iostream>
#include "osgViewer/Viewer"
#include "osg/Texture2D"
#include "osgDB/ReadFile"

#include "SpaceConstruct.h"
#include "SpaceConstructCallback.h"
#include "LoadingUniverseState.h"
#include "BattleState.h"

using namespace Shooter;


int main(int argc, char** argv)
{
	SpaceConstruct construct;
	construct.setUpdater(new SpaceConstructCallback(&construct));
	construct.setState(new LoadingUniverseState(new BattleState()));
	return construct.run();
}