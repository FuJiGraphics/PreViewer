#include "pch.h"
#include "Pylon_Camera.h"
#include <Core/PreException.h>

namespace PreViewer {

	using namespace Pylon;

	void PylonCamera::Init()
	{
		try
		{
			PylonInitialize();
			m_Initialized = TRUE;
			m_OnCapture = FALSE;
			m_MaxBufferCount = 10;
			
			CTlFactory& factory = CTlFactory::GetInstance();
			m_PylonDevice = factory.CreateFirstDevice();
			m_PylonCamera.Attach(m_PylonDevice);
			m_PylonCamera.MaxNumBuffer = m_MaxBufferCount;
			m_PylonCamera.StartGrabbing(500);
			
			// Grab Test and saving device info
			this->Grab();
			m_Width = (*m_CurrGrabData)->GetWidth();
			m_Height = (*m_CurrGrabData)->GetHeight();
		}
		catch (const GenericException & e)
		{
			throw PreException();
		}

	}

	void PylonCamera::Cleanup()
	{
		m_Width = 0;
		m_Height = 0;
		m_MaxBufferCount = 0;
		m_OnCapture = FALSE;
		m_PylonCamera.Close();
		PylonTerminate();
	}

	void PylonCamera::Display() 
	{
		try
		{
			if (m_Initialized == FALSE)
				throw PreException();
			
			if (m_OnCapture == TRUE)
				Pylon::DisplayImage(1, *m_CurrGrabData);
		} 
		catch (const GenericException& e)
		{
			throw PreException();
		}
	}

	BOOL PylonCamera::isOpen()
	{
		try
		{
			auto& info = m_PylonDevice->GetDeviceInfo();
			info.GetAddress();
			if (m_PylonDevice->IsOpen() == false)
				return FALSE;
			return TRUE;
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

	SnapData PylonCamera::Snap()
	{
		try
		{
			if (m_Initialized == FALSE)
				throw PreException();

			if (this->Grab() == FALSE)
				return SnapData();

			const CGrabResultPtr& data = (*m_CurrGrabData);
			if (data->GrabSucceeded())
				return SnapData(data->GetWidth(), data->GetHeight(), data->GetBuffer(), data->GetImageSize());
			else
				return SnapData();
		}
		catch (const GenericException& e)
		{
			throw PreException();
		}
	}

	PrePtr<SnapData> PylonCamera::SharedSnap()
	{
		try
		{
			if (m_Initialized == FALSE)
				throw PreException();

			PrePtr<SnapData> ptrSnap;
			if (this->Grab() == FALSE)
				ptrSnap.reset(new SnapData());

			const CGrabResultPtr& data = (*m_CurrGrabData);
			if (data->GrabSucceeded())
				ptrSnap.reset(new SnapData(data->GetWidth(), data->GetHeight(), data->GetBuffer(), data->GetImageSize()));
			else
				ptrSnap.reset(new SnapData());

			return ptrSnap;
		}
		catch (const GenericException& e)
		{
			throw PreException();
		}
	}

	BOOL PylonCamera::Grab(PrePtr<CGrabResultPtr>* out)
	{
		m_OnCapture = FALSE;
		if (m_PylonCamera.IsGrabbing())
		{
			PrePtr<CGrabResultPtr> grab;
			grab.reset(new CGrabResultPtr);
			m_PylonCamera.RetrieveResult(500, *grab, TimeoutHandling_ThrowException);

			if ((*grab)->GrabSucceeded())
			{
				m_OnCapture = TRUE;
				if (out == nullptr)
					m_CurrGrabData = grab;
				else
					(*out) = grab;
			}
		}
		return m_OnCapture;
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