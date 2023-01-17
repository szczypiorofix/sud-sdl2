#include "Scene.h"



Scene::Scene( std::string name, SDL_Renderer * renderer) {
	this->renderer = renderer;
	this->name = name;
	this->spriteSheet = NULL;
}


Scene::~Scene( void ) {

}

void Scene::addSpriteSheet(std::string spriteSheetName, int tileWidth, int tileHeight) {
	this->spriteSheet = new Spritesheet(spriteSheetName, this->renderer, tileWidth, tileHeight);
}


void Scene::load( void ) {
	this->spriteSheet->load();
}


void Scene::draw( void ) {
	this->spriteSheet->draw();
}


void Scene::unload( void ) {
	this->spriteSheet->unload();
}
