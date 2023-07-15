#pragma once
#include "Colour.h"

class Material{
public:
	Material();
	Material(const Colour& amb, const Colour& dif, const Colour& spe, float shi);

	const Colour& getAmbient()const;
	const Colour& getDiffuse()const;
	const Colour& getSpecular()const;
	int getShininess()const;

	void setAmbient(const Colour& amb);
	void setDiffuse(const Colour& dif);
	void setSpecular(const Colour& spe);
	void setShininess(int shi);

	void bind();
private:
	Colour m_ambient;
	Colour m_diffuse;
	Colour m_specular;
	int m_shininess;
};