#pragma once

#include "Core.h"

#include "Window.h"
#include "Mystic/LayerStack.h"
#include "Events/Event.h"
#include "Mystic/Events/ApplicationEvent.h"

#include "Mystic/ImGui/ImGuiLayer.h"

#include "Mystic/Core/Timestep.h"

#include "Renderer/Buffer.h"

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

		Window& GetWindow() { return *_window; };

		static Application& Get();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> _window;
		ImGuiLayer* _imGuiLayer;
		bool _running = true;
		LayerStack _layerStack;

		float _lastFrameTime = 0.0f;
	private:
		static Application* _instance;
	};

	//To be defined in client
	Application* CreateApplication();

}