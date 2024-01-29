#include "pch.h"
#include "Camera.h"

#include "RendererAPI.h"
#include <Platform/OpenGL/OpenGL_Camera.h>

namespace PreViewer {
	Camera* Camera::Create()
	{
		switch (RendererAPI::GetType())
		{
		case RenderAPI::OpenGL: return new OpenGLCamera();
			// case RenderAPI::DirectX12: return nullptr;
			// case RenderAPI::Vulkan: return new VulkanAPI();
		}
		return nullptr;
	}

}
