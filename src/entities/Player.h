#pragma once

#include "Character.h"
#include "../graphics/Vector2D.h"



class Player : public Character {

public:

	Player( Properties* props );
	~Player();

	void Draw();
	void Clean();
	void Update(double dt);
	void Input(SDL_Event* event);

	void SetTileIndex(int _index);

	double movX;
	double movY;
	int tileIndex;

	double movingSpeed = 32.0; // temporary?
};

