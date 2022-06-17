#include "mspch.h"
#include "Application.h"

#include <GLFW/glfw3.h>

#include "Renderer/Renderer.h"

namespace Mystic {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::_instance = nullptr;

	Application::Application()
	{
		MS_CORE_ASSERT(!_instance, "Application already exists");
		_instance = this;

		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		_window->SetVSync(false);

		Renderer::Init();

		_imGuiLayer = new ImGuiLayer();
		PushOverlay(_imGuiLayer);
	}

	Application::~Application() 
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		_layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = _layerStack.end(); it != _layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run() 
	{
		while (_running)
		{
			float time = (float)glfwGetTime(); //Platform::GetTime()
			Timestep timestep = time - _lastFrameTime;
			_lastFrameTime = time;

			for (Layer* layer : _layerStack)
				layer->OnUpdate(timestep);

			_imGuiLayer->Begin();
			for (Layer* layer : _layerStack)
				layer->OnImGuiRender();
			_imGuiLayer->End();

			_window->OnUpdate();
		}
	}

	Application& Application::Get()
	{
		return *_instance;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		_running = false;
		return true;
	}
}