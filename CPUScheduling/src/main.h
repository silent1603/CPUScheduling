#pragma once

#include "Core/engine.h"
#include "Core/Application.h"

// To be implemented in client app
// The client returns a pointer to an instance of a class derived from hippo::App
// The ownership of the returned pointer belongs to Hippo, and will be managed as such
//
// Example:
// class ClientApp : public hippo::App {};
// hippo::App* CreateApp() { return new ClientApp(); }

::Application* CreateApp();

int main()
{
	::Application* app = CreateApp();
	::Core::Engine::Instance().Run(app);
	delete app;
	return 0;
}