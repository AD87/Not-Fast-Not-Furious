// Maths for Game Programming
// Quaternion class - to be completed in lesson
// Jason Colman Qantm London 2009

#include <assert.h>
#ifdef WIN32
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include "Quaternion.h"

// TODO Default ctor - set to identity
Quaternion::Quaternion(){
	m_x = m_y = m_z = 0.0f;
	m_w = 1.0f;
}

Quaternion::Quaternion(const Vec3& vec, float angle){
	float rads = float((angle / 180.0f)*M_PI);
	float result = sinf (rads * 0.5f);

	m_w = cosf(rads / 2.0f);
	m_x = vec.x * result;
	m_y = vec.y * result;
	m_z = vec.z * result;
}

// TODO Ctor - set from axis and angle
Quaternion::~Quaternion(){

}

void Quaternion::normalize(){
	float oneOverLength = 1 / sqrtf(m_x*m_x + m_y*m_y + m_z*m_z + m_w*m_w);
	m_x *= oneOverLength;
	m_y *= oneOverLength;
	m_z *= oneOverLength;
	m_w *= oneOverLength;
}


void Quaternion::ToMatrix(float pMatrix[16]) const
{
	assert(pMatrix);

	pMatrix[0] = 1.0f - 2.0f * (m_y * m_y + m_z * m_z);
	pMatrix[1] = 2.0f * (m_x * m_y + m_z * m_w);
	pMatrix[2] = 2.0f * (m_x * m_z - m_y * m_w);
	pMatrix[3] = 0.0f;

	pMatrix[4] = 2.0f * (m_x * m_y - m_z * m_w);
	pMatrix[5] = 1.0f - 2.0f * (m_x * m_x + m_z * m_z);
	pMatrix[6] = 2.0f * (m_z * m_y + m_x * m_w);
	pMatrix[7] = 0.0f;

	pMatrix[8] = 2.0f * (m_x * m_z + m_y * m_w);
	pMatrix[9] = 2.0f * (m_y * m_z - m_x * m_w);
	pMatrix[10] = 1.0f - 2.0f * (m_x * m_x + m_y * m_y);
	pMatrix[11] = 0.0f;

	pMatrix[12] = 0;
	pMatrix[13] = 0;
	pMatrix[14] = 0;
	pMatrix[15] = 1.0f;
}

Quaternion operator*(const Quaternion& p, const Quaternion& q)
{
	Quaternion r;

	r.m_w = p.m_w * q.m_w - p.m_x * q.m_x - p.m_y * q.m_y - p.m_z * q.m_z;
	r.m_x = p.m_w * q.m_x + p.m_x * q.m_w + p.m_y * q.m_z - p.m_z * q.m_y;
	r.m_y = p.m_w * q.m_y + p.m_y * q.m_w + p.m_z * q.m_x - p.m_x * q.m_z;
	r.m_z = p.m_w * q.m_z + p.m_z * q.m_w + p.m_x * q.m_y - p.m_y * q.m_x;

	return r;
}

Quaternion Slerp(const Quaternion& from, const Quaternion& to, float t)
{
	float to1[4];
	double omega, cosom, sinom, scale0, scale1;

	// calc cosine
	cosom = from.m_x * to.m_x + from.m_y * to.m_y + from.m_z * to.m_z
		+ from.m_w * to.m_w;

	// adjust signs (if necessary)
	if (cosom < 0)
	{
		cosom = -cosom;
		to1[0] = -to.m_x;
		to1[1] = -to.m_y;
		to1[2] = -to.m_z;
		to1[3] = -to.m_w;
	}
	else
	{
		to1[0] = to.m_x;
		to1[1] = to.m_y;
		to1[2] = to.m_z;
		to1[3] = to.m_w;
	}

	// calculate coefficients

	static const double DELTA = 0.001;
	if ((1.0 - cosom) > DELTA)
	{
		// standard case (slerp)
		omega = acos(cosom);
		sinom = sin(omega);
		scale0 = sin((1.0 - t) * omega) / sinom;
		scale1 = sin(t * omega) / sinom;
	}
	else
	{
		// "from" and "to" quaternions are very close 
		//  ... so we can do a linear interpolation
		scale0 = 1.0 - t;
		scale1 = t;
	}

	Quaternion res;

	// calculate final values
	res.m_x = (float)(scale0 * (double)from.m_x + scale1 * (double)to1[0]);
	res.m_y = (float)(scale0 * (double)from.m_y + scale1 * (double)to1[1]);
	res.m_z = (float)(scale0 * (double)from.m_z + scale1 * (double)to1[2]);
	res.m_w = (float)(scale0 * (double)from.m_w + scale1 * (double)to1[3]);

	return res;
}

