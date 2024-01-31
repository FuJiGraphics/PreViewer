#include <pch.h>
#include "BufferLayout.h"

namespace PreViewer {
//------------------------------- Static Functions Line -------------------------------//

	int ShaderDataTypeToGLType(const ShaderDataType & type)
	{
		switch (type)
		{
			case ShaderDataType::Float:   return GL_FLOAT;
			case ShaderDataType::Float2:  return GL_FLOAT;
			case ShaderDataType::Float3:  return GL_FLOAT;
			case ShaderDataType::Float4:  return GL_FLOAT;
			case ShaderDataType::Mat3:    return GL_FLOAT;
			case ShaderDataType::Mat4:    return GL_FLOAT;
			case ShaderDataType::Int:     return GL_INT;
			case ShaderDataType::Int2:    return GL_INT;
			case ShaderDataType::Int3:    return GL_INT;
			case ShaderDataType::Int4:    return GL_INT;
			case ShaderDataType::Bool:    return GL_BOOL;
		}
		return GL_FALSE;
	}

	int ShaderDataTypeSize(const ShaderDataType& type)
	{
		switch (type)
		{
		case ShaderDataType::Float:   return 4;
		case ShaderDataType::Float2:  return 4 * 2;
		case ShaderDataType::Float3:  return 4 * 3;
		case ShaderDataType::Float4:  return 4 * 4;
		case ShaderDataType::Mat3:    return 3 * 4 * 3;
		case ShaderDataType::Mat4:    return 4 * 4 * 4;
		case ShaderDataType::Int:     return 4;
		case ShaderDataType::Int2:    return 4 * 2;
		case ShaderDataType::Int3:    return 4 * 3;
		case ShaderDataType::Int4:    return 4 * 4;
		case ShaderDataType::Bool:    return 1;
		}
		// NR_CORE_ASSERT(nullptr, "Unexpected Error: Unknown ShaderDataType.");
		return 0;
	}

	int ShaderDataTypeToCount(const ShaderDataType & type)
	{
		switch (type)
		{
		case ShaderDataType::Float:   return 1;
		case ShaderDataType::Float2:  return 2;
		case ShaderDataType::Float3:  return 3;
		case ShaderDataType::Float4:  return 4;
		case ShaderDataType::Mat3:    return 3 * 3;
		case ShaderDataType::Mat4:    return 4 * 4;
		case ShaderDataType::Int:     return 1;
		case ShaderDataType::Int2:    return 2;
		case ShaderDataType::Int3:    return 3;
		case ShaderDataType::Int4:    return 4;
		case ShaderDataType::Bool:    return 1;
		}
		// NR_CORE_ASSERT(nullptr, "Unexpected Error: Unknown ShaderDataType.");
		return 0;
	}


//------------------------------- Layout Element Line -------------------------------//

	LayoutElement::LayoutElement(ShaderDataType&& type, std::string&& name, bool normalized)
		: Type(std::move(type))
		, Name(std::move(name))
		, DataSize(ShaderDataTypeSize(type))
		, Count(ShaderDataTypeToCount(type))
		, Offset(0)
		, Normalized(normalized)
	{/* Empty */}

	LayoutElement::LayoutElement(const LayoutElement& element)
	{
		this->Type = element.Type;
		this->Name = element.Name;
		this->DataSize = element.DataSize;
		this->Count = element.Count;
		this->Offset = element.Offset;
		this->Normalized = element.Normalized;
	}

//------------------------------- Buffer Layout Line -------------------------------//

	BufferLayout::BufferLayout(const std::initializer_list<LayoutElement>& elements)
		: m_Elements(elements)
		, m_Stride(0)
	{
		CalculateOffsetAndStride();
	}

	BufferLayout::BufferLayout(const BufferLayout& layout)
	{
		// clear layout in this object
		this->m_Elements.clear();

		const LayoutElements& elements = layout.GetElementsData();
		for (const auto& element : elements)
		{
			this->m_Elements.push_back(element);
		}
		this->m_Stride = layout.m_Stride;
	}

	void BufferLayout::CalculateOffsetAndStride()
	{
		unsigned int offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.DataSize;
			m_Stride += element.DataSize;
		}
	}

}