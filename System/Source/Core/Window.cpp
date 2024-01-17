#include "pch.h"
#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace PreViewer {
	Window* Window::Create(const WindowProps & props)
	{
		switch (props.Platform)
		{
		case WindowPlatform::Windows :
			return new WindowsWindow(props.Width, props.Height);
		}
	}

}