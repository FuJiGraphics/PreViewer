#include <pch.h>
#include "OpenGL_VertexArray.h"
#include "OpenGL_Buffer.h"


namespace PreViewer {

	OpenGLVertexArray::OpenGLVertexArray()
		: m_ObjectID(0)
	{
		glCreateVertexArrays(1, &m_ObjectID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_ObjectID);
	}

	void OpenGLVertexArray::Bind() const
	{
		// Bind VertexArray in the context
		glBindVertexArray(m_ObjectID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const PrePtr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_ObjectID);
		vertexBuffer->Bind();

		const auto& BufferLayout = vertexBuffer->GetLayout();
		// NR_CORE_ASSERT(BufferLayout.GetElementsSize(), "Vertex Buffer Has no layout!");

		GLuint index = 0;
		for (const auto& element : BufferLayout)
		{
			glVertexAttribPointer(index,
				(GLuint)element.Count,
				ShaderDataTypeToGLType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				(GLsizei)BufferLayout.GetStride(),
				(void*)element.Offset);
			glEnableVertexAttribArray(index);
			++index;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const PrePtr<IndexBuffer>& indexBuffer)
	{
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

}