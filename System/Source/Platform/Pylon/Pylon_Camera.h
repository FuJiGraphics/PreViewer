#pragma once

// Pylon Libries
#include <Pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#	include <pylon/PylonGUI.h>
#endif
#include <pylon/ImageFormatConverter.h>
#include "Pylon_Configurator.h"
#include <Core/RealCamera.h>
#include <vector>

namespace PreViewer {
	class PylonCamera final : public RealCamera
	{
	public:
		virtual void Init() override;
		virtual void Cleanup() override;
		virtual void Display() override;
		virtual void Snap(SnapData* out) override;
		virtual SnapData Snap() override;
		
	protected:
		Pylon::CPylonImage PylonCamera::Mono8bitToBMP24(const Pylon::CGrabResultPtr& grab);
		void ToSnapData(SnapData* out, const Pylon::CGrabResultPtr& ptrGrab);

	private:
		int		 m_MaxBufferCount = 10;
		BOOL	 m_OnCapture	  = FALSE;

		Pylon::CInstantCamera	m_PylonCamera;
		Pylon::CGrabResultPtr*	m_TempGrabData = nullptr;
	};
}

