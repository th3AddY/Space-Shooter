#pragma once

#include <math.h>

#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osgDB/ReadFile>

#include "Matter.h"
#include "Follower.h"
#include "MatterCallback.h"

using namespace osg;
using namespace osgDB;

namespace Shooter
{
	typedef struct _spaceCraftParams
	{
		float defaultSpeed;
		float maxSpeed;
		float minSpeed;

		float forwardAcceleration;
		float backwardAcceleration;
		float defaultSpeedAcceleration;

		float maxLateralDeflection;
		float maxAttitudeDeflection;
		float attitudeReduction;

		Vec3 followerPosition;
		Quat followerAttitude;
		float followerConvergence;
	} SpaceCraftParams;

	class SpaceCraft : public Matter
	{
	public:
		SpaceCraft(double* simTimeDiff);

		void update();

		void controlDirection(Vec2 direction);
		void controlLateral(float direction);

		void accelerate();
		void retard();
		
		void setFollowerPosition(Follower* follower);

	private:
		// Speed control
		SpaceCraftParams m_params;

		bool m_accelerated;
		float m_speed;

		// Attitude Control
		Vec2 m_attitudeAcceleration;
		float m_lateralAcceleration;

		// Follower data
		Vec3 m_followerPosition;
		Quat m_followerAttitude;

		void goToDefaultSpeed();
		void getFollowerPosition(Vec3* position, Quat* attitude);
	};
}