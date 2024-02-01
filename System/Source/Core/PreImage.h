#pragma once

#include <string>
#include "SnapData.h"

namespace PreViewer {

	struct ImageData
	{
		CImage	Image;
		int		ImageSize; 
		int		Width;
		int		Height;
	};

	class PreImage
	{
	public:
		PreImage(int width, int height, const void* pBuf, int bufSize);
		PreImage(const SnapData& snap);
		~PreImage();

		bool	Save(const CString& pathName);
		bool	Save(const std::string& path, const std::string& fileName);
		bool	Load(const std::string& path, const std::string& fileName);

	private:
		ImageData	m_Data;
	};
}
