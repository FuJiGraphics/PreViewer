#include <pch.h>
#include "Application.h"


namespace PreViewer {
	Application::Application()
	{
		s_instance = this;

		m_pWindow.reset(Window::Create());
		m_pLayers.reset(new LayerArray());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (true)
		{
			// Window Loop
			m_pWindow->OnUpdate();

			// Layer Loop
			for (auto layer : *m_pLayers)
			{
				layer->OnUpdate(0.0f);
			}
			for (auto layer : *m_pLayers)
			{
				layer->OnMFCRender();
			}
		}

	}

	void Application::AttachLayer(Layer * layer)
	{
		PV_CORE_ASSERT(layer, "Failed to Attached Layer.");
		m_pLayers->InsertLevel(layer);
		layer->OnAttach();
	}

	void Application::DetachLayer(Layer * layer)
	{
		PV_CORE_ASSERT(layer, "Failed to Detached Layer.");
		m_pLayers->RemoveLevel(layer);
		layer->OnDetach();
	}

} // namespace PreViewer
