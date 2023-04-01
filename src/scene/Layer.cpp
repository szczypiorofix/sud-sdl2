#include "Layer.h"




Layer::Layer() : x(0), y(0), width(0), height(0), id(0), name(""), visible(true), offsetX(0.0f), offsetY(0.0f), paralaxX(0.0f), paralaxY(0.0f), spriteSheetId(""), data({}), objects({}) {
}


Layer::~Layer() {
	for (unsigned int i = 0; i < data.size(); i++) {
		delete data.at(i);
	}
	for (unsigned int i = 0; i < objects.size(); i++) {
		delete objects.at(i);
	}
}

