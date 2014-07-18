#pragma once


// CTheMoreDlg �Ի���
class CRoomParentDlg;
class CTheMoreDlg : public CDialog
{
	DECLARE_DYNAMIC(CTheMoreDlg)

public:
	CTheMoreDlg( CRoomParentDlg* pParentDlg, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTheMoreDlg();

// �Ի�������
	enum { IDD = IDD_ROOM_THE_MORE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);

	void OnClickBtnStamp();
	void OnClickBtnCleanScreen();
	void OnClickBtnCopyUrl();

	DECLARE_MESSAGE_MAP()
private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	CRoomParentDlg* m_pRoomParentDlg ;
	
};
