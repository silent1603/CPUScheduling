#ifndef WINDOW_H
#define WINDOW_H
#include "glm/glm.hpp"
#include "ImguiWindow.h"
struct SDL_Window;
using SDL_GLContext = void*;
namespace CPUScheduling{
    namespace Core{
        struct WindowProperties
        {
            std::string title;
            int x, y, w, h;
            int wMin, hMin;
            int flags;
            float aspectRatio;
            glm::vec3 clearColour;
            ImguiWindowProperties imguiProps;

            WindowProperties();
        };
        class Window{
            public:
                Window();
                ~Window();
                bool Create(const WindowProperties& props);
                void Shutdown();
                void PumpEvent();
                void BeginRender();
                void EndRender();
                glm::ivec2 GetSize();
                SDL_Window* GetSDL2Window() { return mWindow; }
                SDL_GLContext GetGLContext() { return mGLContext; }
                eastl::string GetGLSLVersion() { return glsl_version; }
                glm::ivec2 GetSizeInAspectRatio(int width, int height);
        private:
            WindowProperties mWindowProperties;
                eastl::string glsl_version;
                SDL_Window* mWindow;
                SDL_GLContext mGLContext;
                ImguiWindow mImguiWindow;
        };
    } 
}
#endif