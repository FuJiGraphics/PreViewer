#include <pch.h>
#include "OpenGL_Camera.h"
#include "OpenGL_RendererAPI.h"

namespace PreViewer {
	OpenGLCamera::OpenGLCamera(int windowWidth, int windowHeight)
		: m_Width(windowWidth)
		, m_Height(windowHeight)
	{
		this->SetViewport(0, 0, m_Width, m_Height);
		m_Quad.SetRect(0, 0, m_Width, m_Height);


		const char *vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Complie the vertex shader
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);


		const char *fragmentShaderSource = R"(#version 330 core
			out vec4 FragColor;
			void main()
			{
				FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
			})";

		// Complie the fragment shader
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		// Created the Shader Program
		m_ShaderProgram = glCreateProgram();

		// Attach and Link the shaders
		glAttachShader(m_ShaderProgram, vertexShader);
		glAttachShader(m_ShaderProgram, fragmentShader);
		glLinkProgram(m_ShaderProgram);
		glUseProgram(m_ShaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	void OpenGLCamera::BeginRender() const
	{
	}

	void OpenGLCamera::DrawQuad2D()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		OpenGLRenderAPI::DrawIndexed(*m_Quad.GetVAO());

	} // DrawPixels

	void OpenGLCamera::EndRender() const
	{
		glFlush();
	}

	void OpenGLCamera::SetViewport(int x, int y, int cx, int cy)
	{
		glViewport(x, y, cx, cy);
		m_Width = cx;
		m_Height = cy;
	}

	void OpenGLCamera::SetProjMode(ProjType type)
	{

	}

}