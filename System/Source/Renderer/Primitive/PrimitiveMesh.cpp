#include <pch.h>
#include "PrimitiveMesh.h"

namespace PreViewer {

	PrimitiveMesh::PrimitiveMesh()
		:	m_Primitive(nullptr)
		,	m_Type(PrimitiveType::None)
		,	m_fRadius(0.0f)
	{/* Empty */}

	PrimitiveMesh::~PrimitiveMesh()
	{
		if (m_Primitive != nullptr)
			delete m_Primitive;
	}

	void PrimitiveMesh::SetTriangle(const glm::vec2& x1, const glm::vec2& x2, const glm::vec2& x3)
	{

	}

	void PrimitiveMesh::SetRect(float posX, float posY, float width, float height)
	{
		if (m_Primitive != nullptr)
		{
			delete m_Primitive;
			m_Primitive = nullptr;
		}
		m_Type = PrimitiveType::Rectangle;

		float rx  = static_cast<float>(posX);
		float ry  = static_cast<float>(posY);
		float rcx = static_cast<float>(width);
		float rcy = static_cast<float>(height);
		glm::vec2 tr{ rx + rcx, ry + rcy };	// top-right
		glm::vec2 br{ rx + rcx, ry - rcy };	// bottom-right
		glm::vec2 bl{ rx - rcx, ry - rcy };	// bottom-left
		glm::vec2 tl{ rx - rcx, ry + rcy };	// top-left
		m_Primitive = new PrimitiveRectangle(tr, br, bl, tl);
	}




}