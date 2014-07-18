#pragma once
#include <vector>
#include "afxcmn.h"
#include "..\Resource.h"
#include "Skin_i.h"
#include "AutoReplyConfig.h"
#include "afxwin.h"

// CAutoReplySettingDlg �Ի���

class CAutoReplySettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CAutoReplySettingDlg)

public:
	CAutoReplySettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAutoReplySettingDlg();

// �Ի�������
	enum { IDD = IDD_AUTOREPLY_SETTING_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);
	afx_msg void OnNMHoverListAutoreply(NMHDR *pNMHDR, LRESULT *pResult);

	void InitListCtrl();
    void OnClickBtnAdd();
	void OnClickBtnDelete();
	void OnClickBtnModify();

	void OnClickBtnConfirm();
	void OnClickBtnClose();

	DECLARE_MESSAGE_MAP()
private:
	CComPtr<ISkinEngine> m_pSkinEngine;

	std::vector<stAutoReplyMenuItem> m_vAutoReplyList ;
	CListCtrl m_autoReplyListCtrl;
	CButton m_OpenAutoReply;
	BOOL m_bCheck;
	int m_nMySelelected;//ѡ�е��Զ��ظ���Ϣ
	BOOL m_bChange;//�н�����ɾ��
public:
	BOOL GetAutoReplyState();
	int GetSelectedItem(){ return m_nMySelelected; }
	BOOL GetAutoReplyChange(){return m_bChange;}
	std::vector<stAutoReplyMenuItem>& GetNewAutoReply(){return m_vAutoReplyList;}	
};
