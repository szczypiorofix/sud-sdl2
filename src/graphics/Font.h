#pragma once
#include <vector>
#include "Texture.h"
#include "../core/Defines.h"


typedef struct FontItem {
	int ascii = 0;
	int ucode = 0;
	int top = 0;
	int bottom = 0;
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	int leading = 0;
	int trailing = 0;
} FontItem;


class Font {

public:
	Font( std::string fn, Texture* tex );
	~Font( void );
	void Draw( std::wstring text, int x, int y, float size );

private:
	Texture* fontImage;
	int imageWidth;
	int imageHeight;
	std::vector<FontItem*> fontItems;
	int charsCount;
	std::string fontName;
	int fontWidth;
	int fontHeight;
	int fontSpace;
	void ParseXML( std::string xmlFileName );

	char* GetUnicodeChar( unsigned int code );
};
