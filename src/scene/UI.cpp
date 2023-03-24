#include "UI.h"
#include "../graphics/TextureManager.h"
#include "../core/GameSystem.h"


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
	isMouseUp = false;
}


void UI::Draw() {
	if ( isHovered ) {
		if ( isMouseDown ) {
			if (props->TextureID != "") {
				TextureManager::GetInstance()->DrawSprite(props->TextureID, props->X, props->Y, props->Width, props->Height, 0, 64, props->Width, props->Height, SDL_FLIP_NONE);
			}
			else {
				_drawGenericButton();
			}
			
		} else {
			if (props->TextureID != "") {
				TextureManager::GetInstance()->DrawSprite(props->TextureID, props->X, props->Y, props->Width, props->Height, 0, 32, props->Width, props->Height, SDL_FLIP_NONE);
			}
			else {
				_drawGenericButton();
			}
		}
	} else {
		if (props->TextureID != "") {
			TextureManager::GetInstance()->DrawSprite(props->TextureID, props->X, props->Y, props->Width, props->Height, 0, 0, props->Width, props->Height, SDL_FLIP_NONE);
		}
		else {
			_drawGenericButton();
		}
	}

	isClicked = false;
}

void UI::_drawGenericButton() {
	const SDL_Rect rect = {
		props->X,
		props->Y,
		props->Width,
		props->Height
	};

	SDL_Color oldColor;
	SDL_GetRenderDrawColor(SUD::GameSystem::GetInstance()->GetRenderer(), &oldColor.r, &oldColor.g, &oldColor.b, &oldColor.a);
	SDL_SetRenderDrawColor(SUD::GameSystem::GetInstance()->GetRenderer(), props->BackgroundColor.r, props->BackgroundColor.g, props->BackgroundColor.b, props->BackgroundColor.a);

	SDL_RenderFillRect(SUD::GameSystem::GetInstance()->GetRenderer(), &rect);

	props->_font->Draw(L"Reload", props->X + 5, props->Y + 5, 1.0f, props->FontColor);

	SDL_SetRenderDrawColor(SUD::GameSystem::GetInstance()->GetRenderer(), oldColor.r, oldColor.g, oldColor.b, oldColor.a);

}


void UI::Clean() {
}

