#include "UI.h"
#include "../graphics/TextureManager.h"



void UI::Input( SDL_Event* event ) {
	int mx = 0;
	int my = 0;

	if ( ( *event ).type == SDL_MOUSEMOTION ) {
		SDL_GetMouseState( &mx, &my );
		if (
			mx > props->X
			&& mx < props->X + props->Width
			&& my > props->Y
			&& my < props->Y + props->Height
			) {
			isHovered = true;
		} else {
			isHovered = false;
			isMouseDown = false;
		}
	}

	switch ( ( *event ).type ) {
		case SDL_MOUSEBUTTONDOWN:
			if ( ( *event ).button.button == SDL_BUTTON_LEFT ) {
				isMouseUp = false;
				if ( isHovered ) {
					isMouseDown = true;
				}
			}
			break;

		case SDL_MOUSEBUTTONUP:
			if ( ( *event ).button.button == SDL_BUTTON_LEFT ) {
				
				isMouseDown = false;
				
				if ( isHovered ) {
					isClicked = true;
					isMouseUp = true;
				}
			}
			break;

		default:
			// nothing
			break;
	}

	if ( (*event ).type == SDL_KEYDOWN ) {
		switch ( (*event ).key.keysym.sym ) {
			case SDLK_LEFT:
				this->props->X -= 4;
				break;
			case SDLK_RIGHT:
				this->props->X += 4;
				break;
			default:
				break;
		}
	}

}


void UI::Update( double dt ) {

	//if ( isMouseDown ) {
	//	printf( "UI:isMouseDown\n" );
	//}

	//if ( isMouseUp ) {
	//	printf( "UI:isMouseUp\n" );
	//}

	//if ( isClicked ) {
	//	printf( "UI:isClicked\n" );
	//	( this->event->OnClickCallback )( uiEvent );
	//}

	isMouseUp = false;
}


void UI::Draw() {
	if ( isHovered ) {
		if ( isMouseDown ) {
			TextureManager::GetInstance()->DrawSprite( props->TextureID, props->X, props->Y, props->Width, props->Height, 0, 64, props->Width, props->Height, SDL_FLIP_NONE );
		} else {
			TextureManager::GetInstance()->DrawSprite( props->TextureID, props->X, props->Y, props->Width, props->Height, 0, 32, props->Width, props->Height, SDL_FLIP_NONE );
		}
	} else {
		TextureManager::GetInstance()->DrawSprite( props->TextureID, props->X, props->Y, props->Width, props->Height, 0, 0, props->Width, props->Height, SDL_FLIP_NONE );
	}

	// resetting events
	/*isMouseUp = false;
	isClicked = false;*/
	//isHovered = false;

	//if ( isClicked ) {
	//	isClicked = false;
	//}

	//if ( isMouseUp && !isClicked) {
	//	isClicked = true;
	//}

	isClicked = false;
}


void UI::Clean() {

}

//void UI::AddOnClickCallback( UIEvents* event, void( UIEvents::* _OnClickCallback )( UIEvent uiEvent ) ) {
//	this->event = event;
//}



//void UI::AddOnClickCallback( void ( *clickCallback )( ) ) {
//	this->clickCallback = clickCallback;
//}
