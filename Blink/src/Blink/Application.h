#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Blink {

	class BLINK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in a Client
	Application* CreateApplication();
}

