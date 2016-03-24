#include "Light.h"
#include "MyGL.h"

Light::Light(){
	m_id = 0;
	setAmbient(Colour(0.2f, 0.2f, 0.2f));
	setDiffuse(Colour(0.6f, 0.6f, 0.6f));
	setSpecular(Colour(1.0f, 1.0f, 1.0f));
}
Light::~Light(){
	glDisable(m_id);
}

void Light::switchOn(){
	//before you call this enable GL_LIGHTING
	glEnable(m_id);

	GLfloat params[] = { m_vec.x, m_vec.y, m_vec.z, static_cast<float> (m_type) };
	glLightfv(m_id, GL_POSITION, params);

	GLfloat ambParams[] = { m_ambient.r, m_ambient.g, m_ambient.b, m_ambient.a};
	glLightfv(m_id, GL_AMBIENT, ambParams);
	GLfloat difParams[] = { m_diffuse.r, m_diffuse.g, m_diffuse.b, m_diffuse.a };
	glLightfv(m_id, GL_DIFFUSE, difParams);
	GLfloat speParams[] = { m_specular.r, m_specular.g, m_specular.b, m_specular.a };
	glLightfv(m_id, GL_SPECULAR, speParams);
}

void Light::setId(int id){
	m_id = id;
}
void Light::setVec(const Vec3& vec){
	m_vec = vec;
}
void Light::setType(LightTye type){
	m_type = type;
}
void Light::setAmbient(const Colour& a){
	m_ambient = a;
}
void Light::setDiffuse(const Colour& d){
	m_diffuse = d;
}
void Light::setSpecular(const Colour& s){
	m_specular = s;
}

const Vec3& Light::getVec() const{
	return m_vec;
}
LightTye Light::getType() const{
	return m_type;
}
int Light::getId() const{
	return m_id;
}
const Colour& Light::getAmbient()const{
	return m_ambient;
}
const Colour& Light::getDiffuse()const{
	return m_diffuse;
}
const Colour& Light::getSpecular()const{
	return m_specular;
}

void Light::enable(){
	glEnable(m_id);
}

void Light::disable(){
	glDisable(m_id);
}

static void enableLightning(){
	glEnable(GL_LIGHTING);
}
static void disableLightning(){
	glDisable(GL_LIGHTING);
}