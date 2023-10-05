#pragma once

// Needed for macro
#include "SDL_render.h"

#include <memory>

#define ColorRed 255, 0, 0, 255
#define ColorBlue 0, 0, 255, 255
#define ColorGreen 0, 255, 0, 255

class Object;
class WrapperWindow;

enum class Result;

class WrapperRenderer
{
public:
	~WrapperRenderer();
public:
	static bool InitializeRenderer(std::unique_ptr<WrapperRenderer>& renderer, SDL_Window* window);
private:
	SDL_Renderer* _renderer = nullptr;
	Uint32 _rendererFlags = SDL_RENDERER_ACCELERATED;
	SDL_Color _renderDrawColor = { 96, 128, 255, 255 };

public:
	void DestroyRenderer();
	const WrapperRenderer* SetRendererFlags(Uint32 flags);
	void SetRenderDrawColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);
	void SetRenderDrawColor(const SDL_Color color);
	const SDL_Color& GetRenderDrawColor() const;
	void PrepareScene();
	void PresentScene();
	void Render(Object* object);
private:
	Result CreateRenderer(SDL_Window* window);
	void RenderOrientationVectors(Object* object);
	// Applies stored color from wrapper to SDl_Renderer
	void UpdateRenderDrawColor();
};