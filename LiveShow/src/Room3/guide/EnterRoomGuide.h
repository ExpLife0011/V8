#pragma once
#include "..\Resource.h"
#include "Skin_i.h"
#include "..\include/ui/mlhtmlview.h"

// CEnterRoomGuide �Ի���

class CEnterRoomGuide : public CDialog
{
	DECLARE_DYNAMIC(CEnterRoomGuide)

public:
	CEnterRoomGuide(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEnterRoomGuide();

// �Ի�������
	enum { IDD = IDD_ROOM_ENTERROOMGUIDE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);
	afx_msg void OnClose();

	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);	

	void InitGuideBrowser();
	void OnClickRecommendRoom(uint32 roomID); 

	DECLARE_MESSAGE_MAP()

private:
	CComPtr<ISkinEngine> m_pSkinEngine;

	CMLHtmlView m_htmlRecommendRoom;

};
