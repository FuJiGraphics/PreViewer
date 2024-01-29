#include "pch.h"
#include "OpenGL_Context.h"

#include <glad/glad.h>
#include <gl/GLU.h>
#include <gl/GL.h>
#include <KHR/khrplatform.h>

namespace PreViewer {

	HGLRC OpenGLRenderAPI::GenerateContext(const CDC& dc)
	{
		HGLRC hRC = ::wglCreateContext(dc);
		::wglMakeCurrent(dc.GetSafeHdc(), hRC);
		return hRC;
	}

	void OpenGLRenderAPI::ClearColor(float r, float g, float b, float a)
	{
		::glClearColor(r, g, b, a);
	}

	void OpenGLRenderAPI::SetClearDepthValue(float val)
	{
		::glClearDepth(val);
	}

	void OpenGLRenderAPI::DepthTest(bool enabled)
	{
		(enabled) ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	}

}
