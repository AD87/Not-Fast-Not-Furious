#pragma once
#include "EventListener.h"
#include "GameState.h"
#include "Mesh.h"
#include "Singleton.h"
#include "Player.h"
#include "Texture.h"
#include "Frustum.h"
#include "Car.h"

class PlayState :public GameState, public EventListener{
private:
	PlayState(){}
	friend Singleton<PlayState>;
public:
	bool load();
	virtual void update() override;
	virtual void draw() override;

	virtual void onActive()override;
	virtual void onDeactivated()override;
	void OnKeyboardEvent(const SDL_KeyboardEvent& ke)override;
	virtual void OnQuit()override;

private:
	void setCameraPos();
	bool m_cameraUp;//bool to change the camera perspective

	Car m_cars[5];
	Texture m_floor;
	Frustum m_frustum;
};

typedef Singleton<PlayState> ThePlayState;