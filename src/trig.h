#pragma once
#include"Vec3.h"
#include <math.h>

//useful trigonometry functions
inline float degToRad(float degs){
	return static_cast<float>(degs / 360.0f * 2.0f * M_PI);
}

inline float radToDeg(float rads){
	return static_cast<float>(rads / (2.0f * M_PI) * 360.0f);
}

inline float vecToRad(const Vec3f& v){
	return atan2f(v.y, v.x);
}

inline Vec3f degToVec(float deg){
	return Vec3f(sin(degToRad(deg)), 0, cos(degToRad(deg)));
}