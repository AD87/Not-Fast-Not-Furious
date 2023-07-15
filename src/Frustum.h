#pragma once
#include "Matrix.h"
#include "Box.h"

class Frustum{
public:
	void update();

	bool intersects(const Vec3f& v);
	bool intersects(const Box& b);
private:
	int getOutcode(const Vec3f v);

	Matrix m_clip;// Clip matrix
};