#include "UI.h"
#include "../graphics/TextureManager.h"


UI::UI() {
	printf("Default UI constructor ...\n");
	borderWidth = 0;
	isHovered = false;
	isClicked = false;
}

void UI::Draw() {
	if ( isHovered ) {
		if ( isClicked ) {
			TextureManager::GetInstance()->DrawSprite( props->TextureID, props->X, props->Y, props->Width, props->Height, 0, 64, props->Width, props->Height, SDL_FLIP_NONE );
		} else {
			TextureManager::GetInstance()->DrawSprite( props->TextureID, props->X, props->Y, props->Width, props->Height, 0, 32, props->Width, props->Height, SDL_FLIP_NONE );
		}
	} else {
		TextureManager::GetInstance()->DrawSprite( props->TextureID, props->X, props->Y, props->Width, props->Height, 0, 0, props->Width, props->Height, SDL_FLIP_NONE );
	}
	
}

void UI::Update( double dt ) {

}

void UI::Input( SDL_Event* event ) {
	int mx = 0;
	int my = 0;
	if ( (*event).type == SDL_MOUSEMOTION ) {
		isHovered = false;
		SDL_GetMouseState( &mx, &my );
		if ( 
			mx > props->X 
			&& mx < props->X + props->Width 
			&& my > props->Y 
			&& my < props->Y + props->Height
		) {
			isHovered = true;
		}
	} else {
		if ( ( *event ).type == SDL_MOUSEBUTTONDOWN && ( *event ).button.button == SDL_BUTTON_LEFT ) {
			isClicked = true;
		} else {
			if ( ( *event ).type == SDL_MOUSEBUTTONUP && ( *event ).button.button == SDL_BUTTON_LEFT ) {
				isClicked = false;
			}
		}
	}
	//if ( isHovered ) {
	//	printf( "%d:%d\n", mx, my );
	//}
}

void UI::Clean() {

}
