#pragma once
#include <Renderer/Camera.h>

class CChildView : public CWnd
{
// Variable
private:
	HGLRC	m_hRC;	// Rendering ContextS
	CDC*	m_pDC;	// Device Context
	
	std::shared_ptr<PreViewer::Camera> m_Camera;
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
	
	inline PreViewer::Camera* GetCamera() { return &*m_Camera; }
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

