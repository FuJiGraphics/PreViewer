#include "pch.h"
#include "RendererAPI.h"

#include <Platform/OpenGL/OpenGL_RendererAPI.h>


namespace PreViewer {
	
	HGLRC RendererAPI::GenerateRC(const CDC& dc)
	{
		switch (RendererAPI::GetType())
		{
			case RenderAPI::OpenGL: return OpenGLRenderAPI::GenerateContext(dc);
			// case RenderAPI::DirectX12: return nullptr;
			// case RenderAPI::Vulkan: return new VulkanAPI();
		}
		return 0;
	}

	void RendererAPI::ClearColor(float r, float g, float b, float a)
	{
		switch (RendererAPI::GetType())
		{
			case RenderAPI::OpenGL: OpenGLRenderAPI::ClearColor(r, g, b, a);
			// case RenderAPI::DirectX12: return nullptr;
			// case RenderAPI::Vulkan: return new VulkanAPI();
		}
	}

	void RendererAPI::SetClearDepthValue(float val)
	{
		switch (RendererAPI::GetType())
		{
			case RenderAPI::OpenGL: OpenGLRenderAPI::SetClearDepthValue(val);
			// case RenderAPI::DirectX12: return nullptr;
			// case RenderAPI::Vulkan: return new VulkanAPI();
		}
	}

	void RendererAPI::DepthTest(bool enabled)
	{
		switch (RendererAPI::GetType())
		{
			case RenderAPI::OpenGL: return OpenGLRenderAPI::DepthTest(enabled);
			// case RenderAPI::DirectX12: return nullptr;
			// case RenderAPI::Vulkan: return new VulkanAPI();
		}
	}
	void RendererAPI::DrawIndexed(const VertexArray& vao)
	{
		switch (RendererAPI::GetType())
		{
		case RenderAPI::OpenGL: return OpenGLRenderAPI::DrawIndexed(vao);
			// case RenderAPI::DirectX12: return nullptr;
			// case RenderAPI::Vulkan: return new VulkanAPI();
		}
	}
} // namespace PreViewer 