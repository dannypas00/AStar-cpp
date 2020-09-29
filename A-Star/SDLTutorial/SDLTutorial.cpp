#include <iostream>
#include <map>
#include <SDL.h>
#include <vector>
#include "Cell.h"
#define WIDTH 800
#define HEIGHT 600
#define CELLSIZE 40

Cell* map [WIDTH / CELLSIZE * HEIGHT / CELLSIZE];

SDL_Rect PosToRect(int col, int row)
{
	SDL_Rect rect;
	rect.x = CELLSIZE * col;
	rect.y = CELLSIZE * row;
	rect.w = CELLSIZE;
	rect.h = CELLSIZE;
	return rect;
}

int main(int argc, char *argv[])
{
	SDL_Surface* imageSurface = nullptr;
	SDL_Surface* windowSurface = nullptr;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "SDL could not initialise! SDL Error: " << SDL_GetError() << std::endl;
	}

	SDL_Window* window = SDL_CreateWindow("Hello SDL World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	windowSurface = SDL_GetWindowSurface(window);

	if ( NULL == window )
	{
		std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	SDL_Event windowEvent;

	imageSurface = SDL_LoadBMP("Gnome.bmp");

	if (NULL == imageSurface)
	{
		std::cerr << "SDL could not load image: " << SDL_GetError() << std::endl;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	for (int i = 0; i < WIDTH / CELLSIZE; i++)
	{
		for (int j = 0; j < HEIGHT / CELLSIZE; j++)
		{
			SDL_Rect* rect = &PosToRect(i, j);
			Cell cell = Cell(rect);
			map[i * WIDTH / CELLSIZE + j] = &cell;

			
		}
	}
	
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (SDL_QUIT == windowEvent.type) {
				break;
			}
			if (SDL_MOUSEBUTTONDOWN == windowEvent.type) {
				continue;
			}
		}
		SDL_RenderClear(renderer);
		for (int i = 0; i < WIDTH / CELLSIZE; i++)
		{
			for (int j = 0; j < HEIGHT / CELLSIZE; j++)
			{
				Cell* cell = map[i * WIDTH / CELLSIZE + j];

				SDL_SetRenderDrawColor(renderer, cell->r_color, cell->g_color, cell->b_color, cell->a_color);
				SDL_RenderFillRect(renderer, cell->rect);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, cell->rect);
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderPresent(renderer);

	}

	SDL_FreeSurface(windowSurface);
	SDL_FreeSurface(imageSurface);
	windowSurface = NULL;
	imageSurface = NULL;
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return EXIT_SUCCESS;
}
