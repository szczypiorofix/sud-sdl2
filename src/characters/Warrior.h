#pragma once

#include "Character.h"


class Warrior : public Character {


public:

	Warrior( Properties* props ) : Character( props ) {
		row = 0;
		frame = 0;
		frameCount = 0;
	}


	virtual void Draw();
	virtual void Clean();
	virtual void Update( float dt );


protected:


private:

	int row, frame, frameCount;


};

