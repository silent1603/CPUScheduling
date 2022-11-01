#ifndef WINDOW_H
#define WINDOW_H
#include "glm/glm.hpp"
#include "imguiwindow.h"
struct SDL_Window;
using SDL_GLContext = void*;
namespace CPUScheduling{
    namespace Core{
        class Window{
            public:
                Window();
                ~Window();
                bool Create();
                void Shutdown();
                void PumpEvent();
                void BeginRender();
                void EndRender();
                inline SDL_Window* GetSDLWindow() { return mWindow; }
                inline SDL_GLContext GetGLContext() { return mGLContext; }
                inline eastl::string GetGLSLString() { return glsl_version; }
                glm::ivec2 GetSize();
                eastl::string glsl_version;
            private:
                SDL_Window* mWindow;
                SDL_GLContext mGLContext;
                ImguiWindow mImguiWindow;
        };
    } 
}
#endif