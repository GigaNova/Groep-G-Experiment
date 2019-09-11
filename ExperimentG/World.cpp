#include "World.h"
#include "Box2D/Box2D.h"

World::World() : m_world(b2Vec2(0.0f, 9.8)), m_timeStep(1.0f / 60.0f)
{
	m_groundBodyDef.position.Set(400.0 * MPP, 601.0f * MPP);
	m_groundBody = m_world.CreateBody(&m_groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(400.0f * MPP, 1.0f * MPP);
	m_groundBody->CreateFixture(&groundBox, 0.0f);
}

void World::update()
{
	m_world.Step(m_timeStep, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
	for (auto box : m_boxes)
	{
		box->update();
	}
}

void World::render(SDL_Renderer* _renderer)
{
	for(auto box : m_boxes)
	{
		box->draw(_renderer);
	}
}

void World::createBox(const std::string& _textureName, int _x, int _y, int _width, int _height, SDL_Renderer* _renderer)
{
	m_boxes.push_back(new Box(_textureName, _x, _y, _width, _height, _renderer, &m_world));
}
