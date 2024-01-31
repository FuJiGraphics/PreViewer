
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "Application.h"
#include "ChildView.h"
#include "PreImage.h"

// Core
#include <Renderer/RendererAPI.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
	: m_pDC(nullptr)
{
	s_Instance = this;
	m_Camera.reset(PreViewer::Camera::Create());
}

CChildView::~CChildView()
{
	if (m_pDC != nullptr)
		delete m_pDC;
}

bool CChildView::InitRenderer()
{
	using namespace PreViewer;
	m_pDC = new CClientDC(this);
	if (m_pDC == nullptr)
		return false;
	
	if (this->SetPixelFormat() == false)
		return false;
	
	// Initialized a Rendering Context
	 RendererAPI::GenerateRC(*m_pDC);
	if (m_hRC == 0)
		return false;

	// RendererAPI::ClearColor();
	// RendererAPI::SetClearDepthValue(1.0f);
	// RendererAPI::DepthTest(true);

	m_Camera.reset(Camera::Create());

	// Set Callback Function
	CPreViewerApp::GetInstance().SetRenderCallback(this->Render);
}

bool CChildView::SetPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
		1,								// version
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,		// rgba TYPE
		24,					// 24-bit color depth
		0, 0, 0, 0, 0, 0,	// color bits ignored
		0,					// no alpha buffer
		0,					// shift bit ignored
		0,					// no accumulation buffer
		0, 0, 0, 0,			// accumulation bits ignored
		16,					// 16-bit z-buffer
		0,					// no stencil buffer
		0,					// no auxiliary buffer
		PFD_MAIN_PLANE,		// main layer
		0,					// reserved
		0, 0, 0				// layer masks ignored
	};

	int pixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (pixelFormat == 0)
		return false;

	if (::SetPixelFormat(m_pDC->GetSafeHdc(), pixelFormat, &pfd) == FALSE)
		return false;

	return true;
}

void CChildView::Render(const float& dt)
{
	using namespace PreViewer;
	auto* view = CChildView::GetInstance();
	if (view == nullptr)
		return;

	auto& realCamera = CPreViewerApp::GetInstance().GetRealCamera();
	auto* camera = view->GetCamera();
	if (camera == nullptr)
		return;
	
	// Rendering
	camera->BeginRender();
	SnapData& snap = realCamera.Snap();
	camera->DrawPixels(snap.GetBuffer());
	camera->EndRender();
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CChildView message handlers
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;


	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{


}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (this->InitRenderer() == false)
		return -1;

	return 0;
}


void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	double aspectRatio;
	if (cx <= 0 || cy <= 0)
		return;

	
}
