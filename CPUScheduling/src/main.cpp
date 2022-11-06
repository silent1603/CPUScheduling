
#include "core/engine.h"
#include "core/Application.h"
#include "main.h"

#include "input/mouse.h"
#include "input/keyboard.h"


#include "imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Editor : public ::Application
{
private:
	bool mImguiEnabled = true;




	glm::vec2 mRectPos, mRectSize;


public:
	Core::WindowProperties GetWindowProperties() override
	{
		Core::WindowProperties props;
		props.title = "HippoEditor";
		props.w = 1280;
		props.h = 720;
		props.imguiProps.IsDockingEnabled = true;
		return props;
	}

	void Initialize() override
	{
		auto& window = Core::Engine::Instance().GetWindow();
		window.SetShouldRenderToScreen(false);
		mRectPos = glm::vec2(0.f);
		mRectSize = glm::vec2(1.f);


    }

	void Shutdown() override
	{

	}
	
	void Update() override
	{
		if (Input::Keyboard::KeyDown(::Input::INPUT_KEY_GRAVE))
		{
			mImguiEnabled = !mImguiEnabled;
			auto& window = Core::Engine::Instance().GetWindow();
			window.SetShouldRenderToScreen(!mImguiEnabled);
		}
	}

	void Render() override
	{
	}

	void ImguiRender() override
	{
		if (mImguiEnabled)
		{
			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
			ImGui::ShowDemoWindow();
		}
	}

	
};

::Application* CreateApp()
{
	return new Editor();
}
