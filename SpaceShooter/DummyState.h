#pragma once

#include "SpaceState.h"

using namespace osg;

namespace Shooter {

	class FreeLookState : public SpaceState
	{
		public:
			FreeLookState(Vec3 rotation);

			SpaceState* update();
		private:
			Vec3 m_freeLookAngle;
	};

}