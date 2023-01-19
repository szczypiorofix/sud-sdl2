#pragma once
#include <vector>
#include "Texture.h"
#include "Defines.h"


typedef struct FontItem {
	short ascii;
	short ucode;
	short top;
	short bottom;
	short x;
	short y;
	short width;
	short height;
	short leading;
	short trailing;
} FontItem;


class Font {

public:
	Font( std::string fn, Texture* tex );
	~Font( void );
	void draw( const char* text, int x, int y, float size );

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
	void parseXML( std::string xmlFileName );
	int getWithOfFontString( const char* text );

};

