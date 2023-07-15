#include <math.h>
#include "PlayState.h"
#include "EventPoller.h"
#include "Screen.h"
#include "Game.h"
#include "GameObject.h"
#include "Timer.h"
#include "trig.h"
#include "GameObjectFactory.h"
#include "ReportError.h"
#include "MyHud.h"
#include "File.h"
#include "MyGL.h"

bool PlayState::load(){
	static bool loaded = false;
	if (loaded)return true;

	if (!ThePlayer::Instance()->load()) return false;
	if (!TheHud::Instance()->load()) return false;
	if (!m_floor.load("grass.jpg")) return false;

	if (!m_cars[0].load(Vec3(-5.1f, 0, 16.8f), 2, "riored.bmp")) return false;
	if (!m_cars[1].load(Vec3(2.0f, 0, -10.0f), 3, "riowhite.bmp")) return false;
	if (!m_cars[2].load(Vec3(12.2f, 0, -4.1f), 4, "rioblue.bmp")) return false;
	if (!m_cars[3].load(Vec3(3.0f, 0, 8.0f), 5, "riosilver.bmp")) return false;
	if (!m_cars[4].load(Vec3(-15.0f, 0, -2.5f), 6, "rioyellow.bmp")) return false;

	m_cameraUp = false;

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	loaded = true;
	return true;
}

void PlayState::draw() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspectRatio = static_cast<float>(TheScreen::Instance()->getSize().x) / static_cast<float>(TheScreen::Instance()->getSize().y);
	gluPerspective(45.0, aspectRatio, 1.0, 500.0);// field of view, aspect ratio, distance to near plane, distance to far plane

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setCameraPos();

	m_frustum.update();//update the frustum once the camera is set

	int numCars = 0;
	if (m_frustum.intersects(ThePlayer::Instance()->getBox())){
		//this will always be true because camera moves with the player
		numCars++;
		ThePlayer::Instance()->draw();
	}
	for (size_t i = 0; i < 5; i++){
		if (m_frustum.intersects(m_cars[i].getBox())){
			//we check if the boxes of the cars are inside the view frustum
			//they are drawn only if they are inside the 6 planes of the frustum
			numCars++;
			m_cars[i].draw();
		}
	}
	TheHud::Instance()->updateNumCars(numCars);//hud display how many cars are being drawn
	
	//draw floor
	m_floor.bind();
	glBegin(GL_QUADS);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-30, 0, -30);
	
	glNormal3f(0, 1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(30, 0, -30);

	glNormal3f(0, 1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(30, 0, 30);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-30, 0, 30);

	glEnd();
	m_floor.unbind();

	TheHud::Instance()->draw();
	//hud must be last thing to be drawn because matrices are reset
	//and z buffer is disabled inside its draw function
}

void PlayState::update(){
	ThePlayer::Instance()->update();
}

void PlayState::onActive(){
	bool b = load();
	assert(b);
	TheEventPoller::Instance()->addHandler(ThePlayer::Instance());
	TheEventPoller::Instance()->addHandler(this);
}

void PlayState::onDeactivated(){
	TheEventPoller::Instance()->removeHandler(ThePlayer::Instance());
	TheEventPoller::Instance()->removeHandler(this);
}

void PlayState::OnKeyboardEvent(const SDL_KeyboardEvent& ke){
	if (ke.state == SDL_PRESSED){
		if (ke.keysym.sym == SDLK_SPACE){
			m_cameraUp = !m_cameraUp;//change camera perspective when pressing space button
		}
	}
}

void PlayState::OnQuit(){
	TheGame::Instance()->quit();
}

void PlayState::setCameraPos(){
	//putting camera always on the back of car
	Player* pPlayer = ThePlayer::Instance();
	Vec3 cameraBackPos = pPlayer->getPos();
	Vec3 offset = degToVec(-pPlayer->getCarY());
	cameraBackPos += (offset * 8);//how far from the back of car

	Vec3 cameraTopPos = pPlayer->getPos() + Vec3(0, 10, 0);

	//we create a line segment between the two points we have created,
	//one on top of the car and the other on the back of the car
	LineSegment ls(cameraBackPos, cameraTopPos);

	static float t = 0.3f;//set the minimun point on the line segment to be a bit higher,
	//otherwise the camera would be too close to the floor

	//once we change the perspective, the camera will travel from one point to the other in the line seg
	if (m_cameraUp == false){
		t -= TheTimer::Instance()->GetDt();
	}
	else{
		t += TheTimer::Instance()->GetDt();
	}

	//dont let t go beyond the line seg min and max
	if (t > 0.9){
		t = 0.9;//make sure that t is not iqual to 1, because the up vector of the camera is (0, 1, 0)
	}
	if (t < 0.3){
		t = 0.3;
	}

	Vec3 finalPosCam = ls.getPoint(t);

	gluLookAt(finalPosCam.x, finalPosCam.y, finalPosCam.z,
		pPlayer->getPos().x, pPlayer->getPos().y, pPlayer->getPos().z,
		0, 1.0, 0);//position of camera, point camera is looking at, camera up
}