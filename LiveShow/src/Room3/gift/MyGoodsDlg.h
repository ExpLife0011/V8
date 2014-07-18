#pragma once
#include "..\Resource.h"
#include "Skin_i.h"
#include "MyGoodsListCtrl.h"


// CMyGoodsDlg �Ի���

class CMyGoodsDlg : public CDialog
{
	DECLARE_DYNAMIC(CMyGoodsDlg)

public:
	CMyGoodsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyGoodsDlg();

// �Ի�������
	enum { IDD = IDD_MYGOODS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	CMyGoodsListCtrl m_MyGoodsListCtrl;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};
