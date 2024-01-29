#pragma once

namespace PreViewer {

	class OpenGLRenderAPI
	{
	public:
		static HGLRC GenerateContext(const CDC& dc);
		static void ClearColor(float r, float g, float b, float a);
		static void SetClearDepthValue(float val);
		static void DepthTest(bool enabled);
	};


}