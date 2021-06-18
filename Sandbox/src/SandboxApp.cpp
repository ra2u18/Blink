#include "Blink.h"

#include "imgui/imgui.h"

class ExampleLayer : public Blink::Layer
{
public:
	ExampleLayer()
		:Layer("Example") {}

	void OnUpdate() override
	{
		if (Blink::Input::IsKeyPressed(BL_KEY_TAB))
			BL_INFO("Tab Key Pressed!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Blink::Event& e) override
	{
		if (e.GetEventType() == Blink::EventType::KeyPressed)
		{
			Blink::KeyPressedEvent& event = static_cast<Blink::KeyPressedEvent&>(e);
			BL_TRACE("{0}", (char)event.GetKeyCode());
		}
	}
};

class Sandbox : public Blink::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
	}

	~Sandbox()
	{

	}
};

Blink::Application* Blink::CreateApplication()
{
	return new Sandbox();
}