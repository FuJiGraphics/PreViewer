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
		m_PylonCamera.StartGrabbing(5000);
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

		CPylonImage image = this->Mono8bitToBMP24(*m_TempGrabData);
		
		int width = image.GetWidth();
		int height = image.GetHeight();
		int bufSize = image.GetImageSize();
		void* nativeBuf = image.GetBuffer();
		if (out != nullptr)
			out->SetData(width, height, nativeBuf, bufSize);
		image.Release();
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

	CPylonImage PylonCamera::Mono8bitToBMP24(const CGrabResultPtr& grab)
	{
		CPylonImage image(CPylonImage::Create(PixelType_RGB8packed, grab->GetWidth(), grab->GetHeight()));
		CImageFormatConverter converter;
		converter.OutputPixelFormat = EPixelType::PixelType_RGB8packed;
		converter.OutputBitAlignment = OutputBitAlignment_MsbAligned;
		converter.Convert(image, grab);
		return image;
	}

	void PylonCamera::ToSnapData(SnapData* out, const Pylon::CGrabResultPtr& in)
	{
		if (out != nullptr)
		{
			out->SetData(in->GetWidth(), in->GetHeight(), in->GetBuffer(), in->GetImageSize());
		}
	}

}