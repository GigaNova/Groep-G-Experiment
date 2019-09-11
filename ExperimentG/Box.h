#pragma once
#include <SDL/SDL.h>
#include <string>
#include "Box2D/Box2D.h"

class Box
{
public:
	Box(const std::string& _textureName, int _x, int _y, int _width, int _height, SDL_Renderer* _renderer, b2World* _world);

	void draw(SDL_Renderer* _render) const;
	void update();
private:
	SDL_Texture* m_image;
	SDL_Rect m_bounds{};

	b2PolygonShape m_polygon;
	b2FixtureDef m_fixture;
	b2BodyDef m_bodyDef;
	b2Body* m_body;
};

