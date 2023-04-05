#pragma once


class Vector2D {

public:
	double X, Y;


public:

	Vector2D(double x = 0, double y = 0 ) :X( x ), Y( y ) { }


	inline Vector2D operator+( const Vector2D& v2 ) const {
		return Vector2D( X + v2.X, Y + v2.Y );
	}


	inline Vector2D operator-( const Vector2D& v2 ) const {
		return Vector2D( X - v2.X, Y - v2.Y );
	}


	inline Vector2D operator*( const double scalar ) const {
		return Vector2D( X * scalar, Y * scalar );
	}

};

