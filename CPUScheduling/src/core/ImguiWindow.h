#ifndef IMGUIWINDOW_H
#define IMGUIWINDOW_H
typedef union SDL_Event  SDL_Event;
namespace CPUScheduling {
	namespace Core {
		struct ImguiWindowProperties
		{
			bool MoveFromTitleBarOnly = true;
			bool IsDockingEnabled = false;
			bool IsViewportEnabled = false;
		};

		class ImguiWindow {
		public:
			ImguiWindow() {}
			~ImguiWindow() {}
			void Create(const ImguiWindowProperties& props);
			void Shutdown();
			void HandleSDLEvent(SDL_Event& e);
			void BeginRender();
			virtual void Render();
			bool WantCaptureMouse();
			bool WantCaptureKeyboard();
			void EndRender();
			bool show_demo_window = true;

		};
	}
}
#endif // !IMGUIWINDOW_H
