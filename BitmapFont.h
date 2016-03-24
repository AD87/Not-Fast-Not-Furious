#pragma once
#include <string>
#include "Texture.h"
#include "Vec2.h"
#include "Vec3.h"

class BitmapFont{
public:
	BitmapFont();
	bool load(const std::string& fileName);
	void draw(const Vec2f& pos, const std::string& text, float fontSize, const Vec3& RGBcolor);
private:
	bool loadWidthsFile(const std::string& fileName);

	Texture m_texture;
	int m_rowSize;
	int m_columnSize;
	float m_cellWidth;
	float m_cellHeight;
	int m_characterWidths[255];
};