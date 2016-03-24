#include "BitmapFont.h"
#include "File.h"
#include "ReportError.h"
#include "MyGL.h"

BitmapFont::BitmapFont(){

}

bool BitmapFont::load(const std::string& fileName){
	File file;
	if(!file.openRead(fileName)){
		ReportError("failed to open file");
		return false;
	}
	std::string textFileName;
	if (!file.getString(&textFileName)){
		ReportError("failed to read file");
		return false;
	}
	if (!m_texture.load(textFileName)){
		ReportError("failed to load texture");
		return false;
	}
	if (!file.getInt(&m_rowSize)){
		ReportError("bitmapfont row size error");
		return false;
	}
	if (!file.getInt(&m_columnSize)){
		ReportError("bitmapfont column size error");
		return false;
	}

	std::string widthsFile;

	if (!file.getString(&widthsFile)){
		ReportError("failed to read file");
		return false;
	}

	if (!loadWidthsFile(widthsFile)){
		ReportError("failed to load widthsFile");
		return false;
	}

	m_cellWidth = static_cast<float>(m_texture.getWidth() / static_cast<unsigned int> (m_rowSize));
	m_cellHeight = static_cast<float>(m_texture.getHeight() / static_cast<unsigned int>(m_columnSize));
	//size in pixels, now converting it to UVs size
	m_cellWidth /= static_cast<float>(m_texture.getWidth());
	m_cellHeight /= static_cast<float>(m_texture.getHeight());

	return true;
}

void BitmapFont::draw(const Vec2f& pos, const std::string& text, float fontSize, const Vec3& RGBcolor){
	//pos goes from 0 to 2
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glEnable(GL_COLOR_MATERIAL);

	Vec2f position = pos;
	position.x -= 1.0f;
	position.y += 1.0f;//opengl works from x(-1,-1,-1) to y(1,1,1)

	Vec2f charCellPos;//position of the character on the whole spreadsheet
	fontSize /= 100.0f;//we need to reduce the font size for it to be close to other programs

	m_texture.bind();

	glColor3f(RGBcolor.x, RGBcolor.y, RGBcolor.z);
	glBegin(GL_QUADS);
	{
		for (unsigned int i = 0; i < text.size(); i++){
			char c = text[i];

			charCellPos.x = c % m_rowSize * m_cellWidth;
			charCellPos.y = c / m_columnSize * m_cellHeight;

			//top left corner
			glTexCoord2fv(charCellPos.toArray());
			glVertex2f(position.x, position.y);
			//bottom left
			glTexCoord2f(charCellPos.x, charCellPos.y + m_cellHeight);
			glVertex2f(position.x, position.y - fontSize);
			//bottom right
			glTexCoord2f(charCellPos.x + m_cellWidth, charCellPos.y + m_cellHeight);
			glVertex2f(position.x + fontSize, position.y - fontSize);
			//top right
			glTexCoord2f(charCellPos.x + m_cellWidth, charCellPos.y);
			glVertex2f(position.x + fontSize, position.y);
			
			position.x += fontSize;
		}
	}
	glEnd();

	glColor3f(1, 1, 1);
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDisable(GL_COLOR_MATERIAL);
}

bool BitmapFont::loadWidthsFile(const std::string& fileName){
	std::ifstream file(fileName);
	if (!file.is_open()){
		ReportError("failed to load widthsFile");
		return false;
	}

	unsigned int counter = 0;
	while (!file.eof()){
		file >> m_characterWidths[counter];
		counter++;
	}
	return true;
}