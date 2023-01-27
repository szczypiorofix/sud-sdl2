#pragma once

#include "GameObject.h"


class UI : public GameObject {


public:

	UI();

	UI( Properties* props ) : GameObject( props ) {
		this->props = props;
		borderWidth = 0;
		isHovered = false;
		isClicked = false;
	}

	SDL_Color foregroundColor{ 255,255,255,255 };
	SDL_Color backgroundColor{ 0,0,0,255 };
	int borderWidth;
	SDL_Color borderColor { 255, 255, 255, 255 };

	void Draw();
	void Update( double dt );
	void Input( SDL_Event* event );
	void Clean();

	bool isHovered;
	bool isClicked;

private:

};

