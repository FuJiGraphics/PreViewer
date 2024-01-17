#include <PreViewer.h>

class Client : public PreViewer::Application
{
public:

private:

};

PreViewer::Application* PreViewer::CreateApplication()
{
	return new Client();
}