#pragma once

#include "Mystic/Input.h"

namespace Mystic {

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

		virtual float GetMouseOffsetXImpl() override;
		virtual float GetMouseOffsetYImpl() override;
	private:
		float prevX = 640.0f;
		float prevY = 360.0f;
		float offsetX = 0.0f;
		float offsetY = 0.0f;
	};

}