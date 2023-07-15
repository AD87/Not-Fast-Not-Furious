#pragma once

#include "Vec3.h"

class Box{
public:
	Box();
	Box(const Vec3& _min, const Vec3& _max);
	bool intersects(const Box& b)const;
	void draw();

	bool contains(const Vec3& point);//check if a given point is inside the box
	Box splitIntoEight(unsigned int n)const;//split the box onto 8 small boxes (for Octree purposes)
	//function return one of the 8 small boxes:
	//0 -> bottom left closer to screen
	//1 -> bottom right closer to screen
	//2 -> bottom left away from screen
	//3 -> bottom right away from screen
	//4 -> top left closer to screen
	//5 -> top right closer to screen
	//6 -> top left away from screen
	//7 -> top right away from screen
public:
	Vec3 m_min;
	Vec3 m_max;
};