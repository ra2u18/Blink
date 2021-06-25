#include "blpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Blink
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Blink::ShaderDataType::Float:	   return GL_FLOAT;
			case Blink::ShaderDataType::Float2:    return GL_FLOAT;
			case Blink::ShaderDataType::Float3:    return GL_FLOAT;
			case Blink::ShaderDataType::Float4:    return GL_FLOAT;
			case Blink::ShaderDataType::Mat3:      return GL_FLOAT;
			case Blink::ShaderDataType::Mat4:      return GL_FLOAT;
			case Blink::ShaderDataType::Int:       return GL_INT;
			case Blink::ShaderDataType::Int2:      return GL_INT;
			case Blink::ShaderDataType::Int3:      return GL_INT;
			case Blink::ShaderDataType::Int4:      return GL_INT;
			case Blink::ShaderDataType::Bool:      return GL_BOOL;
		}

		BL_CORE_ASSERT(false, "ShaderDataTypeToOpenGLBaseType: Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		BL_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		/////////////////////////////////////////////////////////////////////////////////
		/// We can write this for-loop with layout instead of (layout.GetElements() /////
		/// because we have provided the Buffer layout class with iterators /////////////
		/////////////////////////////////////////////////////////////////////////////////
		const auto& layout = vertexBuffer->GetLayout();
		uint32_t index = 0;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
}