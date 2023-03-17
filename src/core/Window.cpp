#include "Window.h"



Window::Window() {
	window = nullptr;
	width = 0;
	height = 0;
}



Window::~Window() {

}


void Window::Init(int _width, int _height, const char* name) {
	this->width = _width;
	this->height = _height;

	SDL_Log("Initializing window");
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		SDL_LogError(SDL_LogCategory::SDL_LOG_CATEGORY_SYSTEM, "Window could not be created! SDL Error: %s\n", SDL_GetError());
		exit(1);
	}
}


void Window::Destroy() {
	SDL_DestroyWindow(window);
	window = nullptr;
}

SDL_Window* Window::GetWindow() {
	return window;
}
