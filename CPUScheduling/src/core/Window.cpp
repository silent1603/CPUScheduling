#include "Engine.h"
#include "glad/glad.h"
#include "SDL2/SDL.h"
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "Window.h"
#include "input/mouse.h"
#include "input/keyboard.h"

namespace Core {

		WindowProperties::WindowProperties()
		{
			title = "HippoApp";
			x = SDL_WINDOWPOS_CENTERED;
			y = SDL_WINDOWPOS_CENTERED;
			w = 1920;
			h = 1080;
			wMin = 320;
			hMin = 180;
			flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
			aspectRatio = 16.f / 9.f;
			clearColour = glm::vec3(
				static_cast<float>(0x64) / static_cast<float>(0xFF),
				static_cast<float>(0x95) / static_cast<float>(0xFF),
				static_cast<float>(0xED) / static_cast<float>(0xFF));
		}

		Window::Window() : mWindow(nullptr)
		{
		}

		Window::~Window()
		{
			if (mWindow)
			{
				Shutdown();
			}
		}

		bool Window::Create(const WindowProperties& props)
		{
			mWindowProperties = props;
			mWindow = SDL_CreateWindow(props.title.c_str(), props.x, props.y, props.w, props.h, props.flags);
			if (!mWindow)
			{
				APP_CORE_ERROR("Error creating window: {}", SDL_GetError());
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


        void Window::PumpEvents()
        {
            SDL_Event e;
            while (SDL_PollEvent(&e))
            {
                switch (e.type)
                {
                case SDL_QUIT:
                    Engine::Instance().Quit();
                default:
                    break;
                }
				mImguiWindow.HandleSDLEvent(e);
			}
			if (!mImguiWindow.WantCaptureMouse())
			{
				Input::Mouse::Update();
			}
			if (!mImguiWindow.WantCaptureKeyboard())
			{
				Input::Keyboard::Update();
			}
        }

		void Window::Shutdown()
		{
			SDL_DestroyWindow(mWindow);
			mWindow = nullptr;
		}

		glm::ivec2 Window::GetSize()
		{
			int w, h;
			SDL_GetWindowSize(mWindow, &w, &h);
			return glm::ivec2(w, h);
		}

		void Window::HandleResize(int width, int height)
		{
			mFramebufferSize = GetSizeInAspectRatio(width, height);
		}

		glm::ivec2 Window::GetSizeInAspectRatio(int width, int height)
		{
			int framebufferWidth = (int)(height * mWindowProperties.aspectRatio);
			int framebufferHeight = (int)(width * (1.f / mWindowProperties.aspectRatio));

			if (height >= framebufferHeight)
			{
				framebufferWidth = width;
			}
			else
			{
				framebufferHeight = height;
			}

			return { framebufferWidth, framebufferHeight };
		}


		void Window::BeginRender()
		{
		}

        void Window::EndRender()
        {
			if (mShouldRenderToScreen)
			{
				RenderToScreen();
			}
            mImguiWindow.BeginRender();
			Engine::Instance().GetApp().ImguiRender();
            mImguiWindow.EndRender();
            SDL_GL_SwapWindow(mWindow);
        }

		void Window::RenderToScreen()
		{

		}

}

