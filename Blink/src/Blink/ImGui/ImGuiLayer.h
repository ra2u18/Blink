#pragma once

#include "Blink/Layer.h"
#include "Blink/Events/ApplicationEvent.h"
#include "Blink/Events/MouseEvent.h"
#include "Blink/Events/KeyEvent.h"

namespace Blink
{
	class BLINK_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override {};
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}
