#include "pch.h"
#include "Camera.h"

#include "RendererAPI.h"
#include <Platform/OpenGL/OpenGL_Camera.h>

namespace PreViewer {
	Camera* Camera::Create(int wWidth, int wHeight)
	{
		switch (RendererAPI::GetType())
		{
			case RenderAPI::OpenGL: return new OpenGLCamera(wWidth, wHeight);
			// case RenderAPI::DirectX12: return nullptr;
			// case RenderAPI::Vulkan: return new VulkanAPI();
		}
		return nullptr;
	}

}
