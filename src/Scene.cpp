#include "Scene.h"



Scene::Scene( std::string name, SDL_Renderer * renderer) {
	this->renderer = renderer;
	this->name = name;
	this->spriteSheet = NULL;
}


Scene::~Scene() {

}


void Scene::addSpriteSheet( std::string spriteSheetName ) {
	this->spriteSheet = new Spritesheet( spriteSheetName, this->renderer );
}


void Scene::load() {
	this->spriteSheet->load();
}


void Scene::draw() {
	this->spriteSheet->draw();
}


void Scene::unload() {
	this->spriteSheet->unload();
}
