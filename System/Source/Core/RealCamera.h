#pragma once

#include <Core/SnapData.h>

namespace PreViewer {

	enum class CameraAPI {
		None,
		Pylon,
		Max
	};

	// static variable
	static CameraAPI s_CameraAPI = CameraAPI::Pylon;
	
	class RealCamera
	{
	public:
		virtual void Init() = 0;
		virtual void Cleanup() = 0;
		virtual void Display() = 0;
		virtual void Snap(SnapData* out) = 0;
		virtual SnapData Snap() = 0;

		static RealCamera* Create();
	};
}
