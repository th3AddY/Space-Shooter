#include "DummyState.h"

using namespace Shooter;

FreeLookState::FreeLookState(Vec3 rotation)
	: SpaceState(),
	  m_freeLookAngle(rotation)
{
}

SpaceState* FreeLookState::update()
{
	if (keyDown('w'))
		m_follower->move(Vec3f(0.0f, *m_simTimeDiff * 10.0f, 0.0f));
	if (keyDown('s'))
		m_follower->move(Vec3f(0.0f, -*m_simTimeDiff * 10.0f, 0.0f));
	if (keyDown('a'))
		m_follower->move(Vec3f(-*m_simTimeDiff * 10.0f, 0.0f, 0.0f));
	if (keyDown('d'))
		m_follower->move(Vec3f(*m_simTimeDiff * 10.0f, 0.0f, 0.0f));

	m_freeLookAngle.set(
		m_freeLookAngle.x() +  float(getMouseYspeed())*0.01f,
		m_freeLookAngle.y() - float(getMouseXspeed())*0.01f,
		0);

	m_follower->setAttitude(getQuatFromEuler(0, m_freeLookAngle.y(), m_freeLookAngle.x()));

	m_follower->updateLookAtMatrix();
	m_universe->updateSkybox(m_follower);


	return 0;
}