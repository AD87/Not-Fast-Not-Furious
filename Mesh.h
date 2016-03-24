#pragma once

#include <string>
#include <vector>
#include "Vec2.h"
#include "Vec3.h"
#include "ObjUsefulFunctions.h"
#include "Texture.h"
#include "Material.h"

class Mesh{
public:
	bool load(const std::string& fileName);
	void draw();//draws all groups
	void draw(const std::string& groupName, Texture* t=nullptr);//draws specific group only
	Group* getGroup(const std::string& groupName);
	Vecs* getPoints();
private:
	typedef std::map <std::string, std::pair <Material, P_texture>> ObjMaterialMap;
	ObjMaterialMap m_materialMap;

	bool loadMtl(const std::string& fileName);

	Vecs m_points;
	Vecs m_normals;
	UVs m_uvs;
	Groups m_groups;	
};