#include "Frustum.h"
#include "Matrix.h"
#include "MyGL.h"

void Frustum::update(){
	Matrix model;
	Matrix proj;

	model.getModelview();
	proj.getProjection();

	m_clip = proj * model;//to get clip matrix we multiply modelview and projection together
}

//check collision with points, I am not using this code because I check against AABBs
bool Frustum::intersects(const Vec3f& v){
	Vec3f vec = m_clip * v;//multiplying the vec3 with the clip matrix gives us the vec3 in clip space
	//if it is not within cube (-1,-1,-1) (1,1,1) then the point is outside the frustum
	if (vec.x > 1 || vec.x < -1 || vec.y > 1 || vec.y < -1 || vec.z > 1 || vec.z < -1){
        return false;
    }
    else return true;
}

bool Frustum::intersects(const Box& b){
	Vec3 v[8];//all 8 vertices of the AABB
	v[0] = Vec3(b.m_min.x, b.m_min.y, b.m_min.z);
	v[1] = Vec3(b.m_min.x, b.m_min.y, b.m_max.z);
	v[2] = Vec3(b.m_min.x, b.m_max.y, b.m_min.z);
	v[3] = Vec3(b.m_min.x, b.m_max.y, b.m_max.z);
	v[4] = Vec3(b.m_max.x, b.m_min.y, b.m_min.z);
	v[5] = Vec3(b.m_max.x, b.m_min.y, b.m_max.z);
	v[6] = Vec3(b.m_max.x, b.m_max.y, b.m_min.z);
	v[7] = Vec3(b.m_max.x, b.m_max.y, b.m_max.z);

	//for each vertex we get the outcode
    int outcode = 0xff;
    for (size_t i = 0; i < 8; i++){
		//using the bitwise operator AND we compare the 8 different outcodes of each vertex
		outcode &= getOutcode(v[i]);
        if (outcode == 0){
            return true;//the box is inside the frustum if any of its vertices are inside of all 6 planes
        }
    }
    return false;//the box is outside the frustum if all of its vertices are outside of any one plane
}

int Frustum::getOutcode(const Vec3f v){
	//we get the vertex in clip space but instead of dividing by w, we compare it with w
	float x = v.x * m_clip.m_array[0] + v.y * m_clip.m_array[4] + v.z * m_clip.m_array[8] + 1.0f * m_clip.m_array[12];
	float y = v.x * m_clip.m_array[1] + v.y * m_clip.m_array[5] + v.z * m_clip.m_array[9] + 1.0f * m_clip.m_array[13];
	float z = v.x * m_clip.m_array[2] + v.y * m_clip.m_array[6] + v.z * m_clip.m_array[10] + 1.0f * m_clip.m_array[14];
	float w = v.x * m_clip.m_array[3] + v.y * m_clip.m_array[7] + v.z * m_clip.m_array[11] + 1.0f * m_clip.m_array[15];

	int outcode = 0;

	//we check if the vertex is inside the frustum comparing if it is in front or behind the 6 planes
	//0=in front/inside  1=behind/outside
	//using the bitwise operator OR we set the bit representing each plane to 1 if it is outside that plane
	//if vertex is inside all planes then we will return 0
	//the outcode represents from which plane is outside
	if (x > w) outcode |= 0x01;
	if (x < -w) outcode |= 0x02;

	if (y > w) outcode |= 0x04;
	if (y < -w) outcode |= 0x08;
		
	if (z > w) outcode |= 0x10;
	if (z < -w) outcode |= 0x20;
	
	return outcode;
}
