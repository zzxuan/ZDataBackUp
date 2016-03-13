// ZEncrpt_GUIDlg.h : 头文件
//

#pragma once
#include "Ui_Normal.h"
#include "Ui_Filelist.h"


// CZEncrpt_GUIDlg 对话框
class CZEncrpt_GUIDlg : public CDialog
{
// 构造
public:
	CZEncrpt_GUIDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ZENCRPT_GUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	afx_msg void OnEraseBkgnd(CDC* pDC);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()

private:
	CTabCtrl m_tab;
	UINT m_CurSelTab;
	CUi_Normal m_item_normal;
	CUi_Filelist m_item_filelist;
	CDialog* pDialog[2];  //用来保存对话框对象指针
};
