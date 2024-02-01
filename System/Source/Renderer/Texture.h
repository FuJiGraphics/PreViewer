#pragma once

#include <Core/Core.h>

namespace PreViewer {

	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Bind() = 0;

		inline virtual unsigned int GetWidth() const = 0;
		inline virtual unsigned int GetHeight() const = 0;
	};


	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;

		virtual void Bind() = 0;
		virtual void SetData(void* data, unsigned int size) = 0;

		inline virtual unsigned int GetWidth() const = 0;
		inline virtual unsigned int GetHeight() const = 0;

		static Texture2D* Create(int width, int height);
		static Texture2D* Create(const std::string& path);
	};

} // namespace Normal