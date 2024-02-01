#include "pch.h"
#include "Pylon_Camera.h"

namespace PreViewer {

	using namespace Pylon;

	void PylonCamera::Init()
	{
		PylonInitialize();
		IPylonDevice* device = CTlFactory::GetInstance().CreateFirstDevice();
		m_PylonCamera.Attach(device);
		m_PylonCamera.MaxNumBuffer = m_MaxBufferCount;
		m_PylonCamera.StartGrabbing(100);
	}

	void PylonCamera::Cleanup()
	{
		m_PylonCamera.Close();
		PylonTerminate();
	}

	void PylonCamera::Display() 
	{
		m_OnCapture = true;
		if (m_PylonCamera.IsGrabbing())
		{
			if (m_TempGrabData != nullptr)
				delete m_TempGrabData;
			m_TempGrabData = new CGrabResultPtr;
			m_PylonCamera.RetrieveResult(500, *m_TempGrabData, TimeoutHandling_ThrowException);
			if ((*m_TempGrabData)->GrabSucceeded())
			{
				Pylon::DisplayImage(1, *m_TempGrabData);
			}
		}
		return;
	}

	void PylonCamera::Snap(SnapData* out)
	{
		if (m_OnCapture == FALSE)
			return;
		const CGrabResultPtr& data = (*m_TempGrabData);
		auto type = data->GetPixelType();
		if (out != nullptr)
			out->SetData(data->GetWidth(), data->GetHeight(), data->GetBuffer(), data->GetImageSize());
	}

	SnapData PylonCamera::Snap()
	{
		if (m_OnCapture == FALSE)
			return SnapData();;
		const CGrabResultPtr& data = (*m_TempGrabData);
		if (data->GrabSucceeded())
			return SnapData(data->GetWidth(), data->GetHeight(), data->GetBuffer(), data->GetImageSize());
		else
			return SnapData();
	}

	void PylonCamera::ToSnapData(SnapData* out, const Pylon::CGrabResultPtr& in)
	{
		if (out != nullptr)
		{
			out->SetData(in->GetWidth(), in->GetHeight(), in->GetBuffer(), in->GetImageSize());
		}
	}

}