#pragma once
#include <Box2D/Box2D.h>
#include <SDL/SDL.h>
#include <string>
#include <vector>
#include "Box.h"

class World
{
public:
	static constexpr float PPM = 32;
	static constexpr float MPP = 1 / PPM;
	static constexpr int VELOCITY_ITERATIONS = 8;
	static constexpr int POSITION_ITERATIONS = 5;

	World();

	void update();
	void render(SDL_Renderer* _renderer);

	void createBox(const std::string& _textureName, int _x, int _y, int _width, int _height, SDL_Renderer* _renderer);
private:
	float m_timeStep;

	b2World m_world;
	b2BodyDef m_groundBodyDef;
	b2Body* m_groundBody;

	std::vector<Box*> m_boxes{};
};

