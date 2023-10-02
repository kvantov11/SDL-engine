#include "window.h"

#include "logUtils.h"

#include <iostream>
#include <stdexcept>

Window::~Window()
{
	DestroyWindow();
}

void Window::CreateWindow()
{
	if (!_window)
	{
		_window = SDL_CreateWindow(_windowName.c_str(), _windowPositionX, _windowPositionY, _windowWidth, _windowHeight, _windowFlags);
	}

	try
	{
		if (!_window)
		{
			throw std::runtime_error(std::string(__FUNCTION__ " -> ").append(SDL_GetError()));
		}
	}

	catch (std::exception &e)
	{
		std::cerr << e.what() << '\n';
		exit(1);
	}
}

SDL_Window* Window::GetWindow()
{
	return _window;
}

void Window::DestroyWindow()
{
	SDL_DestroyWindow(_window);
	if (!_window)
	{
		LogSDLError;
	}
	else
	{
		_window = nullptr;
	}
}

const Window* Window::SetWindowName(const std::string& name)
{
	if (this)
	{
		_windowName = name;
	}
	return this;
}

const std::string& Window::GetWindowName() const
{
	return _windowName;
}

const int Window::GetWindowWidth() const
{
	return _windowWidth;
}

const int Window::GetWindowHeight() const
{
	return _windowHeight;
}

const Window* Window::SetWindowWidth(int width)
{
	if (this)
	{
		_windowWidth = width;
	}

	return this;
}

const Window* Window::SetWindowHeight(int height)
{
	if (this)
	{
		_windowHeight = height;
	}

	return this;
}

const Window* Window::SetWindowFlags(Uint32 flags)
{
	if (this)
	{
		_windowFlags = flags;
	}
	
	return this;
}

Uint32 Window::GetWindowFlags() const
{
	return _windowFlags;
}
