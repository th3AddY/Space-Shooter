#include "SpaceCraft.h"

using namespace Shooter;

SpaceCraft::SpaceCraft(double* simTimeDiff, SpaceCraftParams params)
	: Matter(simTimeDiff),
	  m_attitudeAcceleration(0, 0),
	  m_lateralAcceleration(0),
	  m_accelerated(false),
	  m_params(params)
{
	m_speed = m_params.defaultSpeed;

	getFollowerPosition(&m_followerPosition, &m_followerAttitude);

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
	Vec3 vec(m_lateralAcceleration, m_attitudeAcceleration.x(), m_attitudeAcceleration.y());
	vec *= (*m_simTimeDiff);

	mat.mult(Matrix::rotate(getQuatFromEuler(vec.x(), vec.y(), vec.z())), Matrix::rotate(getAttitude()));

	setAttitude(mat.getRotate());
	
	float reduction = pow(m_params.attitudeReduction, -float(*m_simTimeDiff));
	m_attitudeAcceleration *= reduction;
	m_lateralAcceleration *= reduction;
}

void SpaceCraft::accelerate()
{
	m_speed += m_params.forwardAcceleration * float(*m_simTimeDiff);
	if (m_speed > m_params.maxSpeed)
		m_speed = m_params.maxSpeed;

	m_accelerated = true;
}

void SpaceCraft::retard()
{
	m_speed -= m_params.backwardAcceleration * float(*m_simTimeDiff);
	if (m_speed < m_params.minSpeed)
		m_speed = m_params.minSpeed;

	m_accelerated = true;
}

void SpaceCraft::controlDirection(Vec2 direction)
{
	m_attitudeAcceleration += direction;

	float length = m_attitudeAcceleration.length();
	 if (length > m_params.maxAttitudeDeflection)
		m_attitudeAcceleration *= (m_params.maxAttitudeDeflection / length);
}

void SpaceCraft::controlLateral(float direction)
{
	m_lateralAcceleration += direction;

	if (m_lateralAcceleration > m_params.maxLateralDeflection)
		m_lateralAcceleration = m_params.maxLateralDeflection;

	if (m_lateralAcceleration < -m_params.maxLateralDeflection)
		m_lateralAcceleration = -m_params.maxLateralDeflection;
}

void SpaceCraft::setFollowerPosition(Follower* follower)
{
	Vec3 position;
	Quat attitude;

	getFollowerPosition(&position, &attitude);

	float convergence = 1.0f - pow(m_params.followerConvergence, -float(*m_simTimeDiff));

	m_followerPosition = m_followerPosition + (position - m_followerPosition) * convergence;
	m_followerAttitude.slerp(convergence, m_followerAttitude, attitude);

	follower->setPosition(m_followerPosition);
	follower->setAttitude(m_followerAttitude);
}

void SpaceCraft::goToDefaultSpeed()
{
	if (m_speed > m_params.defaultSpeed)
	{
		m_speed -= m_params.defaultSpeedAcceleration * (*m_simTimeDiff);
		if (m_speed < m_params.defaultSpeed)
			m_speed = m_params.defaultSpeed;
	}

	if (m_speed < m_params.defaultSpeed)
	{
		m_speed += m_params.defaultSpeedAcceleration * (*m_simTimeDiff);
		if (m_speed > m_params.defaultSpeed)
			m_speed = m_params.defaultSpeed;
	}
}

void SpaceCraft::getFollowerPosition(Vec3* position, Quat* attitude)
{
	Matrix matAttitude = Matrix::rotate(getAttitude());

	Vec3 pos = m_params.followerPosition;
	transformVector(&pos, &matAttitude);

	Matrix att;
	att.mult(Matrix::rotate(m_params.followerAttitude), matAttitude);

	*position = pos + getPosition();
	*attitude = att.getRotate();
}