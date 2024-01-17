#include "pch.h"
#include "Layer.h"
#include "LayerArray.h"

namespace PreViewer {

	LayerArray::LayerArray()
		: m_Container()
		, m_InsertIndex(0)
	{ }

	LayerArray::~LayerArray()
	{
		if (m_Container.size())
		{
			for (const auto& level : m_Container)
			{
				PV_CORE_ASSERT(level, "Unexpected Error : Failed to deallocate memory.");
				delete level;
			}
		}
	}

	bool LayerArray::InsertLevel(Layer* pLevel)
	{
		PV_CORE_ASSERT(pLevel, "Unexpected Error : Failed to called a emplace");

		auto findLevel = FindLevel(pLevel);
		if (findLevel == m_Container.end())
		{
			m_Container.emplace(m_Container.begin() + m_InsertIndex, pLevel);
			++m_InsertIndex;
			return true;
		}
		return false;
	}

	bool LayerArray::InsertOverlay(Layer* pOverlay)
	{
		PV_CORE_ASSERT(pOverlay, "Unexpected Error : Failed to called a emplace_back");

		auto findOverlay = FindLevel(pOverlay);
		if (findOverlay == m_Container.end())
		{
			m_Container.emplace_back(pOverlay);
			return true;
		}
		return false;
	}

	bool LayerArray::RemoveLevel(Layer* pLevel)
	{
		PV_CORE_ASSERT(pLevel, "Unexpected Error : Failed to called a PopLevel");

		auto findLevel = FindLevel(pLevel);
		if (findLevel != m_Container.end())
		{
			m_Container.erase(findLevel);
			--m_InsertIndex;
			return true;
		}
		return false;
	}

	bool LayerArray::RemoveOverlay(Layer* pOverlay)
	{
		PV_CORE_ASSERT(pOverlay, "Unexpected Error : Failed to called a PopOverlay");

		auto findOverlay = FindLevel(pOverlay);
		if (findOverlay != m_Container.end())
		{
			m_Container.erase(findOverlay);
			return true;
		}
		return false;
	}

	LayerArray::iter LayerArray::FindLevel(Layer* pLevel)
	{
		return std::find_if(m_Container.begin(), m_Container.end(),
			[pLevel](Layer* pTarget)
		{
			return pLevel == pTarget;
		});
	} // auto LevelContainer::FindLevel( Level* pLevel )


} // namespace PreViewer