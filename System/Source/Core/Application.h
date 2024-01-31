
// PreViewer.h : main header file for the PreViewer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "Core.h"
#include "RealCamera.h"
#include <../Resource/Resource.h> // main symbols

class CPreViewerApp final : public CWinApp
{
//// Member Variables
private:
	inline static CPreViewerApp* s_instance = nullptr;

	PreViewer::PrePtr<PreViewer::RealCamera> m_ViewCamera;
	inline static void(*s_pCallbackRender)(const float& dt) = nullptr;

	CString m_strAppName;
	int		m_iPosX;
	int		m_iPosY;
	int		m_iWidth;
	int		m_iHeight;

public:
	CPreViewerApp() noexcept;
	virtual ~CPreViewerApp() = default;
// Get
	inline static CPreViewerApp& GetInstance() { return *s_instance; }
	inline int GetPosX() const { return m_iPosX; }
	inline int GetPosY() const { return m_iPosY; }
	inline int GetWidth() const { return m_iWidth; }
	inline int GetHeight() const { return m_iHeight; }
	inline CString GetAppName() const { return m_strAppName; }
	inline PreViewer::RealCamera& GetRealCamera() { return *m_ViewCamera; }
	inline PreViewer::RealCamera& GetRealCamera() const { return *m_ViewCamera; }
// Set
	inline void SetPosX(int iPosX) { m_iPosX = iPosX; }
	inline void SetPosY(int iPosY) { m_iPosY = iPosY; }
	inline void SetWidth(int iWidth) { m_iWidth = iWidth; }
	inline void SetHeight(int iHeight) { m_iHeight = iHeight; }
	inline void SetAppName(const CString& strAppName) { m_strAppName = strAppName; }
	static void SetRenderCallback(void(*callbackRender)(const float& dt)) 
	{ s_pCallbackRender = callbackRender; }

// Others

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
// Implementation
	virtual BOOL OnIdle(LONG lcount);

public:
	afx_msg void OnAppAbout();
	afx_msg void OnFileSave();
	DECLARE_MESSAGE_MAP()
};

extern CPreViewerApp theApp;
