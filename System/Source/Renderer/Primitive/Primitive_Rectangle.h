#pragma once
#include <Core/Core.h>
#include <Renderer/VertexArray.h>

namespace PreViewer {
	class PrimitiveRectangle
	{
	public:
		PrimitiveRectangle(
			const glm::vec2& tr, 
			const glm::vec2& br, 
			const glm::vec2& bl, 
			const glm::vec2& tl);

		void Bind() const;
		void UnBind() const;

		const PrePtr<VertexArray>& GetVAO() const { return m_VAO; }
	private:
		PrePtr<VertexArray> m_VAO;
	};

}