#include "pch.h"
#include "Renderer2D.h"

#include "RendererAPI.h"
#include <Platform/OpenGL/OpenGL_Renderer2D.h>

namespace PreViewer {

	void Renderer2D::SetClearColor(float r, float g, float b, float a)
	{
		RendererAPI::ClearColor(r, g, b, a);
	}

	Renderer2D* Renderer2D::Create(int wWidth, int wHeight)
	{
		switch (RendererAPI::GetType())
		{
			case RenderAPI::OpenGL: return new OpenGLRenderer2D(wWidth, wHeight);
			// case RenderAPI::DirectX12: return nullptr;
			// case RenderAPI::Vulkan: return new VulkanAPI();
		}
		return nullptr;
	}

}
