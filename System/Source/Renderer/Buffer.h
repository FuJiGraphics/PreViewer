#pragma once

#include <Core/Core.h>
#include "BufferLayout.h"

namespace PreViewer {

	class VertexBuffer
	{
	public:
		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		
		static VertexBuffer* Create(const float* vertices);
	};

	class IndexBuffer
	{
	public:
		virtual unsigned int GetIndexCount() const = 0;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static IndexBuffer* Create(const unsigned int* indices, unsigned int count);
	};

	class PixelBuffer
	{
	public:
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static PixelBuffer* Create(const void* pic_buf, int size);
	};

}

