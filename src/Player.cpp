#include "Player.h"
#include "Timer.h"
#include "Matrix.h"
#include "trig.h"
#include "Game.h"
#include "MyHud.h"
#include "MyGL.h"

bool Player::load(){
	static bool loaded = false;
	if (loaded)return true;

	if (!m_mesh.load("mustangimpalasmall.obj")) return false;

	m_wheelX = 0;
	m_wheelY = 0;
	m_carY = 0;

	m_halfDimension = Vec3f(1.7, .3, 1.7);//set half dimesions to draw the box

	m_obb.set(m_pos, Vec3(1.2, .6, 3.1), m_matrix);
	m_obb.m_pos.y += .32;//move obb up on the y axis

	TheGame::Instance()->addGameObject(1, this);

	loaded = true;
	return true;
}

void Player::draw(){
	glPushMatrix();
	{
		glTranslatef(m_pos.x, m_pos.y, m_pos.z);
		
		glRotatef(-m_carY, 0, 1, 0);
		//car's body
		glPushMatrix();
		{
			m_mesh.draw("Chrome");
		}
		glPopMatrix();

		//back right wheel
		glPushMatrix();
		{
			glTranslatef(.58, .2, .95);//wheels starting position are 0,0,0. Needs to be moved to correct pos
			glRotatef(m_wheelX, 1, 0, 0);//wheels rotate when car is moving
			m_mesh.draw("Wheel_right_rear");
		}
		glPopMatrix();
		//back left wheel
		glPushMatrix();
		{
			glTranslatef(-.58, .2, .95);
			glRotatef(m_wheelX, 1, 0, 0);
			m_mesh.draw("Wheel_left_rear");
		}
		glPopMatrix();
		//front right wheel
		glPushMatrix();
		{
			glTranslatef(.58, .2, -.95);
			glRotatef(m_wheelY, 0, 1, 0);//only front wheels steer
			glRotatef(m_wheelX, 1, 0, 0);
			m_mesh.draw("Wheel_right_front");
		}
		glPopMatrix();
		//front left wheel
		glPushMatrix();
		{
			glTranslatef(-.58, .2, -.95);
			glRotatef(m_wheelY, 0, 1, 0);
			glRotatef(m_wheelX, 1, 0, 0);
			m_mesh.draw("Wheel_left_front");
		}
		glPopMatrix();
	}
	glPopMatrix();

	m_box.draw();
	m_obb.draw();
}

void Player::update(){
	updateCarPos();
	updateBox();
	updateMatrix();
	m_obb.update(m_matrix);	
	
	TheHud::Instance()->changeSpeed(m_speed * 4);
}

const char* Player::staticTypeName(){
	return "Player";
}

const char* Player::getTypeName()const{
	return staticTypeName();
}

const Vec3& Player::getPos()const{
	return m_pos;
}

float Player::getCarY()const{
	return m_carY;
}

const Box& Player::getBox() const{
	return m_box;
}

OBB Player::getOBB() const{
	return m_obb;
}

void Player::OnKeyboardEvent(const SDL_KeyboardEvent& ke){
	if (ke.state == SDL_PRESSED){
		if (ke.keysym.sym == SDLK_LEFT){
			m_isLeft = true;
		}
		if (ke.keysym.sym == SDLK_RIGHT){
			m_isRight = true;
		}
		if (ke.keysym.sym == SDLK_UP){
			m_isForward = true;
		}
		if (ke.keysym.sym == SDLK_DOWN){
			m_isBackward = true;
		}		
	}
	if (ke.state == SDL_RELEASED){
		if (ke.keysym.sym == SDLK_LEFT){
			m_isLeft = false;
		}
		if (ke.keysym.sym == SDLK_RIGHT){
			m_isRight = false;
		}
		if (ke.keysym.sym == SDLK_UP){
			m_isForward = false;
		}
		if (ke.keysym.sym == SDLK_DOWN){
			m_isBackward = false;
		}
	}
}

void Player::updateCarPos(){
	float dt = TheTimer::Instance()->GetDt();

	//input checking
	if (m_isForward){
		m_speed -= 2.0f*dt;
	}
	if (m_isBackward){
		m_speed += 2.0f*dt;
	}
	if (m_isLeft){
		if (m_wheelY < 20.0f){
			m_wheelY += 10.0f*dt;
		}
	}
	if (m_isRight){
		if (m_wheelY > -20.0f){
			m_wheelY -= 10.0f*dt;
		}
	}

	//calculating vel and pos
	if (m_speed != 0){
		m_carY += m_wheelY * dt * m_speed * 0.5f;

		Vec3f newVel = degToVec(-m_carY);
		newVel.normalize();
		newVel *= m_speed;

		m_pos += (newVel + m_vel)*0.5f*dt;
		m_vel = newVel;
	}

	//calculating wheel rotation
	m_wheelX += m_speed * 0.07f;


	//adding friction
	if (m_speed > 0){
		m_speed -= .5f*dt;
	}
	if (m_speed < 0){
		m_speed += .5f*dt;
	}
	if (m_speed > -0.001f && m_speed < 0.001f){
		m_speed = 0.0f;//if speed values is very low set it to 0
	}
}

void Player::updateBox(){
	m_box.m_min = m_pos - m_halfDimension;
	m_box.m_max = m_pos + m_halfDimension;
	//moving the box on the y axis so it doesn't go inside the floor
	m_box.m_min.y += .32;
	m_box.m_max.y += .32;
}

void Player::updateMatrix(){
	m_matrix.setToIdentity();//first we reset matrix
	m_matrix.setTranslate(m_pos);
	Matrix matrix2;
	matrix2.setRotateY(degToRad(-m_carY));
	m_matrix = m_matrix * matrix2;//update matrix with current pos and rotation of player
}