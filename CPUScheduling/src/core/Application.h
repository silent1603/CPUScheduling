#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"

	class Application
	{
	public:
		Application() {}
		~Application() {}

		virtual Core::WindowProperties GetWindowProperties() { return Core::WindowProperties(); }

		virtual void Initialize() {}
		virtual void Shutdown() {}

		virtual void Update() {}
		virtual void Render() {}
		virtual void ImguiRender() {}
	private:

	};

#endif