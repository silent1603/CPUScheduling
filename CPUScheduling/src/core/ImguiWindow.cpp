#include "ImguiWindow.h"
#include "Engine.h"
#include "SDL2/SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

namespace Core {
		void ImguiWindow::Create()
		{
			IMGUI_CHECKVERSION();

			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO();
			io.ConfigWindowsMoveFromTitleBarOnly = true;
		
			{
				io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			}
			
			{
				io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			}

			auto& window = Engine::Instance().GetWindow();
			ImGui_ImplSDL2_InitForOpenGL(window.GetSDLWindow(), window.GetGLContext());
			ImGui_ImplOpenGL3_Init(window.GetGLSLString().c_str());
		}

		void ImguiWindow::Shutdown()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplSDL2_Shutdown();
			ImGui::DestroyContext();
		}

		void ImguiWindow::HandleSDLEvent(SDL_Event& e)
		{
			ImGui_ImplSDL2_ProcessEvent(&e);
		}

		void ImguiWindow::BeginRender()
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame(Engine::Instance().GetWindow().GetSDLWindow());
			ImGui::NewFrame();
		}

		void ImguiWindow::EndRender()
		{
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				auto& window = Engine::Instance().GetWindow();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				SDL_GL_MakeCurrent(window.GetSDLWindow(), window.GetGLContext());
			}
		}

		bool ImguiWindow::WantCaptureMouse()
		{
			return ImGui::GetIO().WantCaptureMouse;
		}

		bool ImguiWindow::WantCaptureKeyboard()
		{
			return ImGui::GetIO().WantCaptureKeyboard;
		}
}
