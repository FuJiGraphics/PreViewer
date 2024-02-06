

// PreViewer.cpp : Defines the class behaviors for the application.
//
#include "pch.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Application.h"
#include "MainFrm.h"

#include "PreImage.h"
#include "PreException.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CPreViewerApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CPreViewerApp::OnAppAbout)
	ON_COMMAND(ID_FILE_SAVE, &CPreViewerApp::OnFileSave)
END_MESSAGE_MAP()


// CPreViewerApp construction

CPreViewerApp::CPreViewerApp() noexcept
	: m_strAppName(_T("PreViewer"))
	, m_ptrCamera(nullptr)
	, m_iPosX(100), m_iPosY(100)
	, m_iWidth(1024), m_iHeight(768)
{
	if (s_instance == nullptr)
	{
		s_instance = this;
		SetAppID(_T("PreViewer.AppID.NoVersion"));
	}
}

// The one and only CPreViewerApp object
CPreViewerApp theApp;

BOOL CPreViewerApp::LoadRealCamera()
{
	try
	{ // camera
		m_ptrCamera = PreViewer::RealCamera::Create();
		m_ptrCamera->Init();
		return TRUE;
	}
	catch (const PreException& e)
	{
		return FALSE;
	}
}

void CPreViewerApp::DestroyCamera()
{
	if (m_ptrCamera != nullptr)
	{
		m_ptrCamera->Cleanup();
		delete m_ptrCamera;
		m_ptrCamera = nullptr;
	}
}

void CPreViewerApp::ExitProgram()
{
	RECT data;
	GetWindowRect(m_pMainWnd->GetSafeHwnd(), &data);

	WriteProfileInt(_T("Position"), _T("X"), data.left);
	WriteProfileInt(_T("Position"), _T("Y"), data.top);
	WriteProfileInt(_T("Size"), _T("Width"), data.right - data.left);
	WriteProfileInt(_T("Size"), _T("Height"), data.bottom - data.top);

	m_pMainWnd->DestroyWindow();
}

BOOL CPreViewerApp::InitInstance()
{
	CWinApp::InitInstance();

	// Initialized Camera;
	m_HasLinkedCamera = this->LoadRealCamera();

	EnableTaskbarInteraction(FALSE);
	SetRegistryKey(_T("ZVLab"));

	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr,
		nullptr);
	// The one and only window has been initialized, so show and update it
	// pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

int CPreViewerApp::ExitInstance()
{
	::MessageBox(NULL, _T("프로그램을 종료합니다."), _T("종료"), MB_OK | MB_ICONQUESTION);
	this->DestroyCamera();
	return CWinApp::ExitInstance();
}

BOOL CPreViewerApp::OnIdle(LONG lcount)
{
	int result = IDOK;

	if (m_HasLinkedCamera)
	{
		try
		{
			m_ptrCamera->Display();

			if (s_pCallbackRender != nullptr)
				s_pCallbackRender(0.0f);
		}
		catch (const PreException& e)
		{
			m_HasLinkedCamera = FALSE;
		}
	}
	else
	{
		result = ::MessageBox(NULL, 
			_T("카메라 연결에 실패하였습니다. 연결을 확인하십시오."), 
			_T("Error"), 
			MB_RETRYCANCEL | MB_ICONQUESTION);
		this->DestroyCamera();
		m_HasLinkedCamera = this->LoadRealCamera();
	}

	if (result == IDCANCEL || result == IDNO)
		this->ExitProgram();

	return TRUE;
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CPreViewerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CPreViewerApp message handlers

void CPreViewerApp::OnFileSave()
{
	using namespace PreViewer;
	CString path;
	CFileDialog save(FALSE, _T("Files (*.bmp)"), NULL,
		OFN_FILEMUSTEXIST |		// 존재하는 파일만 선택 가능
		OFN_PATHMUSTEXIST |		// 존재하는 경로만 선택 가능
		OFN_HIDEREADONLY |		// ReadOnly 체크박스 숨김
		OFN_LONGNAMES,			// 긴 파일 이름 포맷 지원
		_T("Files (*.bmp)|*.bmp|*.*|"));
	if (save.DoModal() == IDOK)
		path.SetString(save.GetPathName());

	const SnapData& snap = CChildView::GetInstance()->GetSnapData();
	PreImage image(snap);
	image.Save(path);
}
