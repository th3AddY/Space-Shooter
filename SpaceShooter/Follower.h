#pragma once

#include <osg/Camera>

#include "Misc.h"

using namespace osg;

namespace Shooter {

	class Follower : public Camera
	{
		public:
			Follower();

			Vec3f getPosition();
			Quat getAttitude();
			
			void setPosition(Vec3f position);
			void setAttitude(Quat rotation);

			void move(Vec3f vec);

			void updateLookAtMatrix();
		private:
			Matrix m_transformation;
			Vec3f m_position;
			Quat m_attitude;
	};
}