#include <assert.h>
#include "Mesh.h"
#include "File.h"
#include "ReportError.h"
#include "TextureManager.h"
#include "MyGL.h"

bool Mesh::load(const std::string& fileName){
	//reserve space on the containers so it doesn't have to be resizing every time
	m_normals.reserve(1000);
	m_points.reserve(1000);
	m_uvs.reserve(1000);

	File file;
	if (!file.openRead(fileName)){
		ReportError("failed to load mesh");
		return false;
	}

	Group* currentGroup = nullptr;

	while (!file.isEndOfFile()){
		std::string line;
		if (!file.getString(&line)){
			if (file.isEndOfFile()){
				return true;
			}
			return false;
		}

		Strings strings = Split(line, ' ');

		if (strings[0] == "v"){
			m_points.push_back(ToVec3(strings));
		}

		else if (strings[0] == "vn"){
			m_normals.push_back(ToVec3(strings));
		}

		else if (strings[0] == "vt"){
			m_uvs.push_back(ToVec2(strings));
			m_uvs.back().y = -m_uvs.back().y;
		}

		else if (strings[0] == "f"){
			if (strings.size() < 4){
				Face f;
				ToFace(strings, &f);
				currentGroup->m_faces.push_back(f);
			}
			else{
				Face f[2];
				ToFace(strings, f);
				currentGroup->m_faces.push_back(f[0]);
				currentGroup->m_faces.push_back(f[1]);
			}
		}

		else if (strings[0] == "g"){
			Group group;
			group.m_name = strings[1];
			m_groups[strings[1]] = group;
			currentGroup = &m_groups[group.m_name];
		}

		else if (strings[0] == "usemtl"){
			currentGroup->m_materialName = strings[1];
		}

		else if (strings[0] == "mtllib"){
			std::string mtlfile = strings[1];
			if (!loadMtl(mtlfile)){

				return false;
			}
		}
	}
	return false;
}

void Mesh::draw(){
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	for (auto it = m_groups.begin(); it != m_groups.end(); it++){
		//binding colour
		m_materialMap[it->second.m_materialName].first.bind();

		//binding texture
		m_materialMap[it->second.m_materialName].second->bind();

		Faces* faces = &m_groups[it->first].m_faces;
		glBegin(GL_TRIANGLES);
		//iterating through our faces in our group
		for (auto jt = faces->begin(); jt != faces->end(); jt++){
			Face* face = &(*jt);
			for (unsigned int n = 0; n < 3; n++){
				glNormal3fv(m_normals[face->m_normalIndex[n]].toArray());
				glTexCoord2fv(m_uvs[face->m_uvIndex[n]].toArray());
				glVertex3fv(m_points[face->m_pointIndex[n]].toArray());
			}
		}
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
}

void Mesh::draw(const std::string& groupName, Texture* t){
	auto it = m_groups.find(groupName);
	assert(it != m_groups.end());

	m_materialMap[it->second.m_materialName].first.bind();

	//binding texture
	if (t == nullptr){
		m_materialMap[it->second.m_materialName].second->bind();
		//P_texture temp = m_materialMap[it->second.m_materialName].second;
	}
	else {
		t->bind();//bind texture passed to the function instead of the one on the file
	}
	
	Faces* faces = &m_groups[it->first].m_faces;
	glBegin(GL_TRIANGLES);
	//iterating through our faces in our group
	for (auto jt = faces->begin(); jt != faces->end(); jt++){
		Face* face = &(*jt);
		for (unsigned int n = 0; n < 3; n++){
			glNormal3fv(m_normals[face->m_normalIndex[n]].toArray());
			glTexCoord2fv(m_uvs[face->m_uvIndex[n]].toArray());
			glVertex3fv(m_points[face->m_pointIndex[n]].toArray());
		}
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
}

Group* Mesh::getGroup(const std::string& groupName){
	auto it = m_groups.find(groupName);
	assert(it != m_groups.end());
	return &it->second;
}

Vecs* Mesh::getPoints(){
	return &m_points;
}

bool Mesh::loadMtl(const std::string& fileName){
	File file;

	if (!file.openRead(fileName)){
		ReportError("failed to load material");
		return false;
	}

	std::string currentPair;

	while (!file.isEndOfFile()){
		std::string line;
		if (!file.getString(&line)){
			if (file.isEndOfFile()){
				return true;
			}
			return false;
		}

		Strings strings = Split(line, ' ');

		if (strings[0] == "newmtl"){
			std::pair <Material, P_texture> tex;

			m_materialMap[strings[1]] = tex;

			currentPair = strings[1];
		}

		if (strings[0] == "Ka"){
			float r = ToFloat(strings[1]);
			float g = ToFloat(strings[2]);
			float b = ToFloat(strings[3]);

			//putting ambience component into material
			m_materialMap[currentPair].first.setAmbient(Colour(r, g, b));
		}

		if (strings[0] == "Kd"){
			float r = ToFloat(strings[1]);
			float g = ToFloat(strings[2]);
			float b = ToFloat(strings[3]);

			//putting diffuse component into material
			m_materialMap[currentPair].first.setDiffuse(Colour(r, g, b));
		}

		if (strings[0] == "Ks"){
			float r = ToFloat(strings[1]);
			float g = ToFloat(strings[2]);
			float b = ToFloat(strings[3]);

			//putting specular component into material
			m_materialMap[currentPair].first.setSpecular(Colour(r, g, b));
		}

		if (strings[0] == "Ns"){
			float s = ToFloat(strings[1]);
			m_materialMap[currentPair].first.setShininess(s);
		}

		if (strings[0] == "map_Kd"){
			P_texture tempTexture = TheTextureManager::Instance()->getTexture(strings[1]);
			if (tempTexture.isNull()){
				ReportError("Failed to load texture");
				return false;
			}
			m_materialMap[currentPair].second = tempTexture;
		}
	}
	return true;
}