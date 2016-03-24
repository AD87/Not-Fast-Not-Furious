#pragma once
#include <map>
#include "Texture.h"
#include "SmartPtr.h"
#include "Singleton.h"

class TextureManager : public Uncopyable{
private:
	TextureManager(){}
	friend Singleton<TextureManager>;
public:
	P_texture getTexture(const std::string& textureName);
	void deleteUnusedTextures();
private:
	typedef std::map<std::string, P_texture> TextureMap;
	TextureMap m_textureMap;
};

typedef Singleton<TextureManager> TheTextureManager;