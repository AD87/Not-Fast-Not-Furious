#pragma once
#include "GameObject.h"
#include "Mesh.h"

class Car:public GameObject{
public:
	bool load(const Vec3& pos, int id, const std::string& texture);
	virtual void draw() override;
	virtual void update() override;

	static const char* staticTypeName();
	virtual const char* getTypeName()const override;

	virtual const Box& getBox() const override;
	virtual OBB getOBB() const override;
private:
	Mesh m_mesh;
	Texture m_texture;
};