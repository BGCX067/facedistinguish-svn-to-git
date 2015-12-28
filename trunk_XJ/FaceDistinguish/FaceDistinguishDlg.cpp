// FaceDistinguishDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FaceDistinguish.h"
#include "FaceDistinguishDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CFaceDistinguishDlg 对话框




CFaceDistinguishDlg::CFaceDistinguishDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFaceDistinguishDlg::IDD, pParent)
    ,m_expand(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFaceDistinguishDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFaceDistinguishDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTONSETTING, &CFaceDistinguishDlg::OnBnClickedButtonsetting)
    ON_BN_CLICKED(IDC_BUTTONBROWSE, &CFaceDistinguishDlg::OnBnClickedButtonbrowse)
    ON_BN_CLICKED(IDC_CHECKSTOP, &CFaceDistinguishDlg::OnBnClickedCheckstop)
END_MESSAGE_MAP()


// CFaceDistinguishDlg 消息处理程序

BOOL CFaceDistinguishDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    GetWindowRect(&m_DlgRect);
    GetDlgItem(IDC_SEPERATOR)->GetWindowRect(&m_SeperatorRect);
    SetWindowPos(NULL,100,100,m_SeperatorRect.left-m_DlgRect.left,m_DlgRect.bottom-m_DlgRect.top,SWP_NOZORDER);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFaceDistinguishDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFaceDistinguishDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CFaceDistinguishDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFaceDistinguishDlg::OnBnClickedButtonsetting()
{
    // TODO: 在此添加控件通知处理程序代码
    if(m_expand)
    {
        SetDlgItemText(IDC_BUTTONSETTING,L"识别设置<<<");
        m_expand = !m_expand;
        SetWindowPos(NULL,0,0,m_SeperatorRect.left-m_DlgRect.left,m_DlgRect.bottom-m_DlgRect.top,SWP_NOZORDER|SWP_NOMOVE);
    }
    else
    {
        SetDlgItemText(IDC_BUTTONSETTING,L"识别设置>>>");
        m_expand = !m_expand;
        SetWindowPos(NULL,0,0,m_DlgRect.right-m_DlgRect.left,m_DlgRect.bottom-m_DlgRect.top,SWP_NOZORDER|SWP_NOMOVE);
    }
}

void CFaceDistinguishDlg::OnBnClickedButtonbrowse()
{
    // TODO: 在此添加控件通知处理程序代码
    BROWSEINFO bi;
    ZeroMemory(&bi,sizeof(BROWSEINFO));
    LPMALLOC pMalloc;
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    TCHAR * path = new TCHAR[MAX_PATH];
    if(pidl != NULL)
    {
        SHGetPathFromIDList(pidl,path);
        GetDlgItem(IDC_EDITPATH)->SetWindowText(path);
        UpdateData(TRUE);
        if(SUCCEEDED(SHGetMalloc(&pMalloc)))
        {
            pMalloc->Free(pidl);
            pMalloc->Release();
        }
    }
    m_DirName=path;
    delete path;
}

void CFaceDistinguishDlg::OnBnClickedCheckstop()
{
    // TODO: 在此添加控件通知处理程序代码
    MessageBoxA(NULL,"dsf","dsf",MB_OK);
}
