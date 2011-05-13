#pragma once

#include <string>
#include <algorithm>
#include <cctype>

#include <xercesc/dom/DOM.hpp>

#include <osg/Vec3>
#include <osg/Matrix>
#include <osg/Geode>
#include <osg/Texture2D>
#include <osg/Depth>
#include <osgDB/ReadFile>
#include <osgUtil/TangentSpaceGenerator>

using namespace std;
using namespace osg;
using namespace osgDB;
using namespace xercesc;

namespace Shooter
{
	const unsigned int MOUSE_LEFT = 1;
	const unsigned int MOUSE_MIDDLE = 2;
	const unsigned int MOUSE_RIGHT = 4;

	const unsigned int KEY_A = 97;
	const unsigned int KEY_D = 100;
	const unsigned int KEY_S = 115;
	const unsigned int KEY_W = 119;

	typedef struct _inputStateStamp
	{
		bool keydown[256];
		bool keyhit[256];

		bool mousedown[8];
		bool mousehit[8];

		int mouseXspeed;
		int mouseYspeed;
	} InputStateStamp;

	void checkKeysAndMouse(bool* keys, bool* mouse);

	Geode* createSkyboxGeode(char* dir);

	void transformVector(Vec3* vec, Matrixd* mat);
	Quat getQuatFromEuler(double heading, double attitude, double bank);

	string getLower(const char* text);
	
	void generateTangentAndBinormal(Node* node);

	// XML Helper
	float XMLGetScalar(DOMNode* node);
	Vec3 XMLGetVec3(DOMNode* node);
	Quat XMLGetQuat(DOMNode* node);
	Vec4 XMLGetColor(DOMNode* node);

}