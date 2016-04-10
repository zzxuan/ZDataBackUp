// ZDencrptDlg.h : 头文件
//

#pragma once


// CZDencrptDlg 对话框
class CZDencrptDlg : public CDialog
{
// 构造
public:
	CZDencrptDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ZDENCRPT_DIALOG };

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
	afx_msg void OnBnClickedButton2();

private:
	CString m_fileName;
	CString m_passWord;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
