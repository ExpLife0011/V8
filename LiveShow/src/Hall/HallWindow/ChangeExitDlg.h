#pragma once

#include "resource.h"
#include "Skin_i.h"
// CChangeExitDlg �Ի���

class CChangeExitDlg : public CDialog
{
	DECLARE_DYNAMIC(CChangeExitDlg)

public:
	CChangeExitDlg(IModuleManager* pModuleManager, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangeExitDlg();

// �Ի�������
	enum { IDD = IDD_CHANGEUSER_OR_EXIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
    
	afx_msg void OnClose();	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	DECLARE_MESSAGE_MAP()

private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	IModuleManager* m_pModuleManager;
	
};
