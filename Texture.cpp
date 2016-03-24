#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
#include "ReportError.h"
#include "MyGL.h"

Texture::Texture(){
	m_textureID = 0;
}

Texture::~Texture(){
	if (m_textureID){
		glDeleteTextures(1, &m_textureID);
	}
}

bool Texture::load(const std::string& fileName){
	SDL_Surface* surf = IMG_Load(fileName.c_str());
	
	if (!surf){
		ReportError("failed to load texture");
		return false;
	}
	//generating texture ID
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	//getting image info
	unsigned char* data = static_cast<unsigned char*> (surf->pixels);
	m_width = surf->w;
	m_height = surf->h;
	m_bpp = surf->format->BytesPerPixel;
	if (m_bpp == 24 || m_bpp == 3){
		m_format = GL_RGB;
	}
	else {
		m_format=GL_RGBA;
	}

	//sending image data to opengl
	glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, data);
	gluBuild2DMipmaps(GL_TEXTURE_2D, m_format, m_width, m_height, m_format, GL_UNSIGNED_BYTE, data);

	//freeing it up as it is no longer needed
	SDL_FreeSurface(surf);

	//setting up filters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return true;
}

void Texture::bind(){
	if (m_textureID != 0){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
	}
}

void Texture::unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getHeight()const{
	return m_height;
}

int Texture::getWidth()const{
	return m_width;
}