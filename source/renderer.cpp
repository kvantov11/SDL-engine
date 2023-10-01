#include "renderer.h"

#include "logUtils.h"
#include "randomstuff.h"

#include "SDL.h"

namespace
{
	const char* rendererError = "Renderer is nullptr";
}

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
		LogSDLError;
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
		LogSDLError;
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

void Renderer::SetRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	_renderDrawColor.r = r;
	_renderDrawColor.g = g;
	_renderDrawColor.b = b;
	_renderDrawColor.a = a;

	if (!_renderer)
	{
		return;
	}

	SDL_SetRenderDrawColor(_renderer, _renderDrawColor.r, _renderDrawColor.g, _renderDrawColor.b, _renderDrawColor.a);
}

void Renderer::SetRenderDrawColor(SDL_Color color)
{
	_renderDrawColor = color;

	if (!_renderer)
	{
		return;
	}

	SDL_SetRenderDrawColor(_renderer, _renderDrawColor.r, _renderDrawColor.g, _renderDrawColor.b, _renderDrawColor.a);
}

const SDL_Color& Renderer::GetRenderDrawColor() const
{
	return _renderDrawColor;
}

void Renderer::PrepareScene()
{
	if (!_renderer)
	{
		LogCustomError(rendererError);
		return;
	}

	SDL_RenderClear(_renderer);
}

void Renderer::PresentScene()
{
	if (!_renderer)
	{
		LogCustomError(rendererError);
		return;
	}

	SDL_RenderPresent(_renderer);
}

void Renderer::Render(Object* object)
{
	if (!_renderer)
	{
		LogCustomError("failed to render object");
		return;
	}

	if (!object)
	{
		LogCustomError("failed to render object");
		return;
	}
	else
	{
		float lineLength = 50;
		float x0 = object->GetTransform().GetPosition().GetElement(0);
		float y0 = object->GetTransform().GetPosition().GetElement(1);

		float x1 = x0 + object->GetTransform().GetForwardVector().GetElement(0) * lineLength;
		float y1 = y0 + object->GetTransform().GetForwardVector().GetElement(1) * lineLength;
		SetRenderDrawColor(ColorRed);
		SDL_RenderDrawLineF(_renderer,x0, y0,x1,y1);

		SetRenderDrawColor(ColorBlue);
		x1 = x0 - object->GetTransform().GetRightVector().GetElement(0) * lineLength;
		y1 = y0 - object->GetTransform().GetRightVector().GetElement(1) * lineLength;
		SDL_RenderDrawLineF(_renderer, x0, y0, x1, y1);

		SetRenderDrawColor(ColorGreen);
		x1 = x0 + object->GetTransform().GetUpVector().GetElement(0) * lineLength;
		y1 = y0 + object->GetTransform().GetUpVector().GetElement(1) * lineLength;
		SDL_RenderDrawLineF(_renderer, x0, y0, x1, y1);
	}
}
