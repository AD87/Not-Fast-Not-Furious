#pragma once
#include "Vec3.h"
#include "LineSegment.h"

class Plane{
public:
	Plane();
	Plane(const Vec3& p0, const Vec3& p1, const Vec3& p2);
	void create(const Vec3& p0, const Vec3& p1, const Vec3& p2);
	float distancePointToPlane(const Vec3& point);
	float distanceSegToPlane(const LineSegment& a);
private:
	void normalize();

	Vec3 m_normal;
	float m_distance;
};

enum pointType{
	IN_FRONT, BEHIND, ON_PLANE
};