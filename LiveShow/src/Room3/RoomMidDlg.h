#pragma once

#include "Resource.h"
#include "Skin_i.h"
#include "..\..\include\ui\mlhtmlview.h"
#include "..\..\include\ui\splitter.h"

#include "iectrl\OutputHtmlEditImpl.h"
#include "iectrl\OutputHtmlLogic.h"
#include "iectrl\InputHtmlLogic.h"
#include "GlobalRoomDefine.h"
#include "usermanager\UserManager.h"
#include "paodao\PaodaoStaitc.h"
#include "flash\flashWnd.h"
#include "..\CommonLibrary\include\ui\Regulator.h"
//#include "..\CommonLibrary\include\ui\VDCComboBox.h"
// CRoomMidDlg �Ի���

class CRoomParentDlg ;
class CTheMoreDlg;
class CRoomMidDlg : public CDialog
{
	DECLARE_DYNAMIC(CRoomMidDlg)

public:
	CRoomMidDlg(CRoomParentDlg* pParentDlg ,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRoomMidDlg();

// �Ի�������
	enum { IDD = IDD_ROOM_MID_DLG };

public:
	void OnAddUser( IUserItem * pUserItem ) ;
	void OnDeleteUser( IUserItem * pUserItem ) ;
	void OnUpdateUser(IUserItem * pUserItem) ;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);
    afx_msg LRESULT OnDragSplit(WPARAM wParam, LPARAM lParam);  //�ƶ��ָ���
	afx_msg LRESULT OnClickEmotionList( WPARAM wParam ,LPARAM lParam ) ;
	afx_msg LRESULT OnClickCaiZi( WPARAM wParam ,LPARAM lParam ) ;
	afx_msg LRESULT OnClickShortCutMsg( WPARAM wParam ,LPARAM lParam ) ;
	//afx_msg void OnCbnSelchangeComboFontsize();
	//afx_msg void OnCbnSelchangeComboFont();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckRoomPillowchat();
	afx_msg void OnBnClickedCheckRoomFlytext();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnInputMsgFocusIn(WPARAM wParam ,LPARAM lParam);
	afx_msg LRESULT OnInputMsgFocusOut(WPARAM wParam ,LPARAM lParam);
	afx_msg LRESULT OnClickMsgBoxGoToRegister(WPARAM wParam, LPARAM lParam);

    void ModifySplitter();                    //�ָ����ƶ�

	void OnClickBtnEmotion();                 //�������
	void OnClickBtnColorWord();               //�������
	void OnClickBtnStamp();					  //�������
	void OnClickBtnShortCut();				  //�����ݼ�
	void OnClickBtnComplaint();				  //�������

	void OnClickBtnFont();                    //�������

//	void OnClickBtnAutoReply();               //����Զ��ظ���ť
	void OnClickBtnCopyUrl();                 //������Ʒ����ַ
	void OnClickBtnFlyText();				  //�����������ѡ���
	void OnClickBtnSendFlyText();			  //������ͷ���
	void OnClickBtnFlyTextEffect();			  //�������Ч���˵�
	void OnClickBtnMore();

	DECLARE_MESSAGE_MAP()
public:
	//DragonZ:�ܵ��Ƶ�RoomParentDlg
	//void SetSendObj( CString& strName , uint32 unUIN ) ;

	void SetChatObj( CString strName , uint32 unUIN ) ;
	void BackMessage( UINT32 dstuin , MessageFont& stFont , std::wstring strText , ENM_SendMessageType enmType, bool bAutoMsg = FALSE) ;
	bool GetAMessageBack( SendMessageEvent& message ) ;
	void OnSendMsg() ;
	void OnSendAutoMsg(uint32 uDestUin);
	//DragonZ:�ܵ��Ƶ�RoomParentDlg
	/*void InsertPaoDaoText(CString& strSrcName , CString& strDstName , CString& strGiftWord ,uint32 unSrc179ID , 
		uint32 unDst179ID ,  uint16 unGiftID ,uint16 unCount , CString& strTime ) ;*/

	void InsertPrivateText(CString& strText ) ;
	void InsertPublicText(CString& strText ) ;
	void SetPublicOutputGotoEndAble( BOOL bAble ) ;
	void SetPrivateOutputGotoEndAble( BOOL bAble ) ;
	void InsertInputMsgDefaultText(CString& strText);

	//DragonZ:�ܵ��Ƶ�RoomParentDlg
	//void OnRoomRightSendToChange( CString& strSelText ) ;

	void OnSendSheChiGiftNotify() ;

	void OnClickNameLink( CString& strName , uint32 unUUID ) ;
	void OnClickNoRemind(uint32 uuUUID);//��������
	void SetFlyTextType(int nType);
	MessageFont GetFontInfo() ;

	//DragonZ:�ܵ��Ƶ�RoomParentDlg
	//void ReloadGiftData();
	
	void GetSendMsgRc(CRect& rcSendMsg);
	void SetPillowChatCheckBox(BOOL bCheck);
	void OnClickBtnCleanScreen();			  //�������
	void CleanPublicOutput();//�幫��
	void CleanPrivateOutput();//��˽��
private:
	bool OnInput( int nContenLen ) ;
	bool CanSendMsg( UINT32& uDestUin , CString&strText, bool bAutoMsg = FALSE) ;
	bool CanSendAutoMsg();
	void SendMsg( UINT32 uDestUin , CString& strText , BOOL bAutoMsg = FALSE) ;
	void InitFontPanel() ;
	void SetButtonStatus(bool bBold ,bool bItalic ,bool bUnderLine ) ;
	void CreateAutoWelcomeTimer() ;
	void CreateFirstLoginAutoWelcomeTimer();
	IUserItem* GetARandomActorUserItem() ;
private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	CSplitter m_Splitter;
	//CVDCComboBox m_comboTalkTo;
	//CVDCComboBox m_comboFont;
	//CVDCComboBox m_comboFontSize;

	COutputHtmlEditImpl *m_pPublicHtml ;			//����
	COutputHtmlLogic m_PublicLogic ;

	COutputHtmlEditImpl* m_pPrivateHtml ;			//˽��
	COutputHtmlLogic m_PrivateLogic ;

	COutputHtmlEditImpl* m_pInputHtml ;			//����
	CInputHtmlLogic m_InputLogic ;

	CString m_strLastMessage ;
	int m_nRepeatCount ;				//���Դ���
	uint32 m_nLastCaiZiTime ;			// ���Ͳ��ֵ�ʱ��
	BOOL m_bShortCutMsgMenu ;
	BOOL m_bCaiZiMenu ;
	common::ui::Regulator<long> m_SendMsgTime;

	//BOOL m_bAutoReplyMenu;

	deque<SendMessageEvent> m_dMessageBack ;
	CRoomParentDlg* m_pParentDlg ;
	//CPaodaoStaitc *m_pPaodaoStatic ;

	int m_nFlyTextType;
	CComboBox m_ComboTalkTo ;

	CTheMoreDlg* m_pTheMoreDlg;

public:
	void GetCaiTiaoAndPublicScreenRect(CRect &rcCaiTiao, CRect &rcPublicScreen);
	//DragonZ: �����Ƶ������
	void SetFontBold( int checked ) ;
	void SetFontItalic( int checked ) ;
	void SetFontUnderLine( int checked )  ;
	void SetFontName(CString& strFontName ) ;
	void SetFontColor(COLORREF cf ) ;
	void OnClickBtnJiaCu(int iBold);		  //����Ӵ�
	void OnClickBtnXieTi(int iItalic);		  //���б��
	void OnClickBtnUnderline(int iUnderline); //����»���
	void OnClickBtnFontColor();				  //���������ɫ
	void SetFontSize(UINT fontsize ) ;
	void OnClickBtnSendMsg();				  //���������Ϣ
	void OnModifyFont();
};
//IDC_COMBO_ROOM_TALKTO