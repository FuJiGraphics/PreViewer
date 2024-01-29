#pragma once

#include <Core/Core.h>
#include <Renderer/Camera.h>

namespace PreViewer {

	class OpenGLCamera : public Camera
	{
	public:
		virtual void BeginRender() const override;
		virtual void DrawPixels(const void* pixels) override;
		virtual void EndRender() const override;
		virtual void SetViewport(int x, int y, int cx, int cy) override;
		virtual void SetProjMode(ProjType type = ProjType::Ortho) override;
	};


}