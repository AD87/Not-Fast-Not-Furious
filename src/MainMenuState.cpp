#include <cassert>
#include "MainMenuState.h"
#include "EventPoller.h"
#include "SoundManager.h"
#include "Vec3.h"
#include "Game.h"


bool MainMenuState::load(){
	static bool loaded = false;
	if (loaded)return true;

	loaded = true;
	return true;
}

void MainMenuState::update(){
}

void MainMenuState::draw(){
	
}

void MainMenuState::onActive(){
	assert(load());
}

void MainMenuState::onDeactivated(){
}

void MainMenuState::OnKeyboardEvent(const SDL_KeyboardEvent& ke){

}

void MainMenuState::OnQuit(){
	TheGame::Instance()->quit();
}
