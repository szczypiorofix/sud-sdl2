#pragma once

#include <SDL2/SDL.h>
#include <lua535/lua.hpp>
#include "IObject.h"
#include "../helpers/Transform.h"



struct Properties {
public:
	Properties( std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE ) {
		X = x;
		Y = y;
		Flip = flip;
		Width = width;
		Height = height;
		TextureID = textureID;
	}

public:
	std::string TextureID;
	int Width, Height;
	int X, Y;
	SDL_RendererFlip Flip;
};



class GameObject : public IObject {


public:

	GameObject( bool active = true) {
		props = new Properties( "default", 0, 0, 0, 0 );
		transform = new Transform(0,0);
		this->active = active;
	}

	GameObject( Properties* props, bool active = true ) {
		this->props = props;
		transform = new Transform(0,0);
		this->active = active;
	}

	virtual void Draw() = 0;
	virtual void Update( double dt ) = 0;
	virtual void Input( SDL_Event* event) = 0;
	virtual void Clean() = 0;

	Properties* GetProps() {
		return props;
	}

	bool active;

	void SetX( int x ) {
		props->X = x;
	}

	void SetY( int y ) {
		props->Y = y;
	}

	void SetWidth( int width ) {
		props->Width = width;
	}

	void SetHeight( int height ) {
		props->Height = height;
	}

protected:

	Transform* transform;
	Properties* props;

private:
	

};

