#include <iostream>
#include "Scene.h"
#include "../graphics/TextureManager.h"
#include "../graphics/Sprites.h"



Scene::Scene( std::string _name, SDL_Renderer * _renderer) {
	this->renderer = _renderer;
	this->name = _name;
	this->gameObjectsUI = {};
	level = nullptr;
}


Scene::~Scene( void ) { }


void Scene::AddUIObject( std::string _id, UI* _uiObject ) {
	gameObjectsUI[_id] = _uiObject;
}


void Scene::SetLevel(Level* _level) {
	this->level = _level;
}


void Scene::Load( void ) {
	std::map<std::string, UI*>::iterator it;
	for ( it = gameObjectsUI.begin(); it != gameObjectsUI.end(); it++ ) {
		// doing nothing for now
	}
}


void Scene::Input( SDL_Event* _event ) {
	std::map<std::string, UI*>::iterator it;
	for ( it = gameObjectsUI.begin(); it != gameObjectsUI.end(); it++ ) {
		it->second->Input( _event );
	}
}


void Scene::Update( double _dt ) {
	std::map<std::string, UI*>::iterator it;
	for ( it = gameObjectsUI.begin(); it != gameObjectsUI.end(); it++ ) {
		it->second->Update( _dt );
	}

	if (level != nullptr) {
		level->Update(_dt);
	}
}


void Scene::Draw( void ) {
	std::map<std::string, UI*>::iterator it;

	if (level != nullptr) {
		level->Draw();
	}

	// UI objects
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
