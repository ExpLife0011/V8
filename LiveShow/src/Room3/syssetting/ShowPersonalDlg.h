#pragma once

#include "..\Resource.h"
#include "Skin_i.h"
#include "afxwin.h"
#include "..\..\include/ui/mlhtmlview.h"


// CShowPersonalDlg �Ի���

//�������϶Ի���
class CShowPersonalDlg : public CDialog
{
	DECLARE_DYNAMIC(CShowPersonalDlg)

public:
	CShowPersonalDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowPersonalDlg();

// �Ի�������
	enum { IDD = IDD_ATROOM_SHOW_PERSONAL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnCancel();
	virtual void OnOK();
    virtual BOOL OnInitDialog();
	virtual void OnShowWindow(BOOL bShow,UINT nStatus);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);	

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);

	void Init();
	void Confirm();

	DECLARE_MESSAGE_MAP()

public:
	void SetApplyEffect(BOOL bEffect);//���õ��Ӧ�õ�Ч��

private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	CMLHtmlView m_htmlPersonalInfo;
};
