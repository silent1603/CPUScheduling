#include "Application.h"
#include "SDL2/SDL.h"
#include "input/mouse.h"
#include "input/keyboard.h"
namespace CPUScheduling {
	namespace Core {
		Application& CPUScheduling::Core::Application::Instance()
		{
			static Application instance;
			return instance;
		}

		Application::~Application()
		{
		}

		bool Application::Initalize()
		{
			Log::Init();
			GetInfo();
			bool ret = false;
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			{
				APP_CORE_ERROR( "Error initializing SDL2: {}", SDL_GetError());
				
			}
			else
			{
				SDL_version version;
				SDL_VERSION(&version);
				APP_CORE_TRACE ("SDL {}.{}.{} " , (int32_t)version.major , 
					(int32_t)version.minor , (int32_t)version.patch );
				WindowProperties props;

				props.title = "HippoEditor",
				props.w = 1280;
				props.h = 720;
				props.imguiProps.IsDockingEnabled = true;

			
				if (mWindow.Create(props))
				{
					ret = true;
					mIsRunning = true;
					Input::Mouse::Initialize();
					Input::Keyboard::Initialize();
				}
			}
			if (!ret)
			{
				std::cout << "Application initialization failed. ShutDown \n";
				Shutdown();
			}
			return ret;
		}

		void Application::Shutdown()
		{
			mWindow.Shutdown();
			SDL_Quit();
		}

		void Application::GetInfo()
		{
			APP_CORE_TRACE("Platform: {}", PLATFORM_NAME);
		}

		Application::Application()
		{
			
		}


		void Application::Run()
		{
			if (Initalize())
			{
				while (mIsRunning)
				{
					mWindow.PumpEvent();
					mWindow.BeginRender();
					mWindow.EndRender();
				}
			}
			Shutdown();
		}
	}
}


void* __cdecl operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{
	return new uint8_t[size];
}