#pragma once

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string>
#include <vector>
#include <SDL2/SDL_stdinc.h>


class XMLHelper {

public:
	static int readPropInt( xmlNodePtr node, std::string prop );

	static Uint16 readPropUInt16( xmlNodePtr node, std::string prop );

	static Uint32 readPropUInt32( xmlNodePtr node, std::string prop );

	static std::string readPropString( xmlNodePtr node, std::string prop );

	static bool readPropBool( xmlNodePtr node, std::string prop );

	static float readPropFloat( xmlNodePtr node, std::string prop );

	static std::vector<std::string> explode( const std::string& s, const char& c );

private:

};

