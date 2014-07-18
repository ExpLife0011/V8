#pragma once
#include "..\Resource.h"
#include "Skin_i.h"
#include "afxwin.h"
//#include "..\..\include/ui/mlhtmlview.h"
#include "..\RoomParentDlg.h"
#include "OrderHtmlView.h"

// COrderSongDlg �Ի���
class CSongWishDlg;
class CSpotSongDlg;
class COrderSongDlg : public CDialog
{
	DECLARE_DYNAMIC(COrderSongDlg)

public:
	COrderSongDlg(CRoomParentDlg* pParentDlg, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COrderSongDlg();

	void InitHeadList(uint32 unSelfUin, uint32 unIndex, bool bUpdate = false);
	void InitSongList(uint32 unIndex, uint32 unSongerUin, bool bRefresh = false, bool bSort = true);
	void InitOrderList(uint32 unSelfUin, bool bActor);
	void InitMarkList(uint32 unSelfUin);
	bool CheckSongListChange();
	void ClearSongListStat();

	void Init();

	BOOL OnSaveSongList(int nSongerID, LPCTSTR lpszParam);
	BOOL OnAddSong(int nSongerID, LPCTSTR lpszSong);
	BOOL OnClearSongList(int nSongerID);
	BOOL OnOrderSong(int nSongerID, LPCTSTR lpszSong);
	BOOL OnOrderPriority(int nSongerID, LPCTSTR lpszSong);
	BOOL OnSongListChange(int nChange);
	BOOL OnDecideSong(int nOrderID, int nStat);
	BOOL OnDecideEvaluate(int nOrderID, int nStat);
	BOOL OnOpenOrderSong();

	void ShowSongList();
	void ShowOrderList();
	void ShowMarkList();

	void SetCurSelIndex(uint32 unIndex);
	void OnPriority(int nCount);

	afx_msg LRESULT OnLoadHTMLComplete(WPARAM wParam,LPARAM lParam);

// �Ի�������
	enum { IDD = IDD_ROOM_ORDERSONG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);

	void InitBrowser();
	void ShowSongWishDlg();
	void ShowSpotSongDlg();
	void InitSongList();
	void InitOrderList();
	void InitMarkList();
	DECLARE_MESSAGE_MAP()
private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	COrderHtmlView m_htmlOrderList;
	COrderHtmlView m_htmlSongList;
	COrderHtmlView m_htmlMarkList;
	CSongWishDlg* m_pSongWishDlg;
	CSpotSongDlg * m_pSpotSongDlg;
	CRoomParentDlg * m_pParentDlg;
	bool m_bSongListChanged;
	ENM_ListType m_enmListType;
	uint32 m_unCurSelIndex;				//��ǰѡ����������
	bool m_bSongListLoadCompleted;		//����б�ҳ��������
	bool m_bOrderListLoadCompleted;		//�ѵ��б�ҳ��������
	bool m_bMarkListLoadCompleted;		//�����б�ҳ��������
	int m_nCurSongerID;
	CString m_strCurSong;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
