#pragma once

#include "..\Resource.h"
#include "Skin_i.h"
#include "afxcmn.h"
#include "TempNoticeManager.h"
#include "..\..\CommonLibrary\include\ui\InputRichEdit.h"
//#include "..\CommonLibrary\include\ui\VDCComboBox.h"
// CTempAnnounceDlg �Ի���
#include "TempAnnounceListCtrl.h"
class CRoomParentDlg ;
class CTempAnnounceDlg : public CDialog
{
	DECLARE_DYNAMIC(CTempAnnounceDlg)

public:
	CTempAnnounceDlg( CRoomParentDlg* pParentDlg , CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTempAnnounceDlg();

	CComboBox m_FontSizeCombo;
	CComboBox m_FontCombo;

	core::MessageFont GetFontInfo();

// �Ի�������
	enum { IDD = IDD_TEMP_ANNOUNCE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);
	afx_msg void OnInputChange();

	void InitSavedAnnounceList();
	void InitFontPanel();	//�����С��������
	void PublishTempAnnounce();
	void OnClickAdd();
	void OnClickSave();
	void OnClickDelete();
	void SaveXML();	

	DECLARE_MESSAGE_MAP()
private:
	CComPtr<ISkinEngine> m_pSkinEngine;

	CTempAnnounceListCtrl m_savedAnnounceList;//�ѱ��湫���б�
	CRoomParentDlg* m_pParentDlg ;
	VecNoticeInfo m_vecNoticeList;
	int m_nCurSelItem;
	CInputRichEdit m_InputCtrl;

public:
	afx_msg void OnCbnSelchangeComboFontsize();
	afx_msg void OnCbnSelchangeComboFont();
	afx_msg void OnNMClickListSavedAnnounced(NMHDR *pNMHDR, LRESULT *pResult);
	void SetInputAnnounce( CString& strText ) ;
	void ClearInputCtrlValue() ; //���������е�����
	void SetApplyEffect(BOOL bEffect);
	afx_msg void OnEnChangeEditTitle();
	void SetButtonStatus( bool bBold , bool bItalic , bool bUnderLine ) ;
};
