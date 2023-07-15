#include "Material.h"
#include "MyGL.h"

Material::Material(){
	m_shininess = 0.0f;
}
Material::Material(const Colour& amb, const Colour& dif, const Colour& spe, float shi){
	m_ambient = amb;
	m_diffuse = dif;
	m_specular = spe;
	m_shininess = shi;
}

const Colour& Material::getAmbient()const{
	return m_ambient;
}
const Colour& Material::getDiffuse()const{
	return m_diffuse;
}
const Colour& Material::getSpecular()const{
	return m_specular;
}
int Material::getShininess()const{
	return m_shininess;
}

void Material::setAmbient(const Colour& amb){
	m_ambient = amb;
}
void Material::setDiffuse(const Colour& dif){
	m_diffuse = dif;
}
void Material::setSpecular(const Colour& spe){
	m_specular = spe;
}
void Material::setShininess(int shi){
	m_shininess = shi;
}

void Material::bind(){
	glDisable(GL_COLOR_MATERIAL);
	//dont forget to disable GL_COLOR_MATERIAL

	glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient.toArray());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse.toArray());
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular.toArray());
	glMateriali(GL_FRONT, GL_SHININESS, m_shininess);
}