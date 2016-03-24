#pragma once
#include "Vec3.h"
#include "Matrix.h"
#include <vector>

class OBB{//Oriented Bounding Boxes
public:
	OBB();
	OBB(const Vec3& pos, const Vec3& extents, const Matrix& m);
	void set(const Vec3& pos, const Vec3& extents, const Matrix& m);

	void update(const Matrix& m);
	void draw();

	bool intersects(OBB* o);
public:
	Vec3 m_pos;
	Vec3 m_extents;
	Vec3 m_verts[8];
	Vec3 m_projections[8];//projection of each vert on the axes, as a normalize vector (for debugging purposes)
};