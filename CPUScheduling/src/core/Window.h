#ifndef WINDOW_H
#define WINDOW_H
#include "glm/glm.hpp"
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
                glm::ivec2 GetSize();
                //static eastl::string glsl_version;
            private:
                SDL_Window* mWindow;
                SDL_GLContext mGLContext;
        };
    } 
}
#endif