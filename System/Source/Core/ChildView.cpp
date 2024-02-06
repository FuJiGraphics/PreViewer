
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "ChildView.h"
#include "Application.h"
#include "MainFrm.h"
#include "PreImage.h"

// Core
#include <Renderer/RendererAPI.h>

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

	// Initialized a Rendering Context
	RendererAPI::GenerateRC(*m_pDC);

	// Initialize the glew
	if (glewInit() != GLEW_OK)
		return false;

	if (m_hRC == 0)
		return false;

	// Created a Renderer2D
	auto& realCamera = CPreViewerApp::GetInstance().GetRealCamera();
	m_Renderer.reset(PreViewer::Renderer2D::Create(realCamera.GetWidth(), realCamera.GetHeight()));

	// Set Callback Function
	CPreViewerApp::GetInstance().SetRenderCallback(this->Render);

	// Texture Flip Mode
	m_Flip = TRUE;

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

	// Rendering
	renderer->BeginRender(&view->GetVirtualCamera());
	if (realCamera.isSnapSuccessful() == TRUE)
	{
		s_currSnap = realCamera.SharedSnap();
		s_currTexture.reset(Texture2D::Create(*s_currSnap));
	}
	auto& info = view->GetVirtualCameraInfo();
	renderer->DrawQuad2D(info, *s_currTexture, view->IsFlipMode());

	renderer->EndRender();

	// Swap Chain
	::SwapBuffers(view->GetDC()->GetSafeHdc());
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
//	ON_COMMAND(ID_ZOOM_IN, &CChildView::OnMouseWheel)
ON_COMMAND(ID_ZOOM_IN, &CChildView::OnZoomIn)
ON_COMMAND(ID_ZOOM_OUT, &CChildView::OnZoomOut)
ON_COMMAND(ID_MOVE_UP, &CChildView::OnMoveUp)
ON_COMMAND(ID_MOVE_DOWN, &CChildView::OnMoveDown)
ON_COMMAND(ID_MOVE_LEFT, &CChildView::OnMoveLeft)
ON_COMMAND(ID_MOVE_RIGHT, &CChildView::OnMoveRight)
ON_COMMAND(ID_ROTATE_LEFT, &CChildView::OnRotateLeft)
ON_COMMAND(ID_ROTATE_RIGHT, &CChildView::OnRotateRight)
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

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pDC = new CClientDC(this);
	if (m_pDC == nullptr)
		return -1;

	if (this->SetPixelFormat() == false)
		return -1;

	if (this->InitRenderer() == false)
		return -1;

	// Created a virtual camera
	auto& realCamera = CPreViewerApp::GetInstance().GetRealCamera();
	m_pvCamera.reset(new CameraManager(realCamera.GetWidth(), realCamera.GetHeight()));
	m_pvCamera->ActivateRotation(true);

	// Set Camera Position
	m_pvCamera->SetMove(-3.0f, -3.0f);
	m_pvCamera->SetScale(-5.0f);

	// Set DrawObject
	m_DrawObject.SetMove(0.0f, 0.0f);
	m_DrawObject.SetScale(1.0f, 1.0f);

	m_IsRotateMode = FALSE;

	return 0;
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	if (cx <= 0 || cy <= 0)
		return;
}

BOOL CChildView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	static float scaleSpeed = 0.3f;
	if (zDelta > 0)
	{
		if (nFlags == MK_CONTROL)
		{
			m_DrawObject.AddScale(scaleSpeed, scaleSpeed);
		}
	}
	else
	{
		if (nFlags == MK_CONTROL)
		{
			m_DrawObject.AddScale(-scaleSpeed, -scaleSpeed);
		}
	}
	Invalidate();
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	static float moveSpeed = 0.1f;
	static float angleSpeed = 3.0f;
	if (nChar == VK_CONTROL)
		m_IsRotateMode = TRUE;

	if (m_IsRotateMode == FALSE)
	{
		switch (nChar)
		{
		case VK_UP:
			m_pvCamera->AddMove(+moveSpeed, Direction::Yaxis);
			break;
		case VK_DOWN:	
			m_pvCamera->AddMove(-moveSpeed, Direction::Yaxis);
			break;
		case VK_LEFT:	
			m_pvCamera->AddMove(-moveSpeed, Direction::Xaxis);
			break;
		case VK_RIGHT:	
			m_pvCamera->AddMove(+moveSpeed, Direction::Xaxis);
			break;
		}
	}
	else
	{
		switch (nChar)
		{
		case VK_UP:
			m_pvCamera->AddRotate(+angleSpeed, EularAngle::Pitch);
			break;
		case VK_DOWN:
			m_pvCamera->AddRotate(-angleSpeed, EularAngle::Pitch);
			break;
		case VK_LEFT:
			m_pvCamera->AddRotate(+angleSpeed, EularAngle::Roll);
			break;
		case VK_RIGHT:
			m_pvCamera->AddRotate(-angleSpeed, EularAngle::Roll);
			break;
		}
	}
	Invalidate();
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_CONTROL)
		m_IsRotateMode = FALSE;
	Invalidate();
	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CChildView::OnZoomIn()
{
	this->OnMouseWheel(MK_CONTROL, 1, { 0, 0 });
}

void CChildView::OnZoomOut()
{
	this->OnMouseWheel(MK_CONTROL, 0, { 0, 0 });
}

void CChildView::OnMoveUp()
{
	this->OnKeyDown(VK_UP, 1, 0);
}

void CChildView::OnMoveDown()
{
	this->OnKeyDown(VK_DOWN, 1, 0);
}

void CChildView::OnMoveLeft()
{
	this->OnKeyDown(VK_LEFT, 1, 0);
}

void CChildView::OnMoveRight()
{
	this->OnKeyDown(VK_RIGHT, 1, 0);
}

void CChildView::OnRotateLeft()
{
	m_IsRotateMode = TRUE;
	this->OnKeyDown(VK_LEFT, 1, 0);
	m_IsRotateMode = FALSE;
}

void CChildView::OnRotateRight()
{
	m_IsRotateMode = TRUE;
	this->OnKeyDown(VK_RIGHT, 1, 0);
	m_IsRotateMode = FALSE;
}
