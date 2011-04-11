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
		void accelerate();
		void retard();
		
		void setFollowerPosition(Follower* follower);

	private:
		// Speed control
		bool m_accelerated;
		float m_minSpeed;
		float m_maxSpeed;

		float m_defaultSpeed;
		float m_speed;

		void goToDefaultSpeed();

		// Attitude Control
		Vec3 m_attitudeAcceleration;
	};
}