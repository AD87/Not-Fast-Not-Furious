#pragma once
#include <math.h>

struct Vec3{

	Vec3(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vec3(float _x, float _y, float _z){
		x = _x;
		y = _y;
		z = _z;
	}

	Vec3& operator+=(const Vec3& v){
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vec3& operator-=(const Vec3& v){
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	Vec3 operator-()const{
		return Vec3(-x, -y, -z);
	}
	Vec3& operator*=(const Vec3& v){
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	Vec3& operator*=(float number){
		x *= number;
		y *= number;
		z *= number;
		return *this;
	}
	Vec3& operator/=(const Vec3& v){
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	float sqLen() const{
		return x*x + y*y + z*z;
	}
	float len() const{
		return sqrtf(sqLen());
	}

	void normalize(){
		if (x == 0 && y == 0 && z == 0)return; //we cant normalize a 0,0,0 vec3
		float oneOverLength = 1 / len();
		x *= oneOverLength;
		y *= oneOverLength;
		z *= oneOverLength;
	}

	float* toArray(){
		return &x;
	}

	float x, y, z;
};

typedef Vec3 Vec3f;

inline Vec3 operator+(const Vec3& v1, const Vec3& v2){
	return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
inline Vec3 operator-(const Vec3& v1, const Vec3& v2){
	return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
inline Vec3 operator*(const Vec3& v1, const Vec3& v2){
	return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
inline Vec3 operator*(const Vec3& v1, float number){
	return Vec3(v1.x * number, v1.y * number, v1.z * number);
}
inline Vec3 operator/(const Vec3& v1, const Vec3& v2){
	return Vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}
inline Vec3 operator/(const Vec3& v1, float number){
	return Vec3(v1.x / number, v1.y / number, v1.z / number);
}

inline float dotProduct(const Vec3& v1, const Vec3& v2){
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vec3f crossProduct(Vec3f v1, Vec3f v2){
	return Vec3(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}