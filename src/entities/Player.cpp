#include "Player.h"
#include "../graphics/TextureManager.h"



Player::Player( Properties* props ) : Character( props ) {
	movX = 0.0;
	movY = 0.0;
	tileIndex = 0;
}


Player::~Player() {

}


void Player::Draw() {
	TextureManager::GetInstance()->DrawSpriteIndex(props->TextureID, (int)props->pos.X, (int)props->pos.Y, 32, 32, tileIndex);
}


void Player::Clean() {

}


void Player::Update(double dt) {
	props->pos.X += movX;;
	props->pos.Y += movY;

	movX = 0;
	movY = 0;
}


void Player::Input(SDL_Event* event) {
	if ((*event).type == SDL_KEYUP) {
		switch ((*event).key.keysym.sym) {
			case SDLK_LEFT:
				movX = -movingSpeed;
				break;

			case SDLK_RIGHT:
				movX = movingSpeed;
				break;

			case SDLK_UP:
				movY = -movingSpeed;
				break;
		
			case SDLK_DOWN:
				movY = movingSpeed;
				break;

			default:
				break;
		}
	}
	/*if ((*event).type == SDL_KEYUP) {
		switch ((*event).key.keysym.sym) {
			case SDLK_LEFT:
			case SDLK_RIGHT:
				movX = 0.0;
				break;
			case SDLK_UP:
			case SDLK_DOWN:
				movY = 0.0;
				break;
			default:
				break;
		}
	}*/
}


void Player::SetTileIndex(int _index) {
	this->tileIndex = _index;
}
