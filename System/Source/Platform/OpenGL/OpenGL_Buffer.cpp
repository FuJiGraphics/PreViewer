#include <pch.h>
#include "OpenGL_Buffer.h"


namespace PreViewer {

//------------------------------- Vertex Buffer Line -------------------------------//

	OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, unsigned int size)
		: m_ObjectID(0)
	{
		glCreateBuffers(1, &m_ObjectID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ObjectID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_ObjectID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ObjectID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

//------------------------------- Pixel Buffer Line -------------------------------// 

	OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int* indices, unsigned int count)
		: m_IndexCount(count)
		, m_ObjectID(0)
	{
		glCreateBuffers(1, &m_ObjectID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ObjectID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_ObjectID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ObjectID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


//------------------------------- Pixel Buffer Line -------------------------------// 

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

	void OpenGLPixelBuffer::Bind() const
	{

	}

	void OpenGLPixelBuffer::UnBind() const
	{

	}
}