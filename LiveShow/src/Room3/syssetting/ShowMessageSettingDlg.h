#pragma once

#include "..\Resource.h"
#include "Skin_i.h"
// CShowHarassmentDlg �Ի���

class CShowMessageSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CShowMessageSettingDlg)

public:
	CShowMessageSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowMessageSettingDlg();

	void Refresh();

// �Ի�������
	enum { IDD = IDD_ATROOM_SHOW_MESSAGE_SETTING_DLG};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);	

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedCheck();  //��ѡ������Ӧ����

	void Init();
	void Confirm();

	DECLARE_MESSAGE_MAP()
public:
	void SetApplyEffect(BOOL bEffect);//���õ��Ӧ�õ�Ч��

private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
