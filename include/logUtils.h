#pragma once

#include "SDL_log.h"

#define LogSDLError SDL_LogMessage(0, SDL_LogPriority::SDL_LOG_PRIORITY_ERROR, __FUNCTION__ " -> %s", SDL_GetError())
#define LogCustomError(string) SDL_LogMessage(0, SDL_LogPriority::SDL_LOG_PRIORITY_ERROR, __FUNCTION__ " -> %s", string)