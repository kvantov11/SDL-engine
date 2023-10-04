#pragma once

#include "SDL_log.h"

#define LogSDLMessage(severity, string) SDL_LogMessage(0, SDL_LogPriority::SDL_LOG_PRIORITY_##severity, \
__FUNCTION__ " line:%d -> %s", __LINE__, string)
#define LogSDLErrorMessage LogSDLMessage(ERROR, SDL_GetError())
#define LogCustomErrorMessage(string)  LogSDLMessage(ERROR, string)
#define LogCustomWarningMessage(string)  LogSDLMessage(WARN, string)
#define LogCustomInfoMessage(string)  LogSDLMessage(INFO, string)