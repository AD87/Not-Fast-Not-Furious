#pragma once
#include "Vec3.h"

class Camera{
public:
	Camera();
	void lookAt(const Vec3& eye, const Vec3& up, const Vec3& center);
	void placeCamera();
	void setPerspective(double near, double far, double fov, double aspect);
	void applyPerspective();//call glutPerspective

	Vec3 getEye()const;
	Vec3 getUp()const;
	Vec3 getCenter()const;
	double getNear()const;
	double getFar()const;
	double getAspectRatio()const;
	double getFov()const;

	void setEye(const Vec3& eye);
	void setUp(const Vec3& up);
	void setCenter(const Vec3& center);
	void setNear(double near);
	void setFar(double far);
	void setAspectRatio(double aspectRatio);
	void setFov(double fov);
private:
	Vec3 m_eye;//pos of camera
	Vec3 m_up;//up vector (where the top of the camera is facing)
	Vec3 m_center;//where the camera is looking at

	double m_near;
	double m_far;
	double m_aspectRatio;
	double m_fieldOfView;
};