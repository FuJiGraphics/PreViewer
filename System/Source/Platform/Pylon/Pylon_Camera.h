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
		inline virtual unsigned int GetWidth() override { return m_Width; }
		inline virtual unsigned int GetHeight() override { return m_Height; }

		virtual void Init() override;
		virtual void Cleanup() override;
		virtual void Display() override;
		virtual BOOL isOpen() override;
		virtual BOOL isSnapSuccessful() override;
		virtual SnapData Snap() override;
		virtual PrePtr<SnapData> SharedSnap() override;

	protected:
		BOOL Grab(PrePtr<CGrabResultPtr>* out = nullptr);
		bool PylonCamera::Mono8bitToBMP24(CPylonImage* dst, const CGrabResultPtr& src);
		void ToSnapData(SnapData* out, const CGrabResultPtr& ptrGrab);

	private:
		int		m_Width;
		int		m_Height;
		int		m_MaxBufferCount;
		BOOL	m_OnCapture;
		BOOL	m_Initialized;

		Pylon::IPylonDevice*	m_PylonDevice;
		Pylon::CInstantCamera	m_PylonCamera;
		PrePtr<CGrabResultPtr>	m_CurrGrabData;
	};
}

