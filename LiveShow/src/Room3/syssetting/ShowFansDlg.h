#pragma once
#include "..\Resource.h"
#include "Skin_i.h"
#include "afxwin.h"
#include "..\..\include/ui/mlhtmlview.h"
#include "..\fans\fansValue.h"

// CShowFansDlg �Ի���

class CShowFansDlg : public CDialog
{
	DECLARE_DYNAMIC(CShowFansDlg)

public:
	CShowFansDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowFansDlg();

// �Ի�������
	enum { IDD = IDD_ATROOM_SHOW_FANS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
	void OnGetFansRsp(Event const&evt);  //��ȡ��˿���ݷ�����Ӧ����	

private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	CMLHtmlView m_htmlFans;
	CFansValue m_fansValue;
};
