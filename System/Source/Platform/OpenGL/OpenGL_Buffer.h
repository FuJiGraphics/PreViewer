#pragma once

#include <Renderer/Buffer.h>
#include <glad/glad.h>

namespace PreViewer {
	class OpenGLPixelBuffer : public PixelBuffer
	{
	public:
		OpenGLPixelBuffer(const void* pic_buf, int size);

		virtual void Bind() override;
		virtual void UnBind() override;

	private:
		unsigned int m_iPboID;
	};

}