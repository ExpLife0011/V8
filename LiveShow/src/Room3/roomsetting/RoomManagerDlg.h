#pragma once

#include "..\Resource.h"
#include "Skin_i.h"

#define WM_NOTIFY_ROOM_ROOMSET_MODIFY WM_USER + 401

// CRoomManagerDlg �Ի���
class CAnnouncementDlg;
class CRoomSettingDlg;
class CMicSettingDlg;
class CUserMgrDlg;
class CTempAnnounceDlg;
class CRoomAnnounceDlg;
class CGetContributionDlg;

class CRoomManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(CRoomManagerDlg)

public:
	CRoomManagerDlg( CRoomParentDlg* pParentDlg , CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRoomManagerDlg();

// �Ի�������
	enum { IDD = IDD_ROOM_MANAGER };	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRoomSetModify(WPARAM wParam, LPARAM lParam);

	void NotifyCreateSkinItem();
    //void SetRoomerSysAddress();//����������̨�����ӵ�ַ	
	void OnClickGetContribute();
	void OnClickBtnRoomerSys();//������̨
	void OnClickBtnConfirm();//���ȷ��
	void OnClickBtnApply();//���Ӧ��
	void SetApplyEffect(BOOL bEffect);//Ӧ���ύЧ��
	void EnableBtnApply(bool bEnable);
	void Confirm();

	DECLARE_MESSAGE_MAP()
private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	
	CAnnouncementDlg * m_pAnnouncementDlg;
	CRoomSettingDlg * m_pRoomSettingDlg;
	CMicSettingDlg * m_pMicSettingDlg;
	CUserMgrDlg   * m_pUserMgrDlg;
	CDialog* m_pCurrentDlg;
	CRoomParentDlg* m_pParentDlg ;
	CTempAnnounceDlg * m_pTempAnnounceDlg;
	CRoomAnnounceDlg * m_pRoomAnnounceDlg;
	CGetContributionDlg * m_pGetContributeDlg;
	
    CString m_strCurItemBk;
public:
	void TurnToAnnouncePanel( CString& strText ) ;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
