#include <pch.h>
#include "OpenGL_Renderer2D.h"
#include "OpenGL_Texture.h"
#include <Renderer/RendererAPI.h>"

namespace PreViewer {
	OpenGLRenderer2D::OpenGLRenderer2D(int windowWidth, int windowHeight)
		: m_Width(windowWidth)
		, m_Height(windowHeight)
	{
		this->SetViewport(0, 0, m_Width, m_Height);
		this->SetClearColor(0.3f, 0.3f, 0.3f);
		m_Quad.SetRect(0.0f, 0.0f, 1.0f, 1.0f);

		ShaderPaths paths;
		paths.VertPath = "D:\\Dev\\PreViewer\\System\\Source\\Renderer\\Shader\\Quad2DTex_VS.glsl";
		paths.FragPath = "D:\\Dev\\PreViewer\\System\\Source\\Renderer\\Shader\\Quad2DTex_PS.glsl";
		m_Storage.Shader.reset(Shader::Create(paths));

		unsigned char data = 0xffffff;
		m_Storage.BlankTexture.reset(Texture2D::Create(1, 1));
		m_Storage.BlankTexture->SetData(&data, sizeof(unsigned int));

		m_Storage.BasicQuadVAO = m_Quad.GetVAO();
	}
	void OpenGLRenderer2D::BeginRender(VirtualCamera* vCamera)
	{
		m_vCamera = vCamera;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer2D::DrawQuad2D(const glm::vec2& pos, const glm::vec2& scale, Texture2D& texture)
	{
		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(scale, 0.0f));

		PrePtr<Shader>& shader = m_Storage.Shader;
		shader->Bind();
		shader->SetMat4("u_Transform", transform);
		shader->SetFloat4("u_SquareColor", glm::vec4(1.0f));
		shader->SetInt("u_Texture", 0);
		texture.Bind();

		// Submit
		shader->Bind();
		shader->SetMat4("u_ViewProj", m_vCamera->GetVPMatrix());
		m_Storage.BasicQuadVAO->Bind();
		const auto& indexBuffer = m_Storage.BasicQuadVAO->GetIndexBuffer();
		::glDrawElements(GL_TRIANGLES, indexBuffer.GetIndexCount(), GL_UNSIGNED_INT, 0);

	} // DrawPixels

	void OpenGLRenderer2D::EndRender() const
	{
		// glFlush();
	}

	void OpenGLRenderer2D::SetViewport(int x, int y, int cx, int cy)
	{
		glViewport(x, y, cx, cy);
		m_Width = cx;
		m_Height = cy;
	}

	void OpenGLRenderer2D::TestRenderExample()
	{
		float vertices[] = {
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};
		unsigned int indices[] = { 0, 1, 3,
								   1, 2, 3 };

		unsigned int vao;
		unsigned int vbo;
		unsigned int ibo;

		glCreateVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glCreateBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glCreateBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, (void*)0);
		glEnableVertexAttribArray(0);

		// glUseProgram(m_ShaderProgram);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

} // namespace PreViewer