#pragma once

#include "..\Resource.h"
#include "Skin_i.h"

// CPhotoDlg �Ի���

class CPhotoDlg : public CDialog
{
	DECLARE_DYNAMIC(CPhotoDlg)

public:
	CPhotoDlg(const CString& strDirPath ,const CString& strFilePath ,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPhotoDlg();

// �Ի�������
	enum { IDD = IDD_PHOTO_SUCCESS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);

	void OnClickPhotoDir();//�����ƬĿ¼
	void OnClickPreview();//������

	DECLARE_MESSAGE_MAP()
private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	CString m_strDirPath ;
	CString m_strFilePath ;
public:
	afx_msg void OnNcDestroy();
};
