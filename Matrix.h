#pragma once
#include "Vec3.h"

class Matrix{
public:
	Matrix();
	Matrix(float arrayMatrix[16]);

	void setToIdentity();
	Matrix operator*=(const Matrix& m);
	Vec3 operator*=(const Vec3& v);

	void setTranslate(const Vec3& v);
	void setScale(const Vec3& v);
	void setRotateX(float angle);
	void setRotateY(float angle);
	void setRotateZ(float angle);

	void getModelview();
	void getProjection();
	//add function to mulyiply the current opengl matrix

	void printMatrix();
public:
	float m_array[16];
};

Matrix operator*(const Matrix& m1, const Matrix& m2);
Vec3 operator*(const Matrix& m1, const Vec3& v);