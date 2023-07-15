#include "Box.h"
#include "MyGL.h"


Box::Box(){
	m_min = Vec3(0, 0, 0);
	m_max = Vec3(3, 3, 3);
}

Box::Box(const Vec3& _min, const Vec3& _max){
	m_min = _min;
	m_max = _max;
}

bool Box::intersects(const Box& b)const{
	return ((m_max.x > b.m_min.x && b.m_max.x > m_min.x) &&
		(m_max.y > b.m_min.y && b.m_max.y > m_min.y) &&
		(m_max.z > b.m_min.z && b.m_max.z > m_min.z));
}

void Box::draw(){

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);

	glColor3f(0, 1, 0);
	glLineWidth(5);
	//front face
	glBegin(GL_LINE_STRIP);
	glVertex3f(m_min.x, m_min.y, m_max.z);
	glVertex3f(m_min.x, m_max.y, m_max.z);
	glVertex3f(m_max.x, m_max.y, m_max.z);
	glVertex3f(m_max.x, m_min.y, m_max.z);
	glVertex3f(m_min.x, m_min.y, m_max.z);
	glEnd();
	//back face
	glBegin(GL_LINE_STRIP);
	glVertex3f(m_min.x, m_min.y, m_min.z);
	glVertex3f(m_min.x, m_max.y, m_min.z);
	glVertex3f(m_max.x, m_max.y, m_min.z);
	glVertex3f(m_max.x, m_min.y, m_min.z);
	glVertex3f(m_min.x, m_min.y, m_min.z);
	glEnd();
	//4 lines connected
	glBegin(GL_LINES);
	glVertex3f(m_min.x, m_min.y, m_max.z);
	glVertex3f(m_min.x, m_min.y, m_min.z);

	glVertex3f(m_max.x, m_min.y, m_max.z);
	glVertex3f(m_max.x, m_min.y, m_min.z);

	glVertex3f(m_min.x, m_max.y, m_max.z);
	glVertex3f(m_min.x, m_max.y, m_min.z);

	glVertex3f(m_max.x, m_max.y, m_max.z);
	glVertex3f(m_max.x, m_max.y, m_min.z);
	glEnd();

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

}

bool Box::contains(const Vec3& point){
	if (m_min.x <= point.x&&m_min.y <= point.y&&m_min.z <= point.z
		&&m_max.x >= point.x&&m_max.y >= point.y&&m_max.z >= point.z){
		return true;
	}
	else return false;
}

Box Box::splitIntoEight(unsigned int n)const{//useful function for octree class
	Vec3 center = m_min + ((m_max - m_min) / 2);//get center point of box
	Box miniBox;

	if (n == 0){
		miniBox.m_min = m_min;
		miniBox.m_max = center;
	}
	else if (n == 1){
		miniBox.m_min = m_min;
		miniBox.m_min.x = center.x;
		miniBox.m_max = center;
		miniBox.m_max.x = m_max.x;
	}
	else if (n == 2){
		miniBox.m_min = m_min;
		miniBox.m_min.z = center.z;
		miniBox.m_max = center;
		miniBox.m_max.z = m_max.z;
	}
	else if (n == 3){
		miniBox.m_min = center;
		miniBox.m_min.y = m_min.y;
		miniBox.m_max = m_max;
		miniBox.m_max.y = center.y;
	}
	else if (n == 4){
		miniBox.m_min = m_min;
		miniBox.m_min.y = center.y;
		miniBox.m_max = center;
		miniBox.m_max.y = m_max.y;
	}
	else if (n == 5){
		miniBox.m_min = m_min;
		miniBox.m_min.x = center.x;
		miniBox.m_min.y = center.y;
		miniBox.m_max = center;
		miniBox.m_max.x = m_max.x;
		miniBox.m_max.y = m_max.y;
	}
	else if (n == 6){
		miniBox.m_min.x = m_min.x;
		miniBox.m_min.z = center.z;
		miniBox.m_min.y = center.y;
		miniBox.m_max.x = center.x;
		miniBox.m_max.z = m_max.z;
		miniBox.m_max.y = m_max.y;
	}
	else if (n == 7){
		miniBox.m_min = center;
		miniBox.m_max = m_max;
	}
	return miniBox;
}