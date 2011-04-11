#pragma once

#include <osg/Vec3>
#include <osg/Matrix>
#include <osg/Geode>
#include <osg/Texture2D>
#include <osg/Depth>
#include <osgDB/ReadFile>

using namespace osg;
using namespace osgDB;

namespace Shooter
{
	typedef struct _inputStateStamp
	{
		bool keydown[256];
		bool keyhit[256];

		bool mousedown[8];
		bool mousehit[8];

		int mouseXspeed;
		int mouseYspeed;
	} InputStateStamp;

	void checkKeys(bool* keys);

	Geode* createSkyboxGeode(char* dir);

	void transformVector(Vec3* vec, Matrixd* mat);
	Quat getQuatFromEuler(double heading, double attitude, double bank);
}