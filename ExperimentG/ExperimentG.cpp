#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "SDL/SDL.h"
#include <SDL/SDL_image.h>
#include <json/json.h>
#include "World.h"
#include "Box.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

Uint32 frameStart;
int frameTime;

std::string readFileAsString(const std::string& _fileName)
{
	std::ifstream ifs(_fileName);
	std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
	return str;
}

int main(int argc, char* argv[])
{
	const Json::CharReaderBuilder builder;
	auto reader = builder.newCharReader();
	Json::Value obj;

	const std::string jsonFileContent = readFileAsString("config.json");
	std::string errors;

	reader->parse(jsonFileContent.c_str(), jsonFileContent.c_str() + jsonFileContent.length(), &obj, &errors);
	delete reader;

	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* image = nullptr;

	int width, height;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	else
	{
		window = SDL_CreateWindow(obj["title"].asCString(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, obj["width"].asInt(), obj["height"].asInt(), SDL_WINDOW_SHOWN);
		if (!window)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return EXIT_FAILURE;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			World experimentWorld;

			for (const Json::Value& box : obj["boxes"])
			{
				experimentWorld.createBox("gamma.jpg", box["x"].asInt(), box["y"].asInt(), box["width"].asInt(), box["height"].asInt(), renderer);
			}

			while(true) {
				frameStart = SDL_GetTicks();

				SDL_Event e;
				if (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT)
					{
						break;
					}
				}

				experimentWorld.update();

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);
				experimentWorld.render(renderer);
				SDL_RenderPresent(renderer);

				frameTime = SDL_GetTicks() - frameStart;
				if(SCREEN_TICKS_PER_FRAME > frameTime)
				{
					SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTime);
				}
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(image);
	SDL_Quit();

	return EXIT_SUCCESS;
}