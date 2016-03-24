#include "GameObject.h"
#include "Timer.h"

void GameObject::update(){
	float dt = TheTimer::Instance()->GetDt();

	Vec3f oldVel = m_vel;//remember old velocity
	m_vel += m_acc*dt;
	m_pos += (oldVel + m_vel)*0.5f*dt;//update new pos
}