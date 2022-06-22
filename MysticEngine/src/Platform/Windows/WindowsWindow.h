#pragma once

#include "Mystic/Window.h"
#include "Mystic/Renderer/GraphicsContext.h"

#include "GLFW/glfw3.h"

namespace Mystic {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return _data.Width; }
		inline unsigned int GetHeight() const override { return _data.Height; }

		//Window Attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { _data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void SetCursorLock(bool enabled) override;
		bool IsCursorLock() const override;

		inline virtual void* GetNativeWindow() const { return _window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();
	private:
		GLFWwindow* _window;
		GraphicsContext* _context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			bool CursorLock;

			EventCallbackFn EventCallback;
		};

		WindowData _data;
	};

}
