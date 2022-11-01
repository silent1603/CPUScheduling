#include "ImguiWindow.h"
#include "core/Application.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "SDL2/SDL.h"
namespace CPUScheduling
{
	namespace Core {
		void ImguiWindow::Create(const ImguiWindowProperties& props)
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigWindowsMoveFromTitleBarOnly = props.MoveFromTitleBarOnly;
			if (props.IsDockingEnabled)
			{
				io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			}
			if (props.IsViewportEnabled)
			{
				io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			}

			auto& window = Application::Instance().GetWindow();
			ImGui_ImplSDL2_InitForOpenGL(window.GetSDL2Window(), window.GetGLContext());
			ImGui_ImplOpenGL3_Init(window.GetGLSLVersion().c_str());
		}
		void ImguiWindow::Shutdown()
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplSDL2_Shutdown();
			ImGui::DestroyContext();
		}

		bool ImguiWindow::WantCaptureMouse()
		{
			return ImGui::GetIO().WantCaptureMouse;
		}

		bool ImguiWindow::WantCaptureKeyboard()
		{
			return ImGui::GetIO().WantCaptureKeyboard;
		}

		void ImguiWindow::HandleSDLEvent(SDL_Event& e)
		{
			ImGui_ImplSDL2_ProcessEvent(&e);
		}

		void ImguiWindow::BeginRender()
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame(Application::Instance().GetWindow().GetSDL2Window());
			ImGui::NewFrame();
		}

		void ImguiWindow::Render()
		{
			 ImGui::ShowDemoWindow(); 
		}

		void ImguiWindow::EndRender()
		{
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				auto& window = Application::Instance().GetWindow();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				SDL_GL_MakeCurrent(window.GetSDL2Window(), window.GetGLContext());
			}
		}
	}
}