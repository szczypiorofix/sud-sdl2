#include "Inputs.h"
#include "../core/Defines.h"



using namespace SUD;



Inputs::Inputs() {
	event = nullptr;
	cursor = nullptr;
	
	keys[Key_Up] = {};
	keys[Key_Right] = {};
	keys[Key_Down] = {};
	keys[Key_Left] = {};
}


Inputs::~Inputs() {
	event = nullptr;
	cursor = nullptr;
}

void SUD::Inputs::ResolveInputs() {

	int numKey = 0;
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDLK_RETURN]) printf("Return Key currently being held.\n");

	if ((*event).type == SDL_KEYUP) {
		switch ((*event).key.keysym.sym) {
		case SDLK_UP:
			keys[Key_Up].keyDown = false;
			break;
		case SDLK_RIGHT:
			keys[Key_Right].keyDown = false;
			break;
		case SDLK_DOWN:
			keys[Key_Down].keyDown = false;
			break;
		case SDLK_LEFT:
			keys[Key_Left].keyDown = false;
			break;
		default:
			break;
		}
	}
	else
	if ((*event).type == SDL_KEYDOWN) {
		switch ((*event).key.keysym.sym) {
			case SDLK_UP:
				keys[Key_Up].keyDown = true;
				break;
			case SDLK_RIGHT:
				keys[Key_Right].keyDown = true;
				break;
			case SDLK_DOWN:
				keys[Key_Down].keyDown = true;
				break;
			case SDLK_LEFT:
				keys[Key_Left].keyDown = true;
				break;

			default:
				break;
		}
	}
	
}


void Inputs::Init( SDL_Window* window, int setMousePositionX, int setMousePositionY, const char* mouseIconImage) {
	event = new SDL_Event();

	SDL_Log("Initializing mouse cursor");

	SDL_ShowCursor(SDL_ENABLE);
	SDL_WarpMouseInWindow(window, setMousePositionX, setMousePositionY);

	SDL_Surface* cursorIcon = IMG_Load(std::string(DIR_RES_IMAGES + mouseIconImage).c_str());
	if (cursorIcon == nullptr) {
		printf("Cannot initialize mouse cursor surface!\n");
		exit(1);
	}
	cursor = SDL_CreateColorCursor(cursorIcon, 0, 0);
	if (cursor == nullptr) {
		printf("Cannot attach mouse icon to cursor!\n");
		exit(1);
	}
	SDL_SetCursor(cursor);
}
