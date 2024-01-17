#pragma once
#include "Core.h"

namespace PreViewer {

	class Application
	{
	public:
		explicit Application();
		virtual ~Application();
	
	public:
		void Run();
		void Render();
		void Update();

	private:
		inline static Application* s_instance = nullptr;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

} // namespace PreViewer