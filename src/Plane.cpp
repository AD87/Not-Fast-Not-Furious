#include "Plane.h"

Plane::Plane(){
	m_distance = 0.0f;
}

Plane::Plane(const Vec3& p0, const Vec3& p1, const Vec3& p2){
	m_normal = crossProduct((p2 - p0), (p1 - p0));
	m_distance = dotProduct(p0, m_normal);
	normalize();
}

void Plane::create(const Vec3& p0, const Vec3& p1, const Vec3& p2){
	m_normal = crossProduct((p2 - p0), (p1 - p0));
	m_distance = dotProduct(p0, m_normal);
	normalize();
}

float Plane::distancePointToPlane(const Vec3& point){
	//if result < 0 then point is behind the plane
	//if result > 0 then point is in front the plane
	//depending which direction the normal is facing

	return m_distance - dotProduct(point, m_normal);
}

float Plane::distanceSegToPlane(const LineSegment& a){
	float distToP0 = distancePointToPlane(a.getStart());
	float distToP1 = distancePointToPlane(a.getEnd());

	if ((distToP0 > 0.0f && distToP1 > 0.0f) || (distToP0 < 0.0f && distToP1 < 0.0f)){
		if (distToP0 < distToP1){
			return distToP0;
		}
		else return distToP1;
	}
	else return 0.0f;
}

void Plane::normalize(){
	float n = 1 / m_normal.len();

	m_normal *= n;
	m_distance *= n;
}