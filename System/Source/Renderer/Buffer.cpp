#include "pch.h"
#include "Buffer.h"
#include "RendererAPI.h"

#include <Platform/OpenGL/OpenGL_Buffer.h>

namespace PreViewer {
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
