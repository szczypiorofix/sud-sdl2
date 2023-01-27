#pragma once

#include <libxml/parser.h>
#include <libxml/tree.h>



class XMLHelper {

public:
	static int readPropInt( xmlNodePtr node, const xmlChar* prop );
	static short readPropShort( xmlNodePtr node, const xmlChar* prop );
private:
	static int xmlCharToInt( const xmlChar* a );
	static short xmlCharToShort( const xmlChar* a );
};

