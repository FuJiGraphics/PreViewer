#pragma once

#include <string>
namespace PreViewer {

	enum class RenderAPI {
		MFC,
		OpenGL,
		DirectX11,
		DirectX12,
		Vulkan
	};

	static RenderAPI g_eRenderAPI = RenderAPI::MFC;

	class RendererAPI
	{
	public:
		virtual void CreateInstance(std::string appName) = 0;

		static RendererAPI* Create();
	};


}