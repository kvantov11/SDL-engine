#include "renderer.h"

#include "logUtils.h"
#include "randomstuff.h"
#include "window.h"

#include "SDL.h"

#include <algorithm>

namespace
{
	const char* rendererError = "Renderer is nullptr";
}

WrapperRenderer::~WrapperRenderer()
{
	DestroyRenderer();
}

bool WrapperRenderer::InitializeRenderer(std::unique_ptr<WrapperRenderer>& renderer, SDL_Window* window)
{
	if (!renderer)
	{
		LogCustomErrorMessage("renderer wrapper doesn't exist, exiting program");
		exit(1);
	}

	switch(renderer.get()->CreateRenderer(window))
	{
	case Result::Fail:
		// CreateWindow will log SDL Error
		LogCustomErrorMessage("exiting program");
		exit(1);
	case Result::Warning:
		LogCustomWarningMessage("Attempt to recreate renderer");
		return false;
	case Result::Success:
		LogCustomInfoMessage("Successfully created renderer");
		return true;
	default:
		LogCustomErrorMessage("Unknown result of creating renderer, exiting program");
		exit(1);
	}
}

Result WrapperRenderer::CreateRenderer(SDL_Window* window)
{
	if (!window)
	{
		return Result::Fail;
		LogCustomErrorMessage("Couldn't create renderer, window instance doesn't exist.");
		exit(1);
	}

	if (_renderer)
	{
		return Result::Warning;
	}

	_renderer = SDL_CreateRenderer(window, -1, _rendererFlags);
	if (!_renderer)
	{
		return Result::Fail;
		LogSDLErrorMessage;
		exit(1);
	}

	return Result::Success;
}

void WrapperRenderer::DestroyRenderer()
{
	SDL_DestroyRenderer(_renderer);
	if (!_renderer)
	{
		LogSDLErrorMessage;
	}
	else
	{
		_renderer = nullptr;
	}
}

const WrapperRenderer* WrapperRenderer::SetRendererFlags(Uint32 flags)
{
	if (_renderer)
	{
		_rendererFlags = flags;
	}

	return this;
}

void WrapperRenderer::SetRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
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

void WrapperRenderer::SetRenderDrawColor(SDL_Color color)
{
	_renderDrawColor = color;

	if (!_renderer)
	{
		return;
	}

	SDL_SetRenderDrawColor(_renderer, _renderDrawColor.r, _renderDrawColor.g, _renderDrawColor.b, _renderDrawColor.a);
}

const SDL_Color& WrapperRenderer::GetRenderDrawColor() const
{
	return _renderDrawColor;
}

void WrapperRenderer::PrepareScene()
{
	if (!_renderer)
	{
		LogCustomErrorMessage(rendererError);
		return;
	}

	SDL_RenderClear(_renderer);
}

void WrapperRenderer::PresentScene()
{
	if (!_renderer)
	{
		LogCustomErrorMessage(rendererError);
		return;
	}

	SDL_RenderPresent(_renderer);
}

void WrapperRenderer::Render(Object* object)
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

void WrapperRenderer::RenderOrientationVectors(Object* object)
{
	if (!_renderer)
	{
		LogCustomErrorMessage("failed to render object, renderer doesn't exist");
		return;
	}

	if (!object)
	{
		LogCustomErrorMessage("failed to render object, object doesn't exist");
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
