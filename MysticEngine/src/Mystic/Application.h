#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Mystic/Events/ApplicationEvent.h"

#include "Window.h"

namespace Mystic {

	class MYSTIC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> _window;
		bool _running;
	};

	//To be defined in client
	Application* CreateApplication();

}
