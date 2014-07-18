#pragma once

#include "..\Resource.h"
#include "Skin_i.h"
#include "afxwin.h"
#include "..\avlogic\RoomAVLogic.h"
// CShowBasicSettingDlg �Ի���

class CShowBasicSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CShowBasicSettingDlg)

public:
	CShowBasicSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowBasicSettingDlg();

// �Ի�������
	enum { IDD = IDD_ATROOM_SHOW_BASIC_SETTING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	virtual void OnShowWindow(BOOL bShow,UINT nStatus);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);	

	void SetRegeditAutoRun();  //���ÿ�������   C:\Documents and Settings\�û���\����ʼ���˵�\����\����
	void ClearRegeditAutoRun(); //��ɾ��������
	bool ReadRegeditAutoRun();  //��ȡ�Ƿ񿪻�����

	void Confirm();
	void Init();

	DECLARE_MESSAGE_MAP()

private:
	CComPtr<ISkinEngine> m_pSkinEngine;


	CString m_curLoginUserName;  //��ǰ��¼�˺�
	CString m_curAutoLogin;
	CString m_curPowerRun;
	CString m_curOpenSound;

	CButton m_autoLogin;
	CButton m_PowerRun;
	CButton m_openSound;
public:
	afx_msg void OnBnClickedCheck();  //��ѡ������Ӧ����
	void SetApplyEffect(BOOL bEffect);//���õ��Ӧ�õ�Ч��
	
};
