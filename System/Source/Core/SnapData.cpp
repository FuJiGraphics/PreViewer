#include "pch.h"
#include "SnapData.h"

namespace PreViewer {

	SnapData::SnapData()
		: m_Width(0), m_Height(0)
		, m_BufferSize(0)
		, m_BitFormatStride(0)
		, m_ImageBuffer(nullptr)
		, m_IsEmpty(TRUE)
	{
		// Empty
	}

	SnapData::SnapData(const SnapData& data)
	{
		SetData(
			data.GetWidth(), 
			data.GetHeight(), 
			data.GetRawBuffer(), 
			data.GetBufferSize(), 
			data.GetDataStride()
		);
	}

	SnapData::SnapData(size_t width, size_t height, void* pImgBuf, size_t imgSize, size_t stride)
		: m_Width(0), m_Height(0)
		, m_BufferSize(0)
		, m_BitFormatStride(0)
		, m_ImageBuffer(nullptr)

	{
		this->SetData(width, height, pImgBuf, imgSize, stride);
	}

	SnapData::~SnapData()
	{
		this->Clear();
	}

	SnapData& SnapData::operator= (const SnapData& data)
	{
		SetData(
			data.GetWidth(), 
			data.GetHeight(), 
			data.GetRawBuffer(),
			data.GetBufferSize(), 
			data.GetDataStride()
		);
		return *this;
	}

	void SnapData::SetData(size_t width, size_t height, void* pImgBuf, size_t imgSize, size_t stride)
	{
		if (this->IsEmpty() == FALSE)
			this->Clear();

		unsigned char *dst, *src;
		unsigned int index, size;
		unsigned char color;

		m_Width = width;
		m_Height = height;
		m_BufferSize = imgSize;
		m_BitFormatStride = stride;
		m_IsEmpty = FALSE;

		m_ImageBuffer = new BYTE[m_BufferSize];
		memcpy(m_ImageBuffer, pImgBuf, imgSize);

		//src = (unsigned char*)pImgBuf;
		//dst = (unsigned char*)m_ImageBuffer;
		//size = m_Width * m_Height;
		//for (int i = 0; i < size; ++i)
		//{
		//	color = src[i];
		//	index = i * 4;
		//	dst[index]		= color;
		//	dst[index + 1]	= color;
		//	dst[index + 2]	= color;
		//	dst[index + 3]	= color;
		//}
		//m_IsEmpty = false;
	}

	void SnapData::Clear()
	{
		delete[]m_ImageBuffer;
		m_ImageBuffer = nullptr;
		m_Width = 0;
		m_Height = 0;
		m_BufferSize = 0;
		m_BitFormatStride = 0;
		m_IsEmpty = TRUE;
	}

}