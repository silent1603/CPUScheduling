#ifndef APPLICATION_H
#define APPLICATION_H
#include "Window.h"
namespace CPUScheduling{
    namespace Core{
        
        class Application{
            public:
            static Application& Instance();
            void Run();
            inline void Quit() { mIsRunning = false; }
            inline Window& GetWindow() { return mWindow; }
        private:
            ~Application();
            [[nodiscard]] bool Initalize();
            void Shutdown();
            void GetInfo();
            Application();
      

        private:
            bool mIsRunning = false;
            Window mWindow;
        };
    }
}
#endif