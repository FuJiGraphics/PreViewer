#include <pch.h>
#include "PrimitiveMesh.h"

namespace PreViewer {

	PrimitiveMesh::PrimitiveMesh()
		:m_Radius(0.0f)
		,m_Type(PrimitiveType::None)
	{/* Empty */}

	PrimitiveMesh::~PrimitiveMesh()
	{
		if (m_Primitive != nullptr)
			delete m_Primitive;
	}

	void PrimitiveMesh::SetTriangle(const glm::vec2& x1, const glm::vec2& x2, const glm::vec2& x3)
	{

	}

	void PrimitiveMesh::SetRect(int x, int y, int cx, int cy)
	{
		m_Type = PrimitiveType::Rectangle;

		float rx  = static_cast<float>(x);
		float ry  = static_cast<float>(y);
		float rcx = static_cast<float>(cx);
		float rcy = static_cast<float>(cy);
		glm::vec2 p1{ rx, ry };
		glm::vec2 p2{ rx + rcx, ry };
		glm::vec2 p3{ rx + rcx, ry + rcy };
		glm::vec2 p4{ rx, ry + rcy };
		m_Primitive = new PrimitiveRectangle(p1, p2, p3, p4);
	}




}