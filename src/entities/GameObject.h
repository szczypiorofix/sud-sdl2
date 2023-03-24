#pragma once

#include <SDL2/SDL.h>
#include "IObject.h"
#include "../graphics/Transform.h"
#include "../core/Defines.h"
#include "../graphics/Font.h"


struct Properties {
public:
	Properties( std::string textureID, int x, int y, int width, int height, bool isGeneric, std::string title, Font* font, SDL_Color fontColor, SDL_Color backgroundColor, SDL_Color borderColor, SDL_RendererFlip flip = SDL_FLIP_NONE ) {
		TextureID = textureID;
		X = x;
		Y = y;
		Width = width;
		Height = height;
		IsGeneric = isGeneric;
		Title = title;
		_font = font;
		FontColor = fontColor;
		BackgroundColor = backgroundColor;
		BorderColor = borderColor;
		Flip = flip;
	}

public:
	std::string TextureID;
	int Width, Height;
	int X, Y;
	bool IsGeneric;
	std::string Title;
	Font* _font;
	SDL_Color FontColor;
	SDL_Color BackgroundColor;
	SDL_Color BorderColor;
	SDL_RendererFlip Flip;
};



class GameObject : public IObject {


public:

	GameObject( bool active = true) {
		props = new Properties( "default", 0, 0, 0, 0, true, "...", nullptr, COLOR_WHITE, COLOR_BLUE, COLOR_BLUE );
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

