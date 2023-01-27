#pragma once

#include <iostream>


class Vector2D {

public:
	int X, Y;


public:

	Vector2D( int x = 0, int y = 0 ) :X( x ), Y( y ) { }


	inline Vector2D operator+( const Vector2D& v2 ) const {
		return Vector2D( X + v2.X, Y + v2.Y );
	}


	inline Vector2D operator-( const Vector2D& v2 ) const {
		return Vector2D( X - v2.X, Y - v2.Y );
	}


	inline Vector2D operator*( const int scalar ) const {
		return Vector2D( X * scalar, Y * scalar );
	}


	void Log( std::string msg = "" ) {
		std::cout << msg << " (X Y) * (" << X << " " << Y << ")" << std::endl;
	}



};

