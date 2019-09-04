#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "SDL/SDL.h"
#include <SDL/SDL_image.h>
#include <json/json.h>

std::string readFileAsString(const std::string& _fileName)
{
	std::ifstream ifs("config.json");
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
			image = IMG_LoadTexture(renderer, "gamma.jpg");
			SDL_QueryTexture(image, nullptr, nullptr, &width, &height);

			SDL_Rect texr; 
			texr.x = obj["width"].asInt() / 2;
			texr.y = obj["height"].asInt() / 2;
			texr.w = width / 2; 
			texr.h = height / 2;

			while(true) {
				SDL_Event e;
				if (SDL_PollEvent(&e)) {
					if (e.type == SDL_QUIT)
					{
						break;
					}
				}

				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, image, nullptr, &texr);
				SDL_RenderPresent(renderer);
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(image);
	SDL_Quit();

	return EXIT_SUCCESS;
}