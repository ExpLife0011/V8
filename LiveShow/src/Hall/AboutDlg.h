#pragma once

#include "Resource.h"
#include "Skin_i.h"
// CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
	DECLARE_DYNAMIC(CAboutDlg)

public:
	CAboutDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam, LPARAM lParam);

	void OnClickBtnLink();//��������
	void OnClickBtnUserAgreement();//�鿴�û�Э�� 

	DECLARE_MESSAGE_MAP()
private:
	CComPtr<ISkinEngine> m_pSkinEngine; 
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
