#include "blpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Blink
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:     BL_CORE_ASSERT(false, "RendererAPI::None not supported!"); return nullptr;
			case RendererAPI::OpenGL:   return new OpenGLVertexArray();
		}
		BL_CORE_ASSERT(false, "RendererAPI::Unknown renderer API!");
		return nullptr;
	}

}