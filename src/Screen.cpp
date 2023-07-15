#include "Screen.h"
#include <cassert>

Screen::Screen(){
	m_renderer = nullptr;
}

bool Screen::createWindow(std::string name, int width, int height){
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL); //SDL_WINDOW_FULLSCREEN);
	
	m_size.x = width;
	m_size.y = height;

	if (!m_window)return false;

	SDL_GLContext context = SDL_GL_CreateContext(m_window);
	if (!context)return false;
	//m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	//m_size = Vec2i(width, height);
	return true;
}

bool Screen::createWindow(std::string name, Vec2i size){
	return createWindow(name, size.x, size.y);
	m_size.x = size.x;
	m_size.y = size.y;
}

void Screen::flipBuffer(){
	//SDL_RenderPresent(m_renderer);
	SDL_GL_SwapWindow(m_window);
}

SDL_Renderer* Screen::getRenderer(){
	return m_renderer;
}

const Vec2i& Screen::getSize()const{
	return m_size;
}
