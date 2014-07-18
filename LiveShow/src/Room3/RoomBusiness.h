#pragma once
#include "usermanager\UserManager.h"
#include "coredefine.h"
#include "globaluidefine.h"
#include "HtmlOutPutManager.h"
#include "HallDefine.h"
#include "sofa\SofaManager.h"
#include "ordersong\OrderSongManager.h"

struct IRoomBusinessSink 
{
	virtual void OnEnterRoom(IUserItem * pUserItem) = 0;									//�û����뷿��
	virtual void OnEnterRoomGetUserList_LuckyStar(IUserItem* pUserItem ) = 0;				//������
	virtual void OnEnterRoomGetUserList_VIPLevelTop( IUserItem* pUserItem ) = 0 ;			//����ʹ��û�����
	virtual void OnEnterRoomGetUserList_VIPLevelBlackDiamond(IUserItem * pUserItem) = 0;	//����ʹ��û�����
	virtual void OnEnterRoomGetUserList_VIPLevelDiamond( IUserItem* pUserItem) = 0;			//��ʯ�ʹ��û�����
	virtual void OnEnterRoomGetUserList_Blink(IUserItem* pUserItem ) = 0 ;					//�����ǳ�	
	virtual void OnEnterRoomGetUserList_GiftStar( IUserItem* pUserItem ) = 0 ;				//����֮��
	virtual void OnEnterRoomGetUserList_Crest(IUserItem * pUserItem) = 0 ;					//���û�����
	virtual void OnEnterRoomGetUserList_Event(IUserItem * pUserItem, uint8 unIndex) = 0;	//��������
	virtual void OnKickUserRsp(uint32 unDstUIN) = 0;						//������Ӧ
	virtual void OnKickUserNotify(uint32 unSrcUIN, uint32 unDstUIN) = 0;	//����֪ͨ
	virtual void OnAddBlackRsp(uint32 unDstUIN) = 0;						//������Ӧ
	virtual void OnAddBlackNotify(uint32 unSrcUIN, uint32 unDstUIN) = 0;	//����֪ͨ
	virtual void OnLockIpRsp(uint32 unDstUIN) = 0;							//��IP��Ӧ
	virtual void OnLockIpNotify(uint32 unSrcUIN, uint32 unDstUIN) = 0;		//��IP֪ͨ
};

class RoomOption ;
class RoomBusiness
{
public:
	RoomBusiness(uint32 roomid, RoomOption * pRoomOption, UserManager * pUserManager, CSofaManager * pSofaManager, IRoomBusinessSink * pRoomBusinessSink);
	~RoomBusiness(void);

	void OnWelecomeWords(  RoomOption* pRoomOption ) ;

	UserManager * GetUserManager() { return m_pUserManager; }
	CSofaManager * GetSofaManager()	{ return m_pSofaManager; }
	COrderSongManager * GetOrderSongManager() { return m_pOrderSongManager; }
	void UpdateAllRoomMic( uint32 unMicVolume ) ;//������˷�����
	uint32 GetRoomID(){ return m_roomid ;}
	RoomOption* GetRoomOption() ; 
public:
	//�����¼�
	void ProcessGetUserListRsp( Event const& evt) ;
	void ProcessGetWaitingListRsp( Event const& evt) ;
	void ProcessEnterRoomNotify(Event const& evt) ;
	void ProcessLeaveRoomNotify(Event const& evt) ;
	void ProcessNotifyUserInfoUpdate(Event const& evt) ;
	void ProcessQueryClientInfoRsp(Event const& evt) ;
	void ProcessSetRoomInfoRsp(Event const& evt) ;
	void ProcessSetRoomInfoNotify(Event const& evt) ;
	void ProcessGetRoomInfoRsp(Event const& evt) ;
	void ProcessLockRoomNotify(Event const& evt) ;  //��ͣ����
	void ProcessGetSofaListRsp(Event const& evt) ;
	void ProcessBuySofaRsp(Event const& evt) ;
	void ProcessBuySofaNotify(Event const& evt) ;
	void ProcessNotifyClearSofaList(Event const& evt) ;

	//����
	void ProcessSendMessageRsp(Event const& evt) ;
	void ProcessSendMessageNotify(Event const& evt) ;

	//��
	void ProcessRequestShowRsp(Event const& evt) ;
	void ProcessRequestShowNotify(Event const& evt) ;
	void ProcessExitShowNotify(Event const& evt) ;
	void ProcessOpenPrivateRsp(Event const& evt) ;
	void ProcessPushOnShowRsp(Event const& evt) ;					//��������
	void ProcessPushOnShowNotify(Event const& evt) ;
	void ProcessPullOffShowRsp(Event const& evt) ;					//��������
	void ProcessPullOffShowNotify(Event const& evt) ;
	void ProcessOpVideoAudioRsp( Event const& evt) ;				//�򿪡��ر�����Ƶ
	void ProcessOpVideoAudioNotify( Event const& evt) ;	
	void ProcessRequestP2PRsp(Event const& evt) ;
	void ProcessRequestP2PNotify(Event const& evt) ;
	void ProcessResponseP2PRsp(Event const& evt) ;
	void ProcessResponseP2PNotify(Event const& evt) ;
	void ProcessNotifyPrivateShow(Event const& evt) ;				//˽���б�
	void ProcessSetMicStatusRsp( Event const& evt ) ;				//����ʹ�ô���
	void ProcessSetMicStatusNotify( Event const& evt ) ;
	void ProcessAnswerPushOnShowRsp(Event const& evt);

	//����
	void ProcessKickUserRsp(Event const& evt) ;
	void ProcessKickUserNotify(Event const& evt) ;
	void ProcessAddBlackRsp(Event const& evt) ;
	void ProcessAddBlackNotify(Event const& evt) ;
	void ProcessLockIpRsp(Event const& evt) ;		
	void ProcessLockIpNotify(Event const& evt) ;
	void ProcessShutUpRsp(Event const& evt) ;
	void ProcessShutUpNotify(Event const& evt) ;
	void ProcessUnLockShutUpRsp(Event const& evt) ; 
	void ProcessUnLockShutUpNotify(Event const& evt) ;
	void ProcessAddTitleRsp(Event const& evt) ;						//��ӹ���Ա
	void ProcessRemoveTitleRsp(Event const& evt) ;					//ȡ������Ա
	void ProcessAddTitleNotify(Event const& evt) ;
	void ProcessRemoveTitleNotify(Event const& evt) ;

	//����
	void ProcessSendGiftRsp(Event const& evt) ;						//����
	void ProcessSendGiftNotify(Event const& evt) ;	
	void ProcessNotifyGiftOverTime(Event const& evt) ;				//���ﵽ��
	void ProcessNotifyPlutusAward(Event const& evt) ;				//����
	void ProcessSendFlyWordsRsp(Event const& evt) ;					//����
	void ProcessSendFlyWordsNofity(Event const& evt) ;
	void ProcessNotifyMoneyUpdate(Event const& evt) ;				//Ǯ�Ҹ���
	void ProcessNotifyOfficeNotice(Event const& evt) ;				//�ٷ�����
	void ProcessNotifyRichStar(Event const& evt ) ;					//�Ƹ�����

	//���
	void ProcessUpdateSongListRsp(Event const& evt ) ;			//���¸����б�
	void ProcessGetSongListRsp(Event const& evt ) ;				//��ø����б�
	void ProcessOrderSongRsp(Event const& evt ) ;				//�����Ӧ
	void ProcessOrderSongNotify(Event const& evt ) ;			//���֪ͨ
	void ProcessTakeOrderRsp(Event const& evt ) ;				//��������Ӧ
	void ProcessTakeOrderNotify(Event const& evt ) ;			//������֪ͨ
	void ProcessGetOrderListRsp(Event const& evt ) ;			//����ѵ�����б�
	//����
	void ProcessMarkSongRsp(Event const& evt ) ;				//������Ӧ
	void ProcessMarkSongNotify(Event const& evt ) ;				//����֪ͨ

	//������Ϣ����
	void ProcessMyInfoUpdate() ;
	void ProcessMyVipLevelUpdate();
	void ProcessMyRichLevelUpdate();

public:
	void OnGetUserList(std::vector<core::room_user_info> & userlist);
	void OnGetWaitingList(std::vector<uint32> & vecWaitinglist);

	void OnEnterRoomNotify(core::room_user_info & userinfo);
	void OnLeaveRoomNotify(uint32 UIN);
	void OnUserStatusChange(uint32 UIN, uint16 unStatus, bool bAdd);
	void OnUserTitleChange(uint32 unSrcUIN , uint32 unDstUIN , uint16 unTitle);
	void OnUserStampChange(uint32 unDstUIN, uint16 unStampID);
	void OnUpdateWaitingList(uint32 UIN, bool bAdd);  //���� ����
	void OnUserChangeVoice(uint32 unDstUIN, uint16 unChangeVoiceID);

	void OnOpVideoAudioOK( uint32 nOpAVType ,uint32 unUIN ) ;

	void OnSpeakerNotify(uint32 unSrcUIN, core::ENM_LoudSpeakerType enmType, std::wstring strMessage);

	void OnSendGiftRsp( SendGiftRspEvent * pInfo ) ;
	void OnSendGiftNotify( SendGiftNotifyEvent *pInfo ) ;
	void OnNotifyGiftOverTime( uint32 unDstUIN , uint32 unGiftID ) ;
	void OnGetRoomInfoRsp( ) ;					//���乫��


	void CollectRoom() ;  //�ղط���
	uint32 GetSearchSeqNo() ;
	void UserStampChange( uint32 unDstUIN, uint16 unStampID ) ;//ӡ�±��

	CString GetRegisteUrl() ;
	CString GetUpdateVipUrl() ;
	CString GetRequestRoomUrl() ;
	CString GetFeedBackRoomUrl() ;
	CString GetPayUrl() ;
	CString GetLevelUpUrl();
	CString GetCopyRoomUrl();
	CString GetTeachAnnounceUrl();//��ȡ��̳��ַ
	CString GetRoomPayUrl();
	CString GetServiceUrl();

	BOOL IsBlockChat( uint32 unUIN ) ;
	void UnBlockChat(uint32 unUIN ) ;
	void BlockChat( uint32 unUIN ) ;		

	void CreatePrivateMicDlgPos() ;
	void GetPrivateMicDlgPos( int& nPosX , int& nPosY , int& nIndex ) ;
	void ErasePrivateMicDlgPos( int nIndex ) ;

	void KickLeaveRoom(uint32 unRoomID, Hall::MsgBox179 msgbox179);

	uint32 GetCaiZiIntervalTime( core::ENM_VipLevel nVipLevel ) ;
private:
	uint16 GetUserStatusByIndex( uint8 unIndex ) ;	
private:
	uint32 m_roomid;
	RoomOption * m_pRoomOption;	
	UserManager * m_pUserManager;
	CSofaManager * m_pSofaManager;
	COrderSongManager * m_pOrderSongManager;
	IRoomBusinessSink * m_pRoomBusinessSink;
	uint32 m_nSeqNo ;
	std::vector<PrivateMicDlgPos> m_vPrivateMicDlgPos ;
};
