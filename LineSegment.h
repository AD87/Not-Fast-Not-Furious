#pragma once
#include "Vec3.h"

class LineSegment{
public:
	LineSegment(){};
	LineSegment(const Vec3& start, const Vec3& end);
	void set(const Vec3& start, const Vec3& end);
	float sqrDistancePointToSeg(const Vec3& point);//square distance from point to line segment

	Vec3 getPoint(float t)const;

	Vec3 getStart()const;
	Vec3 getEnd()const;
private:
	Vec3 m_start;
	Vec3 m_end;
};