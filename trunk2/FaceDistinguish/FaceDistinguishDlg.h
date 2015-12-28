// FaceDistinguishDlg.h : 头文件
//

#pragma once


// CFaceDistinguishDlg 对话框
class CFaceDistinguishDlg : public CDialog
{
// 构造
public:
	CFaceDistinguishDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FACEDISTINGUISH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonsetting();
    afx_msg void OnBnClickedButtonbrowse();
private:
    bool m_expand;
    RECT m_DlgRect;
    RECT m_SeperatorRect;
    CString m_DirName;
    afx_msg void OnBnClickedCheckstop();
};
