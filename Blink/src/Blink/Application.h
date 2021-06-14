#pragma once

#include "Core.h"

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

