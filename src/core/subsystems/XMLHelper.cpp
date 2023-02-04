#include "XMLHelper.h"
#include <iostream>


int XMLHelper::readPropInt( xmlNodePtr node, std::string prop ) {
	xmlChar* c = xmlGetProp( node, ( const xmlChar* ) prop.c_str() );
	if ( c == nullptr ) {
		xmlFree( c );
		return 0;
	}
	int i = std::stoi( std::string( ( const char* ) c ) );
	return i == -1 ? 0 : i;
}


Uint16 XMLHelper::readPropUInt16( xmlNodePtr node, std::string prop ) {
	xmlChar* c = xmlGetProp( node, ( const xmlChar* ) prop.c_str() );
	if ( c == nullptr ) {
		xmlFree( c );
		return 0;
	}
	Uint16 i = ( Uint16 )std::stoi( std::string( ( const char* ) c ) );
	return i == -1 ? 0 : i;
}

Uint32 XMLHelper::readPropUInt32( xmlNodePtr node, std::string prop ) {
	xmlChar* c = xmlGetProp( node, ( const xmlChar* ) prop.c_str() );
	if ( c == nullptr ) {
		xmlFree( c );
		return 0;
	}
	Uint32 i = ( Uint32 )std::stoi( std::string( ( const char* ) c ) );
	return i == -1 ? 0 : i;
}


std::string XMLHelper::readPropString( xmlNodePtr node, std::string prop ) {
	xmlChar* c = xmlGetProp( node, ( const xmlChar* ) prop.c_str() );
	if ( c == nullptr ) {
		return "";
	}
	return std::string( (char*) c );
}


bool XMLHelper::readPropBool( xmlNodePtr node, std::string prop ) {
	xmlChar* c = xmlGetProp( node, ( const xmlChar* ) prop.c_str() );
	if ( c == nullptr ) {
		return false;
	}
	int i = std::stoi( std::string( ( const char* ) c ) );
	return i != 0;
}

float XMLHelper::readPropFloat( xmlNodePtr node, std::string prop ) {
	xmlChar* c = xmlGetProp( node, ( const xmlChar* ) prop.c_str() );
	if ( c == nullptr ) {
		return 0.0f;
	}
	return std::stof( std::string( ( const char* ) c ) );
}

std::vector<std::string> XMLHelper::explode( const std::string& str, const char& delimiter ) {
	std::string buff{ "" };
	std::vector<std::string> v;

	for ( const char n : str ) {
		if ( n != delimiter ) {
			buff += n;
		} else {
			if ( n == delimiter && buff != "" ) {
				v.push_back( buff );
				buff = "";
			}
		}
	}

	if ( buff != "" ) {
		v.push_back( buff );
	}
	return v;
}
