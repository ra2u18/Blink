#include "blpch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Blink
{

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:     BL_CORE_ASSERT(false, "RendererAPI::None not supported!"); return nullptr;
			case RendererAPI::OpenGL:   return new OpenGLVertexBuffer(vertices, size);

		}
		BL_CORE_ASSERT(false, "RendererAPI::Unknown renderer API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:     BL_CORE_ASSERT(false, "RendererAPI::None not supported!"); return nullptr;
			case RendererAPI::OpenGL:   return new OpenGLIndexBuffer(indices, count);
		}
		BL_CORE_ASSERT(false, "RendererAPI::Unknown renderer API!")
		return nullptr;
	}

}