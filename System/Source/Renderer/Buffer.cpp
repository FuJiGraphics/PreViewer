#include "pch.h"
#include "Buffer.h"
#include "RendererAPI.h"

#include <Platform/OpenGL/OpenGL_Buffer.h>

namespace PreViewer {

	VertexBuffer * VertexBuffer::Create(const float * vertices)
	{
		switch (RendererAPI::GetType())
		{
		case RenderAPI::OpenGL: return new OpenGLVertexBuffer(vertices);
			// case RenderAPI::DirectX12: return nullptr;
			// case RenderAPI::Vulkan: return new VulkanAPI();
		}
		return nullptr;
	}

	IndexBuffer * IndexBuffer::Create(const unsigned int* indices, unsigned int count)
	{
		switch (RendererAPI::GetType())
		{
		case RenderAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
			// case RenderAPI::DirectX12: return nullptr;
			// case RenderAPI::Vulkan: return new VulkanAPI();
		}
		return nullptr;
	}

	PixelBuffer* PixelBuffer::Create(const void* pic_buf, int size)
	{
		switch (RendererAPI::GetType())
		{
			case RenderAPI::OpenGL: return new OpenGLPixelBuffer(pic_buf, size);
			// case RenderAPI::DirectX12: return nullptr;
			// case RenderAPI::Vulkan: return new VulkanAPI();
		}
		return nullptr;
	}
}
