#include <Mystic.h>

class ExampleLayer : public Mystic::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		MS_INFO("ExampleLayer::Update");
	}

	void OnEvent(Mystic::Event& event) override
	{
		MS_TRACE("{0}", event);
	}
};

class Sandbox : public Mystic::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Mystic::Application* Mystic::CreateApplication()
{
	return new Sandbox;
}
