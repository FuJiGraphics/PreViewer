#pragma once
#include <string>

namespace PreViewer {

	enum class WindowPlatform 
	{
		None,
		Windows,
		Linux,
		MacOS,
		Max
	};

	struct WindowProps
	{
		WindowPlatform Platform;
		std::string Title;
		int Width;
		int Height;
		WindowProps(
			const WindowPlatform platform = WindowPlatform::Windows,
			const std::string& title = "PreViewer",
			int width = 1280,
			int height = 720)
			: Platform(platform), Title(title), Width(width), Height(height)
		{ }
	};

	class Window
	{
	protected:
		explicit Window() = default;
	public:
		virtual ~Window() = default;

	public:
		virtual void OnUpdate() = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual void SetWindowSize(float width, float height) = 0;

		// Create Function is need to define into the Platform
		static Window* Create(const WindowProps& props = WindowProps());

	private:
		int m_iWidth;
		int m_iHeight;
	};


}