#pragma once

namespace PreViewer {
	// ViewCamera로부터 Snap된 데이터를 관리하는 구조체
	class SnapData
	{
	public:
		SnapData();
		SnapData(const SnapData& data);
		SnapData(size_t width, size_t height, void* pImgBuf, size_t imgSize, size_t stride = 0);
		~SnapData();

		SnapData& operator = (const SnapData& data);

		// Get
		inline size_t		GetWidth()		const { return m_Width; }
		inline size_t		GetHeight()		const { return m_Height; }
		inline size_t		GetBufferSize() const { return m_BufferSize; }
		inline size_t		GetDataStride() const { return m_BitFormatStride; }
		inline void*		GetRawBuffer()	const { return m_ImageBuffer; }
		inline bool			IsEmpty()		const { return m_IsEmpty; }
		// Set
		void SetData(size_t width, size_t height, void* pImgBuf, size_t imgSize, size_t stride = 0);
		// Others
		void Clear();

	private:
		size_t	m_Width, m_Height;
		size_t	m_BufferSize;
		size_t	m_BitFormatStride;
		void*	m_ImageBuffer;
		bool	m_IsEmpty;
	};
}