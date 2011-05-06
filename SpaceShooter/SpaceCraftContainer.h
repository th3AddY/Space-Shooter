#pragma once

#include "CacheContainer.h"
#include "SpaceCraft.h"

namespace Shooter
{
	class SpaceCraftContainer : public CacheContainer
	{
	public:
		char* modelFilename;

		SpaceCraftParams params;
	};
}