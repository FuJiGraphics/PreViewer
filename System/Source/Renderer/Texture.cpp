#include <pch.h>
#include "Texture.h"
#include <Platform/OpenGL/OpenGL_Texture.h>

namespace PreViewer {

	Texture2D * Texture2D::Create(int width, int height, void* data)
	{
		return new OpenGLTexture2D(width, height, data);
	}

	Texture2D* Texture2D::Create(int width, int height)
	{
		return new OpenGLTexture2D(width, height);
	}

	Texture2D* Texture2D::Create(const std::string& path)
	{
		return new OpenGLTexture2D(path);
	}

}