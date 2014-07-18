#pragma once
#include "..\Resource.h"
#include "Skin_i.h"
#include "ChangeVoiceListCtrl.h"
#include "GiftManager.h"


// CChangeVoiceDlg �Ի���

class CChangeVoiceDlg : public CDialog
{
	DECLARE_DYNAMIC(CChangeVoiceDlg)

public:
	CChangeVoiceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangeVoiceDlg();

	void OnSelChangeVoice(IGiftItem * pGiftItem);

// �Ի�������
	enum { IDD = IDD_CHANGEVOICEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();

private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	CChangeVoiceListCtrl m_changeVoiceListCtrl;
};
