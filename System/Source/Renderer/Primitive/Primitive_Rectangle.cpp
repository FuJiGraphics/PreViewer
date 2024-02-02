#include <pch.h>
#include "Primitive_Rectangle.h"

namespace PreViewer {

	PrimitiveRectangle::PrimitiveRectangle(
		const glm::vec2& p1,
		const glm::vec2& p2,
		const glm::vec2& p3,
		const glm::vec2& p4)
	{
		float data[] = 
		{ p1.x, p1.y, 0.0f,		1.0f, 1.0f,		// top-right
		  p2.x, p2.y, 0.0f,		1.0f, 0.0f,		// bottom-right
		  p3.x, p3.y, 0.0f,		0.0f, 0.0f,		// bottom-left
		  p4.x, p4.y, 0.0f,		0.0f, 1.0f};	// top-left

		unsigned int indices[] = {	0, 1, 3,
									1, 2, 3 };

		PrePtr<BufferLayout> layout;
		PrePtr<VertexBuffer> vbo;
		PrePtr<IndexBuffer> ibo;

		layout.reset(new BufferLayout{
			{ShaderDataType::Float3, "a_Pos"},
			{ShaderDataType::Float2, "a_TexCoord"} 
		});

		m_VAO.reset(VertexArray::Create());
		vbo.reset(VertexBuffer::Create(data, sizeof(data)));
		ibo.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(int)));
		
		vbo->SetLayout(*layout);
		m_VAO->AddVertexBuffer(vbo);
		m_VAO->SetIndexBuffer(ibo);
	}

	void PrimitiveRectangle::Bind() const
	{
		m_VAO->Bind();
	}

	void PrimitiveRectangle::UnBind() const
	{
		m_VAO->UnBind();
	}

}