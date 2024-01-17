#pragma once

#ifdef PV_PLATFORM_WINDOWS

extern PreViewer::Application* PreViewer::CreateApplication();

int main(int argc, char** argv)
{
	auto app = PreViewer::CreateApplication();

	app->Run();

	delete app;
//#ifdef _DEBUG
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif
}

#endif