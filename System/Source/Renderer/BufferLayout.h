#pragma once

namespace PreViewer {
	enum class ShaderDataType {
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool,
	};

	// global helper functions
	int ShaderDataTypeToGLType(const ShaderDataType& type);
	int ShaderDataTypeSize(const ShaderDataType& type);
	int ShaderDataTypeToCount(const ShaderDataType& type);

	struct LayoutElement
	{
		ShaderDataType	Type;		// Shader Data Type
		std::string		Name;		// Shader Data Name
		unsigned int	DataSize;	// Size of Datum
		unsigned int	Count;		// Count;
		unsigned int	Offset;		// Begin attribute pointer
		bool			Normalized;	// Enable Normalize Option

		LayoutElement(ShaderDataType&& type, std::string&& name, bool normalized = false);
		LayoutElement(const LayoutElement& element);
	};

	class BufferLayout
	{
		using LayoutElements = std::vector<LayoutElement>;
	public:
		explicit BufferLayout() = default;
		BufferLayout(const std::initializer_list<LayoutElement>& elements);
		BufferLayout(const BufferLayout& layout);

		inline unsigned int GetStride() const { return m_Stride; }
		inline unsigned int GetElementsSize() const { return static_cast<unsigned int>(m_Elements.size()); }
		inline const LayoutElements& GetElementsData() const { return m_Elements; }

		inline LayoutElements::iterator begin() { return m_Elements.begin(); }
		inline LayoutElements::iterator end() { return m_Elements.end(); }

		inline LayoutElements::const_iterator begin() const { return m_Elements.begin(); }
		inline LayoutElements::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride();

	private:
		std::vector<LayoutElement> m_Elements;
		unsigned int m_Stride = 0;
	};

}