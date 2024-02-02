#include "pch.h"
#include "OpenGL_RendererAPI.h"

namespace PreViewer {

	HGLRC OpenGLRendererAPI::GenerateContext(const CDC& dc)
	{
		HGLRC hRC = ::wglCreateContext(dc);
		::wglMakeCurrent(dc.GetSafeHdc(), hRC);
		return hRC;
	}

	void OpenGLRendererAPI::ClearColor(float r, float g, float b, float a)
	{
		::glClearColor(r, g, b, a);
	}

	void OpenGLRendererAPI::SetClearDepthValue(float val)
	{
		::glClearDepth(val);
	}

	void OpenGLRendererAPI::DepthTest(bool enabled)
	{
		(enabled) ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::DrawIndexed(const VertexArray& vao)
	{
		const auto& indexBuffer = vao.GetIndexBuffer();
		vao.Bind();
		::glDrawElements(GL_TRIANGLES, indexBuffer.GetIndexCount(), GL_UNSIGNED_INT, 0);
	}

}
