#pragma once

#include <osg/Geode>
#include <osg/ShapeDrawable>

#include "Matter.h"
#include "Follower.h"
#include "MatterCallback.h"

using namespace osg;

namespace Shooter
{
	class SpaceCraft : public Matter
	{
	public:
		SpaceCraft(double* simTimeDiff);

		void update();

		void controlDirection(Vec3 direction);
		
		void setFollowerPosition(Follower* follower);

	private:

		Vec3 m_attitudeAcceleration;
	};
}