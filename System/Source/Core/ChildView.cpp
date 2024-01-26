
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "Application.h"
#include "ChildView.h"
#include "PreImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CChildView message handlers
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;



	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.style |= WS_HSCROLL | WS_VSCROLL;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_HAND), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	using namespace PreViewer;
	CClientDC dc(this);
	AfxMessageBox(_T("Capture!"), MB_OK);
	CPreViewerApp& app = CPreViewerApp::GetInstance();
	RealCamera& vCamera = app.GetViewCamera();

	SnapData snap;
	vCamera.Snap(&snap);

	PreViewer::PreImage image(snap.GetWidth(), snap.GetHeight(), snap.GetBuffer(), snap.GetBufferSize());
	image.Save(".", ".");

//delete[] puc8;
//delete[] puc32;


}