#ifndef Engine_H
#define Engine_H
#include "Window.h"
#include "Application.h"
namespace Core
    {

        class Engine
        {
        public:
            static Engine &Instance();
            void Run(Application *app);
            inline Application &GetApp() { return *mApp; }
            inline void Quit() { mIsRunning = false; }
            inline Window &GetWindow() { return mWindow; }

        private:
            ~Engine();
            [[nodiscard]] bool Initalize();
            void Shutdown();
            void GetInfo();
            Engine();
            void Update();
            void Render();

        private:
            bool mIsRunning = false;
            Window mWindow;
            Application *mApp;
        };
    }

#endif