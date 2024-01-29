#include <pch.h>
#include "OpenGL_Buffer.h"


namespace PreViewer {
	OpenGLPixelBuffer::OpenGLPixelBuffer(const void* pic_buf, int size)
	{
		glGenBuffersARB(1, &m_iPboID);
		glBindBufferARB(GL_PIXEL_UNPACK_BUFFER, m_iPboID);
		glBufferDataARB(GL_PIXEL_UNPACK_BUFFER, size, 0, GL_STREAM_DRAW);
		GLubyte* ptr = (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
		if (ptr != nullptr)
		{
			glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
		}
	}

	void OpenGLPixelBuffer::Bind()
	{

	}

	void OpenGLPixelBuffer::UnBind()
	{

	}

}