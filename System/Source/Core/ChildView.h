#pragma once
#include <Renderer/Renderer2D.h>
#include <Renderer/CameraManager.h>

using namespace PreViewer;

class CChildView : public CWnd
{
// Variable
private:
	HGLRC	m_hRC;	// Rendering Context
	CDC*	m_pDC;	// Device Context
	
	PrePtr<CameraManager> m_pvCamera;
	std::shared_ptr<PreViewer::Renderer2D> m_Renderer;
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
	bool InitRenderer();
	bool SetPixelFormat();
	
	inline CDC* GetDC() const { return m_pDC; }
	inline Renderer2D* GetRenderer() { return &*m_Renderer; }
	inline VirtualCamera& GetVirtualCamera() { return m_pvCamera->GetCamera(); }
	inline static CChildView* GetInstance() { return s_Instance; }
	static void Render(const float& dt);

// Generated message map functions
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

