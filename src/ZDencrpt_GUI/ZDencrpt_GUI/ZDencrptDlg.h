// ZDencrptDlg.h : ͷ�ļ�
//

#pragma once


// CZDencrptDlg �Ի���
class CZDencrptDlg : public CDialog
{
// ����
public:
	CZDencrptDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ZDENCRPT_DIALOG };

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
	afx_msg void OnBnClickedButton2();

private:
	CString m_fileName;
	CString m_passWord;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
