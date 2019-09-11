#include "Box.h"
#include <SDL/SDL_image.h>
#include <iostream>
#include "World.h"

Box::Box(const std::string& _textureName, int _x, int _y, int _width, int _height, SDL_Renderer* _renderer, b2World* _world) : m_image(IMG_LoadTexture(_renderer, _textureName.c_str()))
{
	SDL_QueryTexture(m_image, nullptr, nullptr, nullptr, nullptr);

	m_bounds.w = _width;
	m_bounds.h = _height;

	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(_x * World::MPP, _y * World::MPP);
	m_body = _world->CreateBody(&m_bodyDef);

	m_polygon.SetAsBox(World::MPP * _width / 2.0f, World::MPP * _height / 2.0f);

	m_fixture.shape = &m_polygon;
	m_fixture.density = 1.0;
	m_body->CreateFixture(&m_fixture);
}

void Box::draw(SDL_Renderer* _render) const
{
	const auto angle = (m_body->GetAngle() * 180.0f) / M_PI;

	SDL_RenderCopyEx(_render, m_image, nullptr, &m_bounds, angle, nullptr, SDL_FLIP_NONE);
}

void Box::update()
{
	m_bounds.x = m_body->GetPosition().x * World::PPM - (m_bounds.w / 2.0f);
	m_bounds.y = m_body->GetPosition().y * World::PPM - (m_bounds.h / 2.0f);
}
