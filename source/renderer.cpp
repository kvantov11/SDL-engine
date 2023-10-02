#include "renderer.h"

#include "logUtils.h"
#include "randomstuff.h"

#include "SDL.h"

#include <algorithm>

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

const SDL_Renderer* Renderer::GetRenderer()
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

const Renderer* Renderer::SetRendererFlags(Uint32 flags)
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
	if (!object)
	{
		return;
	}

	RenderOrientationVectors(object);
	const std::vector<std::weak_ptr<Object>> attachedObjects{ object->GetAttachedObjects() };
	if (attachedObjects.empty())
	{
		return;
	}

	std::for_each(attachedObjects.begin(), attachedObjects.end(), [this](std::weak_ptr<Object> child){
		if (auto ptr = child.lock())
		{
			Render(ptr.get());
		}
		});
}

void Renderer::RenderOrientationVectors(Object* object)
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
		Transform parentTransformGlobal;
		if (auto parent = object->GetParent().lock())
		{
			// parent's global tranform is used to calculate global transform of child
			parentTransformGlobal = parent->GetTransformGlobal();
		}
		else
		{
			// object is root, its global transform can be used directly
			parentTransformGlobal = object->GetTransformGlobal();
		}

		// multiply parent's global transform with object's local transform and assign result to object global transform
		object->SetTransformGlobal(Transform::Multiply(parentTransformGlobal, object->GetTransformLocal()));
		// the length of lines representing object's orientation
		const float lineLength{ 50.f };
		const float x0 = object->GetTransformGlobal().GetPosition().GetElement(0);
		// Y axis is inverted in SDL, y0 is calculated as offset between parent's and child's Y substracted from child's global Y 
		// child new Y = parent Y - (child original Y - parent Y)
		const float y0 = 2 * parentTransformGlobal.GetPosition().GetElement(1) - object->GetTransformGlobal().GetPosition().GetElement(1);

		// X axis
		SetRenderDrawColor(ColorRed);
		float x1 = x0 + object->GetTransformGlobal().GetForwardVector().GetElement(0) * lineLength;
		float y1 = y0 + object->GetTransformGlobal().GetForwardVector().GetElement(1) * lineLength;
		SDL_RenderDrawLineF(_renderer, x0, y0, x1, y1);

		// Y axis
		SetRenderDrawColor(ColorBlue);
		x1 = x0 - object->GetTransformGlobal().GetRightVector().GetElement(0) * lineLength;
		y1 = y0 - object->GetTransformGlobal().GetRightVector().GetElement(1) * lineLength;
		SDL_RenderDrawLineF(_renderer, x0, y0, x1, y1);

		// Z axis
		SetRenderDrawColor(ColorGreen);
		x1 = x0 + object->GetTransformGlobal().GetUpVector().GetElement(0) * lineLength;
		y1 = y0 + object->GetTransformGlobal().GetUpVector().GetElement(1) * lineLength;
		SDL_RenderDrawLineF(_renderer, x0, y0, x1, y1);
	}
}
