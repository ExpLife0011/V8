
#pragma once

#include "51ktv.h"
#include "imodule.h"
#include "coredefine.h"
#include "GlobalManager.h"
#include "RoomDefine.h"
#include "RoomParentEvent.h"
#include "SysSetting/SysSettingDlg.h"

class CRoomParentDlg;
typedef std::map<uint32, CRoomParentDlg*> MapRoomParentDlg;

core::CurInfo GetCurInfo();

class RoomAVLogic ;
class RoomModule : public IModule
{
public:
	RoomModule(void);
	~RoomModule(void);

	virtual void Load(IModuleManager *);
	virtual void Unload();
	virtual void ProcessEvent(Event const&);
	virtual void ProcessMessage(Message const&);
	virtual int32 Invoke(ServiceValue const serviceValue, param);
	void OpenRoomDlg(Room_Create_And_Show * stCreateAndShow);
	CRoomParentDlg* FindRoomParentDlg(uint32 roomid ) ;

	void OnRoomDlgClose(uint32 roomid);
	void UpdatePlutusAwardOrLuckMoney(  uint32 unMoney ) ;  //������ʱ��������Ǯʱ��ҵı�����Լ��н�ʱǮ�ҵı��
	void UpdateAllRoomMoney(uint32 unMoney);
	void ReviseAllRoomMoney( uint32 lMoney ) ; //�뿪����ʱ���������������Ľ�ұ��
	void UpdateAllRoomMic( uint32 unMicVolume ) ;//������˷�����
	void UpdateAllRoomStatus(BOOL bOnLine);//���������뿪״̬
	void CloseMic() ;							//�رջ�Ͳ����˷�
	void OpenMic() ;							//������Ͳ����˷�
	void SetAllRoomVideoCfg( int iDevice ) ;
	void UpdateAllRoomUserStampChange( uint32 unDstUIN, uint16 unStampID ) ;  //ӡ�±��
	//void UpdateAllRoomAudioMode();
	IModuleManager * GetModuleManager(){ return m_pModuleManager ;} ;

	void KickLeaveRoom( uint32 roomid ) ;
	void AddRecentBrowseRoom(uint32 roomId);  //�������������

	void CloseAllRoom();

	bool IsSpeedUpMode()
	{
		return m_bSpeedUpMode;
	}
	bool IsEnteredTheRoom(uint32 unRoomID);
public:
	IModuleManager* m_pModuleManager;
private:
	int32 CreateAndShow(param st ) ;
	int32 GetAudioDeviceList(param st) ;
	int32 GetVideoDeviceList(param st ) ;
	int32 SavePhotoToBmp(param st ) ;
	int32 GetNetState(param st ) ;
	int32 GetRoomList(param st ) ;
	int32 CloseARoom(param st ) ;
	int32 ActiveARoom(param st ) ;
	int32 ClosedRegisterDlg(param st ) ;
	int32 ShowSysSetting(param st );
	int32 GetRichLevelInfo(param st);
	
	void CreateNetStateTimer(uint32 interval);
	void ClearNetStateTimer();
	void OnNetStateTimeOut(uintptr,bool);

	//��ʱ���cpu����
	void CreatePerformanceTimer(uint32 interval);
	void ClearPerformanceTimer();
	void OnPerformanceTimerOut(uintptr,bool);
	
	void NetStateReq(uint32&iRelayIP,struct Service_Av_Net_Status_All& sansa);  //��������Ƶ������������������

	void OnCycleTrigger( Message const& msg );

	void ProcessLoginComplete( Message const& msg ) ;
	//��շ���
	void ProcessCleanRoom(Message const& msg ) ;

	//��������
	void ProcessHallOpenSound(Message const& msg);				//�����򿪹ر�����

	//�û�ͷ���������
	void ProcessHallHeadImageUpdate(Message const& msg ) ;

	//������Դ�������
	void ProcessHallResUpdate(Message const& msg );

	//������Ϣ����
	void ProcessMyInfoUpdate(Message const& msg ) ;
	void ProcessMyVipLevelUpdate(Message const& msg);
	void ProcessMyRichLevelUpdate(Message const& msg);

	//ͨ�õ�Web���ʽӿڷ�����Ӧ
	void ProcessWebGetHttpResp(Event const&evt) ;	

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
	void ProcessNotifyClearSofaList(Event const& evt );
	void ProcessInitOffRoomAcotrRsp(Event const& evt); //���������б�����Ӧ����

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
	void ProcessPushOnShowRsp(Event const& evt ) ;					//��������
	void ProcessPushOnShowNotify(Event const& evt ) ;
	void ProcessPullOffShowRsp(Event const& evt ) ;					//��������
	void ProcessPullOffShowNotify(Event const& evt ) ;
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
	void ProcessSendGiftRsp(Event const& evt ) ;				//����
	void ProcessSendGiftNotify(Event const& evt ) ;	
	void ProcessNotifyGiftOverTime(Event const& evt ) ;			//���ﵽ��
	void ProcessNotifyPlutusAward(Event const& evt ) ;			//����	
	void ProcessNotifyMoneyUpdate(Event const& evt ) ;			//Ǯ�Ҹ���
	void ProcessNotifyOfficeNotice(Event const& evt ) ;			//�ٷ�����
	void ProcessSendFlyWordsRsp(Event const& evt) ;				//������Ӧ
	void ProcessSendFlyWordsNotify(Event const& evt) ;			//����֪ͨ
	void ProcessNotifyRichStar(Event const& evt ) ;				//�Ƹ�����

	//��������
	void ProcessSetSelfInfoRsp(Event const& evt ) ;
	void ProcessGetFansRsp(Event const&evt);                       //��˿����

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

	//����ϵͳ
	//DragonZ:V3.0ȥ���������½ǵ�����
	//void ProcessTaskInfoNotify(Event const& evt);

	
private:
	RoomAVLogic *m_pRoomAvLogic ;
	MapRoomParentDlg m_mapRoomParentDlg;
	typedef void(RoomModule::*MessageFun)(Message const&) ;
	std::map<uint32,MessageFun> m_mMessageFun ;
	typedef void(RoomModule::*EventFun)(Event const& ) ;
	std::map<uint32,EventFun> m_mEventFun ;
	CRoomParentEvent m_RoomParentEvent ;
	CSysSettingDlg* m_pRoomSysSettingDlg;
	int32 m_NetStateTimer;
	int32 m_PerformanceTimer;
	bool m_bSpeedUpMode;//�Ƿ����ģʽ(cpu���ظߣ���������ˢ��������ơ�flash)
	std::vector<uint32> m_vRoomIDList;
	std::map<uint32, bool> m_mapEnteredRoomID;//���ε�¼�������ķ���ID, Ϊtrue��ʾ������ID�ķ���
};