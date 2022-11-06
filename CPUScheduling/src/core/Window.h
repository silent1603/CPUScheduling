#ifndef WINDOW_H
#define WINDOW_H
#include "glm/glm.hpp"
#include "imguiwindow.h"
struct SDL_Window;
using SDL_GLContext = void*;

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
                inline void SetShouldRenderToScreen(bool render) { mShouldRenderToScreen = render; }
                void Shutdown();
                void PumpEvents();
                void BeginRender();
                void EndRender();
                void Window::HandleResize(int width, int height);
                glm::ivec2 Window::GetSizeInAspectRatio(int width, int height);
                inline SDL_Window* GetSDLWindow() { return mWindow; }
                inline SDL_GLContext GetGLContext() { return mGLContext; }
                inline eastl::string GetGLSLString() { return glsl_version; }
                glm::ivec2 GetSize();
                eastl::string glsl_version;
            private:
                void RenderToScreen();
                SDL_Window* mWindow;
                SDL_GLContext mGLContext;
                ImguiWindow mImguiWindow;
                WindowProperties mWindowProperties;
                glm::vec2 mFramebufferSize;
                bool mShouldRenderToScreen;
        };
} 

#endif