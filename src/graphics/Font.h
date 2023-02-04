#pragma once
#include <vector>
#include <map>
#include "Texture.h"
#include "../core/Defines.h"


typedef struct FontChar {
	int id = 0;
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	int xoffset = 0;
	int yoffset = 0;
	int xadvance = 0;
	int page = 0;
	int chnl = 0;
} FontChar;


class Font {

public:

	Font( const std::string fn, Texture* tex );
	Font( const Font& fnt );
	~Font( void );

	void Draw( const std::wstring text, int x, int y, float size );

private:

	Texture* fontImage;
	int imageWidth;
	int imageHeight;

	std::vector<FontChar*> fontChars;

	// Info
	std::string fontName;
	Uint16 size;
	bool bold;
	bool italic;
	std::string charset;
	bool unicode;
	Uint16 stretchH;
	bool smooth;
	bool aa;
	Uint16 paddingTop;
	Uint16 paddingRight;
	Uint16 paddingBottom;
	Uint16 paddingLeft;
	Uint16 spacingLeft;
	Uint16 spacingRight;
	Uint16 outline;

	// Common
	Uint32 lineHeight;
	Uint32 base;
	Uint32 scaleW;
	Uint32 scaleH;
	Uint16 pages;
	bool packed;
	float alphaChnl;
	float redChnl;
	float greenChnl;
	float blueChnl;

	std::map<int, std::string> pagesList;

	Uint32 charCount;



	void ParseXML( const std::string xmlFileName );

};
