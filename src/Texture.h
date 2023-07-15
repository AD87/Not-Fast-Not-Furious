#pragma once
#include <string>
#include "SmartPtr.h"

class Texture : public RefCounted{
public:
	Texture();
	~Texture();

	bool load(const std::string& fileName);
	void bind();
	void unbind();

	int getHeight()const;
	int getWidth()const;
private:
	unsigned int m_textureID;

	int m_width;
	int m_height;
	int m_bpp;
	int m_format;
};

typedef SmartPtr<Texture> P_texture;