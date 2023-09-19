#pragma once

#include "SDL_render.h"
#include "SDL_stdinc.h"

struct SDL_Renderer;
struct SDL_Window;

class Renderer
{
public:
	Renderer() = default;
	~Renderer();
private:
	SDL_Renderer* _renderer = nullptr;
	Uint32 _rendererFlags = SDL_RENDERER_ACCELERATED;
public:
	void CreateRenderer(SDL_Window* window);
	SDL_Renderer* GetRenderer();
	void DestroyRenderer();
	Renderer* SetRendererFlags(Uint32 flags);

};