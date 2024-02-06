#pragma once
#include "VirtualCamera.h"
#include "Texture.h"

namespace PreViewer {
	enum class Color {
		R, G, B, A
	};

	class Renderer2D
	{
	public:
		virtual void BeginRender(VirtualCamera* vCamera) = 0;
		virtual void DrawQuad2D(const DrawInfo& drawInfo, Texture2D& texture, BOOL flip = FALSE) = 0 ;
		virtual void DrawQuad2D(const glm::vec2& pos, const glm::vec2& scale, Texture2D& texture, BOOL flip = FALSE) = 0;
		virtual void EndRender() const = 0;
		virtual void SetGaussian(unsigned int width, unsigned int height, float offset) = 0;

		virtual void SetClearColor(float r, float g, float b, float a = 0.0f);
		virtual void SetViewport(int x, int y, int cx, int cy) = 0;

		static Renderer2D* Create(int wWidth, int wHeight);
	};

}

