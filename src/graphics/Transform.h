#pragma once

#include "Vector2D.h"



class Transform {


public:
	double X, Y;


public:
	Transform(double x = 0.0, double y = 0.0 ) : X( x ), Y( y ) { }

private:

	inline void TranslateX( double x ) { X += x; }
	inline void TranslateY( double y ) { Y += y; }
	inline void Translate( Vector2D v ) { X += v.X; Y += v.Y; }


};

