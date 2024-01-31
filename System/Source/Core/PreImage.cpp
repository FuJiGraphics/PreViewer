#include "pch.h"
#include "PreImage.h"

namespace PreViewer {

	PreImage::PreImage(int width, int height, const BYTE* pBuf, int bufSize)
	{
		m_Data.Image.Create(width, height, 8);
		m_Data.ImageSize = bufSize;
		m_Data.Width = width;
		m_Data.Height = height;
		int nBpp = 8;
		if (nBpp == 8) {
			static RGBQUAD rgb[256];
			for (int i = 0; i < 256; i++)
				rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			m_Data.Image.SetColorTable(0, 256, rgb);
		}
		SetBitmapBits(m_Data.Image, m_Data.Width * m_Data.Height, pBuf);
	}

	PreImage::PreImage(const SnapData& snap)
	{

	}

	PreImage::~PreImage()
	{
		m_Data.Image.Destroy();
		m_Data.Image.ReleaseGDIPlus();
	}

	bool PreImage::Save(const CString& pathName)
	{
		m_Data.Image.Save(pathName, Gdiplus::ImageFormatBMP);
		return true;
	}

	bool PreImage::Save(const std::string& path, const std::string & fileName)
	{
		CString savePath((path + "\\" + fileName).c_str());
		m_Data.Image.Save(savePath, Gdiplus::ImageFormatBMP);
		return true;
	}

	PreImage* PreImage::Load(const std::string& path, const std::string & fileName)
	{
		return nullptr;
	}

}