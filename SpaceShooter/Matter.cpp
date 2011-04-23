#include "Matter.h"

using namespace Shooter;

Matter::Matter()
{
}

void Matter::setSimTimePointer(double* simTimeDiff)
{
	m_simTimeDiff = simTimeDiff;
}

void Matter::move(Vec3f vec)
{
	Matrix mat;
	mat.setRotate(getAttitude());

	transformVector(&vec, &mat);

	setPosition(getPosition() + vec);
}