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

	void Draw( const std::wstring text, int x, int y, float size, SDL_Color color = { 255, 255, 255, 255 });

private:

	Texture* fontImage;
	int imageWidth;
	int imageHeight;

	std::vector<FontChar*> fontChars;

	// This is the name of the true type font.
	std::string fontName;

	// The size of the true type font.
	Uint16 size;

	// The font is bold.
	bool bold;

	// The font is italic.
	bool italic;

	// The name of the OEM charset used (when not unicode).
	std::string charset;

	// Set to 1 if it is the unicode charset.
	bool unicode;

	// The font height stretch in percentage. 100% means no stretch.
	Uint16 stretchH;

	// Set to 1 if smoothing was turned on.
	bool smooth;

	// The supersampling level used. 1 means no supersampling was used.
	bool aa;

	// The padding for each character (up, right, down, left).
	Uint16 paddingTop;
	Uint16 paddingRight;
	Uint16 paddingBottom;
	Uint16 paddingLeft;

	// The spacing for each character (horizontal, vertical).
	Uint16 spacingLeft;
	Uint16 spacingRight;

	// The outline thickness for the characters.
	Uint16 outline;


	// This is the distance in pixels between each line of text.
	Uint32 lineHeight;

	// The number of pixels from the absolute top of the line to the base of the characters.
	Uint32 base;

	// The width of the texture, normally used to scale the x pos of the character image.
	Uint32 scaleW;

	// The height of the texture, normally used to scale the y pos of the character image.
	Uint32 scaleH;

	// 	The number of texture pages included in the font.
	Uint16 pages;
	
	// Set to 1 if the monochrome characters have been packed into each of the texture channels. In this case alphaChnl describes what is stored in each channel.
	bool packed;

	// Set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it holds the glyph and the outline, 3 if its set to zero, and 4 if its set to one.
	float alphaChnl;

	// Set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it holds the glyph and the outline, 3 if its set to zero, and 4 if its set to one.
	float redChnl;

	// 	Set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it holds the glyph and the outline, 3 if its set to zero, and 4 if its set to one.
	float greenChnl;

	// Set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it holds the glyph and the outline, 3 if its set to zero, and 4 if its set to one.
	float blueChnl;


	// Map with font images: page id (int) - texture file name (string).
	std::map<int, std::string> pagesList;

	// Character count
	Uint32 charCount;


	// Parse XML file
	void ParseXML( const std::string xmlFileName );

};
