// FaceDistinguishDlg.h : ͷ�ļ�
//

#pragma once


// CFaceDistinguishDlg �Ի���
class CFaceDistinguishDlg : public CDialog
{
// ����
public:
	CFaceDistinguishDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FACEDISTINGUISH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
