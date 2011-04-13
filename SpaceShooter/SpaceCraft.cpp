#include "SpaceCraft.h"

using namespace Shooter;

SpaceCraft::SpaceCraft(double* simTimeDiff)
	: Matter(simTimeDiff),
	  m_attitudeAcceleration(0, 0),
	  m_lateralAcceleration(0),
	  m_accelerated(false)
{
	m_params.defaultSpeed = 12;
	m_params.minSpeed = 5;
	m_params.maxSpeed = 48;
	m_params.forwardAcceleration = 25;
	m_params.backwardAcceleration = 25;
	m_params.defaultSpeedAcceleration = 20;

	m_params.maxLateralDeflection = 2;
	m_params.maxAttitudeDeflection = 3;
	m_params.attitudeReduction = 50;

	m_speed = m_params.defaultSpeed;

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
	Matrix mat = Matrix::rotate(getAttitude());
	Vec3 position = Vec3(0, -10, 3);

	transformVector(&position, &mat);

	follower->setPosition(getPosition() + position);
	follower->setAttitude(getAttitude());
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