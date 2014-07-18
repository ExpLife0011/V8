#pragma once

//#include "stdafx.h"
#include "Skin_i.h"
#include "..\Resource.h"
#include "..\..\include/ui/mlhtmlview.h"

// CGetContributionDlg �Ի���

class CGetContributionDlg : public CDialog
{
	DECLARE_DYNAMIC(CGetContributionDlg)

public:
	CGetContributionDlg(CWnd* pParent, uint32 unRoomID);   // ��׼���캯��
	virtual ~CGetContributionDlg();

// �Ի�������
	enum { IDD = IDD_GET_CONTRIBUTION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);

	void OnClickGetContribution();
	void InitTheBrowser();

	DECLARE_MESSAGE_MAP()
private:
	CComPtr<ISkinEngine>  m_pSkinEngine;
	uint32 m_nRoomID;
	CMLHtmlView m_htmlGetContribute;
	
public:
	virtual BOOL OnInitDialog();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
