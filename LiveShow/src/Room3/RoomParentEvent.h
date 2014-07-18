#pragma once
#include "51ktv.h"
#include "coredefine.h"

class CRoomParentDlg ;
class CRoomParentEvent
{
public:
	CRoomParentEvent() ;
	~CRoomParentEvent() ;

	void ProcessEvent( CRoomParentDlg* pParentDlg ,Event const&evt );

	//����
	void ProcessGetUserListRsp( Event const& evt ) ;
	void ProcessGetWaitingListRsp( Event const& evt ) ;
	void ProcessEnterRoomNotify(Event const& evt ) ;
	void ProcessLeaveRoomNotify(Event const& evt ) ;
	void ProcessNotifyUserInfoUpdate(Event const& evt ) ;
	void ProcessQueryClientInfoRsp(Event const& evt ) ;
	void ProcessSetRoomInfoRsp(Event const& evt) ;
	void ProcessSetRoomInfoNotify(Event const& evt ) ;
	void ProcessGetRoomInfoRsp(Event const& evt ) ;
	void ProcessLockRoomNotify(Event const& evt ) ;  //��ͣ����
	void ProcessMediaServerResetNotify(Event const& evt ) ;//��ת������IP��ַ���
	void ProcessGetSofaListRsp(Event const& evt );
	void ProcessBuySofaRsp(Event const& evt );
	void ProcessBuySofaNotify(Event const& evt );
	void ProcessNotifyClearSofaList(Event const& evt);


	//����
	void ProcessSendMessageRsp(Event const& evt ) ;
	void ProcessSendMessageNotify(Event const& evt ) ;

	//����
	void ProcessSendLoudSpeakerRsp(Event const& evt ) ;
	void ProcessSendLoudSpeakerNotify(Event const& evt ) ;

	//��
	void ProcessRequestShowRsp(Event const& evt ) ;
	void ProcessRequestShowNotify(Event const& evt ) ;
	void ProcessExitShowNotify(Event const& evt) ;
	void ProcessOpenPrivateRsp(Event const& evt ) ;
	void ProcessPushOnShowRsp(Event const& evt ) ;			//��������
	void ProcessPushOnShowNotify(Event const& evt ) ;
	void ProcessPullOffShowRsp(Event const& evt ) ;			//��������
	void ProcessPuffOffShowNotify(Event const& evt ) ;
	void ProcessOpVideoAudioRsp( Event const& evt ) ;				//�򿪡��ر�����Ƶ
	void ProcessOpVideoAudioNotify( Event const& evt ) ;	
	void ProcessRequestP2PRsp(Event const& evt ) ;
	void ProcessRequestP2PNotify(Event const& evt ) ;
	void ProcessResponseP2PRsp(Event const& evt ) ;
	void ProcessResponseP2PNotify(Event const& evt ) ;
	void ProcessNotifyPrivateShow(Event const& evt ) ;				//˽���б�
	void ProcessSetMicStatusRsp( Event const& evt ) ;				//����ʹ�ô���
	void ProcessSetMicStatusNotify( Event const& evt ) ;
	void ProcessAnswerPushOnShowRsp(Event const& evt);

	//����
	void ProcessKickUserRsp(Event const& evt ) ;
	void ProcessKickUserNotify(Event const& evt ) ;
	void ProcessAddBlackRsp(Event const& evt ) ;
	void ProcessAddBlackNotify(Event const& evt ) ;
	void ProcessLockIpRsp(Event const& evt ) ;		
	void ProcessLockIpNotify(Event const& evt ) ;
	void ProcessShutUpRsp(Event const& evt ) ;
	void ProcessShutUpNotify(Event const& evt ) ;
	void ProcessUnLockShutUpRsp(Event const& evt ) ; 
	void ProcessUnLockShutUpNotify(Event const&evt ) ;
	void ProcessAddTitleRsp(Event const& evt ) ;				//��ӹ���Ա
	void ProcessRemoveTitleRsp( Event const& evt ) ;			//ȡ������Ա
	void ProcessAddTitleNotify( Event const& evt ) ;
	void ProcessRemoveTitleNotify( Event const& evt ) ;

	//����
	void ProcessSendGiftRsp(Event const& evt ) ;					//����
	void ProcessSendGiftNotify(Event const& evt ) ;	
	void ProcessNotifyGiftOverTime(Event const& evt ) ;			//���ﵽ��
	void ProcessNotifyPlutusAward(Event const& evt ) ;			//����
	void ProcessSendFlyWordsRsp(Event const& evt ) ;			//����
	void ProcessSendFlyWordsNofity(Event const& evt ) ;
	void ProcessNotifyMoneyUpdate(Event const& evt ) ;			//Ǯ�Ҹ���
	void ProcessNotifyOfficeNotice(Event const& evt ) ;			//�ٷ�����
	void ProcessNotifyRichStar(Event const& evt ) ;				//�Ƹ�����

	//���ϵͳ
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

	void OnSendNomalGift( core::ENM_GiftDstType enmDstType ,uint32 unSrcUIN ,uint32 unDstUIN , uint32 unSentCount ,
		uint16 unGiftID  , core::ENM_GiftType enmType, uint32 time ) ;
	void OnSendNomalGiftNotify( core::ENM_GiftDstType enmDstType ,uint32 unSrcUIN ,uint32 unDstUIN , uint32 unSentCount , 
		uint16 unGiftID  , core::ENM_GiftType enmType, uint32 time ) ;

private:
	CRoomParentDlg* m_pParentDlg ;
	typedef void(CRoomParentEvent::*EventFun)(Event const& ) ;
	std::map<uint32,EventFun> m_mEventFun ;
};