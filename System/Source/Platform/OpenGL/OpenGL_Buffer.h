#pragma once

#include <Renderer/Buffer.h>

namespace PreViewer {


	class OpenGLVertexBuffer final : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const float* vertices);

		inline virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		inline virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

		virtual void Bind() const override;
		virtual void UnBind() const override;

	private:
		BufferLayout	m_Layout;
		unsigned int	m_ObjectID;
	};

	class OpenGLIndexBuffer final : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const unsigned int* indices, unsigned int count);

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual unsigned int GetIndexCount() const override { return m_IndexCount; }
	private:
		unsigned int	m_IndexCount;
		unsigned int	m_ObjectID;
	};

	class OpenGLPixelBuffer final : public PixelBuffer
	{
	public:
		OpenGLPixelBuffer(const void* pic_buf, int size);

		virtual void Bind() const override;
		virtual void UnBind() const override;

	private:
		unsigned int m_iPboID;
	};

}