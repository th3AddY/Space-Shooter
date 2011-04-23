#pragma once

#include <osg/PositionAttitudeTransform>

#include "Misc.h"

using namespace osg;

namespace Shooter
{
	class Matter : public PositionAttitudeTransform
	{
	public:
		Matter();

		void setSimTimePointer(double* simTimeDiff);

		virtual void update() {}

		void move(Vec3f vec);
	
	protected:
		double* m_simTimeDiff;
	};
}