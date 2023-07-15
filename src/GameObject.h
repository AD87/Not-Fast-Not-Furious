#pragma once
#include <map>
#include "Box.h"
#include "OBB.h"
#include "Vec3.h"

class File;

class GameObject{
public:
	GameObject(){
		m_toBeRemoved = false;
	}
	virtual ~GameObject(){}
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual bool load(File* f = nullptr){ return true; }//default implemention in case this function is not overriden

	bool getRemoveMe() const{
		return m_toBeRemoved;
	}
	void RemoveMe(){
		m_toBeRemoved = true;
	}

	virtual const char* getTypeName()const = 0;//const char* instead of string because it will never change

	virtual const Box& getBox() const = 0;//to be overriden by all game objects, calculating and returning their Box
	virtual OBB getOBB() const = 0;
protected:
	bool m_toBeRemoved;
	Vec3f m_pos;
	Vec3f m_vel;
	Vec3f m_acc;
	Box m_box;
	OBB m_obb;
	Vec3f m_halfDimension;
};

typedef std::map<int, GameObject*> GameObjectMap;