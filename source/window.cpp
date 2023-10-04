#include "window.h"

#include "logUtils.h"

#include <iostream>

WrapperWindow::~WrapperWindow()
{
	DestroyWindow();
}

bool WrapperWindow::InitializeWindow(std::unique_ptr<WrapperWindow>& window)
{
	if (!window)
	{
		LogCustomErrorMessage("window wrapper doesn't exist, exiting program");
		exit(1);
	}

	switch (window->CreateWindow())
	{
	case Result::Fail:
		// CreateWindow will log SDL Error
		LogCustomErrorMessage("exiting program");
		exit(1);
	case Result::Success:
		LogCustomInfoMessage("Successfully created window");
		return true;
	case Result::Warning:
		LogCustomWarningMessage("Attempt to recreate window");
		return false;
	default:
		LogCustomErrorMessage("Unknown result of creating window, exiting program");
		exit(1);
	}
}

Result WrapperWindow::CreateWindow()
{
	if (_window)
	{
		return Result::Warning;
	}

	_window = SDL_CreateWindow(_windowName.c_str(), _windowPositionX, _windowPositionY, _windowWidth, _windowHeight, _windowFlags);
	if (!_window)
	{
		LogSDLErrorMessage;
		return Result::Fail;
	}

	return Result::Success;
}

void WrapperWindow::DestroyWindow()
{
	SDL_DestroyWindow(_window);
	if (!_window)
	{
		LogSDLErrorMessage;
		return;
	}
	else
	{
		_window = nullptr;
	}

	LogCustomInfoMessage("Window was successfully destroyed");
}

WrapperWindow* WrapperWindow::SetWindowName(const std::string& name)
{
	if (this)
	{
		_windowName = name;
	}

	return this;
}

SDL_Window* WrapperWindow::GetWindow()
{
	return _window;
}

const std::string& WrapperWindow::GetWindowName() const
{
	return _windowName;
}

Uint32 WrapperWindow::GetWindowWidth() const
{
	return _windowWidth;
}

Uint32 WrapperWindow::GetWindowHeight() const
{
	return _windowHeight;
}

WrapperWindow* WrapperWindow::SetWindowWidth(const Uint32 width)
{
	if (this)
	{
		_windowWidth = width;
	}

	return this;
}

WrapperWindow* WrapperWindow::SetWindowHeight(const Uint32 height)
{
	if (this)
	{
		_windowHeight = height;
	}

	return this;
}

WrapperWindow* WrapperWindow::SetWindowFlags(const Uint32 flags)
{
	if (this)
	{
		_windowFlags = flags;
	}
	
	return this;
}

Uint32 WrapperWindow::GetWindowFlags() const
{
	return _windowFlags;
}
