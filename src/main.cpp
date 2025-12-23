#include <iostream>
#include <memory>
#include <functional>

#include <glad/glad.h>
#include <imgui.h>
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include "imgui_node_editor.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <GNEngine/event/event_manager.h>

namespace ne = ax::NodeEditor;

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
        (SDL_CreateWindow("RenderNeuds", 1920, 1080, SDL_WINDOW_OPENGL),
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL3_InitForOpenGL(window.get(), glcontext);
    ImGui_ImplOpenGL3_Init("#version 330");

    ne::Config config;
    ne::EditorContext* editor = ne::CreateEditor(&config);
    ne::SetCurrentEditor(editor);

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

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ne::Begin("Node editor");

        ne::BeginNode(5);
        ImGui::Text("Node 1");
        ne::BeginPin(1, ne::PinKind::Output);
        ImGui::Text("Output");
        ne::EndPin();
        ne::EndNode();

        ne::BeginNode(6);
        ImGui::Text("Node 2");
        ne::BeginPin(2, ne::PinKind::Input);
        ImGui::Text("Input");
        ne::EndPin();
        ne::EndNode();

        ne::End();
        ne::SetCurrentEditor(editor);

        ImGui::Render();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
        ImGui_ImplSDL3_ProcessEvent(&event.event);
        eventManager.publish(event);
    }
}