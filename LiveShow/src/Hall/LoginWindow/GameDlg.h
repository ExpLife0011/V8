#pragma once

#include "Resource.h"
#include "Skin_i.h"
#include "LoginDlg.h"
#include "../../include/ui/mlhtmlview.h"

class CGameDlg : public CDialog
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(HWND sendMesHWND, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();

// �Ի�������
	enum { IDD = IDD_REGISTER_DLG };

	void SetURL(CString& strURL);	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnClick(WPARAM wParam,LPARAM lParam);   //��ȡ���ҳ���г�����ʱ����Ӧ����
	afx_msg LRESULT OnOpenURL(WPARAM wParam,LPARAM lParam);

	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void OnSysCommand(UINT nID,LPARAM lParam);
	
	void RegisterElementSetFocus(); //������Ƕҳ��Ľ���

	void SetWindowSize(int wndWidth,int wndHeight);//���ô˽ӿ��Ըı䴰�ڴ�С
	void InitBrowser();

	DECLARE_MESSAGE_MAP()

private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	CMLHtmlView m_htmlGame;
	HWND m_sendMesHWND;	
	CWnd* m_pParent;
	CString m_gameURL;
};
