#include "Blink.h"

class ExampleLayer : public Blink::Layer
{
public:
	ExampleLayer()
		:Layer("Example") {}

	void OnUpdate() override
	{
		//BL_INFO("Example Layer: Update...");
	}

	void OnEvent(Blink::Event& e) override
	{
		BL_TRACE("{0}", e);
	}
};

class Sandbox : public Blink::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
		PushOverlay(new Blink::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Blink::Application* Blink::CreateApplication()
{
	return new Sandbox();
}