#pragma once
#include <Core/Core.h>
#include <Renderer/VertexArray.h>

namespace PreViewer {
	class PrimitiveRectangle
	{
	public:
		PrimitiveRectangle(
			const glm::vec2& p1, 
			const glm::vec2& p2, 
			const glm::vec2& p3, 
			const glm::vec2& p4);

		void Bind() const;
		void UnBind() const;

		const PrePtr<VertexArray>& GetVAO() const { return m_VAO; }
	private:
		PrePtr<VertexArray> m_VAO;
	};

}