#pragma once
#include <Core/Window.h>

#undef _WINDOWS_
#include <afxwin.h>

class CPreApp : public CWinApp 
{
public:
	virtual BOOL InitInstance() override;
};

class CPreFrame : public CFrameWnd
{
public:
	CPreFrame();

protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};

namespace PreViewer {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(int width, int height);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		virtual void* GetNativeWindow() const override;
		virtual unsigned int GetWidth() const override;
		virtual unsigned int GetHeight() const override;
		virtual void SetWindowSize(float width, float height) override;

	private:
		CPreApp m_WindowApp;

	};


}