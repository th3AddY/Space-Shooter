#include "Follower.h"

using namespace Shooter;

Follower::Follower()
	: Camera()
{
	double projectionAngle = 45.0;
	double projectionNear = 0.1;
	double projectionFar = 200.0;
	unsigned int vpwidth;
	unsigned int vpheight;
	GraphicsContext::getWindowingSystemInterface()->getScreenResolution(0, vpwidth, vpheight);

	setClearColor(Vec4(0.0f, 0.0f, 0.0f, 1.0f));
	setProjectionMatrixAsPerspective(
		projectionAngle,
		double(vpwidth) / double(vpheight),
		projectionNear,
		projectionFar);
}

void Follower::updateLookAtMatrix()
{
	Vec3 eye(0.0f, 0.0f, 0.0f);
	Vec3 center(0.0f, 1.0f, 0.0f);
	Vec3 up(0.0f, 0.0f, 1.0f);

	m_transformation.setRotate(m_attitude);
	m_transformation.setTrans(m_position);

	transformVector(&eye, &m_transformation);
	transformVector(&center, &m_transformation);
	transformVector(&up, &m_transformation);

	up -= m_position;

	setViewMatrixAsLookAt(eye, center, up);
}

void Follower::move(Vec3f vec)
{
	transformVector(&vec, &m_transformation);
	m_position = vec;
	m_transformation.setTrans(m_position);
}

Vec3f Follower::getPosition()
{
	return m_position;
}

Quat Follower::getAttitude()
{
	return m_attitude;
}

void Follower::setPosition(Vec3f position)
{
	m_position = position;
}

void Follower::setAttitude(Quat attitude)
{
	m_attitude = attitude;
}