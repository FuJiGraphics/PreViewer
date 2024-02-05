#include "pch.h"
#include "PreImage.h"

namespace PreViewer {

	PreImage::PreImage(int width, int height, const void* pBuf, int bufSize)
	{
		int nBpp = 24;
		m_Data.Image.Create(width, height, nBpp);
		m_Data.ImageSize = bufSize;
		m_Data.Width = width;
		m_Data.Height = height;
		//if (nBpp == 8) { // Generate Pallet
		//	static RGBQUAD rgb[256];
		//	for (int i = 0; i < 256; i++)
		//		rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		//	m_Data.Image.SetColorTable(0, 256, rgb);
		//}
		SetBitmapBits(m_Data.Image, m_Data.Width * m_Data.Height, pBuf);
	}

	PreImage::PreImage(const SnapData& snap)
	{
		int nBpp = 8;
		m_Data.ImageSize = snap.GetBufferSize();
		m_Data.Width = snap.GetWidth();
		m_Data.Height = snap.GetHeight();
		m_Data.Image.Create(m_Data.Width, m_Data.Height, nBpp);
		if (nBpp == 8) { // Generate Pallet
			static RGBQUAD rgb[256];
			for (int i = 0; i < 256; i++)
				rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			m_Data.Image.SetColorTable(0, 256, rgb);
		}
		SetBitmapBits(m_Data.Image, m_Data.Width * m_Data.Height, snap.GetRawBuffer());
	}

	PreImage::~PreImage()
	{
		m_Data.Image.Destroy();
		m_Data.Image.ReleaseGDIPlus();
	}

	bool PreImage::Save(const CString& pathName)
	{
		if (m_Data.Image.IsNull())
			return false;

		m_Data.Image.Save(pathName, Gdiplus::ImageFormatBMP);
		return true;
	}

	bool PreImage::Save(const std::string& path, const std::string & fileName)
	{
		if (m_Data.Image.IsNull())
			return false;

		CString savePath((path + "\\" + fileName).c_str());
		m_Data.Image.Save(savePath, Gdiplus::ImageFormatBMP);
		return true;
	}

	bool PreImage::Load(const std::string& path, const std::string & fileName)
	{
		CString savePath((path + "\\" + fileName).c_str());
		CImage newData;
		
		newData.Load(savePath);
		if (!newData.IsNull())
		{
			m_Data.Image.Destroy();
			m_Data.Image.Attach(newData);
			m_Data.Width = newData.GetWidth();
			m_Data.Height = newData.GetHeight();
			m_Data.ImageSize = m_Data.Width * m_Data.Height * newData.GetBPP();
			return true;
		}
		return false;
	}

}