#include "pch.h"
#include "Pylon_Camera.h"
#include <Core/PreException.h>

namespace PreViewer {

	using namespace Pylon;

	void PylonCamera::Init()
	{
		PylonInitialize();

		try
		{
			CTlFactory& factory = CTlFactory::GetInstance();
			IPylonDevice* device = factory.CreateFirstDevice();
			m_PylonCamera.Attach(device);
			m_PylonCamera.MaxNumBuffer = m_MaxBufferCount;
			m_PylonCamera.StartGrabbing(500);
		}
		catch (const GenericException & e)
		{
			throw PreException();
		}

	}

	void PylonCamera::Cleanup()
	{
		m_PylonCamera.Close();
		PylonTerminate();
	}

	void PylonCamera::Display() 
	{
		try
		{
			m_OnCapture = FALSE;
			if (m_PylonCamera.IsGrabbing())
			{
				if (m_TempGrabData != nullptr)
					delete m_TempGrabData;
				m_TempGrabData = new CGrabResultPtr;
				m_PylonCamera.RetrieveResult(500, *m_TempGrabData, TimeoutHandling_ThrowException);

				if ((*m_TempGrabData)->GrabSucceeded())
				{
					m_OnCapture = TRUE;
					Pylon::DisplayImage(1, *m_TempGrabData);
				}
			}
		} 
		catch (const GenericException& e)
		{
			throw PreException();
		}
	}

	BOOL PylonCamera::isSnapSuccessful()
	{
		return m_OnCapture;
	}

	void PylonCamera::Snap(SnapData* out)
	{
		if (m_OnCapture == FALSE)
			return;

		const CGrabResultPtr& data = (*m_TempGrabData);

		if (data->GrabSucceeded())
		{
			CPylonImage image;
			// TODO: Convert °úÁ¤ Áß ÅÍÁü
			this->Mono8bitToBMP24(&image, *m_TempGrabData);

			int width = image.GetWidth();
			int height = image.GetHeight();
			int bufSize = image.GetImageSize();
			void* nativeBuf = image.GetBuffer();
			if (out != nullptr)
				out->SetData(width, height, nativeBuf, bufSize);
			EPixelType type = image.GetPixelType();
			image.Release();
		}
	}

	SnapData PylonCamera::Snap()
	{
		if (m_OnCapture == FALSE)
			return SnapData();

		const CGrabResultPtr& data = (*m_TempGrabData);
		if (data->GrabSucceeded())
			return SnapData(data->GetWidth(), data->GetHeight(), data->GetBuffer(), data->GetImageSize());
		else
			return SnapData();
	}

	PrePtr<SnapData> PylonCamera::SharedSnap()
	{
		PrePtr<SnapData> ptrSnap;
		if (m_OnCapture == FALSE)
			ptrSnap.reset(new SnapData());

		const CGrabResultPtr& data = (*m_TempGrabData);
		if (data->GrabSucceeded())
			ptrSnap.reset(new SnapData(data->GetWidth(), data->GetHeight(), data->GetBuffer(), data->GetImageSize()));
		else
			ptrSnap.reset(new SnapData());

		return ptrSnap;
	}

	bool PylonCamera::Mono8bitToBMP24(CPylonImage* dst, const CGrabResultPtr& src)
	{
		CImageFormatConverter converter;
		converter.OutputPixelFormat = EPixelType::PixelType_RGB8packed;
		converter.OutputBitAlignment = OutputBitAlignment_MsbAligned;
		converter.Convert(*dst, src);
		return true;
	}

	void PylonCamera::ToSnapData(SnapData* out, const Pylon::CGrabResultPtr& in)
	{
		if (out != nullptr)
		{
			out->SetData(in->GetWidth(), in->GetHeight(), in->GetBuffer(), in->GetImageSize());
		}
	}

}