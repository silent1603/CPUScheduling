#include "Application.h"
#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "Window.h"
#include "input/mouse.h"
#include "input/keyboard.h"
namespace CPUScheduling {
    namespace Core {
        Window::Window(): mWindow(nullptr)
        {
        }

        Window::~Window()
        {
            if (mWindow)
            {
                Shutdown();
            }
        }

        bool Window::Create()
        {
            mWindow = SDL_CreateWindow("CPUScheduling", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
            if (!mWindow)
            {
                APP_CORE_ERROR( "Error creating window: {}",  SDL_GetError());
                return false;
            }
            
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#ifdef APP_PLATFORM_MACOSX
            glsl_version = "#version 410";
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
#elif defined(APP_PLATFORM_WINDOWS) 
            glsl_version = "#version 330";
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#elif defined(APP_PLATFORM_LINUX)
            glsl_version = "#version 430";
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#endif
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_SetWindowMinimumSize(mWindow, 200, 200);
            mGLContext = SDL_GL_CreateContext(mWindow);
            if (mGLContext == nullptr)
            {
                APP_CORE_ERROR("Error creating OpengGL context: {}", SDL_GetError());
                return false;
            }
            int result = gladLoadGLLoader(SDL_GL_GetProcAddress);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glClearColor(200, 200, 0,255);
            mImguiWindow.Create();
            return true;
        }

        void Window::Shutdown()
        {
            SDL_DestroyWindow(mWindow);
            mWindow = nullptr;
        }

        void Window::PumpEvent()
        {
            SDL_Event e;
            while (SDL_PollEvent(&e))
            {
                switch (e.type)
                {
                case SDL_QUIT:
                    Application::Instance().Quit();
                default:
                    break;
                }
                mImguiWindow.HandleSDLEvent(e);
            }
            Input::Mouse::Update();
            Input::Keyboard::Update();
        }

        glm::ivec2 Window::GetSize()
        {
            int w, h;
            SDL_GetWindowSize(mWindow, &w, &h);
            return glm::ivec2(w, h);
        }



        void Window::BeginRender()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void Window::EndRender()
        {
            mImguiWindow.BeginRender();
            ImGui::ShowDemoWindow();
            mImguiWindow.EndRender();
            SDL_GL_SwapWindow(mWindow);
        }

    }
}
