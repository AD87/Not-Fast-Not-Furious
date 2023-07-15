#include "Screen.h"
#include "Game.h"
#include "PlayState.h"
#include "MyGL.h"

int main(int, char**){
	Screen* theScreen = TheScreen::Instance();
	theScreen->createWindow("myWindow", 1100, 700);

	if (!glewInit() == GLEW_OK){
		assert(0);
	}

	TheGame::Instance()->setState(ThePlayState::Instance());

	TheGame::Instance()->run();

	return 0;
}