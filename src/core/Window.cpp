#include "Window.h"
#include <stdio.h>


Window::Window( bool _fullScreen ) {
	window = nullptr;
	width = 0;
	height = 0;
	windowFocusGain = false;
	windowFocusLost = false;
	fullScreen = _fullScreen;
}



Window::~Window() {

}


void Window::Init(int _width, int _height, const char* name) {
	this->width = _width;
	this->height = _height;

	SDL_Log("Initializing window");
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, this->fullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
	if (window == NULL) {
		SDL_LogError(SDL_LogCategory::SDL_LOG_CATEGORY_SYSTEM, "Window could not be created! SDL Error: %s\n", SDL_GetError());
		exit(1);
	}
}

void Window::Input( SDL_Event* _event ) {
	if ((*_event).type == SDL_WINDOWEVENT) {
		switch ((*_event).window.event) {
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				//printf("Focus gain\n");
				windowFocusGain = true; // move it to window->update()
				break;

			case SDL_WINDOWEVENT_FOCUS_LOST:
				//printf("Focus lost\n");
				windowFocusLost = true;
				break;

			default:
				break;
		}
	}
}

void Window::Update(double _dt) {
	windowFocusGain = false;
	windowFocusLost = false;
}


void Window::Destroy() {
	SDL_DestroyWindow(window);
	window = nullptr;
}


SDL_Window* Window::GetWindow() {
	return window;
}
