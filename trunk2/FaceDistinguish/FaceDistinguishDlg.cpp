// FaceDistinguishDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FaceDistinguish.h"
#include "FaceDistinguishDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CFaceDistinguishDlg �Ի���




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


// CFaceDistinguishDlg ��Ϣ�������

BOOL CFaceDistinguishDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    GetWindowRect(&m_DlgRect);
    GetDlgItem(IDC_SEPERATOR)->GetWindowRect(&m_SeperatorRect);
    SetWindowPos(NULL,100,100,m_SeperatorRect.left-m_DlgRect.left,m_DlgRect.bottom-m_DlgRect.top,SWP_NOZORDER);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFaceDistinguishDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CFaceDistinguishDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFaceDistinguishDlg::OnBnClickedButtonsetting()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    if(m_expand)
    {
        SetDlgItemText(IDC_BUTTONSETTING,L"ʶ������<<<");
        m_expand = !m_expand;
        SetWindowPos(NULL,0,0,m_SeperatorRect.left-m_DlgRect.left,m_DlgRect.bottom-m_DlgRect.top,SWP_NOZORDER|SWP_NOMOVE);
    }
    else
    {
        SetDlgItemText(IDC_BUTTONSETTING,L"ʶ������>>>");
        m_expand = !m_expand;
        SetWindowPos(NULL,0,0,m_DlgRect.right-m_DlgRect.left,m_DlgRect.bottom-m_DlgRect.top,SWP_NOZORDER|SWP_NOMOVE);
    }
}

void CFaceDistinguishDlg::OnBnClickedButtonbrowse()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
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
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    MessageBoxA(NULL,"dsf","dsf",MB_OK);
}
