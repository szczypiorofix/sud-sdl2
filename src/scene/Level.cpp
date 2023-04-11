#include "Level.h"
#include "../core/Defines.h"
#include "../graphics/TextureManager.h"


Level::Level() : width(0), height(0), tileWidth(0), tileHeight(0), nextLayerId(0), nextObjectId(0), layers({}), spriteAtlas({}), player(nullptr) {

}


Level::~Level(void) {
	printf("LEVEL: Destroying...\n");
	for (unsigned int i = 0; i < layers.size(); i++) {
		delete layers.at(i);
	}

	for (unsigned int i = 0; i < spriteAtlas.size(); i++) {
		TextureManager::GetInstance()->Drop(spriteAtlas.at(i)->name);
		delete spriteAtlas.at(i);
	}
}



void Level::Create(TiledMap* _tiledMap) {
	printf("LEVEL: Generating level...\n");

	this->width = _tiledMap->mWidth;
	this->height = _tiledMap->mHeight;
	this->tileWidth = _tiledMap->mTileWidth;
	this->tileHeight = _tiledMap->mTileHeight;
	this->nextLayerId = _tiledMap->mNextLeyerId;
	this->nextObjectId = _tiledMap->mNextObjectId;
	
	this->layers = {};
	this->spriteAtlas = {};

	for (unsigned int i = 0; i < _tiledMap->mTileLayers.size(); i++) {
		TileLayer tempTileLayer = _tiledMap->mTileLayers.at(i);
		Layer* tempLayer = new Layer();
		
		tempLayer->id = tempTileLayer.mId;
		tempLayer->x = tempTileLayer.mX;
		tempLayer->y = tempTileLayer.mY;
		tempLayer->width = tempTileLayer.mWidth;
		tempLayer->height = tempTileLayer.mHeight;
		tempLayer->name = tempTileLayer.mName;
		tempLayer->offsetX = tempTileLayer.mOffsetX;
		tempLayer->offsetY = tempTileLayer.mOffsetY;
		tempLayer->paralaxX = tempTileLayer.mParalaxX;
		tempLayer->paralaxY = tempTileLayer.mParalaxY;
		tempLayer->visible = tempTileLayer.mVisible;
		
		tempLayer->data = {};
		for (unsigned int j = 0; j < tempTileLayer.mData.size(); j++) {
			
			if (tempTileLayer.mData.at(j) == 0) {
				continue;
			}

			Tile* tile = new Tile();
			tile->tileId = tempTileLayer.mData.at(j);

			tile->x = ( j % width ) * tileWidth;
			tile->y = ( j / width ) * tileHeight;

			for (unsigned int k = 0; k < _tiledMap->mTileSets.size(); k++) {
				TiledSpriteSheet* sprite = _tiledMap->mTileSets.at(k).mExportSpriteSheet;
				if (tile->tileId - _tiledMap->mTileSets.at(k).mFirstGid <= sprite->mTileCount) {
					tile->spriteSheetId = sprite->mName;
					tile->firstGid = _tiledMap->mTileSets.at(k).mFirstGid;
					for (unsigned int l = 0; l < sprite->mTiles.size(); l++) {
						if (tile->tileId - _tiledMap->mTileSets.at(k).mFirstGid == sprite->mTiles.at(l).mId) {
							TiledTile tiledTile = sprite->mTiles.at(l);
							std::vector<TileAnimation> animations = {};
							for (unsigned int m = 0; m < tiledTile.mAnimation.size(); m++) {
								TileAnimation tempAnim = {};
								tempAnim.duration = tiledTile.mAnimation.at(m).mDuration;
								tempAnim.tileId = tiledTile.mAnimation.at(m).mTileId;
								animations.push_back(tempAnim);
							}
							tile->isAnimated = true;
							tile->animation = animations;
							break;
						}
					}
					break;
				}
			}
			tempLayer->data.push_back(tile);

		}

		tempLayer->objects = {};
		for (unsigned int j = 0; j < tempTileLayer.mObjects.size(); j++) {
			TileObject* tileObject = new TileObject();

			tileObject->name = tempTileLayer.mObjects.at(j).name;
			tileObject->gid = tempTileLayer.mObjects.at(j).gId;
			tileObject->x = tempTileLayer.mObjects.at(j).x;
			tileObject->y = tempTileLayer.mObjects.at(j).y - 32;
			tileObject->width = tempTileLayer.mObjects.at(j).width;
			tileObject->height = tempTileLayer.mObjects.at(j).height;
			tileObject->visible = tempTileLayer.mObjects.at(j).visible;
			tileObject->isPortal = tempTileLayer.mObjects.at(j).properties.isPortal;
			
			if (tileObject->name == "player") {
				this->player = new Player(new Properties("main_spritesheet", tileObject->x, tileObject->y, tileObject->width, tileObject->height, false));
				player->SetTileIndex(3802);
			} else {
				tempLayer->objects.push_back(tileObject);
			}

		}

		this->layers.push_back(tempLayer);
	}

	for (unsigned int i = 0; i < _tiledMap->mTileSets.size(); i++) {
		TileSet tileSet = _tiledMap->mTileSets.at(i);
		
		SpriteAtlas* tempSpriteAtlas = new SpriteAtlas();

		tempSpriteAtlas->columns = tileSet.mExportSpriteSheet->mColumns;
		tempSpriteAtlas->exportFileName = tileSet.mExportFileName;
		tempSpriteAtlas->firstGid = tileSet.mFirstGid;
		tempSpriteAtlas->imageWidth = tileSet.mExportSpriteSheet->mImageWidth;
		tempSpriteAtlas->imageHeight = tileSet.mExportSpriteSheet->mImageHeight;
		tempSpriteAtlas->imagePath = tileSet.mExportSpriteSheet->mImage;
		tempSpriteAtlas->name = tileSet.mName;
		tempSpriteAtlas->tileCount = tileSet.mExportSpriteSheet->mTileCount;
		tempSpriteAtlas->tileWidth = tileSet.mExportSpriteSheet->mTileWidth;
		tempSpriteAtlas->tileHeight = tileSet.mExportSpriteSheet->mTileHeight;

		spriteAtlas.push_back(tempSpriteAtlas);

		TextureManager::GetInstance()->Load(tempSpriteAtlas->name, tileSet.mExportSpriteSheet->mImage, tileSet.mExportSpriteSheet->mTileWidth, tileSet.mExportSpriteSheet->mTileHeight);
	}

	printf("LEVEL: Generating done.\n");
}


void Level::Reload(TiledMap* _tiledMap) {
	printf("LEVEL: Clearing level...\n");
	for (unsigned int i = 0; i < layers.size(); i++) {
		delete layers.at(i);
	}
	for (unsigned int i = 0; i < spriteAtlas.size(); i++) {
		TextureManager::GetInstance()->Drop( spriteAtlas.at(i)->name );
		delete spriteAtlas.at(i);
	}
	Create(_tiledMap);
}


void Level::Update(double dt) {
	for (unsigned int l = 0; l < layers.size(); l++) {
		for (unsigned int t = 0; t < layers.at(l)->data.size(); t++) {
			layers.at(l)->data.at(t)->Update(dt);
		}
	}
}


void Level::Draw() {
	//int drawCalls = 0;
	for (unsigned int l = 0; l < layers.size(); l++) {
		Layer* layer = layers.at(l);
		if (!layer->visible) {
			continue;
		}
		for (unsigned int t = 0; t < layer->data.size(); t++) {
			Tile* tile = layer->data.at(t);
			for (unsigned int a = 0; a < spriteAtlas.size(); a++) {
				SpriteAtlas* atlas = spriteAtlas.at(a);
				if ( tile->tileId > atlas->firstGid  ) {
					//drawCalls++;
					if (tile->isAnimated) {
						TextureManager::GetInstance()->DrawSpriteIndex(atlas->name, tile->x, tile->y, tileWidth, tileHeight, tile->animation.at(tile->animCounter).tileId + 1 - atlas->firstGid);
					}
					else {
						TextureManager::GetInstance()->DrawSpriteIndex(atlas->name, tile->x, tile->y, tileWidth, tileHeight, tile->tileId - atlas->firstGid);
					}
				}
			}
		}

		for (unsigned int o = 0; o < layer->objects.size(); o++) {
			TileObject* tileObject = layer->objects.at(o);
			if (!tileObject->visible) {
				continue;
			}

			for (unsigned int a = 0; a < spriteAtlas.size(); a++) {
				SpriteAtlas* atlas = spriteAtlas.at(a);
				if (tileObject->gid > atlas->firstGid) {
					//drawCalls++;
					TextureManager::GetInstance()->DrawSpriteIndex(atlas->name, tileObject->x, tileObject->y, tileWidth, tileHeight, tileObject->gid - atlas->firstGid);
				}
			}
		}
	}
	//printf("Draw=%i\n", drawCalls);
}

