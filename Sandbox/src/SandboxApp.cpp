#include "Blink.h"

class Sandbox : public Blink::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Blink::Application* Blink::CreateApplication()
{
	return new Sandbox();
}