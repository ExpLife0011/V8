#pragma once

#include "..\Resource.h"
#include "Skin_i.h"
// CVideoDlg �Ի���
#include "MicToolBarDlg.h"
#include "ximage.h"

class CVideoDlg : public CDialog
{
	DECLARE_DYNAMIC(CVideoDlg)

public:
	CVideoDlg( BOOL bToolBar ,HWND hParent , RoomAVLogic *RoomAVLogic ,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVideoDlg();

	static void ReleaseImage();

// �Ի�������
	enum { IDD = IDD_VIDEO_DLG };
	CMicToolBarDlg *m_pToolBarDlg ;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
public:
	void HideToolBarDlg() ;
	void SetToDefault( BOOL bExitShow = FALSE );
	void ChangeVideo( int nBtnState ) ;
	void ChangeAudio(int nBtnState ) ;
	void ChangeSize(int nBtnState ) ;
	void Photo() ;
	void Init( uint32 unUIN  ,uint16 unStatus ) ;
	void Init( uint32 unUIN ) ;

	void OpenVideoRsp( uint32 unUIN ) ;
	void OpenVideoNotify( uint32 unUIN ) ;
	void OpenAudioRsp( uint32 unUIN ) ;
	void OpenAudioNotify( uint32 unUIN ) ;

	void CloseVideoRsp( uint32 unUIN ) ;
	void CloseVideoNotify( uint32 unUIN ) ;
	void CloseAudioRsp( uint32 unUIN ) ;
	void CloseAudioNotify( uint32 unUIN ) ;
	BOOL m_bNeedHideTooBal ;
	uint16 m_unMicStatus ;
	uint16 m_unLookStatus ;	
private:	
	uint32 m_unSelfUIN ;
	uint32 m_unUserUIN ;
	BOOL m_bToolBar ;			//�Ƿ񴴽�ToolBar�Ի���
	HWND m_hParent ;	
	BOOL m_bChangeVideo ;
	BOOL m_bChangeAudio ;
	BOOL m_bChangeSize ;
	RoomAVLogic *m_pRoomAVLogic ;
	CComPtr<ISkinEngine>  m_pSkinEngine;
	BOOL m_bInited ;
	BOOL m_bPreparingVideo; //�Ƿ�����ΪĬ�ϱ���ͼ
	BOOL m_bBigMic;
	static CxImage* m_spImage;	
	static CxImage* m_usingImage ;
	static CxImage* m_preparingImage;
	static CxImage* m_bigSpImage;
	static CxImage* m_bigUsingImage;
	static CxImage* m_bigPreparingImage;
	static CxImage* GetDefaultImage();
	static CxImage* GetUsingImage() ;
	static CxImage* GetPreparingImage();
	static CxImage* GetBigDefaultImage();
	static CxImage* GetBigUsingImage() ;
	static CxImage* GetBigPreparingImage();
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	HRESULT OnMouseLeave( WPARAM wParam , LPARAM lParam ) ;
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void OpenVideo() ;
	void OpenAudio() ;
	void CloseVideoDisable() ;
	void CloseVideoEnable() ;
	void CloseAudioDisable() ;
	void CloseAudioEnable() ;
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void SetBigMic(BOOL bBigMic);
};
