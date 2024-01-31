#include <pch.h>
#include "VertexArray.h"
#include "RendererAPI.h"
#include <Platform/OpenGL/OpenGL_VertexArray.h>

namespace PreViewer {

	VertexArray* VertexArray::Create()
	{
		switch (RendererAPI::GetType())
		{
		case RenderAPI::OpenGL: return new OpenGLVertexArray();
			// case RenderAPI::DirectX12: return nullptr;
			// case RenderAPI::Vulkan: return new VulkanAPI();
		}
		return nullptr;
	}


}