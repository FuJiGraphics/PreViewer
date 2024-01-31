#pragma once
#include <Core/Core.h>
#include <Renderer/VertexArray.h>

namespace PreViewer {
	class PrimitiveTriangle
	{
	public:
		PrimitiveTriangle(const glm::vec2& x1, const glm::vec2& x2, const glm::vec2& x3);
		void Bind() const;
		void UnBind() const;


		const PrePtr<VertexArray>& GetVAO() const { return m_VAO; }
	private:
		PrePtr<VertexArray> m_VAO;
	};

}