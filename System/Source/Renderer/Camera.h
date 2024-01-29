#pragma once


namespace PreViewer {
	enum class Color {
		R, G, B, A
	};

	enum class ProjType {
		Ortho, Perp,
	};

	class Camera
	{
	public:
		virtual void BeginRender() const = 0;
		virtual void DrawPixels(const void* pixels) = 0;
		virtual void EndRender() const = 0;
		virtual void SetViewport(int x, int y, int cx, int cy) = 0;
		virtual void SetProjMode(ProjType type = ProjType::Ortho) = 0;

		static Camera* Create();
	};

}

