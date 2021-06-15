#pragma once

#ifdef BL_PLATFORM_WINDOWS
// The CreateApplication function will be created
// on the client side and this header will import it
extern Blink::Application* Blink::CreateApplication();

int main(int argc, char** argv)
{
	Blink::Log::Init();

	int a = 12;

	BL_CORE_WARN("Initialized Log!");
	BL_INFO("Hello! Var={0}", a);

	auto app = Blink::CreateApplication();
	app->Run();
	delete app;
}
#endif