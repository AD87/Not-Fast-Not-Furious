#include "MyHud.h"
#include "ReportError.h"
#include "MyGL.h"

bool MyHud::load(){
	if (!m_shader.Load("VertexShader.txt", "FragmentShader.txt")){
		ReportError("Failed to load shaders");
		return false;
	}
	if (!m_font.load("arial.txt")){
		return false;
	}
	m_health = -.5f;//set length of health bar
	m_speed = 0;
	m_numCars = 0;

	return true;
}

void MyHud::update(){

}

void MyHud::draw(){
	begin();

	//health bar
	m_shader.UseThisShader();//using a simple shader to change color of health bar
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(-1, .7, 0);

	glTexCoord2f(0, 0);
	glVertex3f(-1, .9, 0);

	glTexCoord2f(1, 0);
	glVertex3f(m_health, .9, 0);

	glTexCoord2f(1, 1);
	glVertex3f(m_health, .7, 0);
	glEnd();
	m_shader.StopUsingThisShader();

	m_font.draw(Vec2f(0, 0), "Health", 9.0f, Vec3(1, 0, 0));
	m_font.draw(Vec2f(0, -1.7f), std::to_string(static_cast<int>(fabs(m_speed)))+"km/h", 9.0f, Vec3(1, 1, 0));
	m_font.draw(Vec2f(0.35f, -1.9f), "Space=change camera", 7.0f, Vec3(1, 1, 1));
	m_font.draw(Vec2f(1.2, 0), "Num of cars", 6.0f, Vec3(1, 1, 1));
	m_font.draw(Vec2f(1.2, -.07), "being drawn:", 6.0f, Vec3(1, 1, 1));
	m_font.draw(Vec2f(1.9, -.05), std::to_string(m_numCars), 10.0f, Vec3(1, 1, 0));
	end();
}

void MyHud::changeSpeed(float newSpeed){
	m_speed = newSpeed;
}

void MyHud::reduceHealth(){
	m_health -= .00003f;
}

void  MyHud::updateNumCars(int number){
	m_numCars = number;
}