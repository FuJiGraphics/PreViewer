#pragma once

#include <Core/Core.h>
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
		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;

		virtual void Init() = 0;
		virtual void Cleanup() = 0;
		virtual void Display() = 0;
		virtual BOOL isOpen() = 0;
		virtual BOOL isSnapSuccessful() = 0;

		virtual SnapData Snap() = 0;
		virtual PrePtr<SnapData> SharedSnap() = 0;

		static RealCamera* Create();
	};
}
