

// PreViewer.cpp : Defines the class behaviors for the application.
//
#include "pch.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Application.h"
#include "MainFrm.h"

#include "PreImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CPreViewerApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CPreViewerApp::OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, &CPreViewerApp::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CPreViewerApp::OnFileSave)
END_MESSAGE_MAP()


// CPreViewerApp construction

CPreViewerApp::CPreViewerApp() noexcept
	: m_strAppName(_T("PreViewer"))
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

BOOL CPreViewerApp::InitInstance()
{
	CWinApp::InitInstance();

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

	// view camera
	m_ViewCamera.reset(PreViewer::RealCamera::Create());
	m_ViewCamera->Init();

	return TRUE;
}

int CPreViewerApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	::MessageBox(NULL, _T("���α׷��� �����մϴ�."), _T("����"), MB_OK | MB_ICONQUESTION);
	m_ViewCamera->Cleanup();

	return CWinApp::ExitInstance();
}

BOOL CPreViewerApp::OnIdle(LONG lcount)
{
	m_ViewCamera->Display();

	if (s_pCallbackRender != nullptr)
		s_pCallbackRender(0.0f);

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
		OFN_FILEMUSTEXIST |		// �����ϴ� ���ϸ� ���� ����
		OFN_PATHMUSTEXIST |		// �����ϴ� ��θ� ���� ����
		OFN_HIDEREADONLY |		// ReadOnly üũ�ڽ� ����
		OFN_LONGNAMES,			// �� ���� �̸� ���� ����
		_T("Files (*.bmp)|*.bmp|*.*|"));
	if (save.DoModal() == IDOK)
		path.SetString(save.GetPathName());

	RealCamera& rCamera = this->GetRealCamera();

	SnapData snap;
	rCamera.Snap(&snap);

	PreImage image(snap.GetWidth(), snap.GetHeight(), snap.GetRawBuffer(), snap.GetBufferSize());
	image.Save(path);

	AfxMessageBox(_T("Capture!"), MB_OK);
}
