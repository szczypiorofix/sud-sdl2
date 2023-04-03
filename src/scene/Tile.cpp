#include "Tile.h"



Tile::Tile() : tileId(0), x(0), y(0), firstGid(0), spriteSheetId(""), isAnimated(false), animation({}), animCounter(0), animC(0.0f) {
	
}


Tile::~Tile() {
	animation.clear();
}



void Tile::Draw() {

}


void Tile::Update(double dt) {
	if (isAnimated) {
		
		animC += animation.at(animCounter).duration;
		if ( animC > 1000.0f / dt ) {
			animCounter++;
			animC = 0.0f;
		}

		if (animCounter > animation.size() - 1) {
			animCounter = 0;
		}

	}
}

