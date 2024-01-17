#pragma once
#include "Core.h"
#include "LayerArray.h"
#include "Layer.h"
#include "Window.h"

namespace PreViewer {

	class Application
	{
		using super = Application;
	public:
		explicit Application();
		virtual ~Application();
	
	public:
		void Run();

		void AttachLayer(Layer* layer);
		void DetachLayer(Layer* layer);

	private:
		inline static Application* s_instance = nullptr;

		std::shared_ptr<Window>		m_pWindow;
		std::shared_ptr<LayerArray>	m_pLayers;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

} // namespace PreViewer