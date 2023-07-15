#include "Car.h"
#include "GameObjectFactory.h"
#include "Game.h"
#include "MyHud.h"
#include "Player.h"
#include "MyGL.h"

GameObject* createCar(){
	return new Car;
}
static int n = TheGameObjectFactory::Instance()->add(Car::staticTypeName(), createCar);

void collidePlayerCar(GameObject* go1, GameObject* go2){
	//narrow phase
	OBB obb = go2->getOBB();
	if (go1->getOBB().intersects(&obb)){
		TheHud::Instance()->reduceHealth();
	}
}
static bool b2 = TheGame::Instance()->addCollisionHandler(Player::staticTypeName(), Car::staticTypeName(), collidePlayerCar);//add collision to game system

bool Car::load(const Vec3& pos, int id, const std::string& texture){
	if (!m_mesh.load("kiario.obj")) return false;
	if (!m_texture.load(texture)) return false;//load different textures on same model

	m_box.m_min = Vec3(-1.4, 0, -.6);
	m_box.m_max = Vec3(1.4, 1.3, .55);//set the box position

	m_pos = pos;//move the car pos on the world
	m_box.m_min += m_pos;
	m_box.m_max += m_pos;//make the box move with the car

	Matrix m;//the obb of this car is static without rotations so we are just going to pass the identity matrix
	m.setToIdentity();
	m_obb.set(m_pos, Vec3(2.75, 1, 1.15), m);
	m_obb.m_pos.y += 0.62;
	m_obb.update(m);//we update the box once only for the change in y position to take effect

	TheGame::Instance()->addGameObject(id, this);

	return true;
}

void Car::draw(){
	glDisable(GL_LIGHTING);

	glPushMatrix();
	{
		glTranslatef(m_pos.x, m_pos.y, m_pos.z);//move to position
		glPushMatrix();
		{
			glScalef(.17f, .17f, .17f);
			glRotatef(180, 0, 1, 0);//flip car horizontal
			m_mesh.draw("KiaRio", &m_texture);
		}
		glPopMatrix();
	}
	glPopMatrix();

	//m_box.draw();
	m_obb.draw();

	glEnable(GL_LIGHTING);
}

void Car::update(){
	
}

const char* Car::staticTypeName(){
	return "Car";
}

const char* Car::getTypeName()const{
	return staticTypeName();
}

const Box& Car::getBox() const{
	return m_box;
}

OBB Car::getOBB() const{
	return m_obb;
}
