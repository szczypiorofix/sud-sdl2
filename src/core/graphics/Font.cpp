#include "Font.h"
#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "../helpers/XMLHelper.h"
#include "../GameSystem.h"

Font::Font( const std::string fn, Texture* tex ) {
	fontName = fn;
	fontImage = tex;
	fontTexture = nullptr;
	imageWidth = 0;
	imageHeight = 0;

	fontChars = {};

	size = 0;
	bold = false;
	italic = false;
	charset = "";
	unicode = false;
	stretchH = 0;
	smooth = false;
	aa = false;
	paddingTop = 0;
	paddingRight = 0;
	paddingBottom = 0;
	paddingLeft = 0;
	spacingLeft = 0;
	spacingRight = 0;
	outline = 0;

	lineHeight = 0;
	base = 0;
	scaleW = 0;
	scaleH = 0;
	pages = 0;
	packed = false;
	alphaChnl = 0.0f;
	redChnl = 0.0f;
	greenChnl = 0.0f;
	blueChnl = 0.0f;

	pagesList = {};
	charCount = 0;

	ParseXML( fn );
}

Font::Font(const std::string fn, SDL_Texture* _fontTexture) {
	fontName = fn;
	fontImage = nullptr;
	fontTexture = _fontTexture;
	imageWidth = 0;
	imageHeight = 0;

	fontChars = {};

	size = 0;
	bold = false;
	italic = false;
	charset = "";
	unicode = false;
	stretchH = 0;
	smooth = false;
	aa = false;
	paddingTop = 0;
	paddingRight = 0;
	paddingBottom = 0;
	paddingLeft = 0;
	spacingLeft = 0;
	spacingRight = 0;
	outline = 0;

	lineHeight = 0;
	base = 0;
	scaleW = 0;
	scaleH = 0;
	pages = 0;
	packed = false;
	alphaChnl = 0.0f;
	redChnl = 0.0f;
	greenChnl = 0.0f;
	blueChnl = 0.0f;

	pagesList = {};
	charCount = 0;

	ParseXML(fn);
}

Font::Font( const Font& fnt ) {
	fontImage = fnt.fontImage;
	imageWidth = fnt.imageWidth;
	imageHeight = fnt.imageHeight;

	fontChars = fnt.fontChars;

	// Info
	fontName = fnt.fontName;
	size = fnt.size;
	bold = fnt.bold;
	italic = fnt.italic;
	charset = fnt.charset;
	unicode = fnt.unicode;
	stretchH = fnt.stretchH;
	smooth = fnt.smooth;
	aa = fnt.aa;
	paddingTop = fnt.paddingTop;
	paddingRight = fnt.paddingRight;
	paddingBottom = fnt.paddingBottom;
	paddingLeft = fnt.paddingLeft;
	spacingLeft = fnt.spacingLeft;
	spacingRight = fnt.spacingRight;
	outline = fnt.outline;

	// Common
	lineHeight = fnt.lineHeight;
	base = fnt.base;
	scaleW = fnt.scaleW;
	scaleH = fnt.scaleH;
	pages = fnt.pages;
	packed = fnt.packed;
	alphaChnl = fnt.alphaChnl;
	redChnl = fnt.redChnl;
	greenChnl = fnt.greenChnl;
	blueChnl = fnt.blueChnl;
	
	pagesList = fnt.pagesList;

	charCount = fnt.charCount;
}




Font::~Font( void ) {
	//printf("Deleting fontImage: '%s'\n", fontName.c_str());
	//delete fontImage;
}


void Font::ParseXML( const std::string xmlFileName ) {
	xmlDocPtr doc;
	xmlNodePtr fontNode;

	std::string xmlFile = DIR_RES_FONTS + xmlFileName + ".fnt";
	doc = xmlParseFile( xmlFile.c_str() );
	if ( !doc ) {
		std::cout << "Document cannot be parsed successfully." << std::endl;
		exit( 1 );
	}

	fontNode = xmlDocGetRootElement( doc );
	if ( !fontNode ) {
		std::cout << "Empty document." << std::endl;
		exit( 1 );
	}

	if ( xmlStrcmp( fontNode->name, ( const xmlChar* ) "font" ) ) {
		std::cout << "Document of the wrong type. Root node must be 'font'." << std::endl;
		xmlFreeDoc( doc );
		exit( 1 );
	}

	xmlNodePtr fontChildren = fontNode->xmlChildrenNode;
	

	while ( fontChildren != nullptr ) {

		if ( !xmlStrcmp( fontChildren->name, ( const xmlChar* ) "info" ) ) {
			fontName = XMLHelper::readPropString( fontChildren, "face" );
			size = XMLHelper::readPropUInt16( fontChildren, "size" );
			bold = XMLHelper::readPropBool( fontChildren, "bold" );
			italic = XMLHelper::readPropBool( fontChildren, "italic" );
			charset = XMLHelper::readPropString( fontChildren, "charset" );
			unicode = XMLHelper::readPropBool( fontChildren, "unicode" );
			stretchH = XMLHelper::readPropUInt16( fontChildren, "stretchH" );
			smooth = XMLHelper::readPropBool( fontChildren, "smooth" );
			aa = XMLHelper::readPropBool( fontChildren, "aa" );
			// padding
			std::string padding = XMLHelper::readPropString( fontChildren, "padding" );
			std::vector<std::string> paddingVector = XMLHelper::explode( padding, ',' );
			if ( paddingVector.size() != 4 ) {
				printf("Error! Padding vector size is not equal 4 !!\n");
				exit( 1 );
			}
			for ( unsigned int i = 0; i < paddingVector.size(); i++ ) {
				switch ( i ) {
					case 1:
						paddingLeft = (Uint16) std::stoi( paddingVector.at( i ) );
						break;
					case 2:
						paddingBottom = ( Uint16 ) std::stoi( paddingVector.at( i ) );
						break;
					case 3:
						paddingRight = ( Uint16 ) std::stoi( paddingVector.at( i ) );
						break;
					default:
						paddingTop = ( Uint16 ) std::stoi( paddingVector.at( i ) );
				}
			}
			// spacing
			std::string spacing = XMLHelper::readPropString( fontChildren, "spacing" );
			std::vector<std::string> spacingVector = XMLHelper::explode( spacing, ',' );
			if ( spacingVector.size() != 2 ) {
				printf( "Error! Spacing vector is not equal 2 !!\n" );
				exit( 1 );
			}
			spacingLeft = ( Uint16 ) std::stoi( spacingVector.at( 0 ) );
			spacingRight = ( Uint16 ) std::stoi( spacingVector.at( 1 ) );
			outline = XMLHelper::readPropUInt16( fontChildren, "outline" );
		}

		if ( !xmlStrcmp( fontChildren->name, ( const xmlChar* ) "common" ) ) {
			lineHeight = XMLHelper::readPropUInt32( fontChildren, "lineHeight" );
			base = XMLHelper::readPropUInt32( fontChildren, "base" );
			scaleW = XMLHelper::readPropUInt32( fontChildren, "scaleW" );
			scaleH = XMLHelper::readPropUInt32( fontChildren, "scaleH" );
			pages = XMLHelper::readPropUInt16( fontChildren, "pages" );
			packed = XMLHelper::readPropBool( fontChildren, "packed" );
			alphaChnl = XMLHelper::readPropFloat( fontChildren, "alphaChnl" );
			redChnl = XMLHelper::readPropFloat( fontChildren, "redChnl" );
			greenChnl = XMLHelper::readPropFloat( fontChildren, "greenChnl" );
			blueChnl = XMLHelper::readPropFloat( fontChildren, "blueChnl" );
		}

		if ( !xmlStrcmp( fontChildren->name, ( const xmlChar* ) "pages" ) ) {
			xmlNodePtr pagesChildren = fontChildren->xmlChildrenNode;
			while ( pagesChildren != nullptr ) {
				if ( !xmlStrcmp( pagesChildren->name, ( const xmlChar* ) "page" ) ) {
					pagesList.emplace( XMLHelper::readPropInt( pagesChildren, "id" ), XMLHelper::readPropString( pagesChildren, "file" ) );
				}
				pagesChildren = pagesChildren->next;
			}

			//std::map<int, std::string>::iterator it;
			//for ( it = pagesList.begin(); it != pagesList.end(); it++ ) {
			//	std::cout << it->first << ':' << it->second << std::endl;
			//}
		}

		if ( !xmlStrcmp( fontChildren->name, ( const xmlChar* ) "chars" ) ) {

			charCount = XMLHelper::readPropUInt32( fontChildren, "count" );

			xmlNodePtr charsChildren = fontChildren->xmlChildrenNode;
			while ( charsChildren != nullptr ) {
				//if ( !xmlStrcmp( charsChildren->name, ( const xmlChar* ) "char" ) ) {
				//	printf( "Char id = %i\n", XMLHelper::readPropInt( charsChildren, "id" ) );
				//}
				FontChar* tempChar = new FontChar();
				
				tempChar->id = XMLHelper::readPropInt( charsChildren, "id" );
				tempChar->x = XMLHelper::readPropInt( charsChildren, "x" );
				tempChar->y = XMLHelper::readPropInt( charsChildren, "y" );
				tempChar->width = XMLHelper::readPropInt( charsChildren, "width" );
				tempChar->height = XMLHelper::readPropInt( charsChildren, "height" );
				tempChar->xoffset = XMLHelper::readPropInt( charsChildren, "xoffset" );
				tempChar->yoffset = XMLHelper::readPropInt( charsChildren, "yoffset" );
				tempChar->xadvance = XMLHelper::readPropInt( charsChildren, "xadvance" );
				tempChar->page = XMLHelper::readPropInt( charsChildren, "page" );
				tempChar->chnl = XMLHelper::readPropInt( charsChildren, "chnl" );

				fontChars.push_back( tempChar );
				charsChildren = charsChildren->next;
			}
		}

		fontChildren = fontChildren->next;
	}

	xmlFreeDoc( doc );
	xmlCleanupMemory();
	xmlCleanupParser();
}


void Font::Draw( const std::wstring text, int x, int y, float _size, SDL_Color color ) {
	int textWidth = 0;
	for ( size_t i = 0; i < text.length(); i++ ) {
		for ( size_t j = 0; j < fontChars.size(); j++ ) {
			if ( text.at( i ) == fontChars.at( j )->id ) {
				SDL_Rect src = {
					fontChars.at(j)->x,
					fontChars.at(j)->y,
					fontChars.at(j)->width,
					fontChars.at(j)->height
				};
				SDL_Rect dest = {
					x + textWidth,
					y + fontChars.at( j )->yoffset,
					fontChars.at( j )->width,
					fontChars.at( j )->height
				};

				if ( fontImage != nullptr ) {
					fontImage->draw(src, dest, color);
				}
				if ( fontTexture != nullptr ) {
					SDL_SetTextureColorMod( fontTexture, color.r, color.g, color.b);
					SDL_RenderCopyEx(SUD::GameSystem::GetInstance()->GetRenderer(), fontTexture, &src, &dest, 0, nullptr, SDL_FLIP_NONE);
				}
				
				textWidth += fontChars.at( j )->width;
			}
		}
		if ( i == text.length() ) {
			textWidth = 0;
		}
	}
}
