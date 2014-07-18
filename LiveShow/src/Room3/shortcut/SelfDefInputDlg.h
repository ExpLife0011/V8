#pragma once

#include "..\Resource.h"
#include "Skin_i.h"
#include "afxwin.h"

// CSelfDefInputDlg �Ի���

class CSelfDefInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CSelfDefInputDlg)

public:
	CSelfDefInputDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelfDefInputDlg();

// �Ի�������
	enum { IDD = IDD_SELF_DEF_INPUT_DLG };

	CString GetInPutString() ;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);	
	DECLARE_MESSAGE_MAP()

private:
	CComPtr<ISkinEngine>  m_pSkinEngine;
	CString m_strInput ;
	
public:
	CEdit m_InputEdit;
};
