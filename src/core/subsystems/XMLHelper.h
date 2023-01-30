#pragma once

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string>


class XMLHelper {

public:
	static int readPropInt( xmlNodePtr node, std::string prop );
private:
	static int xmlCharToInt( const xmlChar* a );

};

