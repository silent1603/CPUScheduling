#include "Engine.h"
#include "SDL2/SDL.h"
#include "input/mouse.h"
#include "input/keyboard.h"

namespace Core
	{
		Engine& Core::Engine::Instance()
		{
			static Engine instance;
			return instance;
		}

		Engine::~Engine()
		{
		}

		bool Engine::Initalize()
		{
			bool ret = false;
			Log::Init();
			GetInfo();
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			{
				APP_CORE_ERROR("Error initializing SDL2: {}", SDL_GetError());
			}
			else
			{
				SDL_version version;
				SDL_VERSION(&version);
				APP_CORE_TRACE("SDL {}.{}.{} ", (int32_t)version.major,
							   (int32_t)version.minor, (int32_t)version.patch);
				WindowProperties props = mApp->GetWindowProperties();
				if (mWindow.Create(props))
				{
					ret = true;
					mIsRunning = true;
					Input::Mouse::Initialize();
					Input::Keyboard::Initialize();

					// Initialize Client
					mApp->Initialize();
				}
			}
			if (!ret)
			{
				std::cout << "Engine initialization failed. ShutDown \n";
				Shutdown();
			}
			return ret;
		}

		void Engine::Shutdown()
		{

			mIsRunning = false;
			mApp->Shutdown();
			mWindow.Shutdown();
			SDL_Quit();
		}

		void Engine::GetInfo()
		{
			APP_CORE_TRACE("Platform: {}", PLATFORM_NAME);
		}

		Engine::Engine()
		{
		}

		void Engine::Run(Application* app)
		{
			if (mApp)
			{
				return;
			}

			mApp = app;
			bool ret = false;
			if (Initalize())
			{
				while (mIsRunning)
				{
					Update();
					Render();
				}
			}
			Shutdown();
		}

		void Engine::Update()
		{
			mWindow.PumpEvents();
			mApp->Update();
		}

		void Engine::Render()
		{
			mWindow.BeginRender();
			mApp->Render();
			mWindow.EndRender();
		}
}


void *__cdecl operator new[](size_t size, const char *name, int flags, unsigned debugFlags, const char *file, int line)
{
	return new uint8_t[size];
}