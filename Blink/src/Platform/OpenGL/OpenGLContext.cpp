#include "blpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Blink
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		BL_CORE_ASSERT(windowHandle, "Window Handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BL_CORE_ASSERT(status, "Failed to Initialize Glad!");

		BL_CORE_INFO("OpenGL Info:");
		BL_CORE_INFO("Vendor {0}", glGetString(GL_VENDOR));
		BL_CORE_INFO("Renderer {0}", glGetString(GL_RENDERER));
		BL_CORE_INFO("Version {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}