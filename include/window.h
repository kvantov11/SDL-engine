#pragma once

// needed for macros
#include <SDL_video.h>

#include <memory>
#include <string>

// Result of creation
enum class Result
{
	Fail,
	Success,
	Warning
};

// Wrapper for SDL_Window
class WrapperWindow
{
public:
	~WrapperWindow();
public:
	// Initialize instance of SDL_Window
	static bool InitializeWindow(std::unique_ptr<WrapperWindow>& window);
private:
	std::string _windowName = "default window name";
	Uint32 _windowWidth = 620;
	Uint32 _windowHeight = 480;
	Uint32 _windowPositionX = SDL_WINDOWPOS_UNDEFINED;
	Uint32 _windowPositionY = SDL_WINDOWPOS_UNDEFINED;
	Uint32 _windowFlags = 0;
	SDL_Window* _window = nullptr;
public:
	void DestroyWindow();
	SDL_Window* GetWindow();
	const std::string& GetWindowName() const;
	Uint32 GetWindowHeight() const;
	Uint32 GetWindowWidth() const;
	Uint32 GetWindowFlags() const;
	WrapperWindow* SetWindowName(const std::string& name);
	WrapperWindow* SetWindowWidth(const Uint32 width);
	WrapperWindow* SetWindowHeight(const Uint32 height);
	// Uses integer to set one or combination of flags
	WrapperWindow* SetWindowFlags(const Uint32 flags);
private:
	Result CreateWindow();
};
