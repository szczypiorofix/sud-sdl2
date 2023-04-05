#include "UI.h"
#include "../graphics/TextureManager.h"
#include "../core/GameSystem.h"


void UI::Input( SDL_Event* event ) {
	int mx = 0;
	int my = 0;

	if ( ( *event ).type == SDL_MOUSEMOTION ) {
		SDL_GetMouseState( &mx, &my );
		if (
			mx > props->pos.X
			&& mx < props->pos.X + props->Width
			&& my > props->pos.Y
			&& my < props->pos.Y + props->Height
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

}


void UI::Update( double dt ) {
	isMouseUp = false;
}


void UI::Draw() {
	if ( isHovered ) {
		if ( isMouseDown ) {
			if (props->TextureID != "") {
				TextureManager::GetInstance()->DrawSprite(props->TextureID, (int)props->pos.X, (int)props->pos.Y, props->Width, props->Height, 0, 64, props->Width, props->Height, SDL_FLIP_NONE);
			}
			else {
				_drawGenericButton();
			}
			
		} else {
			if (props->TextureID != "") {
				TextureManager::GetInstance()->DrawSprite(props->TextureID, (int)props->pos.X, (int)props->pos.Y, props->Width, props->Height, 0, 32, props->Width, props->Height, SDL_FLIP_NONE);
			}
			else {
				_drawGenericButton();
			}
		}
	} else {
		if (props->TextureID != "") {
			TextureManager::GetInstance()->DrawSprite(props->TextureID, (int)props->pos.X, (int)props->pos.Y, props->Width, props->Height, 0, 0, props->Width, props->Height, SDL_FLIP_NONE);
		}
		else {
			_drawGenericButton();
		}
	}

	isClicked = false;
}

void UI::_drawGenericButton() {
	const SDL_Rect rect = {
		(int)props->pos.X,
		(int)props->pos.Y,
		(int)props->Width,
		(int)props->Height
	};

	SDL_Color oldColor;
	SDL_GetRenderDrawColor(SUD::GameSystem::GetInstance()->GetRenderer(), &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);
	SDL_SetRenderDrawColor(SUD::GameSystem::GetInstance()->GetRenderer(), props->BackgroundColor.r, props->BackgroundColor.g, props->BackgroundColor.b, props->BackgroundColor.a);

	SDL_RenderFillRect(SUD::GameSystem::GetInstance()->GetRenderer(), &rect);

	props->_font->Draw(L"Reload", (int)(props->pos.X + 5.0), (int)(props->pos.Y + 5.0), 1.0f, props->FontColor);

	SDL_SetRenderDrawColor(SUD::GameSystem::GetInstance()->GetRenderer(), oldColor.r, oldColor.g, oldColor.b, oldColor.a);

}


void UI::Clean() {
}

