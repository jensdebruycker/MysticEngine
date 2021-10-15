#pragma once

#include "Core.h"

#include "Window.h"
#include "Mystic/LayerStack.h"
#include "Events/Event.h"
#include "Mystic/Events/ApplicationEvent.h"


namespace Mystic {

	class MYSTIC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> _window;
		bool _running = true;
		LayerStack _layerStack;
	};

	//To be defined in client
	Application* CreateApplication();

}
