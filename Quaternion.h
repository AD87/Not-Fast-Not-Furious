// Maths for Game Programming
// Quaternion class - to be completed in lesson
// Jason Colman Qantm London 2009

#ifndef QUATERNION_H_INCLUDED
#define QUATERNION_H_INCLUDED

#include "Vec3.h"

class Quaternion
{
public:
	// TODO Default ctor - set to identity
	Quaternion();

	Quaternion(const Vec3& vec, float angle);

	// TODO Ctor - set from axis and angle
	~Quaternion();
	
	void normalize();


	// Convert to column-major Matrix
	void ToMatrix(float matrix[16]) const;

	// Interpolate between two Quaternions
	// 0 <= t <= 1
	friend Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);

	friend Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

private:
	float m_w;
	float m_x;
	float m_y;
	float m_z;
};

#endif 

