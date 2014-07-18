#pragma once
#include "HtmlBuild.h"
#include "GlobalRoomDefine.h"
#include "roomsetting/RoomOption.h"

class HtmlEditImpl ;
class RoomOption ;
class SpeakerMsg;

class CRoomParentDlg ;
class CSofaItem;
class HtmlOutPutManager
{
public:
	HtmlOutPutManager( CRoomParentDlg* pParentDlg ) ;
	~HtmlOutPutManager() ;
	
	void OnEnterRoomGetUserList_VIPLevelTop( IUserItem* pUserIterm ) ;
	void OnEnterRoomGetUserList_VIPLevelBlackDiamond( IUserItem* pUserIterm ) ;
	void OnEnterRoomGetUserList_VIPLevelDiamond(IUserItem* pUserItem);
	void OnEnterRoomGetUserList_GiftStar( IUserItem* pUserIterm ) ;
	void OnEnterRoomGetUserList_Crest( IUserItem* pUserItem ) ;
	void OnEnterRoomGetUserList_Blink( IUserItem* pUserItem ) ;
	void OnEnterRoomGetUserList_LuckyStar( IUserItem* pUserItem ) ;
	void OnEnterRoomGetUserList_Event(IUserItem * pUserItem, uint8 unIndex);
	void OnEnterRoom( IUserItem * pUserItem ) ;
	void OnLeaveRoom( uint32 srcuin ) ;

	void OnSendMsgSuccess( SendMessageEvent& message ) ;

	void OnSendPublicMsgRsp( uint32 srcuin , uint32 dstuin , CString& strText , MessageFont& stFont ) ;
	void OnPublicMsgNotify( uint32 srcuin , uint32 dstuin , CString& strText , MessageFont& stFont  ) ;						//����

	void OnPrivateMsg( uint32 srcuin , uint32 dstuin , CString& strText , MessageFont& stFont , bool bNotify , bool bAutoMsg = FALSE) ;						//˽��

	void OnTempNoticeMsg(uint32 srcuin ,CString& strText , MessageFont& stFont) ;					//��ʱ����

	void OnWelecomeWords( RoomOption* pRoomOption ) ;	//��ӭ��
	void OnActorAutoSpeak(IUserItem* pUserItem); //�����Զ�����
	void OnAgentAutoSpeak(IUserItem* pUserItem);//�����Զ�����
	void OnShowGiftStar(IUserItem* pUserItem);
	void OnNoticeMsg( CString& strText ) ;//���乫��,strText�ں�������Ϣ
	void OnNoticeMsg( CString& strText , MessageFont& stFont) ;						//���乫��
	void OnOfficialNocice( CString& strText ) ;
	void OnSendMsg_NoPublic() ; //���ܹ���
	void OnSendMsg_NoCaiZi() ;	//���ܷ��Ͳ���
	void OnUserTitleChange( uint32 srcuin ,uint32 dstuin ,uint16 unTitle ) ;		//����Ա�ƺű��
	void OnShutUpNotifyEvent( uint32 srcuin , uint32 dstuin , uint32 unLeftTime ) ;						//����
	void OnSendMsgRsp_Fast() ;					//������Ϣ̫��
	void OnSendMsgRsp_PublicForbid() ;			//���ı���ֹ
	void OnSendMsgRsp_CaiZiForbid() ;			//��������ֹ
	void OnSendMsgRsp_UsrForbid( uint32 unLeftTime ) ;				//�û�������
	void OnSendMsgRsp_NoPermission() ;			//��Ȩ��
	void OnSendMsgRsp_PublicVip() ;
	void OnSendMsgRsp_PublicReg() ;
	void OnNotEnoughGold() ;					//��Ҳ���
	void OnNotRepeat() ;						//��ֹ�ظ�����
	void OnMsgEmpty() ;							//������ϢΪ��	
	void OnNotCaiZiTime( core::ENM_VipLevel nVipLevel , uint32 nLeftTime ) ;						//���ַ��ͼ��δ��10��
	void OnSendMsgLimitedTime(uint32 unLeftTime);
	void OnCopyRoomUrl();

	void OnUserStampChangeRsp( uint32 unDstUIN, uint16 unStampID) ;
	void OnUserStampChangeNotify( uint32 unSrcUIN , uint32 unDstUIN, uint16 unStampID ) ;		//����
	void OnRequestShow_WaitingList( bool freeshow_opened ) ;
	void OnRequestShow_Failed( core::ENM_RequestShowResult nResult ) ;  //��������ʧ��
	void OnRequestShow_Already_OnShow() ;
	void OnRequestShow_Public( uint8 unIndex ) ;   //�Լ����Ϲ���
	void OnRequestShow_PublicNotify( uint32 unSrcUIN ) ;
	void OnRequestShow_Private( ) ;				//�Լ�����˽��
	void OnRequestShow_PrivateNotify( uint32 srcuin ) ; 
	void OnRequestShow_InOtherRoom() ;
	void OnRequestShow_WaitButOnMic( uint32 srcuin ) ;
	void OnRequestShow_WaitingOnMic() ;
	void OnRequestShow_Success() ;
	void OnExitShowSelf( IUserItem *pUserItem  ) ;
	void OnExitShowNotify( uint32 unSrcUIN , int nType ) ;
	void OnExitP2P( uint32 unUIN  ) ;
	void OnKickOutRsp( uint32 unDstUIN ) ;
	void OnKickOutNotify( uint32 srcuin ,uint32 unDstUIN ) ;
	void OnAddBlackNotify( uint32 unSrcUIN , uint32 unDstUIN ) ;
	void OnLockIpNotify( uint32 unSrcUIN , uint32 unDstUIN ) ;
	void OnSpeakerMsg( core::ENM_LoudSpeakerType enmType , CString& strText , MessageFont& stFont , SpeakerInfo& stInfo);
	void OnSpeakerLuckyMsg(CString& strText, SpeakerInfo& stInfo, uint16 unGiftID);
	void OnSpeakerPlutusAward(CString& strText, SpeakerInfo& stInfo, uint16 unGiftID); //����
	void OnSpeakerSystemMsg(CString& strText);
	void OnSpeakerGameMsg(CString& strText);
	void OnSpeakerLuxuryMsg(SpeakerInfo& stSrcInfo, SpeakerInfo& stDstInfo, CString& strRoomName, uint16 unGiftID, uint16 unCount);
	void OnUserChangeVoiceRsp( uint32 unDstUIN, uint16 unChangeVoiceID) ;
	void OnUserChangeVoiceNotify( uint32 unSrcUIN , uint32 unDstUIN, uint16 unChangeVoiceID ) ;		//������

	void OnOpenPrivateRsp_NotOpen() ;			//�ط�û��˽���
	void OnOpenPrivateRsp_NotPermission() ;		//��Ȩ��	
	void OnOpenPrivateRsp_ISFull() ;			//��ǰ�򿪵�˽���Ѵ�����
	void OnOpenPrivateRsp_AlreadyOpened() ;		//�Ѿ��򿪹���
	void OnOpenPrivateRsp_IsSelf();				//���Լ�
	void OnPushOnShowRsp_Success( uint32 dstuin ) ;//��������ɹ�
	void OnPushOnShowRsp_Failed( uint32 dstuin ) ;			   //��������
	void OnPushOnShowRsp_MicLocked() ;
	void OnPushOnShowRsp_OnMic();
	void OnPushOnShowRsp_Mic_HasPlayer();
	void OnPushOnShowRsp_NeedAnswer();			//���뷢���������ͬ��
	void OnPushOnShowRsp_Refuse();				//�Լ��ܾ���������
	void OnPushOnShowRsp_Refuse( uint32 unDstUIN ); //���˾ܾ���������
	void OnPullOffShowRsp_Success( uint32 unDstUIN ) ;
	void OnPullOffShowRsp_Failed() ;
	void OnPushOnShowNotify( uint32 srcuin , uint32 dstuin , uint8 unIndex ) ;
	void OnPuffOffShowNotify( uint32 unSrcUIN ,uint32 unDstUIN ) ;
	void OnSetMicStatusRsp( int nIndex , int nStatus  ) ;
	void OnSetMicStatusNotify( int nIndex , int nStatus , uint32 srcuin ) ;

	void OnRequestP2PRspOK( uint32 dstuin ) ; 
	void OnRequestP2PNotify(  uint32 unSrcUIN ) ;
	void OnRequestP2PRspFailed( uint32 nResult , uint32 dstuin ) ;
	void OnResponseP2PRspFailed( uint32 nResult , uint32 dstuin , ENM_ResponseP2PType enmType ) ;
	void OnResponseP2PRspAccept( uint32 dstuin ) ;		//�Լ�����
	void OnResponseP2PRspRefuse( uint32 dstuin ) ;		//�Լ��ܾ�
	void OnResponseP2PNotifyAccept( uint32 srcuin ) ;		//�Է�����
	void OnResponseP2PNotifyRefuse( uint32 srcuin ) ;		//�Է��ܾ�
	void OnRequestP2PFailed_NotPermission() ;
	void OnKickUserNotPermission( uint32 unDstUIN ) ;
	void OnKickUserRsp_Success( uint32 dstuin , bool bKickAllVisitor ) ;	
	void OnAddBlackRsp_Success( uint32 dstuin ) ;
	void OnLockIpRsp_Success( uint32 dstuin ) ;
	void OnShutUpRsp_Success( uint32 dstuin ) ;
	void OnUnLockShutUpRsp_Success( uint32 dstuin ) ;
	void OnAddTitleRsp_Success( core::ENM_TitleLevel nTitleLevel , uint32 dstuin ) ;
	void OnAddTitleRsp_IsFull( core::ENM_TitleLevel nTitleLevel , uint32 dstuin ) ;
	void OnAddTitleRsp_IsAdmin_InOther( core::ENM_TitleLevel nTitleLevel , uint32 dstuin ) ;
	void OnRemoveTitleRsp_Success( core::ENM_TitleLevel nTitleLevel , uint32 dstuin ) ;
	void OnAddTitleNotify( uint32 unSrcUIN ,uint32 unDstUIN ,core::ENM_TitleLevel nTitleLevel , uint32 unRoomID ) ;
	void OnRemoveTitleNotify( uint32 unSrcUIN ,uint32 unDstUIN , core::ENM_TitleLevel nTitleLevel ,  uint32 unRoomID ) ;
	void OnOperateNotPermission() ;			//���ڽ��ԡ��������Ȩ��
	void OnTopVipClickBlink();
	void OnUnLockShutUpNotify( uint32 unDstUIN ) ;				//�������
	void OnRequestPushOnShowNotify(uint32 unSrcUIN, uint8 unIndex);

	void OnSendGift_NotExist() ;
	void OnSendGift_CanNotSend( uint16 unGiftID ) ;
	void OnSendGift_CanNotSendToVisitor( core::ENM_GiftType enmType ) ;
	void OnSendGift_CanNotSendToManage( ) ;
	void OnPublicGiftTip( uint32 srcuin , uint16 unGiftID , core::ENM_GiftDstType enmDstType ) ;
	void OnPaodaoSheChiGift(core::SendGiftNotifyEvent*) ;//�ݳ޵�������
	void OnLinkEnterGift(uint16 unGiftID) ;			//���������ǳ�����߳ɹ�
	void OnPaodaoSheChiGift( uint32 srcuin , uint32 dstuin ,std::wstring strGiftWord ,uint16 unGiftID , uint16 unCount ,uint32 unTime ) ;
	void OnNotifyPlutusAward( uint32 srcuin , uint32 un179ID , std::wstring& strName ,
		std::wstring strRoomName ,std::vector<uint16>& vecMoneys  , uint16 unGiftID ) ; //����

	void OnPublicChatChange( ENM_RoomPublicChat enmType , uint32 srcuin ) ;
	void OnColorTextChange( bool bColorText , uint32 srcuin ) ;
	void OnFreeShowChange( bool bFreeShow , uint32 srcuin ) ;			//��������
	void OnSignatureChange( std::wstring& strSignature ) ;				//��������

	void SetPublicSheChiGift( uint32 srcuin ,uint32 dstuin ,uint16 unGiftID ,uint32 unCount  ) ;
	void SetPublicNormalGift( GiftInfo& giftinfo, bool reallyOutput ) ;//reallyOutput:�Ƿ�ʵ�����
	void SetPrivateNormalGift( uint32 srcuin , uint32 dstuin ,uint16 unGiftID , uint16 unCount ) ;	
	void SetPrivateFireWork( uint32 srcuin  ) ;
	void SetPrivateSlavo( uint32 srcuin ) ;
	void InsertPrivateTips(const CString& strTitle , const CString& strValue , const CString& strColor ) ;

	bool ProcessSendMsgText( CString& strText , bool bFilter = true ) ; //�����Ƿ����
	void ProcessRecvMsgText( CString& strText , bool bFilter = true ) ; //
	void ProcessRecvNoticeText( CString& strText , bool bFilter = true ) ;//����ķǷ��ʹ���

	//canCheat:��������Ƿ��������(1/2���������),�����Ƿ����׷�����һ��(��������������)
	bool OutPutGift( GiftInfo& giftinfo, bool canCheat ) ;

	void OutPutLucky( LuckyInfo& luckyinfo ) ;
	void PlutusAward( int nPlutesIndex , int nPlutusMoney ) ;

	void OnPrivateShowOff( IUserItem* pUserItem ) ;			//���û��Ѿ���˽��
	void OnModifyRoomName();
	CString GetUserHead( IUserItem* pUserItem ) ;
	CString GetUserItemHeadImg( IUserItem* pUsrItem ) ;//����û���ǰ���º͹�ͼƬ
	CString GetNameAndID(IUserItem * pUserItem);
	void OnBlockChatToMe( std::wstring strName , uint32 un179ID );
	void OnUnBlockChatToMe( std::wstring strName , uint32 un179ID );

	void AutoWelcome( IUserItem* pUserItem ) ;
	void VisitorRegister( IUserItem* pUserItem ) ;
	void OnFlyTextNotify( uint32 unSrcUIN, std::wstring strText );

	CString GetSofaUserHead(CSofaItem * pSofaItem);
	void OnSofaPublicNotify(IUserItem * pUserItem, bool bSameUser = false);
	void OnSofaBeKicked(IUserItem * pUserItem);		//ɳ������
	void OnSofaNewUser(IUserItem * pNewUserItem, IUserItem * pOldUserItem, bool bEmpty = false);		//�û���ɳ��
	void OnSofaNewUser(IUserItem * pNewUserItem, CSofaItem * pSofaItem);
	void OnSofaMyUpdate(IUserItem * pUserItem);		//�Լ�����ɳ��

	void OnModifyFont(); //����ҫVIP���ϲ����޸�����

	void InsertRoomMidInputDefaultText(CString& strText);

	void OnMarkNotify(CString& strSongerName);			//��ʾ�����ȥ����
	void OnMarkSongNotify(CString& strOrderName, CString& strSongName, CString& strMark);//��ʾ����������۽��

private:	
	bool IsPublicMic( uint16 unStatus ) ;
	CString MicChineseIndex( int nIndex ) ;
	void EmotionCodeToPath( CString& strText ) ;

	HtmlBuild m_HtmlBuild ;
	CRoomParentDlg* m_pParentDlg ;
};