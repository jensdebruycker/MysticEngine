#pragma once

#ifdef MS_PLATFORM_WINDOWS

extern Mystic::Application* Mystic::CreateApplication();

int main(int argc, char** argv)
{
	Mystic::Log::Init();
	MS_CORE_WARN("Initialized logger");
	int a = 5;
	MS_INFO("Hello! Var={0}", a);

	auto app = Mystic::CreateApplication();
	app->Run();
	delete app;
}

#endif