#pragma once

#ifdef BL_PLATFORM_WINDOWS
// The CreateApplication function will be created
// on the client side and this header will import it
extern Blink::Application* Blink::CreateApplication();

int main(int argc, char** argv)
{
	Blink::Log::Init();

	auto app = Blink::CreateApplication();
	app->Run();
	delete app;
}
#endif