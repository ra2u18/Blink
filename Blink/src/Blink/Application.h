#pragma once
#include "Core.h"

#include "Window.h"
#include "Blink/LayerStack.h"
#include "Events/Event.h"
#include "Blink/Events/ApplicationEvent.h"
#include "Blink/Renderer/Shader.h"
#include "Blink/Renderer/Buffer.h"
#include "Blink/Renderer/VertexArray.h"

#include "Blink/ImGui/ImGuiLayer.h"

namespace Blink {

	class BLINK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		// [MANAGE EVENTS]
		// 
		// Bind the Callbacks to an OnEvent function that 
		// returns void and takes an event reference as parameter
		void OnEvent(Event& e);

		// [MANAGE LAYERSTACK]
		// 
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() const { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool m_Running = true;
		
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		unsigned int m_RendererID;

		std::shared_ptr<Window> m_Window;
		std::shared_ptr<Shader> m_Shader;

		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		std::shared_ptr<VertexArray> m_SquareVA;
		std::shared_ptr<Shader> m_Shader2;
	private:
		static Application* s_Instance;
	};

	// To be defined in a Client
	Application* CreateApplication();
}

