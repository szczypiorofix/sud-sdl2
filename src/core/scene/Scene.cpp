#include <iostream>
#include "Scene.h"
#include "../graphics/TextureManager.h"
#include "../graphics/Sprites.h"



Scene::Scene( std::string name, SDL_Renderer * renderer) {
	this->renderer = renderer;
	this->name = name;
	level = nullptr;
	this->gameObjectsUI = {};
}


Scene::~Scene( void ) { }


void Scene::AddUIObject( std::string id, UI* uiObject ) {
	gameObjectsUI[id] = uiObject;
}

void Scene::SetLevel(LUA::Object::Level* _level) {
	this->level = _level;
}


void Scene::Load( void ) {
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
	if ( level == nullptr ) {
		return;
	}
	for (unsigned int y = 0; y < level->height; y++) {
		for (unsigned int x = 0; x < level->width; x++) {
			unsigned int charIndex = (y * level->width) + x;
			if (charIndex < level->foreground.size() && charIndex < level->background.size()) {
				// background
				if (level->background.at(charIndex) == '#') { // wall
					TextureManager::GetInstance()->DrawSpriteIndex("main_spritesheet", 32 + (x * 32), 128 + (y * 32), 32, 32, Sprites::WALL_STONE_LIGHT2 );
				}
				if (level->background.at(charIndex) == '.') { // open space
					TextureManager::GetInstance()->DrawSpriteIndex("main_spritesheet", 32 + (x * 32), 128 + (y * 32), 32, 32, Sprites::GRASS_LIGHT1 );
				}
				// foreground
				if (level->foreground.at(charIndex) == 'T') { // big tree
					TextureManager::GetInstance()->DrawSpriteIndex("main_spritesheet", 32 + (x * 32), 128 + (y * 32), 32, 32, Sprites::TREE3 );
				}
				if (level->foreground.at(charIndex) == 't') { // small tree
					TextureManager::GetInstance()->DrawSpriteIndex("main_spritesheet", 32 + (x * 32), 128 + (y * 32), 32, 32, Sprites::TREE_OLD2 );
				}
				if (level->foreground.at(charIndex) == 'P') { // player
					TextureManager::GetInstance()->DrawSpriteIndex("main_spritesheet", 32 + (x * 32), 128 + (y * 32), 32, 32, Sprites::NPC_RAT_WARRIOR );
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
