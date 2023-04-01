#pragma once

#include "../entities/GameObject.h"



class UI : public GameObject {


public:

	UI( Properties* props ) : GameObject( props ) {
		this->props = props;
		borderWidth = 0;
		isHovered = false;
		isClicked = false;
		isMouseDown = false;
		isMouseUp = false;
		moveVecX = 0;
		moveVecY = 0;
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
	bool isMouseDown;
	bool isMouseUp;


	int moveVecX;
	int moveVecY;

private:
	
	void _drawGenericButton();

};

