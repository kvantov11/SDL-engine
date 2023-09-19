#include <SDL_main.h>
#include <SDL.h>

#include "window.h"
#include "renderer.h"

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    Window* window = new Window;
    Renderer* renderer = new Renderer;
    window->CreateWindow();
    renderer->CreateRenderer(window->GetWindow());
    SDL_Delay(2000);

    delete window;
    window = nullptr;

    delete renderer;
    renderer = nullptr;

    return 0;
}