#include "SpaceCraft.h"

using namespace Shooter;

SpaceCraft::SpaceCraft(double* simTimeDiff)
	: Matter(simTimeDiff),
	  m_attitudeAcceleration(0, 0, 0),
	  m_defaultSpeed(12),
	  m_speed(m_defaultSpeed),
	  m_minSpeed(5),
	  m_maxSpeed(48),
	  m_accelerated(false)
{
	Geode* geode = new Geode();
	geode->addDrawable(new ShapeDrawable(new Box()));
	addChild(geode);

	setUpdateCallback(new MatterCallback());
}

void SpaceCraft::update()
{
	if (!m_accelerated)
		goToDefaultSpeed();
	else
		m_accelerated = false;

	move(Vec3(0, m_speed * float(*m_simTimeDiff), 0));

	Matrix mat;
	mat.mult(Matrix::rotate(getQuatFromEuler(m_attitudeAcceleration.x(), m_attitudeAcceleration.y(), m_attitudeAcceleration.z())), Matrix::rotate(getAttitude()));

	setAttitude(mat.getRotate());

	m_attitudeAcceleration *= 0.95;
}

void SpaceCraft::accelerate()
{
	m_speed += 15 * float(*m_simTimeDiff);
	if (m_speed > m_maxSpeed)
		m_speed = m_maxSpeed;

	m_accelerated = true;
}

void SpaceCraft::retard()
{
	m_speed -= 15 * float(*m_simTimeDiff);
	if (m_speed < m_minSpeed)
		m_speed = m_minSpeed;

	m_accelerated = true;
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

void SpaceCraft::goToDefaultSpeed()
{
	if (m_speed > m_defaultSpeed)
	{
		m_speed -= 20 * (*m_simTimeDiff);
		if (m_speed < m_defaultSpeed)
			m_speed = m_defaultSpeed;
	}

	if (m_speed < m_defaultSpeed)
	{
		m_speed += 20 * (*m_simTimeDiff);
		if (m_speed > m_defaultSpeed)
			m_speed = m_defaultSpeed;
	}
}