#include <SDL_main.h>
#include <SDL.h>

int main(int argc, char* argv[])
{
    SDL_LogMessage(0, SDL_LogPriority::SDL_LOG_PRIORITY_INFO, "hello world");
    return 0;
}