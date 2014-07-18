#pragma once

#include "..\Resource.h"
#include "Skin_i.h"
#include "..\..\include/ui/mlhtmlview.h"
// CShowBankAccountDlg �Ի���

class CShowBankAccountDlg : public CDialog
{
	DECLARE_DYNAMIC(CShowBankAccountDlg)

public:
	CShowBankAccountDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowBankAccountDlg();

// �Ի�������
	enum { IDD = IDD_ATROOM_SHOW_BANKACCOUNT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnShowWindow(BOOL bShow,UINT nStatus);
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);	

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);

	void Init();

	DECLARE_MESSAGE_MAP()

public:
	void SetApplyEffect(BOOL bEffect);//���õ��Ӧ�õ�Ч��

private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	CMLHtmlView m_BankAccount;

};
