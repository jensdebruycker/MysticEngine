#pragma once

#include "Core.h"
#include "Events/Event.h"

#include "Mystic/Core/Timestep.h"

namespace Mystic {

	class MYSTIC_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {};

		inline const std::string& GetName() const { return _debugName; }
	protected:
		std::string _debugName;
	};

}
