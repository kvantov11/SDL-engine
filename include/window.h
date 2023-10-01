#pragma once

#include <SDL_video.h>

#include <string>

struct SDL_Window;

class Window
{
public:
	Window() = default;
	~Window();
private:
	std::string _windowName = "default window name";
	int _windowWidth = 620;
	int _windowHeight = 480;
	int _windowPositionX = SDL_WINDOWPOS_UNDEFINED;
	int _windowPositionY = SDL_WINDOWPOS_UNDEFINED;
	Uint32 _windowFlags = 0;
	SDL_Window* _window = nullptr;
public:
	void CreateWindow();
	SDL_Window* GetWindow();
	void DestroyWindow();
	const std::string& GetWindowName() const;
	const int GetWindowWidth() const;
	const int GetWindowHeight() const;
	Uint32 GetWindowFlags() const;
	const Window* SetWindowName(const std::string& name);
	const Window* SetWindowWidth(int width);
	const Window* SetWindowHeight(int height);
	const Window* SetWindowFlags(Uint32 flags);
};

// How to update existing window if parameters are changed