#pragma once

#include <Core/Core.h>
#include "Buffer.h"

namespace PreViewer {

	class VertexArray
	{
	protected:
		explicit VertexArray() = default;
	public:
		virtual ~VertexArray() = default;

	public:
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(const PrePtr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const PrePtr<IndexBuffer>& indexBuffer) = 0;

		virtual const IndexBuffer& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};

}  // namespace Normal