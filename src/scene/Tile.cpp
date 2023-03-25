#include "Tile.h"



Tile::Tile() : tileId(0), firstGid(0), spriteSheetId(""), isAnimated(false), animation({}), animCounter(0), animC(0) {
	
}


Tile::~Tile() {
	animation.clear();
}



void Tile::Draw() {

}


void Tile::Update(float dt) {
	if (isAnimated) {
		
		animC++;
		if (animC > 5) {
			animCounter++;
			animC = 0;
		}

		if (animCounter > animation.size() - 1) {
			//printf("Anim tick!\n");
			animCounter = 0;
		}

	}
}

