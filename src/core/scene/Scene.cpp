#include <iostream>
#include "Scene.h"
#include "../graphics/TextureManager.h"


Scene::Scene( std::string name, SDL_Renderer * renderer) {
	this->renderer = renderer;
	this->name = name;
	spriteSheet = nullptr;
	level = nullptr;
	this->gameObjectsUI = {};
}


Scene::~Scene( void ) { }

void Scene::AddSpriteSheet(std::string spriteSheetName, int tileWidth, int tileHeight) {
	spriteSheet = new Spritesheet(spriteSheetName, renderer, tileWidth, tileHeight);
}

void Scene::AddUIObject( std::string id, UI* uiObject ) {
	gameObjectsUI[id] = uiObject;
}

void Scene::SetLevel(LuaGen::Level* _level) {
	this->level = _level;
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

	// draw level
	for (unsigned int y = 0; y < level->height; y++) {
		for (unsigned int x = 0; x < level->width; x++) {
			unsigned int charIndex = (y * level->width) + x;
			if (charIndex < level->foreground.size() && charIndex < level->background.size()) {
				// background
				if (level->background.at(charIndex) == '#') { // wall
					TextureManager::GetInstance()->DrawSprite("main_spritesheet", 32 + (x * 32), 128 + (y * 32), 32, 32, 384, 128, 32, 32, SDL_FLIP_NONE);
				}
				if (level->background.at(charIndex) == '.') { // open space
					TextureManager::GetInstance()->DrawSprite("main_spritesheet", 32 + (x * 32), 128 + (y * 32), 32, 32, 384, 288, 32, 32, SDL_FLIP_NONE);
				}
				// foreground
				if (level->foreground.at(charIndex) == 'T') { // big tree
					TextureManager::GetInstance()->DrawSprite("main_spritesheet", 32 + (x * 32), 128 + (y * 32), 32, 32, 416, 416, 32, 32, SDL_FLIP_NONE);
				}
				if (level->foreground.at(charIndex) == 't') { // small tree
					TextureManager::GetInstance()->DrawSprite("main_spritesheet", 32 + (x * 32), 128 + (y * 32), 32, 32, 448, 416, 32, 32, SDL_FLIP_NONE);
				}
				if (level->foreground.at(charIndex) == 'P') { // player
					TextureManager::GetInstance()->DrawSprite("main_spritesheet", 32 + (x * 32), 128 + (y * 32), 32, 32, 832, 1888, 32, 32, SDL_FLIP_NONE);
				}
			}
		}
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
