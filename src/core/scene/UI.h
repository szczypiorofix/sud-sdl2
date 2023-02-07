#pragma once

#include "../../objects/GameObject.h"
#include "UIEvents.h"

using namespace Events;


class UI : public GameObject {


public:

	UI( Properties* props ) : GameObject( props ) {
		this->props = props;
		borderWidth = 0;
		isHovered = false;
		isClicked = false;
		isMouseDown = false;
		isMouseUp = false;

		//event = nullptr;
		//uiEvent = {
		//	0,
		//	""
		//};

		//clickCallback = ( *clickCallback ); // WTF ??!!
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

	//void AddOnClickCallback( UIEvents* event, void (UIEvents::* OnClickCallback )( UIEvent uiEvent ) );


private:
	
	//UIEvents* event;
	//UIEvent uiEvent;
};

