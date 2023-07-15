#include "Hud.h"
#include "MyGL.h"

void Hud::begin(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//disabling testing and writing to z buffer
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glDisable(GL_LIGHTING);

	//turn on blending(transparency in textures)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//turning on texture 2D
	// either do it here or in the draw func of your hud elements
	glEnable(GL_TEXTURE_2D);
}
void Hud::end(){
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glEnable(GL_LIGHTING);

	glDisable(GL_BLEND);

	glDisable(GL_TEXTURE_2D);
}