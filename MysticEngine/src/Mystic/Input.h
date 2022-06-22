#pragma once

#include "Mystic/Core.h"

namespace Mystic{

	class MYSTIC_API Input
	{
	public:
		/*virtual bool IsKeyPressed(int keycode) = 0;

		virtual bool IsMouseButtonPressed(int button) = 0;
		virtual std::pair<float, float> GetMousePosition() = 0;
		virtual float GetMouseX() = 0;
		virtual float GetMouseY() = 0;*/

		inline static bool IsKeyPressed(int keycode) { return _instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return _instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return _instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return _instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return _instance->GetMouseYImpl(); }

		inline static float GetMouseOffsetX() { return _instance->GetMouseOffsetXImpl(); }
		inline static float GetMouseOffsetY() { return _instance->GetMouseOffsetYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

		virtual float GetMouseOffsetXImpl() = 0;
		virtual float GetMouseOffsetYImpl() = 0;
	private:
		static Input* _instance;
	};

}