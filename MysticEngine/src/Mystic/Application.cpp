#include "Application.h"

#include "Mystic/Log.h"
#include "Mystic/Events/ApplicationEvent.h"

namespace Mystic {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		MS_TRACE(e);

		while (true);
	}
}