#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>

#include "randomstuff.h"
#include "renderer.h"
#include "window.h"

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    Window* window = new Window;
    Renderer* renderer = new Renderer;
    window->CreateWindow();
    renderer->CreateRenderer(window->GetWindow());

    std::shared_ptr<Object> objPtr = std::make_shared<Object>();
    objPtr->Transform().SetPosition({ 320,240,0 });

    float i = 0;
    const float howLong = 3; // sec
    const float deltaTime = 16; // ms
    const float rotationSpeed = -90; // degree/sec
    const float forwardSpeed = 100; // pixel/sec
    objPtr->Transform().RotateUpAxis(45);
    while (i < howLong * 1000 / deltaTime)
    {
        ++i;
        renderer->SetRenderDrawColor(0, 0, 0, 255);
        renderer->PrepareScene();
        renderer->Render(objPtr.get());
        renderer->PresentScene();

        objPtr->Transform().TranslateForward(forwardSpeed * deltaTime / 1000);
        //objPtr->Transform().RotateUpAxis(rotationSpeed * deltaTime / 1000);
        //objPtr->Transform().RotateForwardAxis(2 * rotationSpeed * deltaTime / 1000);
        //objPtr->Transform().RotateRightAxis(3 * rotationSpeed * deltaTime / 1000);


        SDL_Delay(deltaTime);
    }

    delete window;
    window = nullptr;

    delete renderer;
    renderer = nullptr;

    return 0;
}