#pragma once


class TileObject {

public:

	int gid;
	int x;
	int y;
	int width;
	int height;
	bool visible;

	// properties
	bool isPortal;

	TileObject();
	~TileObject();

	void Update(double dt);
	void Draw();

};

