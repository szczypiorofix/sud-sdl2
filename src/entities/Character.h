#pragma once

#include "GameObject.h"




class Character : public GameObject {


public:
	Character( Properties* props ) : GameObject( props ) { }

	virtual void Draw();
	virtual void Clean();
	virtual void Update( double dt );
	virtual void Input(SDL_Event* event);

protected:
	std::string Name;



public:


private:




};

