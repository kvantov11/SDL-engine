#pragma once

#include "SDL_render.h"
#include "SDL_stdinc.h"

#include <memory>

#define ColorRed 255, 0, 0, 255
#define ColorBlue 0, 0, 255, 255
#define ColorGreen 0, 255, 0, 255

struct SDL_Renderer;
struct SDL_Window;

class Object;

class Renderer
{
public:
	Renderer() = default;
	~Renderer();
private:
	SDL_Renderer* _renderer = nullptr;
	Uint32 _rendererFlags = SDL_RENDERER_ACCELERATED;
	SDL_Color _renderDrawColor = { 96, 128, 255, 255 };
public:
	void CreateRenderer(SDL_Window* window);
	SDL_Renderer* GetRenderer();
	void DestroyRenderer();
	Renderer* SetRendererFlags(Uint32 flags);
	void SetRenderDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void SetRenderDrawColor(SDL_Color color);
	const SDL_Color& GetRenderDrawColor() const;
	void PrepareScene();
	void PresentScene();
	void Render(Object* object);
};