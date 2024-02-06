#pragma once
#include "PreImage.h"
#include <Renderer/Renderer2D.h>
#include <Renderer/CameraManager.h>

using namespace PreViewer;

class CChildView : public CWnd
{
// Variable
private:
	HGLRC	m_hRC;	// Rendering Context
	CDC*	m_pDC;	// Device Context
	BOOL	m_Flip;
	BOOL	m_IsRotateMode;

	DrawInfo				m_DrawObject;
	PrePtr<CameraManager>	m_pvCamera;
	PrePtr<Renderer2D>		m_Renderer;
	inline static PrePtr<SnapData>  s_currSnap;
	inline static PrePtr<Texture2D> s_currTexture;
	inline static CChildView* s_Instance = nullptr;

// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

// Others
public:
	bool	InitRenderer();
	bool	SetPixelFormat();
	
	inline BOOL				IsFlipMode() const { return m_Flip; }
	inline DrawInfo&		GetVirtualCameraInfo() { return m_DrawObject; }
	inline CDC*				GetDC() const { return m_pDC; }
	inline Renderer2D*		GetRenderer() { return &*m_Renderer; }
	inline VirtualCamera&	GetVirtualCamera() { return m_pvCamera->GetCamera(); }
	inline SnapData&		GetSnapData() { return *s_currSnap; }
	
	inline static CChildView* GetInstance() { return s_Instance; }
	static void Render(const float& dt);

// Generated message map functions
protected:
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
//	afx_msg void OnMouseWheel();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnMoveUp();
	afx_msg void OnMoveDown();
	afx_msg void OnMoveLeft();
	afx_msg void OnMoveRight();
	afx_msg void OnRotateLeft();
	afx_msg void OnRotateRight();
};

