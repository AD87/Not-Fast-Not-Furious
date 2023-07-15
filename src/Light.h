#pragma once
#include "Vec3.h"
#include "Colour.h"

enum class LightTye{ DIRECTIONAL, POSITIONAL };//DIRECTIONAL=0 POSITIONAL=1

class Light{
public:
	Light();
	~Light();

	void init(int id, const Vec3& vec, LightTye type);

	void switchOn();

	void setId(int id);
	void setVec(const Vec3& vec);
	void setType(LightTye type);
	void setAmbient(const Colour& a);
	void setDiffuse(const Colour& d);
	void setSpecular(const Colour& s);

	const Vec3& getVec() const;
	LightTye getType() const;
	int getId() const;
	const Colour& getAmbient()const;
	const Colour& getDiffuse()const;
	const Colour& getSpecular()const;

	//enable/disable specific lights
	void enable();
	void disable();

	//enable/disable all lights
	static void enableLightning();
	static void disableLightning();

private:
	Vec3 m_vec;
	LightTye m_type;
	int m_id;
	Colour m_ambient;
	Colour m_diffuse;
	Colour m_specular;
};