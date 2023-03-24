#include "Level.h"
#include "../core/Defines.h"
#include "../graphics/TextureManager.h"


Level::Level() : width(0), height(0), tileWidth(0), tileHeight(0), nextLayerId(0), nextObjectId(0), layers({}), spriteAtlas({}) {

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
			Tile* tile = new Tile();
			tile->tileId = tempTileLayer.mData.at(j);
			for (unsigned int k = 0; k < _tiledMap->mTileSets.size(); k++) {
				TiledSpriteSheet* sprite = _tiledMap->mTileSets.at(k).mExportSpriteSheet;
				if (tile->tileId <= sprite->mTileCount) {
					tile->spriteSheetId = sprite->mName;
					tile->firstGid = _tiledMap->mTileSets.at(k).mFirstGid;
					break;
				}
			}
			tempLayer->data.push_back( tile );
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

}


void Level::Draw() {
	//int drawCalls = 0;
	for (unsigned int l = 0; l < layers.size(); l++) {
		Layer* layer = layers.at(l);
		for (unsigned int t = 0; t < layer->data.size(); t++) {
			int x = t % width;
			int y = t / width;
			Tile* tile = layer->data.at(t);
			for (unsigned int a = 0; a < spriteAtlas.size(); a++) {
				SpriteAtlas* atlas = spriteAtlas.at(a);
				if ( tile->tileId < atlas->firstGid ) {
					continue;
				}
				//drawCalls++;
				TextureManager::GetInstance()->DrawSpriteIndex(atlas->name, (x * tileWidth), (y * tileHeight), tileWidth, tileHeight, tile->tileId - atlas->firstGid);
			}
		}
	}
	//printf("Draw=%i\n", drawCalls);
}

