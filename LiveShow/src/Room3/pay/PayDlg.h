#pragma once

#include "..\Resource.h"
#include "..\include\ui\mlhtmlview.h"

// CPayDlg �Ի���

class CPayDlg : public CDialog
{
	DECLARE_DYNAMIC(CPayDlg)

public:
	CPayDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPayDlg();

// �Ի�������
	enum { IDD = IDD_ROOM_PAY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);

	void InitPayBrowser();

	DECLARE_MESSAGE_MAP()
public:
	void SetTheUrl(CString strUrl);
private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	CMLHtmlView m_htmlPay;
};
