#include "Font.h"
#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "../core/subsystems/XMLHelper.h"


Font::Font( std::string fn, Texture* tex ) {
	this->charsCount = 0;
	this->fontWidth = 0;
	this->fontHeight = 0;
	this->fontSpace = 0;
	this->fontName = fn;
	this->fontImage = tex;
	this->fontItems = {};
	this->ParseXML( fn );
}


Font::~Font( void ) { }


void Font::ParseXML( std::string xmlFileName ) {

	xmlDocPtr doc;
	xmlNodePtr cur;

	std::string xmlFile = DIR_RES_FONTS + xmlFileName + ".xml";
	doc = xmlParseFile( xmlFile.c_str() );
	if ( !doc ) {
		std::cout << "Document cannot be parsed successfully." << std::endl;
		exit( 1 );
	}

	cur = xmlDocGetRootElement( doc );
	if ( !cur ) {
		std::cout << "Empty document." << std::endl;
		exit( 1 );
	}

	//printf("Reading %s file.", xmlFile.c_str() );

	if ( xmlStrcmp( cur->name, ( const xmlChar* ) "font" ) ) {
		std::cout << "Document of the wrong type. Root node must be 'font'." << std::endl;
		xmlFreeDoc( doc );
		exit( 1 );
	}

	this->fontWidth = XMLHelper::readPropShort( cur, ( const xmlChar* ) "width" );
	this->fontHeight = XMLHelper::readPropShort( cur, ( const xmlChar* ) "height" );
	this->fontSpace = XMLHelper::readPropShort( cur, ( const xmlChar* ) "space" );

	cur = cur->xmlChildrenNode;

	xmlNodePtr mainItems = cur;

	while ( mainItems != nullptr ) {
		if ( !xmlStrcmp( mainItems->name, ( const xmlChar* ) "item" ) ) {
			this->charsCount++;
		}
		mainItems = mainItems->next;
	}

	this->fontItems.clear();
	this->fontItems.reserve( this->charsCount );

	mainItems = cur;
	while ( mainItems != nullptr ) {
		if ( !xmlStrcmp( mainItems->name, ( const xmlChar* ) "item" ) ) {
			FontItem* tempItem = new FontItem();
			tempItem->ascii = XMLHelper::readPropShort( mainItems, ( const xmlChar* ) "ascii" );
			tempItem->ucode = XMLHelper::readPropShort( mainItems, ( const xmlChar* ) "ucode" );
			tempItem->top = XMLHelper::readPropShort( mainItems, ( const xmlChar* ) "top" );
			tempItem->bottom = XMLHelper::readPropShort( mainItems, ( const xmlChar* ) "bottom" );
			tempItem->x = XMLHelper::readPropShort( mainItems, ( const xmlChar* ) "x" );
			tempItem->y = XMLHelper::readPropShort( mainItems, ( const xmlChar* ) "y" );
			tempItem->width = XMLHelper::readPropShort( mainItems, ( const xmlChar* ) "width" );
			tempItem->height = XMLHelper::readPropShort( mainItems, ( const xmlChar* ) "height" );
			tempItem->leading = XMLHelper::readPropShort( mainItems, ( const xmlChar* ) "leading" );
			tempItem->trailing = XMLHelper::readPropShort( mainItems, ( const xmlChar* ) "trailing" );

			this->fontItems.push_back( tempItem );
		}
		mainItems = mainItems->next;
	}

	xmlFreeDoc( doc );
	xmlCleanupMemory();
	xmlCleanupParser();
}


int Font::GetWithOfFontString( const char* text ) {
	int c = 0;
	for ( int i = 0; text[ i ] != 0; i++ ) {
		for ( int j = 0; j < this->charsCount; j++ ) {
			if ( text[ i ] == this->fontItems.at( j )->ascii ) {
				c += this->fontItems.at( j )->width;
			}
		}
	}
	return c;
}


void Font::Draw( const char* text, int x, int y, float size ) {
	int c = 0;
	while ( text[ c ] != 0 ) {
		for ( int i = 0; i < this->charsCount; i++ ) {
			if ( text[ c ] == this->fontItems.at( i )->ascii ) {

				SDL_Rect dest = {
					x + fontItems.at( i )->trailing + fontItems.at( i )->leading + ( int ) ( c * fontWidth * size ),
					( int ) y,  // +fontItems[i]->top;
					( int ) ( fontWidth * size ),
					( int ) ( fontHeight * size )
				};

				SDL_Rect src = {
					( int ) fontItems.at( i )->x,
					( int ) fontItems.at( i )->y,
					( int ) fontItems.at( i )->width,
					( int ) fontItems.at( i )->height
				};

				this->fontImage->draw(src, dest);

			}
		}
		c++;
	}
}

