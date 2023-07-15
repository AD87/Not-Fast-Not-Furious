#include "LineSegment.h"

LineSegment::LineSegment(const Vec3& start, const Vec3& end){
	m_start = start;
	m_end = end;
}

void LineSegment::set(const Vec3& start, const Vec3& end){
	m_start = start;
	m_end = end;
}

float LineSegment::sqrDistancePointToSeg(const Vec3& point){
	Vec3 m = m_end - m_start;
	Vec3 q = point - m_start;

	float t = dotProduct(m, q) / dotProduct(m, m);

	Vec3 result;

	if (t < 0){
		result = q;
		return result.sqLen();
	}
	else if (t>1){
		result = point - m_end;
		return result.sqLen();
	}
	else{
		// p = p0 + t(p1 - p0) parametric line equation
		Vec3 p = m_start + (m*t);
		result = point - p;
		return result.sqLen();
	}
}

Vec3 LineSegment::getPoint(float t)const{
	return m_start + ((m_end - m_start)*t);
}

Vec3 LineSegment::getStart()const{
	return m_start;
}
Vec3 LineSegment::getEnd()const{
	return m_end;
}