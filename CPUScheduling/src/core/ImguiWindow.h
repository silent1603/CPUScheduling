#ifndef IMGUIWINDOW_H
#define IMGUIWINDOW_H
typedef union SDL_Event SDL_Event;
namespace CPUScheduling {
	namespace Core {
	struct ImguiWindowProperties
	{
		bool MoveFromTitleBarOnly = true;
		bool IsDockingEnabled = false;
		bool IsViewportEnabled = false;
	};

	class ImguiWindow
	{
	public:
		ImguiWindow() {}
		~ImguiWindow() {}

		void Create();
		void Shutdown();

		void HandleSDLEvent(SDL_Event& e);

		bool WantCaptureMouse();
		bool WantCaptureKeyboard();

		void BeginRender();
		void EndRender();
	};
	}
}
#endif // !IMGUIWINDOW_H
