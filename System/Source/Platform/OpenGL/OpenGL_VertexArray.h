#pragma once
#include <Core/Core.h>
#include <Renderer/VertexArray.h>

namespace PreViewer {


	class OpenGLVertexArray : public VertexArray
	{
	public:
		explicit OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

	public:
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const PrePtr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const PrePtr<IndexBuffer>& indexBuffer) override;

		virtual const IndexBuffer& GetIndexBuffer() const override { return *m_IndexBuffer; }

	private:
		std::vector<PrePtr<VertexBuffer>> m_VertexBuffers;
		PrePtr<IndexBuffer> m_IndexBuffer;

		unsigned int m_ObjectID;
	};

}