#include <SDL.h>
#include <SDL_main.h>
#include <SDL_image.h>

#include "logUtils.h"
#include "randomstuff.h"
#include "renderer.h"
#include "window.h"

#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        LogSDLErrorMessage;
        exit(1);
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"))
    {
        LogCustomErrorMessage("failed to set hints");
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    std::unique_ptr<WrapperWindow> window = std::make_unique<WrapperWindow>();
    WrapperWindow::InitializeWindow(window);

    std::unique_ptr<WrapperRenderer> renderer = std::make_unique<WrapperRenderer>();
    WrapperRenderer::InitializeRenderer(renderer, window.get()->GetWindow());

    std::shared_ptr<Object> leftDown = std::make_shared<Object>();
    leftDown->TransformGlobal().SetPosition({ 200, 300, 0 });

    std::shared_ptr<Object> rightDown = std::make_shared<Object>();
    rightDown->TransformLocal().SetPosition({ 100, 0, 0 });
    Object::AttachToParent(leftDown, rightDown);

    std::shared_ptr<Object> rightUp = std::make_shared<Object>();
    rightUp->TransformLocal().SetPosition({ 100, 100, 0 });
    Object::AttachToParent(leftDown, rightUp);

    std::shared_ptr<Object> leftUp = std::make_shared<Object>();
    leftUp->TransformLocal().SetPosition({ 0, 100, 0 });
    Object::AttachToParent(leftDown, leftUp);

    float i = 0;
    const float howLong = 7; // sec
    const float deltaTime = 16; // ms
    const float rotationSpeed = 90; // degree/sec
    const float forwardSpeed = 100; // pixel/sec
    while (i < howLong * 1000 / deltaTime)
    {
        ++i;
        renderer->SetRenderDrawColor(0, 0, 0, 255);
        renderer->PrepareScene();
        renderer->Render(leftDown.get());
        renderer->PresentScene();

        //leftDown->TransformGlobal().TranslateForward(forwardSpeed * deltaTime / 1000.f);
        leftDown->TransformGlobal().RotateRightAxis(rotationSpeed * deltaTime / 1000.f);
        //leftDown->TransformGlobal().RotateForwardAxis(2 * rotationSpeed * deltaTime / 1000.f);

        SDL_Delay(deltaTime);
    }

    return 0;
}