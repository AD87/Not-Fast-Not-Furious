#pragma once
#include "Hud.h"
#include "Texture.h"
#include "Shader.h"
#include "BitmapFont.h"
#include "Singleton.h"

class MyHud:public Hud,public Uncopyable{
private:
	MyHud(){}
	friend Singleton<MyHud>;
public:
	bool load();
	void update()override;
	void draw()override;

	void changeSpeed(float newSpeed);
	void reduceHealth();
	void updateNumCars(int number);
private:
	BitmapFont m_font;
	float m_health;
	float m_speed;
	int m_numCars;
	Shader m_shader;
};

typedef Singleton<MyHud> TheHud;