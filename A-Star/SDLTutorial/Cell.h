#pragma once
#include <SDL.h>
#include <vector>

class Cell
{
public:
	SDL_Rect* rect;
	bool traversible;
	float gCost;
	float hCost;
	float fCost;
	std::vector<Cell> neighbors;
	void CalculategCost();
	void CalculatehCost();
	void CalculatefCost();
	void SetTraversible(bool);
	Cell(SDL_Rect* rect)
	{
		this->rect = rect;
	};
	int r_color = 255, g_color = 255, b_color = 255, a_color = 255;
};
