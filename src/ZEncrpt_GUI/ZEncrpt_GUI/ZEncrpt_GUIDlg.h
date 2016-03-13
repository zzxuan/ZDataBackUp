// ZEncrpt_GUIDlg.h : ͷ�ļ�
//

#pragma once
#include "Ui_Normal.h"
#include "Ui_Filelist.h"


// CZEncrpt_GUIDlg �Ի���
class CZEncrpt_GUIDlg : public CDialog
{
// ����
public:
	CZEncrpt_GUIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ZENCRPT_GUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	afx_msg void OnEraseBkgnd(CDC* pDC);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	CDialog* pDialog[2];  //��������Ի������ָ��
};
