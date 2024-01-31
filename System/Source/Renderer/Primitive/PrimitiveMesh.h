#pragma once

#include <Core/Core.h>
#include <Renderer/VertexArray.h>
#include <Renderer/Buffer.h>
#include "Primitive_Triangle.h"
#include "Primitive_Rectangle.h"

namespace PreViewer {

	enum class PrimitiveType
	{
		None, 
		Triangle, Rectangle, Cube,
		Max,
	};

	class PrimitiveMesh
	{
	public:
		PrimitiveMesh();
		~PrimitiveMesh();

		const PrePtr<VertexArray>& GetVAO() const { return m_Primitive->GetVAO(); }

		void SetTriangle(
			const glm::vec2& p1 = glm::vec2(-0.5f, 0.0f),
			const glm::vec2& p2 = glm::vec2(0.5f, 0.0f),
			const glm::vec2& p3 = glm::vec2(0.0f, 0.5f));

		void SetRect(int x, int y, int cx, int cy);

	private:
		PrimitiveRectangle*	m_Primitive;
		PrimitiveType	m_Type;
		float			m_Radius;
	};

}