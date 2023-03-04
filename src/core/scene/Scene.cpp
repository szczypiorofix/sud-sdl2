#include <iostream>
#include "Scene.h"



Scene::Scene( std::string name, SDL_Renderer * renderer) {
	this->renderer = renderer;
	this->name = name;
	spriteSheet = NULL;
	this->gameObjectsUI = {};
}


Scene::~Scene( void ) { }

void Scene::AddSpriteSheet(std::string spriteSheetName, int tileWidth, int tileHeight) {
	spriteSheet = new Spritesheet(spriteSheetName, renderer, tileWidth, tileHeight);
}

void Scene::AddUIObject( std::string id, UI* uiObject ) {
	gameObjectsUI[id] = uiObject;
}


void Scene::Load( void ) {
	//spriteSheet->Load();
	std::map<std::string, UI*>::iterator it;
	for ( it = gameObjectsUI.begin(); it != gameObjectsUI.end(); it++ ) {
		// doing nothing for now
	}
}


void Scene::Input( SDL_Event* event ) {
	std::map<std::string, UI*>::iterator it;
	for ( it = gameObjectsUI.begin(); it != gameObjectsUI.end(); it++ ) {
		it->second->Input( event );
	}
}


void Scene::Update( double dt ) {
	std::map<std::string, UI*>::iterator it;
	for ( it = gameObjectsUI.begin(); it != gameObjectsUI.end(); it++ ) {
		it->second->Update( dt );
	}
}


void Scene::Draw( void ) {
	std::map<std::string, UI*>::iterator it;
	for ( it = gameObjectsUI.begin(); it != gameObjectsUI.end(); it++ ) {
		it->second->Draw();
	}
}


void Scene::Unload( void ) {
	std::map<std::string, UI*>::iterator it;
	for ( it = gameObjectsUI.begin(); it != gameObjectsUI.end(); it++ ) {
		it->second->Clean();
	}
}
