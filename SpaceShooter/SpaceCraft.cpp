#include "SpaceCraft.h"

using namespace Shooter;

SpaceCraft::SpaceCraft(double* simTimeDiff)
	: Matter(simTimeDiff),
	  m_attitudeAcceleration(0, 0, 0)
{
	Geode* geode = new Geode();
	geode->addDrawable(new ShapeDrawable(new Box()));
	addChild(geode);

	setUpdateCallback(new MatterCallback());
}

void SpaceCraft::update()
{
	move(Vec3(0, 3 * float(*m_simTimeDiff), 0));

	Matrix mat;
	mat.mult(Matrix::rotate(getQuatFromEuler(m_attitudeAcceleration.x(), m_attitudeAcceleration.y(), m_attitudeAcceleration.z())), Matrix::rotate(getAttitude()));

	setAttitude(mat.getRotate());

	m_attitudeAcceleration *= 0.95;
}

void SpaceCraft::controlDirection(Vec3 direction)
{
	m_attitudeAcceleration += direction;

}

void SpaceCraft::setFollowerPosition(Follower* follower)
{
	Matrix mat = Matrix::rotate(getAttitude());
	Vec3 position = Vec3(0, -10, 3);

	transformVector(&position, &mat);

	follower->setPosition(getPosition() + position);
	follower->setAttitude(getAttitude());
}