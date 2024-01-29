#pragma once

#include <Core/Core.h>

namespace PreViewer {

	class PixelBuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		static PixelBuffer* Create(const void* pic_buf, int size);
	};



}

