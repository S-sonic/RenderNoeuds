#include <iostream>
#include <memory>
#include <functional>

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <GNEngine/event/event_manager.h>

void poll_sdl_event(gn::event_manager& eventManager);

int main(int argc, char** argv)
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        std::cerr << "Init error : " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window;
    window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>
        (SDL_CreateWindow("RenderNeuds", 720, 405, SDL_WINDOW_OPENGL),
            SDL_DestroyWindow);
    if (!window)
    {
        std::cerr << "Window creation error : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_GLContext glcontext = SDL_GL_CreateContext(window.get());
    if (!glcontext)
    {
        std::cerr << "error: unable to create OpenGL context : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_GL_MakeCurrent(window.get(), glcontext);

    SDL_GL_SetSwapInterval(1);

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    bool run = true;

    gn::event_manager eventManager;

    eventManager.subscribe<gn::SDLEvent>([&](const gn::SDLEvent& e)
        {
            if (e.event.type == SDL_EventType::SDL_EVENT_QUIT)
                run = false;
        });

    eventManager.subscribe<gn::SDLEvent>([&](const gn::SDLEvent& e)
        {
            if (e.event.type == SDL_EventType::SDL_EVENT_KEY_DOWN && e.event.key.key == SDLK_ESCAPE)
                run = false;
        });

    while (run)
    {
        poll_sdl_event(eventManager);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window.get());
    }

    SDL_Quit();

    return EXIT_SUCCESS;
}

void poll_sdl_event(gn::event_manager& eventManager)
{
    gn::SDLEvent event;
    while (SDL_PollEvent(&event.event))
    {
        eventManager.publish(event);
    }
}