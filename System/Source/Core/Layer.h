#pragma once

#include "Core.h"

namespace PreViewer {

	class PV_API Layer
	{
	protected:
		using super = Layer;

	public:
		Layer() { ++s_NumOfLevels; }
		virtual ~Layer() { --s_NumOfLevels; }

		virtual void OnAttach() {};
		virtual void OnDetach() {};

		// virtual void OnEvent(Event& event) {};
		virtual void OnUpdate(const float& dt) {};
		virtual void OnMFCRender() {};

		virtual std::string GetName() const { return std::string(); }

	protected:
		inline static unsigned int GetLevelCount() { return s_NumOfLevels; }

	private:
		inline static int s_NumOfLevels = 0;
	};

} // namespace Normal