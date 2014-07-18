#pragma once
#include "afxcmn.h"
#include "..\Resource.h"
#include "Skin_i.h"
//#include "HtmlInputLogic.h"
//#include "OutInputHtmlEditImpl.h"
#include "..\..\CommonLibrary\include\ui\InputRichEdit.h"
#include "TempAnnounceListCtrl.h"
// CRoomAnnounceDlg �Ի���
class CPreviewDlg;
class CRoomAnnounceDlg : public CDialog
{
	DECLARE_DYNAMIC(CRoomAnnounceDlg)

public:
	CRoomAnnounceDlg( CRoomParentDlg* pParentDlg , CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRoomAnnounceDlg();

	void Refresh();

// �Ի�������
	enum { IDD = IDD_ROOM_ANNOUNCE_DLG };

	void ClearInputCtrlValue() ;	//���������е�����
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);
	afx_msg void OnNMClickListRoomAnnounce(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMHoverListRoomAnnounce(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnInputChange();

	void InitRoomAnnounceList();
	void SetTeachYouAddr();//���ý�����Ư������ĵ�ַ

	void InitDlgData();
	void OnClickPreview();
	void OnClickAdd();
	void OnClickSave();
	void OnClickDelete();
	void SaveNotice();
	void OnClickTeachYou();

	DECLARE_MESSAGE_MAP()
public:
	void SetApplyEffect(BOOL bEffect);
	
private:
	CComPtr<ISkinEngine> m_pSkinEngine;

	//HtmlEditImpl* m_pInputHtml ;			//����
	//COutInputHtmlEditImpl * m_pInputHtml ;
	//CHtmlInputLogic m_InputLogic ;
	CInputRichEdit m_InputCtrl;
	CTempAnnounceListCtrl m_listRoomAnnounce;
	CRoomParentDlg* m_pParentDlg ;
	CPreviewDlg * m_pPreviewDlg;
	int m_nCurSelItem;	
};
