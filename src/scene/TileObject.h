#pragma once
#include <string>

class TileObject {

public:

	int gid;
	int x;
	int y;
	int width;
	int height;
	bool visible;
	std::string name;

	// properties
	bool isPortal;

	TileObject();
	~TileObject();

	void Update(double dt);
	void Draw();

};

