#include "pch.h"
#include "RendererAPI.h"

namespace PreViewer {
	RendererAPI* RendererAPI::Create()
	{
		switch (g_eRenderAPI) 
		{
		//case RenderAPI::MFC: return new CDCApi();
		//	break;
		//case RenderAPI::OpenGL: return nullptr;
		//	break;
		//case RenderAPI::DirectX12: return nullptr;
		//	break;
		//case RenderAPI::Vulkan: return new VulkanAPI();
		//	break;
		//Default:
			
		}
		
		return nullptr;
	}

}
