#include "Camera.h"
#include "MyGL.h"

void Camera::lookAt(const Vec3& eye, const Vec3& up, const Vec3& center){
	m_eye = eye;
	m_up = up;
	m_center = center;
}

void Camera::placeCamera(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(m_eye.x, m_eye.y, m_eye.z,
		m_center.x, m_center.y, m_center.z,
		m_up.x, m_up.y, m_up.z);
}

void Camera::setPerspective(double near, double far, double fov, double aspect){
	m_near = near;
	m_far = far;
	m_fieldOfView = fov;
	m_aspectRatio = aspect;
}

void Camera::applyPerspective(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(m_fieldOfView, m_aspectRatio, m_near, m_far);
}

Vec3 Camera::getEye()const{
	return m_eye;
}
Vec3 Camera::getUp()const{
	return m_up;
}
Vec3 Camera::getCenter()const{
	return m_center;
}
double Camera::getNear()const{
	return m_near;
}
double Camera::getFar()const{
	return m_far;
}
double Camera::getAspectRatio()const{
	return m_aspectRatio;
}
double Camera::getFov()const{
	return m_fieldOfView;
}

void Camera::setEye(const Vec3& eye){
	m_eye = eye;
}
void Camera::setUp(const Vec3& up){
	m_up = up;
}
void Camera::setCenter(const Vec3& center){
	m_center = center;
}
void Camera::setNear(double near){
	m_near = near;
}
void Camera::setFar(double far){
	m_far = far;
}
void Camera::setAspectRatio(double aspectRatio){
	m_aspectRatio = aspectRatio;
}
void Camera::setFov(double fov){
	m_fieldOfView = fov;
}