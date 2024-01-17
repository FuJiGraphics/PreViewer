#include "pch.h"
#include "WindowsWindow.h"

PreViewer::WindowsWindow::WindowsWindow(int width, int height)
{
}

PreViewer::WindowsWindow::~WindowsWindow()
{
}

void PreViewer::WindowsWindow::OnUpdate()
{
}

void * PreViewer::WindowsWindow::GetNativeWindow() const
{
	return nullptr;
}

unsigned int PreViewer::WindowsWindow::GetWidth() const
{
	return 0;
}

unsigned int PreViewer::WindowsWindow::GetHeight() const
{
	return 0;
}

void PreViewer::WindowsWindow::SetWindowSize(float width, float height)
{
}

BOOL CPreApp::InitInstance()
{
	m_pMainWnd = new CPreFrame();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	return TRUE;
}

CPreFrame::CPreFrame()
{
	Create(NULL, _T("HelloMFC"));
}

void CPreFrame::OnPaint()
{
	CPaintDC dc(this);
	const TCHAR *msg = _T("Hello, MFC");
	dc.TextOutW(100, 100, msg, lstrlen(msg));
}

void CPreFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	MessageBox(_T("마우스 클릭!"), _T("마우스 메시지"));
}

BEGIN_MESSAGE_MAP(CPreFrame, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()