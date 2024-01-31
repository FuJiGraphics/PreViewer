#pragma once

#include <Renderer/Primitive/PrimitiveMesh.h>
#include <Core/Core.h>
#include <Renderer/Camera.h>

namespace PreViewer {

	class OpenGLCamera : public Camera
	{
	public:
		OpenGLCamera(int windowWidth = 800, int windowHeight = 600);

		virtual void BeginRender() const override;
		virtual void DrawQuad2D() override;
		virtual void EndRender() const override;
		virtual void SetViewport(int x, int y, int cx, int cy) override;
		virtual void SetProjMode(ProjType type = ProjType::Ortho) override;

	private:
		PrimitiveMesh	m_Quad;
		unsigned int	m_ShaderProgram;
		unsigned int	m_Width;
		unsigned int	m_Height;
	};


}