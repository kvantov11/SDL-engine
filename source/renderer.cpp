#include "renderer.h"

#include "logUtils.h"

#include "SDL.h"

Renderer::~Renderer()
{
	DestroyRenderer();
}

void Renderer::CreateRenderer(SDL_Window* window)
{
	if (!_renderer)
	{
		_renderer = SDL_CreateRenderer(window, -1, _rendererFlags);
	}

	if (!_renderer)
	{
		LogError;
	}
}

SDL_Renderer* Renderer::GetRenderer()
{
	return _renderer;
}

void Renderer::DestroyRenderer()
{
	SDL_DestroyRenderer(_renderer);
	if (!_renderer)
	{
		LogError;
	}
	else
	{
		_renderer = nullptr;
	}
}

Renderer* Renderer::SetRendererFlags(Uint32 flags)
{
	if (_renderer)
	{
		_rendererFlags = flags;
	}

	return this;
}
