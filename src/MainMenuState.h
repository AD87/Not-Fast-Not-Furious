#pragma once
#include "GameState.h"
#include "Image.h"
#include "EventListener.h"
#include "Player.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

class MainMenuState :public GameState, public EventListener{
private:
	MainMenuState(){}
	friend Singleton<MainMenuState>;
public:
	bool load();
	virtual void update() override;
	virtual void draw() override;
	virtual void onActive()override;
	virtual void onDeactivated()override;
	void OnKeyboardEvent(const SDL_KeyboardEvent& ke)override;
	virtual void OnQuit()override;
private:
	Texture m_planeTexture;
	Material m_material;
	Mesh m_mesh;
};

typedef Singleton<MainMenuState> TheMainMenuState;