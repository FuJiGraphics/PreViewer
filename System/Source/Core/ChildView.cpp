
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

	 // Initialize the glew
	 if (glewInit() != GLEW_OK)
		 return false;

	 if (m_hRC == 0)
		 return false;

	// Created a Renderer2D
	auto& app = CPreViewerApp::GetInstance();
	m_Renderer.reset(PreViewer::Renderer2D::Create(app.GetWidth(), app.GetHeight()));

	// Created a virtual camera
	// TODO : float의 floor 연산 조심 CameraManager에서 자체 처리 구현
	float aspect_ratio = static_cast<float>(app.GetWidth()) / app.GetHeight();
	m_pvCamera.reset(new CameraManager(aspect_ratio));
	m_pvCamera->ActivateRotation(false);

	// Set Callback Function
	CPreViewerApp::GetInstance().SetRenderCallback(this->Render);

	return true;
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
	auto* renderer = view->GetRenderer();
	if (renderer == nullptr)
		return;
	
	// Position
	glm::vec2 pos(0.0f, 0.0f);
	glm::vec2 scale(0.3f);


 	// Rendering
	renderer->BeginRender(&view->GetVirtualCamera());
	SnapData& snap = realCamera.Snap();

	//PrePtr<Texture2D> texture;
	//texture.reset(Texture2D::Create(snap.GetWidth(), snap.GetHeight()));
	//texture->SetData(snap.GetRawBuffer(), snap.GetBufferSize());
	//renderer->DrawQuad2D(pos, scale, *texture);

	PrePtr<Texture2D> loadTex;
	loadTex.reset(Texture2D::Create("D:\\Dev\\PreViewer\\wall.jpg"));
	renderer->DrawQuad2D(pos, scale, *loadTex);
	
	renderer->EndRender();

	// Swap Chain
	::SwapBuffers(view->GetDC()->GetSafeHdc());
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
	CPaintDC dc(this);
	
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
