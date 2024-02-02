#pragma once

#include <Renderer/Primitive/PrimitiveMesh.h>
#include <Core/Core.h>
#include <Renderer/Renderer2D.h>
#include <Renderer/VirtualCamera.h>
#include <Renderer/Shader.h>

namespace PreViewer {

	struct Render2DStorage
	{
		PrePtr<Shader>			Shader;
		PrePtr<VertexArray>		BasicQuadVAO;
		PrePtr<Texture2D>		BlankTexture;
	};

	class OpenGLRenderer2D : public Renderer2D
	{
	public:
		OpenGLRenderer2D(int windowWidth = 800, int windowHeight = 600);


		virtual void BeginRender(VirtualCamera* vCamera) override;
		virtual void DrawQuad2D(const glm::vec2& pos, const glm::vec2& scale, Texture2D& texture) override;
		virtual void EndRender() const override;
		virtual void SetViewport(int x, int y, int cx, int cy) override;

	protected:
		void TestRenderExample();

	private:
		VirtualCamera*		m_vCamera;
		PrimitiveMesh		m_Quad;
		Render2DStorage		m_Storage;
		unsigned int		m_Width;
		unsigned int		m_Height;
	};


}