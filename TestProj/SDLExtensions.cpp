#include "stdafx.h"
#include "SDLExtensions.h"

int SDLEx_SetRendererDrawingColor(SDL_Renderer* renderer, Color color)
{
	return SDL_SetRenderDrawColor(renderer, color.data[0], color.data[1], color.data[2], color.data[3]);
}