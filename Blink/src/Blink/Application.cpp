#include "blpch.h"
#include "Application.h"

#include "Blink/Events/ApplicationEvent.h"
#include "Blink/Log.h"

namespace Blink {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);
		BL_TRACE(e);

		while (true);
	}

}

