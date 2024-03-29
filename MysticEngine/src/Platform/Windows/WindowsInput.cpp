#include "mspch.h"
#include "WindowsInput.h"

#include "GLFW/glfw3.h"
#include "Mystic/Application.h"

namespace Mystic {

	Input* Input::_instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}

	float WindowsInput::GetMouseOffsetXImpl()
	{
		offsetX = prevX - GetMouseXImpl();
		prevX = GetMouseXImpl();
		return offsetX;
	}

	float WindowsInput::GetMouseOffsetYImpl()
	{
		offsetY = prevY - GetMouseYImpl();
		prevY = GetMouseYImpl();
		return offsetY;
	}

}