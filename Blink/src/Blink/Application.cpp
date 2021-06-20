#include "blpch.h"
#include "Application.h"
#include "Blink/Log.h"

#include "Blink/Input.h"

#include <glad/glad.h>

namespace Blink {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	// Singleton Application
	Application* Application::s_Instance = nullptr;

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
	}

	Application::Application()
	{
		BL_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[3 * 7] = {
			-0.5, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
				{ ShaderDataType::Float4, "a_Color" },
			};
	
			m_VertexBuffer->SetLayout(layout);
		}

		const auto& layout = m_VertexBuffer->GetLayout();
		/////////////////////////////////////////////////////////////////////////////////
		/// We can write this for-loop with layout instead of (layout.GetElements() /////
		/// because we have provided the Buffer layout class with iterators /////////////
		/////////////////////////////////////////////////////////////////////////////////
		uint32_t index = 0;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		} 

		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		// Create Shader
		std::string vertexSrc = R"(
			#version 330 core
				
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
				
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application() { }
	 
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// Bind shader
			m_Shader->Bind();

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			// Update each Layer
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			// Update each Layer
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			// Application updates the window frame by frame
			m_Window->OnUpdate();
		}
	}

	// Application handles Event Callbacks
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

}
