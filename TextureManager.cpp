#include "TextureManager.h"
#include "Texture.h"
#include "ReportError.h"

P_texture TextureManager::getTexture(const std::string& textureName){
	auto it = m_textureMap.find(textureName);
	if (it != m_textureMap.end()){
		return it->second;
	}
	else{
		P_texture t = new Texture;
		if (t->load(textureName)){
			m_textureMap.insert(std::pair <std::string, P_texture>(textureName, t));
			return t;
		}
	}
	return P_texture();
}

void TextureManager::deleteUnusedTextures(){
	for (auto it = m_textureMap.begin(); it != m_textureMap.end(); it++){
		if (it->second.getRefCount() == 1){
			it=m_textureMap.erase(it);
			if (it == m_textureMap.end()) return;
		}
	}
	
}