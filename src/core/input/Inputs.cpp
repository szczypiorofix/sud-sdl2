#include "Inputs.h"

#include "../Defines.h"


using namespace SUD;


Inputs::Inputs() {
	event = nullptr;
	cursor = nullptr;
}


Inputs::~Inputs() {
	event = nullptr;
	cursor = nullptr;
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
