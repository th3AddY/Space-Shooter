#pragma once

#include "CacheContainer.h"
#include "SpaceCraft.h"

namespace Shooter
{
	class SpaceCraftContainer : public CacheContainer
	{
	public:
		char* modelFilename;

		/* Vec3 position;
		Vec3 scale;
		Quat attitude; */

		SpaceCraftParams params;
	};
}