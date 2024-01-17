#include <PreViewer.h>

class Client : public PreViewer::Application
{
public:
	Client()
	{
		
	}
private:

};

PreViewer::Application* PreViewer::CreateApplication()
{
	return new Client();
}