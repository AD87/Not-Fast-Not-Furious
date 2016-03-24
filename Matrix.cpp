#include <iostream>
#include "Matrix.h"
#include "MyGL.h"

Matrix::Matrix(){
	setToIdentity();
}

Matrix::Matrix(float arrayMatrix[16]){
	for(size_t i = 0; i < 16; i++){
		m_array[i] = arrayMatrix[i];
	}
}

void Matrix::setToIdentity(){
	for (size_t i = 0; i < 16; i++){
		m_array[i] = 0.0f;
	}
	m_array[0] = 1.0f;
	m_array[5] = 1.0f;
	m_array[10] = 1.0f;
	m_array[15] = 1.0f;
}

Matrix Matrix::operator*=(const Matrix& m) {
	float tempArray[16];

	tempArray[0] = m_array[0] * m.m_array[0] + m_array[4] * m.m_array[1] + m_array[8] * m.m_array[2] + m_array[12] * m.m_array[3];
	tempArray[1] = m_array[1] * m.m_array[0] + m_array[5] * m.m_array[1] + m_array[9] * m.m_array[2] + m_array[13] * m.m_array[3];
	tempArray[2] = m_array[2] * m.m_array[0] + m_array[6] * m.m_array[1] + m_array[10] * m.m_array[2] + m_array[14] * m.m_array[3];
	tempArray[3] = m_array[3] * m.m_array[0] + m_array[7] * m.m_array[1] + m_array[11] * m.m_array[2] + m_array[15] * m.m_array[3];

	tempArray[4] = m_array[0] * m.m_array[4] + m_array[4] * m.m_array[5] + m_array[8] * m.m_array[6] + m_array[12] * m.m_array[7];
	tempArray[5] = m_array[1] * m.m_array[4] + m_array[5] * m.m_array[5] + m_array[9] * m.m_array[6] + m_array[13] * m.m_array[7];
	tempArray[6] = m_array[2] * m.m_array[4] + m_array[6] * m.m_array[5] + m_array[10] * m.m_array[6] + m_array[14] * m.m_array[7];
	tempArray[7] = m_array[3] * m.m_array[4] + m_array[7] * m.m_array[5] + m_array[11] * m.m_array[6] + m_array[15] * m.m_array[7];

	tempArray[8] = m_array[0] * m.m_array[8] + m_array[4] * m.m_array[9] + m_array[8] * m.m_array[10] + m_array[12] * m.m_array[11];
	tempArray[9] = m_array[1] * m.m_array[8] + m_array[5] * m.m_array[9] + m_array[9] * m.m_array[10] + m_array[13] * m.m_array[11];
	tempArray[10] = m_array[2] * m.m_array[8] + m_array[6] * m.m_array[9] + m_array[10] * m.m_array[10] + m_array[14] * m.m_array[11];
	tempArray[11] = m_array[3] * m.m_array[8] + m_array[7] * m.m_array[9] + m_array[11] * m.m_array[10] + m_array[15] * m.m_array[11];

	tempArray[12] = m_array[0] * m.m_array[12] + m_array[4] * m.m_array[13] + m_array[8] * m.m_array[14] + m_array[12] * m.m_array[15];
	tempArray[13] = m_array[1] * m.m_array[12] + m_array[5] * m.m_array[13] + m_array[9] * m.m_array[14] + m_array[13] * m.m_array[15];
	tempArray[14] = m_array[2] * m.m_array[12] + m_array[6] * m.m_array[13] + m_array[10] * m.m_array[14] + m_array[14] * m.m_array[15];
	tempArray[15] = m_array[3] * m.m_array[12] + m_array[7] * m.m_array[13] + m_array[11] * m.m_array[14] + m_array[15] * m.m_array[15];

	for (size_t i = 0; i < 16; i++){
		m_array[i] = tempArray[i];
	}

	return *this;
}

Vec3 Matrix::operator*=(const Vec3& v){
	float x = m_array[0] * v.x + m_array[4] * v.y + m_array[8] * v.z + m_array[12] * 1;
	float y = m_array[1] * v.x + m_array[5] * v.y + m_array[9] * v.z + m_array[13] * 1;
	float z = m_array[2] * v.x + m_array[6] * v.y + m_array[10] * v.z + m_array[14] * 1;
	float w = m_array[3] * v.x + m_array[7] * v.y + m_array[11] * v.z + m_array[15] * 1;

	return Vec3(x / w, y / w, z / w);
}

void Matrix::setTranslate(const Vec3& v){
	m_array[12] = v.x;
	m_array[13] = v.y;
	m_array[14] = v.z;
}

void Matrix::setScale(const Vec3& v){
	m_array[0] = v.x;
	m_array[5] = v.y;
	m_array[10] = v.z;
}

void Matrix::setRotateX(float angle){
	m_array[0] = 1;
	m_array[5] = cos(angle);
	m_array[6] = sin(angle);
	m_array[9] = -sin(angle);
	m_array[10] = cos(angle);
	m_array[15] = 1;
}
void Matrix::setRotateY(float angle){
	m_array[0] = cos(angle);
	m_array[2] = -sin(angle);
	m_array[5] = 1;
	m_array[8] = sin(angle);
	m_array[10] = cos(angle);
	m_array[15] = 1;
}
void Matrix::setRotateZ(float angle){
	m_array[0] = cos(angle);
	m_array[1] = sin(angle);
	m_array[4] = -sin(angle);
	m_array[5] = cos(angle);
	m_array[10] = 1;
	m_array[15] = 1;
}

void Matrix::printMatrix(){
	std::cout << m_array[0] << " " << m_array[4] << " " << m_array[8] << " " << m_array[12] << std::endl;
	std::cout << m_array[1] << " " << m_array[5] << " " << m_array[9] << " " << m_array[13] << std::endl;
	std::cout << m_array[2] << " " << m_array[6] << " " << m_array[10] << " " << m_array[14] << std::endl;
	std::cout << m_array[3] << " " << m_array[7] << " " << m_array[11] << " " << m_array[15] << std::endl;
}

void Matrix::getModelview(){
	glGetFloatv(GL_MODELVIEW_MATRIX, m_array);
}

void Matrix::getProjection(){
	glGetFloatv(GL_PROJECTION_MATRIX, m_array);
}

Matrix operator*(const Matrix& m1, const Matrix& m2){
	Matrix result;

	result.m_array[0] = m1.m_array[0] * m2.m_array[0] + m1.m_array[4] * m2.m_array[1] + m1.m_array[8] * m2.m_array[2] + m1.m_array[12] * m2.m_array[3];
	result.m_array[1] = m1.m_array[1] * m2.m_array[0] + m1.m_array[5] * m2.m_array[1] + m1.m_array[9] * m2.m_array[2] + m1.m_array[13] * m2.m_array[3];
	result.m_array[2] = m1.m_array[2] * m2.m_array[0] + m1.m_array[6] * m2.m_array[1] + m1.m_array[10] * m2.m_array[2] + m1.m_array[14] * m2.m_array[3];
	result.m_array[3] = m1.m_array[3] * m2.m_array[0] + m1.m_array[7] * m2.m_array[1] + m1.m_array[11] * m2.m_array[2] + m1.m_array[15] * m2.m_array[3];
										 								 				
	result.m_array[4] = m1.m_array[0] * m2.m_array[4] + m1.m_array[4] * m2.m_array[5] + m1.m_array[8] * m2.m_array[6] + m1.m_array[12] * m2.m_array[7];
	result.m_array[5] = m1.m_array[1] * m2.m_array[4] + m1.m_array[5] * m2.m_array[5] + m1.m_array[9] * m2.m_array[6] + m1.m_array[13] * m2.m_array[7];
	result.m_array[6] = m1.m_array[2] * m2.m_array[4] + m1.m_array[6] * m2.m_array[5] + m1.m_array[10] * m2.m_array[6] + m1.m_array[14] * m2.m_array[7];
	result.m_array[7] = m1.m_array[3] * m2.m_array[4] + m1.m_array[7] * m2.m_array[5] + m1.m_array[11] * m2.m_array[6] + m1.m_array[15] * m2.m_array[7];
										 								 			
	result.m_array[8] = m1.m_array[0] * m2.m_array[8] + m1.m_array[4] * m2.m_array[9] + m1.m_array[8] * m2.m_array[10] + m1.m_array[12] * m2.m_array[11];
	result.m_array[9] = m1.m_array[1] * m2.m_array[8] + m1.m_array[5] * m2.m_array[9] + m1.m_array[9] * m2.m_array[10] + m1.m_array[13] * m2.m_array[11];
	result.m_array[10] = m1.m_array[2] * m2.m_array[8] + m1.m_array[6] * m2.m_array[9] + m1.m_array[10] * m2.m_array[10] + m1.m_array[14] * m2.m_array[11];
	result.m_array[11] = m1.m_array[3] * m2.m_array[8] + m1.m_array[7] * m2.m_array[9] + m1.m_array[11] * m2.m_array[10] + m1.m_array[15] * m2.m_array[11];
										  
	result.m_array[12] = m1.m_array[0] * m2.m_array[12] + m1.m_array[4] * m2.m_array[13] + m1.m_array[8] * m2.m_array[14] + m1.m_array[12] * m2.m_array[15];
	result.m_array[13] = m1.m_array[1] * m2.m_array[12] + m1.m_array[5] * m2.m_array[13] + m1.m_array[9] * m2.m_array[14] + m1.m_array[13] * m2.m_array[15];
	result.m_array[14] = m1.m_array[2] * m2.m_array[12] + m1.m_array[6] * m2.m_array[13] + m1.m_array[10] * m2.m_array[14] + m1.m_array[14] * m2.m_array[15];
	result.m_array[15] = m1.m_array[3] * m2.m_array[12] + m1.m_array[7] * m2.m_array[13] + m1.m_array[11] * m2.m_array[14] + m1.m_array[15] * m2.m_array[15];

	return result;
}

Vec3 operator*(const Matrix& m1, const Vec3& v){
	float x = m1.m_array[0] * v.x + m1.m_array[4] * v.y + m1.m_array[8] * v.z + m1.m_array[12] * 1;//w=1
	float y = m1.m_array[1] * v.x + m1.m_array[5] * v.y + m1.m_array[9] * v.z + m1.m_array[13] * 1;
	float z = m1.m_array[2] * v.x + m1.m_array[6] * v.y + m1.m_array[10] * v.z + m1.m_array[14] * 1;
	float w = m1.m_array[3] * v.x + m1.m_array[7] * v.y + m1.m_array[11] * v.z + m1.m_array[15] * 1;

	return Vec3(x / w, y / w, z / w);
}