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

using namespace Pylon;

namespace PreViewer {
	class PylonCamera final : public RealCamera
	{
	public:
		virtual void Init() override;
		virtual void Cleanup() override;
		virtual void Display() override;
		virtual BOOL isSnapSuccessful() override;
		virtual void Snap(SnapData* out) override;
		virtual SnapData Snap() override;
		virtual PrePtr<SnapData> SharedSnap() override;
		
	protected:
		bool PylonCamera::Mono8bitToBMP24(CPylonImage* dst, const CGrabResultPtr& src);
		void ToSnapData(SnapData* out, const CGrabResultPtr& ptrGrab);

	private:
		int		 m_MaxBufferCount = 10;
		BOOL	 m_OnCapture	  = FALSE;

		Pylon::CInstantCamera	m_PylonCamera;
		Pylon::CGrabResultPtr*	m_TempGrabData = nullptr;
	};
}

