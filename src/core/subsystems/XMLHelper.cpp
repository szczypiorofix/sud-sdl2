#include "XMLHelper.h"



int XMLHelper::xmlCharToInt( const xmlChar* a ) {
	int c = 0;
	int sign = 0;
	int offset = 0;
	int n = 0;
	if ( a[ 0 ] == '-' ) {
		sign = -1;
	}
	if ( sign == -1 ) {
		offset = 1;
	} else {
		offset = 0;
	}
	for ( c = offset; a[ c ] != '\0'; c++ ) {
		n = n * 10 + a[ c ] - '0';
	}
	if ( sign == -1 ) {
		n = -n;
	}
	return n;
}

int XMLHelper::readPropInt( xmlNodePtr node, std::string prop ) {
	int i = 0;
	xmlChar* c = xmlGetProp( node, ( const xmlChar* ) prop.c_str() );
	
	if ( c == nullptr ) {
		xmlFree( c );
		return 0;
	}
	

	i = std::stoi( std::string( ( const char* ) c ) );
	if ( i == -1 ) {
		i = 0;
	}

	//if ( prop == "ucode" ) {
	//	printf( "%s=%d\n", prop.c_str(), i );
	//}
	

	//printf("FOUND char: %c, %d\n", c, c);

	//if ( c != NULL ) {
	//	//i = xmlCharToInt( c );
	//	printf("Converting string %s to int %s\n", prop.c_str(), c);
	//	i = std::stoi( std::string( (const char*)c ));
	//	// 
	//	
	//	//std::cout << "Prop: " << prop << std::endl;

	//	//std::string str = "7";
	//	//std::cout << "I am a string " << str << std::endl;
	//	//int num = stoi( str );
	//	//std::cout << "I am an int " << num << std::endl;
	//	xmlFree( c );
	//}
	return i;
}
