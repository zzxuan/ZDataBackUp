#pragma once


// CUi_Filelist �Ի���

class CUi_Filelist : public CDialog
{
	DECLARE_DYNAMIC(CUi_Filelist)

public:
	CUi_Filelist(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUi_Filelist();

// �Ի�������
	enum { IDD = IDD_UI_FILELIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
