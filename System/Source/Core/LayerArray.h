#pragma once
#include "Core.h"

#include <vector>

namespace PreViewer {

	class Layer;

	class PV_API LayerArray
	{
		using iter = std::vector<Layer*>::iterator;

	public:
		explicit LayerArray();
		virtual ~LayerArray();

	private:
		LayerArray(LayerArray&) = delete;
		void operator= (LayerArray&) = delete;

	public:
		bool InsertLevel(Layer* pLevel);
		bool InsertOverlay(Layer* pOverlay);
		bool RemoveLevel(Layer* pLevel);
		bool RemoveOverlay(Layer* pOverlay);

	protected:
		iter FindLevel(Layer* pLevel);

	public:
		inline bool empty() const { return m_Container.empty(); }
		iter begin() { return m_Container.begin(); }
		iter end() { return m_Container.end(); }

	private:
		std::vector<Layer*> m_Container;
		int m_InsertIndex;
	};
} // namespace PreViewer