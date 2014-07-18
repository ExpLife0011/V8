#pragma once

#include "Resource.h"
#include "Skin_i.h"
#include "usermanager\iusermanagersink.h"
#include "..\..\include\ui\mlhtmlview.h"
#include "RoomBusiness.h"
#include "avlogic\RoomAVLogic.h"
#include "UserMessageDefine.h"
#include "screeneffect\ScreenEffectManager.h"
#include "..\CommonLibrary\include\ui\TickerStatic.h"
#include "afxwin.h"
#include "flash/flashWnd.h"
#include "statreport\StatReport.h"
//#include "..\CommonLibrary\include\ui\VDCComboBox.h"
#include "..\CommonLibrary\include\ui\GifButton.h"
#include "..\CommonLibrary\include\ui\PngButton.h"
#include "..\CommonLibrary\include\ui\FlashFrameWnd.h"
#include "guide\GuideFlash.h"
#include "fans\AnchorFansCardDlg.h"
#include "sofa\SofaManager.h"
#include "iectrl\OutputHtmlEditImpl.h"
#include "loudspeaker\SpeakerOutputLogic.h"
#include "loudspeaker\LoudSpeakerManager.h"

// CRoomParentDlg �Ի���

//DragonZ:CRoomLeftDlg����ΪCRoomTopManager
//class CRoomLeftDlg;

class CRoomMidDlg;
class CRoomRightDlg;
class CStampDlg ;
class CEmotionDlg ;
class CPngDlg ;
class CPrivateMicDlg ;
class CP2PChatDlg ;
class CScrollBtnDlg ;
class CSpeakerDlg ;
class CWishSpeakerDlg ;
class CKickDlg ;
class CPaodaoBtnDlg ;
class CChangeVoiceDlg;
class CFlyingTextInputDlg;
class CUserInfoCardDlg ;
class CSysSettingDlg ;
class COtherUserInfoDlg ;
class CShowAudioTestDlg;
class CGuestRegisterDlg;
class CCoverWnd ;
class CGiftWordsDlg ;
class CModifyNameTipWnd;
//class CTaskDlg;
class CEnterRoomGuide;
class COrderSongDlg;
class CRoomBottomLeftDlg;
class CPublicMicDlg;
class CRoomTopManager;
class CPaodaoStaitc;
class CIconIntroductionDlg;
class CPayDlg;
class CRoomParentDlg : public CDialog, public IUserManagerSink, public IRoomBusinessSink, public ISofaManagerSink
{
	DECLARE_DYNAMIC(CRoomParentDlg)

public:
	CRoomParentDlg(uint32 uRoomID, RoomOption * pRoomOption, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRoomParentDlg();

public:
	//ҵ���߼�
	void SetRoomBusiness(RoomBusiness * pRoomBusiness);
	RoomBusiness * GetRoomBusiness();
	HtmlOutPutManager* GetHtmlOutPutManager(){ return m_pHtmlOutPutManager; } ;

	//�û��б�֪ͨ��Ϣ
	virtual void OnGetUserList(std::map<uint32, IUserItem*> & mapAllUser);													
	virtual void OnGetAdminList(std::map<uint32, IUserItem*> & mapAdminUser);
	virtual void OnGetWaitingList(std::map<uint32, IUserItem*> & mapWaitingUser);
	virtual void OnAddUser(IUserItem * pUserItem );
	virtual void OnUpdateUser(IUserItem * pUserItem);
	virtual void OnDeleteUser(IUserItem * pUserItem);
	virtual void OnAddAdminUser(IUserItem * pUserItem);
	virtual void OnDeleteAdminUser(IUserItem * pUserItem);
	virtual void OnAddWaitingUser(IUserItem * pUserItem);
	virtual void OnDeleteWaitingUser(IUserItem * pUserItem);
	virtual void OnUserListCountChange();
	void OnGetUserListBegin();
	void OnGetUserListComplete();

	//����ҵ��֪ͨ��Ϣ
	virtual void OnEnterRoom(IUserItem * pUserItem);
	virtual void OnEnterRoomGetUserList_LuckyStar(IUserItem* pUserItem ) ;			//������
	virtual void OnEnterRoomGetUserList_VIPLevelTop( IUserItem* pUserItem ) ;		//����ʹڽ���
	virtual void OnEnterRoomGetUserList_VIPLevelBlackDiamond(IUserItem * pUserItem);//����ʹڽ���
	virtual void OnEnterRoomGetUserList_VIPLevelDiamond(IUserItem* pUserItem);		//��ʯ�ʹڽ���  
	virtual void OnEnterRoomGetUserList_Blink(IUserItem* pUserItem ) ;				//�����ǳ�
	virtual void OnEnterRoomGetUserList_GiftStar( IUserItem* pUserItem ) ;			//����֮��
	virtual void OnEnterRoomGetUserList_Crest(IUserItem * pUserItem);				//���û�����
	virtual void OnEnterRoomGetUserList_Event(IUserItem * pUserItem, uint8 unIndex);//�������� 
	virtual void OnKickUserRsp(uint32 unDstUIN);
	virtual void OnKickUserNotify(uint32 unSrcUIN, uint32 unDstUIN);
	virtual void OnAddBlackRsp(uint32 unDstUIN);
	virtual void OnAddBlackNotify(uint32 unSrcUIN, uint32 unDstUIN);
	virtual void OnLockIpRsp(uint32 unDstUIN);
	virtual void OnLockIpNotify(uint32 unSrcUIN, uint32 unDstUIN);

	//ɳ��֪ͨ��Ϣ
	virtual void OnBuySofaNotify(CSofaItem * pSofaItem);
	virtual void OnSofaInfoUpdate(std::vector<CSofaItem*> vecSofaItem);

// �Ի�������
	enum { IDD = IDD_ROOM_PARENT_DLG };

public:
	//�Ӵ�����Ϣ��Ӧ
	afx_msg LRESULT OnClickStamp(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClickSpeaker(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClickWishSong(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClickUserList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDBClickUserList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClickStampList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClickChangeVoice(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClickChangeVoiceList(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClickFlyingText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClickSofaName(WPARAM wParam, LPARAM lParam);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PostNcDestroy();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);
	afx_msg void OnClose() ;
	afx_msg void OnTimer(UINT_PTR nIDEvent) ;
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) ;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg LRESULT OnPostPaint(WPARAM wParam, LPARAM lParam);//����Ƥ����Ϣ
	afx_msg LRESULT OnModifyNameClickClose( WPARAM wParam ,LPARAM lParam ) ;
	//afx_msg LRESULT OnBtnTaskClick( WPARAM wParam ,LPARAM lParam ) ;
	afx_msg LRESULT OnBtnFansHover( WPARAM wParam ,LPARAM lParam ) ;
	afx_msg LRESULT OnBtnFansLeave( WPARAM wParam ,LPARAM lParam ) ;
	afx_msg LRESULT OnClickMsgBoxGoToRegister(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMouseMove(UINT nHitTest, CPoint point);
	
	void NotifyCreateSkinItem();

	void OnClickBtnCollectRoom();          //����ղط���

	//void DrawGifButton();
	//void MoveGifButton(BOOL bShow);

	void ShowFans(int nIndex);  //��ʾĳ���϶�Ӧ������˿���а�
	void MoveBtnFans(BOOL bShow); 
	void MoveBtnUnDealSong(BOOL bShow);//�ƶ�δ���������Ŀ��λ��
	void SetUnDealSongBtn(int nIndex, int songCount);//����ĳ����δ���������Ŀ

	DECLARE_MESSAGE_MAP()
public:
	void OnClickStamp() ;
	void OnClickEmotion( CWnd* pParentWnd ) ;
	void SetNetState() ;//�����Լ�����·״̬
	RoomAVLogic* GetRoomAvLogic(){ return m_pRoomAvLogic ;} ;

	void OnClickHerfLink( CString& strName , CString& strUUID , CString& str179ID , int nType , CString strIndex = L"") ;
	void OnClickStampLink( CString& strName , CString& strUUID ) ;						//����򣬵���˸���
	void OnClickNameLink( CString& strName , CString& strUUID ) ;						//���롢�������򣬵���� ����
	void OnClickPrivateLink( CString& strName , CString& strUUID , CString& str179ID ) ;					//����鿴˽������
	void OnClickP2PAccept( CString& strName ,CString& strUUID ) ;						//ͬ��һ��һ˽��
	void OnClickP2PRefuse( CString& strName ,CString& strUUID ) ;						//�ܾ�һ��һ˽��
	void OnClickTempNotice( CString& strTempNotice , CString& strUUID ) ;				//ת������ʱ����
	void OnClickVoiceLink( CString& strName , CString& strUUID ) ;						//���ѡ�������
	void OnClickNoRemind(CString& strUUID);
	void OnClickPublicAccept(CString& strName, CString& strUUID, CString& strIndex);
	void OnClickPublicRefuse(CString& strName, CString& strUUID, CString& strIndex);
	void OnClickHrefMark();
	void OnOutPutHtmlMouseOver( CRect& CWindowRect , ENM_HTML_TYPE nHtmlType ) ;					//bSpeakerΪtureʱΪ������
	void OnOutPutHtmlMouseOut( CRect& CWindowRect , ENM_HTML_TYPE nHtmlType ) ;
	void OnSendMsg() ;
	void OnSendAutoMsg(uint32 unDstUin);
	//void OnClickBtnStatus();//���״̬
	//void OnClickBtnAudioSet();//�����Ƶ��ͷ
	void SetMyStatus(BOOL bOnLine);
	//afx_msg LRESULT OnClickBtnAutoReplyMsg(WPARAM wParam, LPARAM lParam);//����Զ��ظ�ĳ��˵� 
	afx_msg void OnMenuOnline();
	//afx_msg LRESULT OnClickMenuAudioSet(WPARAM wParam, LPARAM lParam);//�����Ƶ�˵� 

	void OnClickSpeakerShortCut(std::wstring strName, bool bBigSpeaker = false) ;
	void OnClickWishShortCut(std::wstring strName) ;
	void OnClickRoomShortCut(uint32 unRoomID) ;
	void OnClickGameReward(std::wstring strUrl);

	void CreateSpeakerDlg(CString strInitContent, core::ENM_LoudSpeakerType enmType) ;
	void CreateWishSpeakerDlg(CString strInitContent) ;

	void SendOpenPrivate( uint32 unDstUin ) ;
	void SendRequestP2PMic( uint32 unDstUin ) ;
	void OnResponseP2PRspAccept( uint32 dstuin ) ;
	void OnSetMicStatus( int16 nIndex , int16 nStatus ) ;
	void CleanAVLogic() ;
	void DrawBtnFans(int nIndex); //����ĳ���Ϸ�˿��Ť
	void DeleteFansBtn(uint32 unSrc); //ɾ��ĳ���Ϸ�˿��Ť	
	void DrawBtnUnDealSong(int nIndex, int songCount);//����δ���������Ŀ��������Ŀ�������
	void DeleteUnDealSongBtn(uint32 unSrc);//ɾ��ĳ����δ���������ť
public:
	IUserItem* m_pSelectUserItem ;
	uint32 GetRoomID() { return m_uRoomID; }
	RoomOption * GetRoomOption() { return m_pRoomOption; }
	void FangMai( bool bTips ) ; //����
	void ShowKickDlg(uint8 unType) ;
	bool InitAVLogic( uint32 unRoomID ,uint32 uRelayIP ,uint32 uRelayPort , uint32 iKey , RoomModule& Module ) ;
	void RestRelayServer( uint32 uRelayIP ,uint32 uRelayPort ) ;
	void SetRoomMicVolume( uint32 unMicVolume ) ;
	void CloseMic() ;
	void OpenMic() ;
	void SetAllVideoCfg( int iDevice ) ;
	void OnUpdateMoney( uint32 unMoney , BOOL bFirstInit = FALSE )	;		//����Ǯ��
	void InitPublicMic( std::vector<room_user_info>& vecPubMic ) ;  //����ʱ�����б�
	void OnUserInfo( IUserItem* pUserItem ) ;			//�û���Ϣ
	void OnOtherUserInfo(uint32 unUIN,bool isMan,bool IsActor = false);  //�����û���Ϣ
	void OnAgentInfo(IUserItem* pUserItem);        //������Ϣ
	void OnHallHeadImageUpdate(uint32 unUIN) ;
	void OnGetFansRsp(Event const&evt); //��ȡ��˿�������ݷ��غ���

	void AddGiftInfo( uint32 srcuin , uint32 dstuin , uint32 unCount , 
		uint16 unGiftid, uint16 unType, uint32 time )  ;

	void CreateLuckyInfoList( uint32 srcuin ,uint32 dstuin ,uint32 unCount ,uint16 unGiftid ,
		std::vector<SendGiftLuckyInfo>& vecLuckyInfo, uint32 time ) ;
	
	void OnNotifyPlutusAward( uint32 unSrcUIN , uint32 un179ID ,std::wstring& strDecodeName ,
		std::wstring strRoomName ,std::vector<uint16>& vecMoneys , uint32 unGiftID ) ;

	int GetSenToComboInfo(vector<SenToComboInfo>& vSenToComboInfoList ) ;
	uint32 GetGiftBaseListCount( uint32 unDstuin ,uint32 unGiftid ) ;
	void AdjustGiftBaseListCountAndGiftInfoList( uint32 unDstuin ,uint32 unGiftid ) ;
	void OnLuckyMessage(uint32 unSrc179ID, uint16 unLuckyTimes, std::wstring strUserName, std::wstring strRoomName);
	void OnClickNeedGiftWord( IGiftItem * pGiftItem , IUserItem *pUserItem , uint16 unCount ) ;
public:
	void OnCycleTrigger();
	uint32 GetPulicMicUINByIndex( int nIndex ) ;
	void SetSendObj( CString strName , uint32 unUIN ) ;
	void SetChatObj( CString strName , uint32 unUIN ) ;
	void BackMessage( UINT32 dstuin , MessageFont& stFont , std::wstring strText , ENM_SendMessageType enmType , bool bAutoMsg = FALSE) ;
	bool GetAMessageBack( SendMessageEvent& message ) ;
	void SetPublicOutputGotoEndAble( BOOL bAble ) ;
	void SetPrivateOutputGotoEndAble( BOOL bAble ) ;
	void SetSpeakerOutputGotoEndAble( BOOL bAble ) ;
	void CleanPublicOutput();
	void CleanPrivateOutput();
	void CleanSpeakerOutput();

	void OnRoomRightSendToChange( CString& strSelText ) ;
	void OnPaodaoSendToChange( CString& strSelText ) ;

	void InsertPaoDaoText(CString strSrcName , CString strDstName , CString strGiftWord ,uint32 unSrc179ID , 
	uint32 unDst179ID ,  uint16 unGiftID ,uint16 unCount , CString& strTime ) ;
	void InsertPrivateText(CString& strText ) ; //����˽���Ҵ�����С��ʱ��˸����
	void InsertPublicText(CString& strText ) ;
	void InsertSpeakerText(CString& strText ) ;
	void InsertSystemSpeaker(CString& strText ) ;
	void ClearSpeakerMsg();
	void FlashRoomWindow() ;
	void InsertRoomMidInputDefaultText(CString& strText);

	void OnRequestShow_NeedSelect() ;
	void OnRequestShow_Failed() ;
	void OnRequestShow_Public( uint8 unIndex , uint32 unTime ) ;//�Լ����Ϲ���
	void OnRequestShow_WaitingList() ;
	void OnRequestShow_PublicNotify( uint32 unSrcUIN , uint8 unIndex , uint16 unTime ) ;//�������Ϲ���
	void OnRequestShow_Private() ;
	void OnExitShowNotify( uint32 srcuin , int nType ) ;
	void OnOpenPrivate( uint32 unDstUIN ) ;
	void OnPushOnShow_Success( uint32 unDstUIN , uint8 unIndex ) ;//��������ɹ�
	void OnPullOffShowRsp_Success( uint32 unDstUIN ) ;
	void OnOpVideoAudioRsp( uint32 nOpAVType ,uint32 unUIN ) ;
	void OnOpVideoAudioNotify( uint32 nOpAVType ,uint32 unUIN ) ;
	void OnRespnseP2PNotifyAccept( uint32 unSrcUIN ) ;  //һ��һ˽��
	void OnNotifyPrivateShow( std::vector<uint32>& vecUIN) ;

	void OnSignature(   ) ;
	void OutPutNoticeMsg( ) ; //������ʱ�ķ��乫��
	void OnWelecomeWords( ) ;
	void OnGuestRegister();
	BOOL IsCoverWndVisible() ;
	BOOL IsGuideWndVisible();

	void ClosedRegisterDlg( ) ;
	void OnClickRegister();

	void OnSetRoomInfo( uint32 unSrcUIN ) ;

	int GetFlyTextEffect();
	void SetFlyTextEffect(int nType);
	//void UpdateAudioMode();
	ScreenEffectManager * GetEffectManager();
	//DragonZ:
	//CRoomLeftDlg* GetRoomLeftDlg(){ return m_pRoomLeftDlg ;} ;
	CRoomTopManager* GetRoomTopManager(){ return m_pRoomTopManager; };
	CRoomMidDlg* GetRoomMidDlg(){return m_pRoomMidDlg ;};
	CRoomRightDlg* GetRoomRightDlg(){return m_pRoomRightDlg ;};

	CLoudSpeakerManager * GetLoudSpeakerManager() { return m_pLoudSpeakerManager; }

	long GetPlutusAwardLeftMoney() ;	//��ȡ������ʱδ�ӵ�ʣ����
	long GetLuckLeftMoney() ;
	void AddBottomUserInfo();
	CStatReport& GetStatReportInstance()
	{
		return m_ipStatReport;
	}

	void ShowGuide();
	
	void ReloadGiftData();
	
	void ShowEnterRoomGuide();
	void InitSofaList();
	void UpdateSofa(uint32 unIndex);
	void OnSofaChat(uint32 unSrcUIN, uint32 unDstUIN, CString strText, bool bPublic);
	void ClearSofaList();

	void OnClickOrderSong(uint32 unIndex = 0);
	void ShowOrderSongDlg();
	void UpdateSongList(uint32 unIndex, uint32 unSongerID, bool bRefresh = false, bool bSort = true);
	void UpdateOrderList(uint32 unSelfID, bool bActor);
	void SendGetSongList();
	void OnOrderSongRsp(uint32 unSongerID, bool bSuccess);
	void UpdateUndealCount();
	void OnSongTakeOrderRsp(uint32 unResult);
	void UpdateMarkList(uint32 unSelfID);
	void OnInitRoomActor();
private:
	afx_msg LRESULT OnPrivateMicDlgClose( WPARAM wParam ,LPARAM lParam ) ;
	afx_msg LRESULT OnP2PMicDlgClose( WPARAM wParam ,LPARAM lParam ) ;
	afx_msg LRESULT OnIpStatReport( WPARAM wParam, LPARAM lParam );  //��ȡ����IP��ַ��Ӧ����
	void PlutusAward( ) ;

	//�����Ƿ����׷�����һ��
	bool OutPutGift() ;

	void CreatePrivateMic(CString strSrcName , uint32 srcuin ,uint32 un179ID , uint16 nUserStatus ) ;
	void CreateP2PMic( uint32 UIN ) ;
	void CloseMicActive( IUserItem* pMyUserItem ) ;
	void CloseMicPassive( IUserItem* pSrcUserItem  ) ; 
	void CloseP2PPassive( IUserItem* pSrcUserItem ) ;

	void ClosePublicMic(uint32 UIN ) ;
	BOOL ClosePrivateMic(uint32 UIN ) ;
	void CloseP2PMic( uint32 UIN ) ;
	
	void SetRoomName() ;
	void InitMicSlider() ;

	//void OnClickBtnCloseSound() ;				//�ر�����
	//void OnClickBtnOpenSound() ;

	//void ShowAudioTest();

	void MoveTicker();  //�����λ�õ���
	void OnMyHeadImgUpdate();

	void MoveModifyNameTipWnd();  //�޸��ǳ�λ�õ���
	//void SetRichLevel(IUserItem * pUserItem);
	//void SetRichLevelTip();

	//void MoveTaskDlg();
	//void MoveBtnTask(BOOL bShow);
	//void DrawBtnTask();

	void UpdateSongMarkDlg(int nIndex = 0);			//�����������л�����������
	uint32 CheckActorOnMic();						//�����Ƿ�������

//	void DrawChatWithMeTip();
//	void DrawFlashFrame();
//	void MoveFlashFrame();
//	void MoveChatWithTip();
	void MovePaoDao();
	void OnClickBtnIconIntro();

	void OnActorSpeak();
	void OnAgentSpeak();
private:
	CComPtr<ISkinEngine> m_pSkinEngine;
//	CVDCComboBox m_comboAudioMode;

	common::ui::CTickerStatic m_RoomTitleTicker;
    //DragonZ:
	//CRoomLeftDlg *  m_pRoomLeftDlg;			//�������ӶԻ���
	CRoomTopManager* m_pRoomTopManager;     //�����ϰ벿���߼�������

	CRoomMidDlg *   m_pRoomMidDlg;			//�������ӶԻ���
	CRoomRightDlg * m_pRoomRightDlg;		//�������ӶԻ���
	CRoomBottomLeftDlg* m_pRoomBottomLeftDlg;//����ײ����ӶԻ���

	CStampDlg * m_pStampDlg ;				//���¶Ի���
	CEmotionDlg *m_pEmotionDlg ;			//����Ի���
	//CPngDlg* m_pPngDlg ;					//��ͼ�Ի���
	CChangeVoiceDlg * m_pChangeVoiceDlg;	//�������Ի���
	CFlyingTextInputDlg * m_pFlyingTextInputDlg;	//��������Ի���

	//CShowAudioTestDlg *m_pAudioTest;		//��Ƶ���ԶԻ���

	RoomBusiness * m_pRoomBusiness;
	HtmlOutPutManager* m_pHtmlOutPutManager ;

	map<uint32 , CPrivateMicDlg*> m_mPrivateMicDlg ;  // <UUID ,CPrivateMicDlg*>  ˽��
	CP2PChatDlg* m_pP2PChatDlg ;						  //һ��һ˽�Ĵ���
	CScrollBtnDlg *m_pScrollBtnDlg;
	RoomAVLogic *m_pRoomAvLogic ;
	RoomOption * m_pRoomOption ;						//�������Ժ�RoomBusiness���У�Ϊ��ʾ�û��б��еķ����������Ҫȥ��

	CSpeakerDlg * m_pSpeakerDlg ;
	CWishSpeakerDlg * m_pWishSpeakDlg ;
	CKickDlg * m_pKickDlg ;

	CUserInfoCardDlg* m_pUserInfoCardDlg ;
	CSysSettingDlg* m_pUserInfoDlg ;  //������Ϣ
	COtherUserInfoDlg* m_pOtherUserInfoDlg ; //������Ϣ
	CAnchorFansCardDlg* m_pAnchorFansCardDlg; //��˿���п�Ƭ
	std::map<int, common::ui::PngButton *> m_pMapFansBtn;//���Ϸ�˿��Ť
	std::map<int, common::ui::PngButton *> m_pMapUnDealSongBtn;//δ���������ť
	
	uint32 m_uRoomID;
	uint32 m_nOutGiftIndex ;
	std::list<GiftInfo> m_vGiftInfoList ;
	std::map<uint32, std::list<LuckyInfo>> m_vLuckyInfoList ;
	std::vector<PlutusAwardInfo> m_vPlutusAwardMoneys ;		//������Ǯ��Ϣ
	ScreenEffectManager * m_pEffectManager;
	map<uint32 ,map<uint32 ,RecvGiftCountInfo > > m_mGiftBaseList ;	

	//CSliderCtrl m_MicSliderCtrl;
	//CSliderCtrl m_SpeakerSliderCtrl;

	CCoverWnd* m_pCoverWnd ;
	CStatReport m_ipStatReport;
	CGiftWordsDlg* m_pGiftWordsDlg ;

	//�޸��ǳ���ʾ��
	CModifyNameTipWnd* m_pModifyNameTipWnd;

	//common::ui::GifButton *m_pRichLevelBtn;
	bool m_bShowRichLevel;
	
	//CTaskDlg* m_pTaskDlg;
	//common::ui::PngButton *m_pBtnTask;

	CGuideFlash * m_pGuideFlash;

	CEnterRoomGuide * m_pEnterRoomGuideDlg;
	//��������
	//common::ui::FlashFrameWnd * m_pFlashFrameWnd;
	//CModifyNameTipWnd* m_pChatWithMeTip;
	
	//���
	COrderSongDlg* m_pOrderSongDlg;

	map<int , CPublicMicDlg*> m_mPublicMicDlg ;
	CPaodaoStaitc *m_pPaodaoStatic ;
	CIconIntroductionDlg* m_pIconIntroducDlg;

	COutputHtmlEditImpl* m_pSpeakerHtml;										//��������ؼ�
	CSpeakerOutputLogic m_SpeakerLogic;											//��������߼�
	CLoudSpeakerManager * m_pLoudSpeakerManager;								//���ȹ����߼�

	CPayDlg* m_pPayDlg;

public:
//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//	afx_msg void OnCbnSelchangeComboRoomBottomAudiomode();	
	afx_msg void OnMove(int x, int y);

	void GetFleshGuidRect(CString& strRect);
	//��������ϵͳ
	//DragonZ:V3.0ȥ���������½ǵ�����
	//void UpdateTaskInfo();
	//void TaskToRegister();//������򿪵�ע��
	//void TaskToClose();//����������Ͻ�����
	
	//CSelfInfoAndSetDlg���е���
	void ShowSelfUserInfo();
	CComPtr<ISkinEngine> GetSkinEngine(){ return m_pSkinEngine; };
	void OnClickNameLink( CString& strName , uint32 unUUID );

	void SetCollectRoom(BOOL bCollected);//���÷����Ƿ��ղ�
	void OnClickRoomPay(CString strUrl); //���������ĳ�ֵ 
	void OnClickGotoRegister();//�����ʾ��Ŀ�ȥע���
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
