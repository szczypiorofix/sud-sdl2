#include "Font.h"
#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "../core/subsystems/XMLHelper.h"


Font::Font( std::string fn, Texture* tex ) {
	charsCount = 0;
	fontWidth = 0;
	fontHeight = 0;
	fontSpace = 0;
	fontName = fn;
	fontImage = tex;
	fontItems = {};
	ParseXML( fn );
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

	if ( xmlStrcmp( cur->name, ( const xmlChar* ) "font" ) ) {
		std::cout << "Document of the wrong type. Root node must be 'font'." << std::endl;
		xmlFreeDoc( doc );
		exit( 1 );
	}

	fontWidth = XMLHelper::readPropInt( cur,  "width" );
	fontHeight = XMLHelper::readPropInt( cur,  "height" );
	fontSpace = XMLHelper::readPropInt( cur,  "space" );

	cur = cur->xmlChildrenNode;

	xmlNodePtr mainItems = cur;

	while ( mainItems != nullptr ) {
		if ( !xmlStrcmp( mainItems->name, ( const xmlChar* ) "item" ) ) {
			charsCount++;
		}
		mainItems = mainItems->next;
	}

	fontItems.clear();
	fontItems.reserve( charsCount );

	mainItems = cur;
	while ( mainItems != nullptr ) {
		if ( !xmlStrcmp( mainItems->name, ( const xmlChar* ) "item" ) ) {
			FontItem* tempItem = new FontItem();
			tempItem->ascii = XMLHelper::readPropInt( mainItems,  "ascii" );
			tempItem->ucode = XMLHelper::readPropInt( mainItems, "ucode" );
			tempItem->top = XMLHelper::readPropInt( mainItems, "top" );
			tempItem->bottom = XMLHelper::readPropInt( mainItems, "bottom" );
			tempItem->x = XMLHelper::readPropInt( mainItems, "x" );
			tempItem->y = XMLHelper::readPropInt( mainItems, "y" );
			tempItem->width = XMLHelper::readPropInt( mainItems,  "width" );
			tempItem->height = XMLHelper::readPropInt( mainItems,  "height" );
			tempItem->leading = XMLHelper::readPropInt( mainItems, "leading" );
			tempItem->trailing = XMLHelper::readPropInt( mainItems,  "trailing" );
			//std::cout << "Font prop: ASCII=" << tempItem->ascii << ", UCODE=" << tempItem->ucode << ", char: " << (wchar_t)( tempItem->ucode > 0 ? tempItem->ucode : tempItem->ascii ) << std::endl;
			fontItems.push_back( tempItem );
		}
		mainItems = mainItems->next;
	}

	xmlFreeDoc( doc );
	xmlCleanupMemory();
	xmlCleanupParser();
}


void Font::Draw( std::wstring text, int x, int y, float size ) {
	for ( size_t i = 0; i < text.length(); i++ ) {
		for ( size_t j = 0; j < fontItems.size(); j++ ) {
			if ( text.at( i ) == fontItems.at( j )->ascii || text.at( i ) == fontItems.at( j )->ucode ) {
				SDL_Rect dest = {
					x + fontItems.at( j )->trailing + fontItems.at( j )->leading + ( int ) ( i * fontWidth * size ),
					( int ) (y + fontItems.at( j )->top ),
					( int ) ( fontWidth * size ),
					( int ) ( ( fontItems.at( j )->height + fontItems.at( j )->bottom ) * size )
				};
				SDL_Rect src = {
					( int ) fontItems.at( j )->x,
					( int ) fontItems.at( j )->y,
					( int ) fontItems.at( j )->width,
					( int ) fontItems.at( j )->height
				};
				this->fontImage->draw(src, dest);
			}
		}
	}
}
