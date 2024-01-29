#pragma once

namespace PreViewer {

	enum class RenderAPI {
		MFC,
		OpenGL,
		DirectX11,
		DirectX12,
		Vulkan
	};

	static RenderAPI s_RenderAPI = RenderAPI::MFC;

	class RendererAPI
	{
	public:
		inline static RenderAPI GetType() { return s_RenderAPI; };
		static HGLRC GenerateRC(const CDC& dc);
		static void ClearColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);
		static void SetClearDepthValue(float val = 1.0f);
		static void DepthTest(bool enabled = true);
	};


}