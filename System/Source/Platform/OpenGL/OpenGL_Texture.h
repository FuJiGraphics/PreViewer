#pragma once

#include <Core/Core.h>
#include <Renderer/Texture.h>

namespace PreViewer {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		explicit OpenGLTexture2D(const int& width, const int& height);
		explicit OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual void Bind() override;
		virtual void SetData(void* data, unsigned int size) override;

		inline virtual unsigned int GetWidth() const override { return m_Width; }
		inline virtual unsigned int GetHeight() const override { return m_Height; }

	private:
		unsigned int	m_RenderID;
		int				m_Width;
		int				m_Height;
		GLenum			m_StorFormat, m_SubFormat;
	};





}