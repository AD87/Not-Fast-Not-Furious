#include "OBB.h"
#include "Matrix.h"
#include "MyGL.h"

OBB::OBB(){
	//default values
	m_pos = Vec3(0.0f, 0.0f, 0.0f);
	m_extents = Vec3(1, 1, 1);

	float halfW = m_extents.x * 0.5f;
	float halfH = m_extents.y * 0.5f;
	float halfD = m_extents.z * 0.5f;

	m_verts[0] = Vec3(m_pos.x - halfW, m_pos.y + halfH, m_pos.z + halfD);
	m_verts[1] = Vec3(m_pos.x + halfW, m_pos.y + halfH, m_pos.z + halfD);
	m_verts[2] = Vec3(m_pos.x + halfW, m_pos.y - halfH, m_pos.z + halfD);
	m_verts[3] = Vec3(m_pos.x - halfW, m_pos.y - halfH, m_pos.z + halfD);
	m_verts[4] = Vec3(m_pos.x - halfW, m_pos.y + halfH, m_pos.z - halfD);
	m_verts[5] = Vec3(m_pos.x + halfW, m_pos.y + halfH, m_pos.z - halfD);
	m_verts[6] = Vec3(m_pos.x + halfW, m_pos.y - halfH, m_pos.z - halfD);
	m_verts[7] = Vec3(m_pos.x - halfW, m_pos.y - halfH, m_pos.z - halfD);
}

OBB::OBB(const Vec3& pos, const Vec3& extents, const Matrix& m){
	set(pos, extents, m);
}

void OBB::set(const Vec3& pos, const Vec3& extents, const Matrix& m){
	m_pos = pos;
	m_extents = extents;

	float halfW = m_extents.x * 0.5f;
	float halfH = m_extents.y * 0.5f;
	float halfD = m_extents.z * 0.5f;

	m_verts[0] = Vec3(m_pos.x - halfW, m_pos.y + halfH, m_pos.z + halfD);
	m_verts[1] = Vec3(m_pos.x + halfW, m_pos.y + halfH, m_pos.z + halfD);
	m_verts[2] = Vec3(m_pos.x + halfW, m_pos.y - halfH, m_pos.z + halfD);
	m_verts[3] = Vec3(m_pos.x - halfW, m_pos.y - halfH, m_pos.z + halfD);
	m_verts[4] = Vec3(m_pos.x - halfW, m_pos.y + halfH, m_pos.z - halfD);
	m_verts[5] = Vec3(m_pos.x + halfW, m_pos.y + halfH, m_pos.z - halfD);
	m_verts[6] = Vec3(m_pos.x + halfW, m_pos.y - halfH, m_pos.z - halfD);
	m_verts[7] = Vec3(m_pos.x - halfW, m_pos.y - halfH, m_pos.z - halfD);

	for (size_t i = 0; i < 8; i++){
		m_verts[i] = m * m_verts[i];//multiply each vert with the matrix
	}
}

void OBB::update(const Matrix& m){
	float halfW = m_extents.x * 0.5f;
	float halfH = m_extents.y * 0.5f;
	float halfD = m_extents.z * 0.5f;

	m_verts[0] = Vec3(m_pos.x - halfW, m_pos.y + halfH, m_pos.z + halfD);
	m_verts[1] = Vec3(m_pos.x + halfW, m_pos.y + halfH, m_pos.z + halfD);
	m_verts[2] = Vec3(m_pos.x + halfW, m_pos.y - halfH, m_pos.z + halfD);
	m_verts[3] = Vec3(m_pos.x - halfW, m_pos.y - halfH, m_pos.z + halfD);
	m_verts[4] = Vec3(m_pos.x - halfW, m_pos.y + halfH, m_pos.z - halfD);
	m_verts[5] = Vec3(m_pos.x + halfW, m_pos.y + halfH, m_pos.z - halfD);
	m_verts[6] = Vec3(m_pos.x + halfW, m_pos.y - halfH, m_pos.z - halfD);
	m_verts[7] = Vec3(m_pos.x - halfW, m_pos.y - halfH, m_pos.z - halfD);

	for (size_t i = 0; i < 8; i++){
		m_verts[i] = m * m_verts[i];
	}
}

void OBB::draw(){
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glColor3f(1, 0, 0);
	glLineWidth(5);

	//front face
	glBegin(GL_LINE_STRIP);
	glVertex3f(m_verts[0].x, m_verts[0].y, m_verts[0].z);
	glVertex3f(m_verts[1].x, m_verts[1].y, m_verts[1].z);
	glVertex3f(m_verts[2].x, m_verts[2].y, m_verts[2].z);
	glVertex3f(m_verts[3].x, m_verts[3].y, m_verts[3].z);
	glVertex3f(m_verts[0].x, m_verts[0].y, m_verts[0].z);
	glEnd();
	//back face
	glBegin(GL_LINE_STRIP);
	glVertex3f(m_verts[4].x, m_verts[4].y, m_verts[4].z);
	glVertex3f(m_verts[5].x, m_verts[5].y, m_verts[5].z);
	glVertex3f(m_verts[6].x, m_verts[6].y, m_verts[6].z);
	glVertex3f(m_verts[7].x, m_verts[7].y, m_verts[7].z);
	glVertex3f(m_verts[4].x, m_verts[4].y, m_verts[4].z);
	glEnd();
	//4 lines connected
	glBegin(GL_LINES);
	glVertex3f(m_verts[0].x, m_verts[0].y, m_verts[0].z);
	glVertex3f(m_verts[4].x, m_verts[4].y, m_verts[4].z);

	glVertex3f(m_verts[1].x, m_verts[1].y, m_verts[1].z);
	glVertex3f(m_verts[5].x, m_verts[5].y, m_verts[5].z);

	glVertex3f(m_verts[2].x, m_verts[2].y, m_verts[2].z);
	glVertex3f(m_verts[6].x, m_verts[6].y, m_verts[6].z);

	glVertex3f(m_verts[3].x, m_verts[3].y, m_verts[3].z);
	glVertex3f(m_verts[7].x, m_verts[7].y, m_verts[7].z);
	glEnd();

	glPopMatrix();

	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
}

bool OBB::intersects(OBB* o){
	Vec3 direction1X = m_verts[1] - m_verts[0];
	Vec3 direction1Y = m_verts[1] - m_verts[2];
	Vec3 direction1Z = m_verts[1] - m_verts[5];
	Vec3 direction2X = o->m_verts[1] - o->m_verts[0];
	Vec3 direction2Y = o->m_verts[1] - o->m_verts[2];
	Vec3 direction2Z = o->m_verts[1] - o->m_verts[5];

	Vec3 axis;
	//using a for loop we check the extents of the OBBs for the 15 different cases
	//in each loop we test a different axis

	for (size_t i = 0; i < 15; i++){//15 different axes tests
		//face normal axes

		if (i == 0){//this object face normal x
			axis = direction1X;
		}
		else if (i == 1){//this object face normal y
			axis = direction1Y;
		}
		else if (i == 2){//this object face normal z
			axis = direction1Z;
		}
		else if (i == 3){//other object face normal x
			axis = direction2X;
		}
		else if (i == 4){//other object face normal y
			axis = direction2Y;
		}
		else if (i == 5){//other object face normal z
			axis = direction2Z;
		}

		//cross product axes

		//this object face normal x with all 3 others
		else if (i == 6){
			axis = crossProduct(direction1X, direction2X);
		}
		else if (i == 7){
			axis = crossProduct(direction1X, direction2Y);
		}
		else if (i == 8){
			axis = crossProduct(direction1X, direction2Z);
		}
		//this object face normal y with all 3 others
		else if (i == 9){
			axis = crossProduct(direction1Y, direction2X);
		}
		else if (i == 10){
			axis = crossProduct(direction1Y, direction2Y);
			if (axis.x == 0 && axis.y == 0 && axis.z == 0){//if both directions are the same the cross product will be 0
				//but we need a meaningful axis, we can find what the axis would be by getting the vector between both same points of the boxes
				//and using the cross product between 1 of the directions and this resulting vector.
				Vec3 vec = m_verts[1] - o->m_verts[1];
				axis = crossProduct(direction1Y, vec);
				if (axis.x == 0 && axis.y == 0 && axis.z == 0){//we check again because there is a chance that it is (0, 0, 0) and that would be
					//when both vectors are in the same position. If this happens then they will be touching, so without further testing we can say
					//that they are intersecting
					return true;
				}
			}
		}
		else if (i == 11){
			axis = crossProduct(direction1Y, direction2Z);
		}
		//this object face normal z with all 3 others
		else if (i == 12){
			axis = crossProduct(direction1Z, direction2X);
		}
		else if (i == 13){
			axis = crossProduct(direction1Z, direction2Y);
		}
		else if (i == 14){
			axis = crossProduct(direction1Z, direction2Z);
		}

		Vec3 norm = axis;
		norm.normalize();

		float f1[8];
		f1[0] = dotProduct(norm, m_verts[0]);
		f1[1] = dotProduct(norm, m_verts[1]);
		f1[2] = dotProduct(norm, m_verts[2]);
		f1[3] = dotProduct(norm, m_verts[3]);
		f1[4] = dotProduct(norm, m_verts[4]);
		f1[5] = dotProduct(norm, m_verts[5]);
		f1[6] = dotProduct(norm, m_verts[6]);
		f1[7] = dotProduct(norm, m_verts[7]);

		float f2[8];
		f2[0] = dotProduct(norm, o->m_verts[0]);
		f2[1] = dotProduct(norm, o->m_verts[1]);
		f2[2] = dotProduct(norm, o->m_verts[2]);
		f2[3] = dotProduct(norm, o->m_verts[3]);
		f2[4] = dotProduct(norm, o->m_verts[4]);
		f2[5] = dotProduct(norm, o->m_verts[5]);
		f2[6] = dotProduct(norm, o->m_verts[6]);
		f2[7] = dotProduct(norm, o->m_verts[7]);

		//m_projections is used for debugging purposes only
		m_projections[0] = norm * f1[0];
		m_projections[1] = norm * f1[1];
		m_projections[2] = norm * f1[2];
		m_projections[3] = norm * f1[3];
		m_projections[4] = norm * f1[4];
		m_projections[5] = norm * f1[5];
		m_projections[6] = norm * f1[6];
		m_projections[7] = norm * f1[7];

		o->m_projections[0] = norm * f2[0];
		o->m_projections[1] = norm * f2[1];
		o->m_projections[2] = norm * f2[2];
		o->m_projections[3] = norm * f2[3];
		o->m_projections[4] = norm * f2[4];
		o->m_projections[5] = norm * f2[5];
		o->m_projections[6] = norm * f2[6];
		o->m_projections[7] = norm * f2[7];

		//get this object min
		float min1 = f1[0];
		for (size_t i = 0; i < 8; i++){
			if (f1[i] < min1){
				min1 = f1[i];
			}
		}
		//get this object max
		float max1 = f1[0];
		for (size_t i = 0; i < 8; i++){
			if (f1[i] > max1){
				max1 = f1[i];
			}
		}
		//get other object min
		float min2 = f2[0];
		for (size_t i = 0; i < 8; i++){
			if (f2[i] < min2){
				min2 = f2[i];
			}
		}
		//get other object max
		float max2 = f2[0];
		for (size_t i = 0; i < 8; i++){
			if (f2[i] > max2){
				max2 = f2[i];
			}
		}

		//check if extents overlap
		if (!(min1 < max2 && max1 > min2 || max1 > min2 && min1 < max2)){
			return false;//if we didnt find an intersection in one of the axis we stop checking for other axes, 
			//they are not colliding
		}

	}//end of for loop

	//if we reach this point then they are overlapping in all 15 axes, so they must be intersecting
	return true;
}

