#pragma once

#include "Mystic/Layer.h"

#include "Mystic/Events/ApplicationEvent.h"
#include "Mystic/Events/KeyEvent.h"
#include "Mystic/Events/MouseEvent.h"

namespace Mystic{

	class MYSTIC_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float _time = 0.0f;
	};

}