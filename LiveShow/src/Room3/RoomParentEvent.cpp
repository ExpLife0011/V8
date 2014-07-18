#include "stdafx.h"
#include "RoomParentEvent.h"
#include "RoomParentDlg.h"
#include "personalsetting\PersonalConfig.h"
#include "loudspeaker\SpeakerMsg.h"
#include "gift\GiftManager.h"
#include "Room.h"
#include "autoreply\AutoReplyConfig.h"
#include "SendEventManager.h"

#include "..\CommonLibrary\include\utility\SystemHelper.h"
#include "..\CommonLibrary\\include\utility\StringHelper.h"

CRoomParentEvent::CRoomParentEvent( )
{
	//����
	m_mEventFun[core::EVENT_VALUE_CORE_GET_USERLIST_RSP] = &CRoomParentEvent::ProcessGetUserListRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_GET_WAITTINGLIST_RSP] = &CRoomParentEvent::ProcessGetWaitingListRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_ENTER_ROOM_NOTIFY] = &CRoomParentEvent::ProcessEnterRoomNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_LEAVE_ROOM_NOTIFY] = &CRoomParentEvent::ProcessLeaveRoomNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_NOTIFY_ROOM_USER_INFO_UPDATE] = &CRoomParentEvent::ProcessNotifyUserInfoUpdate ;
	m_mEventFun[core::EVENT_VALUE_CORE_QUERY_CLIENTINFO_RSP] = &CRoomParentEvent::ProcessQueryClientInfoRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_SET_ROOMINFO_RSP] = &CRoomParentEvent::ProcessSetRoomInfoRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_SET_ROOMINFO_NOTIFY] = &CRoomParentEvent::ProcessSetRoomInfoNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_GET_ROOMINFO_RSP] = &CRoomParentEvent::ProcessGetRoomInfoRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_NOTIFY_ROOM_LOCKED] = &CRoomParentEvent::ProcessLockRoomNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_NOTIFY_MEDIA_SERVER_RESET] = &CRoomParentEvent::ProcessMediaServerResetNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_GET_SOFA_LIST_RSP] = &CRoomParentEvent::ProcessGetSofaListRsp;
	m_mEventFun[core::EVENT_VALUE_CORE_BUY_SOFA_RSP] = &CRoomParentEvent::ProcessBuySofaRsp;
	m_mEventFun[core::EVENT_VALUE_CORE_BUY_SOFA_NOTIFY] = &CRoomParentEvent::ProcessBuySofaNotify;
	m_mEventFun[core::EVENT_VALUE_CORE_NOTIFY_CLEAR_SOFA_LIST] = &CRoomParentEvent::ProcessNotifyClearSofaList;

	//����
	m_mEventFun[core::EVENT_VALUE_CORE_SEND_MESSAGE_RSP] = &CRoomParentEvent::ProcessSendMessageRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_SEND_MESSAGE_NOTIFY] = &CRoomParentEvent::ProcessSendMessageNotify ;

	//����
	m_mEventFun[core::EVENT_VALUE_CORE_SEND_LOUDSPEAKER_RSP] = &CRoomParentEvent::ProcessSendLoudSpeakerRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_SEND_LOUDSPEAKER_NOTIFY] =&CRoomParentEvent::ProcessSendLoudSpeakerNotify ;

	//��
	m_mEventFun[core::EVENT_VALUE_CORE_REQUEST_SHOW_RSP] = &CRoomParentEvent::ProcessRequestShowRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_REQUEST_SHOW_NOTIFY] =&CRoomParentEvent::ProcessRequestShowNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_EXIT_SHOW_NOTIFY] = &CRoomParentEvent::ProcessExitShowNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_OPEN_PRIVATE_RSP] = &CRoomParentEvent::ProcessOpenPrivateRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_PUSH_ON_SHOW_RSP] = &CRoomParentEvent::ProcessPushOnShowRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_PUSH_ON_SHOW_NOTIFY] = &CRoomParentEvent::ProcessPushOnShowNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_PULL_OFF_SHOW_RSP] = &CRoomParentEvent::ProcessPullOffShowRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_PULL_OFF_SHOW_NOTIFY] = &CRoomParentEvent::ProcessPuffOffShowNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_OPERATE_VIDEO_AUDIO_RSP] = &CRoomParentEvent::ProcessOpVideoAudioRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_OPERATE_VIDEO_AUDIO_NOTIFY] = &CRoomParentEvent::ProcessOpVideoAudioNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_REQUEST_P2P_RSP] = &CRoomParentEvent::ProcessRequestP2PRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_REQUEST_P2P_NOTIFY] = &CRoomParentEvent::ProcessRequestP2PNotify ;	
	m_mEventFun[core::EVENT_VALUE_CORE_RESPONSE_P2P_RSP] = &CRoomParentEvent::ProcessResponseP2PRsp ;	
	m_mEventFun[core::EVENT_VALUE_CORE_RESPONSE_P2P_NOTIFY] = &CRoomParentEvent::ProcessResponseP2PNotify;
	m_mEventFun[core::EVENT_VALUE_CORE_NOTIFY_PRIVATE_SHOW] = &CRoomParentEvent::ProcessNotifyPrivateShow ;
	m_mEventFun[core::EVENT_VALUE_CORE_MIC_SET_MIC_STATUS_RSP] = &CRoomParentEvent::ProcessSetMicStatusRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_MIC_SET_MIC_STATUS_NOTIFY] = &CRoomParentEvent::ProcessSetMicStatusNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_ANSWER_PUSH_ON_SHOW_RSP] = &CRoomParentEvent::ProcessAnswerPushOnShowRsp;

	//����
	m_mEventFun[core::EVENT_VALUE_CORE_KICK_USER_RSP] = &CRoomParentEvent::ProcessKickUserRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_KICK_USER_NOTIFY] = &CRoomParentEvent::ProcessKickUserNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_ADD_BLACK_RSP] = &CRoomParentEvent::ProcessAddBlackRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_ADD_BLACK_NOTIFY] = &CRoomParentEvent::ProcessAddBlackNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_LOCK_IP_RSP] = &CRoomParentEvent::ProcessLockIpRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_LOCK_IP_NOTIFY] = &CRoomParentEvent::ProcessLockIpNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_SHUT_UP_RSP] = &CRoomParentEvent::ProcessShutUpRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_SHUT_UP_NOTIFY] =&CRoomParentEvent::ProcessShutUpNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_UNLOCK_SHUTUP_RSP] = &CRoomParentEvent::ProcessUnLockShutUpRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_UNLOCK_SHUTUP_NOTIFY] =&CRoomParentEvent::ProcessUnLockShutUpNotify ;

	m_mEventFun[core::EVENT_VALUE_CORE_ADD_TITLE_RSP] = &CRoomParentEvent::ProcessAddTitleRsp ; 
	m_mEventFun[core::EVENT_VALUE_CORE_REMOVE_TITLE_RSP] = &CRoomParentEvent::ProcessRemoveTitleRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_ADD_TITLE_NOTIFY] = &CRoomParentEvent::ProcessAddTitleNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_REMOVE_TITLE_NOTIFY] = &CRoomParentEvent::ProcessRemoveTitleNotify ;

	//����
	m_mEventFun[core::EVENT_VALUE_CORE_SEND_GIFT_RSP] = &CRoomParentEvent::ProcessSendGiftRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_SEND_GIFT_NOTIFY] = &CRoomParentEvent::ProcessSendGiftNotify ;
	m_mEventFun[core::EVENT_VALUE_CORE_NOTIFY_GIFT_OVER_TIME] = &CRoomParentEvent::ProcessNotifyGiftOverTime ;
	m_mEventFun[core::EVENT_VALUE_CORE_NOTIFY_PLUTUS_AWARD] = &CRoomParentEvent::ProcessNotifyPlutusAward ;
	m_mEventFun[core::EVENT_VALUE_CORE_NOTIFY_MONEY_UPDATE] = &CRoomParentEvent::ProcessNotifyMoneyUpdate ;
	m_mEventFun[core::EVENT_VALUE_CORE_NOTIFY_OFFICIAL_NOTICE] = &CRoomParentEvent::ProcessNotifyOfficeNotice ;
	m_mEventFun[core::EVENT_VALUE_CORE_SEND_FLYWORDS_RSP] = &CRoomParentEvent::ProcessSendFlyWordsRsp ;
	m_mEventFun[core::EVENT_VALUE_CORE_SEND_FLYWORDS_NOTIFY] = &CRoomParentEvent::ProcessSendFlyWordsNofity ;
	m_mEventFun[core::EVENT_VALUE_CORE_NOTIFY_RICH_STAR] = &CRoomParentEvent::ProcessNotifyRichStar ;

	//���
	m_mEventFun[core::EVENT_VALUE_UPDATE_SONGLIST_RSP] = &CRoomParentEvent::ProcessUpdateSongListRsp ;
	m_mEventFun[core::EVENT_VALUE_GET_SONGLIST_RSP] = &CRoomParentEvent::ProcessGetSongListRsp ;
	m_mEventFun[core::EVENT_VALUE_ORDER_SONG_RSP] = &CRoomParentEvent::ProcessOrderSongRsp ;
	m_mEventFun[core::EVENT_VALUE_ORDER_SONG_NOTIFY] = &CRoomParentEvent::ProcessOrderSongNotify ;
	m_mEventFun[core::EVENT_VALUE_PROCESS_ORDER_RSP] = &CRoomParentEvent::ProcessTakeOrderRsp ;
	m_mEventFun[core::EVENT_VALUE_PROCESS_ORDER_NOTIFY] = &CRoomParentEvent::ProcessTakeOrderNotify ;
	m_mEventFun[core::EVENT_VALUE_GET_ORDERLIST_RSP] = &CRoomParentEvent::ProcessGetOrderListRsp ;
	//����
	m_mEventFun[core::EVENT_VALUE_MARK_SONG_RSP] = &CRoomParentEvent::ProcessMarkSongRsp ;
	m_mEventFun[core::EVENT_VALUE_MARK_SONG_NOTIFY] = &CRoomParentEvent::ProcessMarkSongNotify ;
}

CRoomParentEvent::~CRoomParentEvent()
{

}

void CRoomParentEvent::ProcessEvent( CRoomParentDlg* pParentDlg ,Event const& evt )
{
	m_pParentDlg = pParentDlg ;
	std::map<uint32,EventFun>::iterator iter ;
	iter = m_mEventFun.find( evt.eventValue ) ;
	if ( iter != m_mEventFun.end() )
	{
		EventFun fun = iter->second ;
		(this->*fun)( evt ) ;
	}
}



//����
void CRoomParentEvent::ProcessGetUserListRsp( Event const& evt ) 
{
	ASSERT(evt.m_pstExtraInfo != NULL);
	//core::GetUserListRspEvent * pInfo = (core::GetUserListRspEvent*)evt.m_pstExtraInfo;
	//�û���������
	m_pParentDlg->ShowEnterRoomGuide();
}

void CRoomParentEvent::ProcessGetWaitingListRsp( Event const& evt ) 
{
	m_pParentDlg->OnSignature( ) ;
	m_pParentDlg->OutPutNoticeMsg(  ) ;
	m_pParentDlg->OnWelecomeWords(  ) ;	
	m_pParentDlg->OnGuestRegister();
	m_pParentDlg->OnInitRoomActor();
}

void CRoomParentEvent::ProcessEnterRoomNotify(Event const& evt ) 
{

}

void CRoomParentEvent::ProcessLeaveRoomNotify(Event const& evt ) 
{

}

void CRoomParentEvent::ProcessNotifyUserInfoUpdate(Event const& evt ) 
{

}

void CRoomParentEvent::ProcessQueryClientInfoRsp(Event const& evt ) 
{

}

void CRoomParentEvent::ProcessSetRoomInfoRsp(Event const& evt) 
{
	switch( evt.param1 )
	{
	case core::SETROOMINFORESULT_OK:
		{
			core::CurInfo myCurInfo = GetCurInfo() ;
			m_pParentDlg->OnSetRoomInfo( myCurInfo.unUIN ) ;
		}
		break;
	default:break;
	}
}

void CRoomParentEvent::ProcessSetRoomInfoNotify(Event const& evt ) 
{
	core::SetRoomInfoNotifyEvent * pInfo = (core::SetRoomInfoNotifyEvent*)evt.m_pstExtraInfo;
	m_pParentDlg->OnSetRoomInfo( pInfo->unSrcUIN ) ;
}

void CRoomParentEvent::ProcessGetRoomInfoRsp(Event const& evt ) 
{

}

void CRoomParentEvent::ProcessLockRoomNotify(Event const& evt )  //��ͣ����
{

}

//��ת������IP��ַ���
void CRoomParentEvent::ProcessMediaServerResetNotify(Event const& evt ) 
{
	ASSERT(evt.m_pstExtraInfo != NULL ) ;
	core::NotifyMediaServerResetEvent* pInfo = ( core::NotifyMediaServerResetEvent*)evt.m_pstExtraInfo ;
	core::CurInfo myCurInfo = GetCurInfo() ; 
	if ( myCurInfo.bUseDianxin )
	{
		m_pParentDlg->RestRelayServer( pInfo->relayIP_dianxin , pInfo->relayPort_dianxin ) ;
	}
	else
	{
		m_pParentDlg->RestRelayServer( pInfo->relayIP_wangtong , pInfo->relayPort_wangtong ) ;
	}
}

//����
void CRoomParentEvent::ProcessSendMessageRsp(Event const& evt ) 
{
	ASSERT(evt.m_pstExtraInfo != NULL ) ;
	core::SendMessageRspEvent *pInfo = (core::SendMessageRspEvent*)evt.m_pstExtraInfo ;
	core::SendMessageEvent message ;
	if ( m_pParentDlg->GetAMessageBack( message ) )
	{
		switch( pInfo->enmResult)
		{
		case core::SENDMESSAGERESULT_OK:
			{
				m_pParentDlg->GetHtmlOutPutManager()->OnSendMsgSuccess( message ) ;
				if (message.enmType == SENDMESSAGETYPE_PUBLIC && message.stFont.font_style != FONTSTYLETYPE_COLORTEXT)
				{
					m_pParentDlg->OnSofaChat(GetCurInfo().unUIN, message.dstuin, message.message.c_str(), true);
				}
			}
			break ;
		case core::SENDMESSAGERESULT_TOO_FAST:
			{
				//����̫��
				m_pParentDlg->GetHtmlOutPutManager()->OnSendMsgRsp_Fast() ;
			}
			break ;
		case core::SENDMESSAGERESULT_PUBLICCHAT_CLOSED:
			{
				//���ı���ֹ
				m_pParentDlg->GetHtmlOutPutManager()->OnSendMsgRsp_PublicForbid() ;
			}
			break ;
		case core::SENDMESSAGERESULT_COLORTEXT_CLOSED:
			{
				//����������
				m_pParentDlg->GetHtmlOutPutManager()->OnSendMsgRsp_CaiZiForbid() ;
			}
			break ;
		case core::SENDMESSAGERESULT_USER_SHUTUP:
			{
				//�û�������
				m_pParentDlg->GetHtmlOutPutManager()->OnSendMsgRsp_UsrForbid( pInfo->unLeftTime ) ;
			}
			break ;
		case core::SENDMESSAGERESULT_NO_PERMISSION:
			{
				//û��Ȩ��
				m_pParentDlg->GetHtmlOutPutManager()->OnSendMsgRsp_NoPermission() ;
			}
			break ;
		case core::SENDMESSAGERESULT_PUBLICCHAT_VIP:
			{
				m_pParentDlg->GetHtmlOutPutManager()->OnSendMsgRsp_PublicVip() ;
			}
			break;
		case core::SENDMESSAGERESULT_PUBLICCHAT_REG:
			{
				m_pParentDlg->GetHtmlOutPutManager()->OnSendMsgRsp_PublicReg() ;
			}
			break;
		default:
			break ;

		}
	}
}

void CRoomParentEvent::ProcessSendMessageNotify(Event const& evt ) 
{
	ASSERT(evt.m_pstExtraInfo != NULL ) ;
	core::SendMessageNotifyEvent *pInfo = (core::SendMessageNotifyEvent*)evt.m_pstExtraInfo ;
	switch( pInfo->enmType )
	{
	case core::SENDMESSAGETYPE_PUBLIC:
		{
			//����
			//�յ�������Ϣ����һ�������Զ��ظ�����Ϣ
			core::CurInfo myCurInfo = GetCurInfo() ;
			if (pInfo->dstuin == myCurInfo.unUIN && pInfo->stFont.font_style != FONTSTYLETYPE_COLORTEXT)//˵����һ��һ�Ĺ��ģ����Ƕ������˵�,���ҷ��Ĳ��ǲ���
			{
				if (AutoReplyMgr->IsAutoReply() && pInfo->bRejectAutoMsg == FALSE)//�Է����Ƿ��Զ��ظ����Լ��������Զ��ظ����Է������ò������ѣ����յ���Ϣ�󼴿̻ظ��Զ��ظ�
				{
					m_pParentDlg->OnSendAutoMsg(pInfo->srcuin);
				}
			}
			m_pParentDlg->GetHtmlOutPutManager()->OnPublicMsgNotify( pInfo->srcuin , pInfo->dstuin , CString(pInfo->message.c_str()) , pInfo->stFont ) ;	
			if (pInfo->stFont.font_style != FONTSTYLETYPE_COLORTEXT)
			{
				m_pParentDlg->OnSofaChat(pInfo->srcuin, pInfo->dstuin, pInfo->message.c_str(), true);
			}
		}
		break; 
	case core::SENDMESSAGETYPE_PRIVATE:
		{
			//���Ļ�
			if (pInfo->bIsAutoMsg && AutoReplyMgr->IsAutoReply())//�յ������Զ��ظ�����Ϣ�������Լ�Ҳ���������Զ��ظ�
			   return;

			m_pParentDlg->GetHtmlOutPutManager()->OnPrivateMsg( pInfo->srcuin ,pInfo->dstuin , CString(pInfo->message.c_str()) , pInfo->stFont , true , pInfo->bIsAutoMsg) ;
			if (AutoReplyMgr->IsAutoReply() && pInfo->bRejectAutoMsg == FALSE)//�Է����Ƿ��Զ��ظ���û�е㲻�����ѣ��Լ��������Զ��ظ������յ���Ϣ�󼴿̻ظ��Զ��ظ�
			{
				if(pInfo->srcuin != 0)
				   m_pParentDlg->OnSendAutoMsg(pInfo->srcuin);
			}
		}
		break; 
	case core::SENDMESSAGETYPE_TEMP_NOTICE:
		{
			//��ʱ����
			m_pParentDlg->GetHtmlOutPutManager()->OnTempNoticeMsg( pInfo->srcuin , L" "+CString(pInfo->message.c_str()) , pInfo->stFont ) ;
		}
		break;
	case core::SENDMESSAGETYPE_NOTICE:
		{
			//����
			m_pParentDlg->GetHtmlOutPutManager()->OnNoticeMsg( L" "+CString(pInfo->message.c_str()) , pInfo->stFont ) ;
		}
		break; 
	default:
		break;
	}
}

//����
void CRoomParentEvent::ProcessSendLoudSpeakerRsp(Event const& evt ) 
{
	ASSERT(evt.m_pstExtraInfo != NULL);
	core::SendLoudSpeakerRspEvent * pInfo = (core::SendLoudSpeakerRspEvent*)evt.m_pstExtraInfo;

	switch (pInfo->enmResult)
	{
	case core::SENDGIFTRESULT_OK:
		{
			g_RoomModule->UpdateAllRoomMoney( pInfo->unLeftMoney );
		}
		break;
	case core::SENDGIFTRESULT_NOT_ENOUGH_MONEY:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnNotEnoughGold() ;
		}
		break;
	case core::SENDGIFTRESULT_OTHER:
		{

		}
		break;
	case core::SENDGIFTRESULT_UNKNOWN:
		{

		}
		break;
	default:
		break;
	}
}

void CRoomParentEvent::ProcessSendLoudSpeakerNotify(Event const& evt ) 
{
	ASSERT(evt.m_pstExtraInfo != NULL);
	core::SendLoudSpeakerNotifyEvent * pInfo = (core::SendLoudSpeakerNotifyEvent*)evt.m_pstExtraInfo;
	if (pInfo->enmMessageType == core::SendLoudSpeakerNotifyEvent::SPEAKERMESSAGETYPE_LOUD)
	{
		//std::wstring strTemp = pInfo->strMessage;
		//core::MessageFont stFont;
		//SpeakerInfo stInfo;
		//if(CSpeakerMsg::DecodeMessage(strTemp, stFont, stInfo))
		//{	
		//	stInfo.unRichLevel = pInfo->unRichLevel;
		//	CString strSpeaker = strTemp.c_str();
		//	m_pParentDlg->GetHtmlOutPutManager()->OnSpeakerMsg( pInfo->enmType , strSpeaker, stFont, stInfo);
		//}

		//if ( pInfo->enmType >= core::LOUDSPEAKERTYPE_BIG && !CPersonalConfig::GetInstance()->GetIsBlockSpeakerSound())
		//{
		//	std::wstring strPath = common::utility::systemhelper::Get179AppPath();
		//	strPath += L"resource\\sound\\msg.wav";
		//	::PlaySound(strPath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
		//}
		m_pParentDlg->GetLoudSpeakerManager()->ProcessLoudSpeaker(pInfo->enmType, pInfo->strMessage);
	}
	else
	{
		SpeakerInfo stInfo;
		if (pInfo->enmMessageType == core::SendLoudSpeakerNotifyEvent::SPEAKERMESSAGETYPE_LUCKY  
			|| pInfo->enmMessageType == core::SendLoudSpeakerNotifyEvent::SPEAKERMESSAGETYPE_PLUTUSAWARD )
		{
			if ( pInfo->enmMessageType == core::SendLoudSpeakerNotifyEvent::SPEAKERMESSAGETYPE_LUCKY )
			{
				stInfo.enmType = SpeakerInfo::SPEAKERTYPE_LUCKY;
			}			
			else
			{
				stInfo.enmType = SpeakerInfo::SPEAKERTYPE_PLUTUSAWARD ;
			}
			stInfo.strName = pInfo->strName;
			stInfo.un179ID = pInfo->un179id;
			stInfo.unVipLevel = pInfo->unVipLevel;
			stInfo.unRichLevel = pInfo->unRichLevel;
			for (std::vector<uint16>::iterator it = pInfo->vecGiftID.begin(); it != pInfo->vecGiftID.end(); ++it)
			{
				if (GiftManager::GetInstance()->IsStamp(*it))
				{
					stInfo.unStampID = *it;
				}
			}
		}
		else if (pInfo->enmMessageType == core::SendLoudSpeakerNotifyEvent::SPEAKERMESSAGETYPE_SYSTEM)
		{
			stInfo.enmType = SpeakerInfo::SPEAKERTYPE_SYSTEM;
		}
		else if (pInfo->enmMessageType == core::SendLoudSpeakerNotifyEvent::SPEAKERMESSAGETYPE_GAMEREWARD)
		{
			stInfo.enmType = SpeakerInfo::SPEAKERTYPE_GAMEREWARD;
		}
		else if (pInfo->enmMessageType == core::SendLoudSpeakerNotifyEvent::SPEAKERMESSAGETYPE_LUXURY)
		{
			stInfo.strName = pInfo->strName;
			stInfo.un179ID = pInfo->un179id;
			stInfo.unVipLevel = pInfo->unVipLevel;
			stInfo.unRichLevel = pInfo->unRichLevel;
			stInfo.enmType = SpeakerInfo::SPEAKERTYPE_LUXURY;
		}


		CString strContent = pInfo->strMessage.c_str();
		if (stInfo.enmType == SpeakerInfo::SPEAKERTYPE_LUCKY)
		{
			CString strTemp = strContent;
			CString strTimes;
			CString strRoomName;
			int nPos = strContent.Find(L",") ;
			if (nPos != -1)
			{
				strRoomName = strTemp.Left(nPos);
				strTemp = strTemp.Right(strTemp.GetLength() - nPos - 1) ;
				nPos = strTemp.Find(L",");
				if (nPos != -1)
				{
					strTimes = strTemp.Left(nPos) ;
				}
			}
			int nTimes = common::utility::stringhelper::StringToInt(strTimes.GetBuffer(0));
			//500�����н���Ϣֻ��flash�н���ʾ��û�������н���Ϣ���̻�������Ҫ��С����
			if (nTimes > 500 || GiftManager::GetInstance()->IsFirework(pInfo->unGiftID) || GiftManager::GetInstance()->IsSalute(pInfo->unGiftID))
			{
				m_pParentDlg->GetHtmlOutPutManager()->OnSpeakerLuckyMsg(strTemp, stInfo,  pInfo->unGiftID);
			}

			//���ǻ����������Ϣ����Ҫflashչʾ
			if (nTimes >= 500 && strRoomName != L"" && pInfo->unCache == 0)
			{
				m_pParentDlg->OnLuckyMessage(pInfo->un179id, nTimes, pInfo->strName, strRoomName.GetBuffer(0));
			}
		}
		else if (stInfo.enmType == SpeakerInfo::SPEAKERTYPE_SYSTEM)
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnSpeakerSystemMsg(strContent);
		}
		else if ( stInfo.enmType == SpeakerInfo::SPEAKERTYPE_PLUTUSAWARD)
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnSpeakerPlutusAward(strContent,stInfo,pInfo->unGiftID) ;
		}
		else if (stInfo.enmType == SpeakerInfo::SPEAKERTYPE_GAMEREWARD)
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnSpeakerGameMsg(strContent);
		}
		else if (stInfo.enmType == SpeakerInfo::SPEAKERTYPE_LUXURY)
		{
			CString strRoomName, strDstName;
			int nDst179ID, nDstVipLevel, nSendCount;
			CString strTemp = strContent;
			int nPos = strTemp.Find(L"{([])}");
			if (nPos != -1)
			{
				strRoomName = strTemp.Left(nPos);
				strTemp = strTemp.Right(strTemp.GetLength() - nPos - 6);

				nPos = strTemp.Find(L"{([])}");
				if (nPos != -1)
				{
					CString strID = strTemp.Left(nPos);
					nDst179ID = common::utility::stringhelper::StringToInt(strID.GetBuffer(0));
					strTemp = strTemp.Right(strTemp.GetLength() - nPos - 6);

					nPos = strTemp.Find(L"{([])}");
					if (nPos != -1)
					{
						strDstName = strTemp.Left(nPos);
						strTemp = strTemp.Right(strTemp.GetLength() - nPos - 6);

						nPos = strTemp.Find(L"{([])}");
						if (nPos != -1)
						{
							CString strVipLevel = strTemp.Left(nPos);
							nDstVipLevel = common::utility::stringhelper::StringToInt(strVipLevel.GetBuffer(0));

							CString strSendCount = strTemp.Right(strTemp.GetLength() - nPos - 6);
							nSendCount = common::utility::stringhelper::StringToInt(strSendCount.GetBuffer(0));
						}
					}
				}
			}

			SpeakerInfo stDstInfo;
			stDstInfo.strName = strDstName.GetBuffer(0);
			stDstInfo.un179ID = nDst179ID;
			stDstInfo.unVipLevel = nDstVipLevel;
			stDstInfo.unRichLevel = 0;
			stDstInfo.enmType = SpeakerInfo::SPEAKERTYPE_LUXURY;

			m_pParentDlg->GetHtmlOutPutManager()->OnSpeakerLuxuryMsg(stInfo, stDstInfo, strRoomName, pInfo->unGiftID, nSendCount);
		}
	}
}

void CRoomParentEvent::ProcessRequestShowRsp(Event const& evt ) 
{
	ASSERT(evt.m_pstExtraInfo != NULL ) ;
	core::RequestShowRspEvent * pInfo = (core::RequestShowRspEvent*)evt.m_pstExtraInfo ;
	switch( pInfo->enmResult )
	{
	case REQUESTSHOWRESULT_NEED_SELECT:  //��Ҫѡ������˽��
		{
			m_pParentDlg->OnRequestShow_NeedSelect() ;
		}
		break;
	case REQUESTSHOWRESULT_FULL:		//������
	case REQUESTSHOWRESULT_PRIVATE_CLOSED: //����˽���ѹر�
	case REQUESTSHOWRESULT_FAIL:		//����ʧ��
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnRequestShow_Failed( pInfo->enmResult ) ;
			m_pParentDlg->OnRequestShow_Failed( ) ;
		}
		break;
	case REQUESTSHOWRESULT_PUBLIC:  //���Ϲ���
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnRequestShow_Public( pInfo->unIndex ) ;
			m_pParentDlg->OnRequestShow_Public( pInfo->unIndex , pInfo->unTime ) ;
		}
		break;
	case REQUESTSHOWRESULT_WAITTINGLIST: //���뵽�������
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnRequestShow_WaitingList( pInfo->bFreeShowOpened ) ;
			m_pParentDlg->OnRequestShow_WaitingList( ) ;
		}
		break;
	case REQUESTSHOWRESULT_PRIVATE:  //����˽�� ,�����û��б��е�״̬
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnRequestShow_Private() ;
			m_pParentDlg->OnRequestShow_Private() ;
		}
		break;
	case REQUESTSHOWRESULT_ALREADY_ON_SHOW:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnRequestShow_Already_OnShow() ;
			m_pParentDlg->OnRequestShow_Failed( ) ;
		}
		break;
	case REQUESTSHOWRESULT_ONMIC_IN_OTHERROOM: //���������������
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnRequestShow_InOtherRoom() ;
			m_pParentDlg->OnRequestShow_Failed() ;
		}
		break;
	case REQUESTSHOWRESULT_WAIT_BUT_ONMIC: //�����������ʱ����������������
		{
			core::CurInfo myCurInfo = GetCurInfo() ;
			m_pParentDlg->GetHtmlOutPutManager()->OnRequestShow_WaitButOnMic( myCurInfo.unUIN ) ;
			m_pParentDlg->OnRequestShow_Failed() ;
		}
		break;
	case REQUESTSHOWRESULT_WAITTING_ONMIC://�������������󣬹�������
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnRequestShow_WaitingOnMic( ) ;
			m_pParentDlg->OnRequestShow_WaitingList( ) ;
		}
		break;
	default: break;
	}
}

void CRoomParentEvent::ProcessRequestShowNotify(Event const& evt ) 
{
	ASSERT(evt.m_pstExtraInfo != NULL ) ;
	core::RequestShowNotifyEvent* pInfo = (core::RequestShowNotifyEvent*)evt.m_pstExtraInfo ;
	switch( pInfo->enmResult )
	{
	case REQUESTSHOWRESULT_PUBLIC:  //���Ϲ���
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnRequestShow_PublicNotify( pInfo->unSrcUIN ) ;
			m_pParentDlg->OnRequestShow_PublicNotify( pInfo->unSrcUIN , pInfo->unIndex , pInfo->unTime ) ;
		}
		break;
	case REQUESTSHOWRESULT_PRIVATE:  //����˽�� ,�����û��б��е�״̬
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnRequestShow_PrivateNotify( pInfo->unSrcUIN ) ;
		}
		break;
	case REQUESTSHOWRESULT_WAIT_BUT_ONMIC: //�����������ʱ����������������
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnRequestShow_WaitButOnMic( pInfo->unSrcUIN ) ;
			m_pParentDlg->OnRequestShow_Failed() ;
		}
		break;
	default: break;
	}
}

void CRoomParentEvent::ProcessExitShowNotify(Event const& evt)
{
	m_pParentDlg->GetHtmlOutPutManager()->OnExitShowNotify( evt.param1 , evt.param2 ) ;
	m_pParentDlg->OnExitShowNotify( evt.param1 , evt.param2 ) ;

}

void CRoomParentEvent::ProcessOpenPrivateRsp(Event const& evt ) 
{
	switch( evt.param1 )
	{
	case OPENPRIVATERESULT_OK:
		{			
			m_pParentDlg->OnOpenPrivate( evt.param2 ) ;
		}
		break ;
	case OPENPRIVATERESULT_NOT_OPEN:		//�Է�˽��û�д�
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnOpenPrivateRsp_NotOpen() ;
		}
		break ;
	case OPENPRIVATERESULT_NO_PERMISSION:	//û��Ȩ��(����ɫvip�Լ�����)
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnOpenPrivateRsp_NotPermission() ;
		}
		break ;
	case OPENPRIVATERESULT_IS_FULL:		//�ﵽ˽������
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnOpenPrivateRsp_ISFull() ;
		}
		break;
	case OPENPRIVATERESULT_ALREADY_OPENED:	//�Ѿ��򿪹���
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnOpenPrivateRsp_AlreadyOpened() ;
		}
		break;
	case OPENPRIVATERESULT_IS_SELF:	//���Լ�
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnOpenPrivateRsp_IsSelf() ;
		}
		break;
	default: break ;
	}
}

void CRoomParentEvent::ProcessPushOnShowRsp(Event const& evt ) 		//��������
{
	core::PushOnShowRspEvent* pInfo = (core::PushOnShowRspEvent*)evt.m_pstExtraInfo ;
	switch( pInfo->enmResult )
	{
	case core::PUSHONRESULT_OK:
		{
			//�����ɹ�
			m_pParentDlg->GetHtmlOutPutManager()->OnPushOnShowRsp_Success(  pInfo->unDstUIN ) ;
			m_pParentDlg->OnPushOnShow_Success(  pInfo->unDstUIN , pInfo->unIndex ) ;   
		}
		break;
	case core::PUSHONRESULT_NO_PERMISSION:
		{
			//Ȩ�޲���
			m_pParentDlg->GetHtmlOutPutManager()->OnOperateNotPermission() ;
		}
		break;
	case core::PULLOFFRESULT_UNKNOWN:
	case core::PUSHONRESULT_IS_ON_SHOW:
		{
			//�Ѿ�������
			m_pParentDlg->GetHtmlOutPutManager()->OnPushOnShowRsp_Failed( pInfo->unDstUIN ) ;
		}
		break;
	case core::PUSHONRESULT_MIC_IS_LOCKED:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnPushOnShowRsp_MicLocked() ;
		}
		break;
	case core::PUSHONRESULT_NEED_ANSWER:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnPushOnShowRsp_NeedAnswer();
		}
		break;
	default:break;
	}
}

void CRoomParentEvent::ProcessPushOnShowNotify(Event const& evt ) 
{
	core::PushOnShowNotifyEvent* pInfo = (core::PushOnShowNotifyEvent*)evt.m_pstExtraInfo ;
	switch (pInfo->unType)
	{
	case PUSHONNOTIFY_TYPE_NEEDANSWER:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnRequestPushOnShowNotify(pInfo->unSrcUIN, pInfo->unIndex);
		}
		break;
	case PUSHONNOTIFY_TYPE_CONNECT:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnPushOnShowNotify(  pInfo->unSrcUIN , pInfo->unDstUIN ,pInfo->unIndex  ) ;
			m_pParentDlg->OnPushOnShow_Success( pInfo->unDstUIN ,pInfo->unIndex  ) ;
		}
		break;
	case PUSHONNOTIFY_TYPE_REJECT:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnPushOnShowRsp_Refuse(pInfo->unDstUIN);
		}
		break;
	}
}

void CRoomParentEvent::ProcessPullOffShowRsp(Event const& evt ) 		//��������
{
	switch( evt.param1 )
	{
	case core::PULLOFFRESULT_OK:
		{
			//�����ɹ�
			m_pParentDlg->GetHtmlOutPutManager()->OnPullOffShowRsp_Success( evt.param2 )  ;
			m_pParentDlg->OnPullOffShowRsp_Success( evt.param2 ) ;
		}
		break ;
	case core::PULLOFFRESULT_NO_PERMISSION:
		{
			//Ȩ�޲���
			m_pParentDlg->GetHtmlOutPutManager()->OnOperateNotPermission() ;
		}
		break;
	case core::PULLOFFRESULT_IS_OFF_SHOW:
		{
			//��������
			m_pParentDlg->GetHtmlOutPutManager()->OnPullOffShowRsp_Failed() ;
		}
		break;
	}
}

void CRoomParentEvent::ProcessPuffOffShowNotify(Event const& evt ) 
{
	m_pParentDlg->GetHtmlOutPutManager()->OnPuffOffShowNotify( evt.param1 , evt.param2 ) ;
	m_pParentDlg->OnExitShowNotify( evt.param2 , EXIT_SHOW_OTHER ) ;
}

void CRoomParentEvent::ProcessOpVideoAudioRsp( Event const& evt ) 				//�򿪡��ر�����Ƶ
{
	core::OperateVideoAudioRspEvent* pInfo = (core::OperateVideoAudioRspEvent*)evt.m_pstExtraInfo ;
	switch( pInfo->enmResult )
	{
	case OPERATEAVRESULT_OK:
		{
			m_pParentDlg->OnOpVideoAudioRsp(  pInfo->enmType ,pInfo->unDstUIN ) ;
		}
		break;
	case OPERATEAVRESULT_NOT_ON_SHOW:
		{

		}
		break;
	default:break;
	}
}

void CRoomParentEvent::ProcessOpVideoAudioNotify( Event const& evt )
{
	m_pParentDlg->OnOpVideoAudioNotify(  evt.param1 ,evt.param2 ) ;
}

void CRoomParentEvent::ProcessRequestP2PRsp(Event const& evt ) 
{
	if ( evt.param1 == core::CONNECTP2PRESULT_OK )
	{
		m_pParentDlg->GetHtmlOutPutManager()->OnRequestP2PRspOK( evt.param2 ) ;
	}
	else
	{
		m_pParentDlg->GetHtmlOutPutManager()->OnRequestP2PRspFailed( evt.param1 ,evt.param2 ) ;
	}
}

void CRoomParentEvent::ProcessRequestP2PNotify(Event const& evt ) 
{
	m_pParentDlg->GetHtmlOutPutManager()->OnRequestP2PNotify( evt.param1 ) ;
}

void CRoomParentEvent::ProcessResponseP2PRsp(Event const& evt ) 
{
	core::ResponseP2PRspEvent* pInfo = ( core::ResponseP2PRspEvent*)evt.m_pstExtraInfo ;
	if ( pInfo->enmResult == core::CONNECTP2PRESULT_OK )
	{
		if ( pInfo->enmType == core::RESPONSEP2PTYPE_ACCEPT )
		{
			//�Լ�����һ��һ˽��
			m_pParentDlg->GetHtmlOutPutManager()->OnResponseP2PRspAccept( pInfo->unDstUIN ) ;
			m_pParentDlg->OnResponseP2PRspAccept( pInfo->unDstUIN ) ;
		}
		else if ( pInfo->enmType == core::RESPONSEP2PTYPE_REFUSE )
		{
			//�Լ��ܾ�һ��һ˽��   ,�������ϲ�������Ϣ
		//	m_pParentDlg->GetHtmlOutPutManager()->OnResponseP2PRspRefuse( pInfo->unDstUIN ) ;
		}
	}
	else
	{
		m_pParentDlg->GetHtmlOutPutManager()->OnResponseP2PRspFailed( pInfo->enmResult , pInfo->unDstUIN , pInfo->enmType ) ;
	}
}

void CRoomParentEvent::ProcessResponseP2PNotify(Event const& evt ) 
{
	core::ResponseP2PNotifyEvent* pInfo = (core::ResponseP2PNotifyEvent*)evt.m_pstExtraInfo ;
	switch( pInfo->enmType )
	{
	case core::RESPONSEP2PTYPE_ACCEPT:			//ͬ��
		{
			core::CurInfo myCurInfo = GetCurInfo() ; 
			if ( pInfo->unDstUIN == myCurInfo.unUIN )
			{
				m_pParentDlg->GetHtmlOutPutManager()->OnResponseP2PNotifyAccept( pInfo->unSrcUIN ) ;
				m_pParentDlg->OnRespnseP2PNotifyAccept( pInfo->unSrcUIN ) ;
			}
		}
		break;
	case core::RESPONSEP2PTYPE_REFUSE:			//�ܾ�
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnResponseP2PNotifyRefuse( pInfo->unSrcUIN ) ;
		}
		break;
	}
}

void CRoomParentEvent::ProcessNotifyPrivateShow(Event const& evt ) 				//˽���б�
{
	core::NotifyPrivateShowEvent * pInfo = (core::NotifyPrivateShowEvent*)evt.m_pstExtraInfo;
	m_pParentDlg->OnNotifyPrivateShow( pInfo->vecUIN ) ;
}

void CRoomParentEvent::ProcessSetMicStatusRsp( Event const& evt ) //����ʹ�ô���
{
	uint16 nIndex = evt.param1&0xFFFF;
	uint16 nStatus = evt.param1>>16 ;
	core::ENM_SetMicStatusResult nResult = (core::ENM_SetMicStatusResult)evt.param2 ;
	switch( evt.param2 )
	{
	case core::SETMICSTATUSRESULT_OK:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnSetMicStatusRsp( nIndex , nStatus ) ;
			m_pParentDlg->OnSetMicStatus( nIndex ,nStatus ) ;
		}
		break;
	case core::SETMICSTATUSRESULT_NO_PERMISSION:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnOperateNotPermission() ;
		}
		break;
	case core::SETMICSTATUSRESULT_UNKNOWN:
		{

		}
		break;
	default:break;
	}
}

void CRoomParentEvent::ProcessSetMicStatusNotify( Event const& evt ) 
{
	uint16 nIndex = evt.param1&0xFFFF;
	uint16 nStatus = evt.param1>>16 ;
	uint32 unSrcUIN = evt.param2 ;
	m_pParentDlg->GetHtmlOutPutManager()->OnSetMicStatusNotify( nIndex , nStatus , unSrcUIN ) ;
	m_pParentDlg->OnSetMicStatus( nIndex ,nStatus ) ;
}

//����
void CRoomParentEvent::ProcessKickUserRsp(Event const& evt ) 
{
	core::KickUserRspEvent * pInfo = (core::KickUserRspEvent*)evt.m_pstExtraInfo ;
	switch( pInfo->enmKickResult )
	{
	case core::KICKRESULT_OK:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnKickUserRsp_Success( pInfo->unDstUIN , pInfo->bKickAllVisitor ) ;
/*			if ( bKickAllVisitor )
			{
				std::vector<IUserItem*>::iterator iter ;
				std::vector<IUserItem*> vecGuestList ;
				m_pUserManager->GetGuestList( vecGuestList ) ;
				for ( iter = vecGuestList.begin() ; iter != vecGuestList.end() ; ++iter )
				{
					IUserItem* pUserItem = *iter ;
					m_pHtmlOutPutManager->OnKickOutRsp( pUserItem->GetUserUIN() ) ;
					m_pRoomDlg->OnLeaveRoom( pUserItem->GetUserUIN() ) ;
				}
				m_pUserManager->DeleteAllGuest();
			}
			else
			{
				m_pRoomDlg->OnLeaveRoom( unDstUIN ) ;
				m_pUserManager->DeleteUserItem( unDstUIN ) ; 
			}*/		
		}
		break;
	case core::KICKRESULT_NO_PERMISSION:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnOperateNotPermission() ;
		}
		break;
	case core::KICKRESULT_OTHER_IS_KING:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnKickUserNotPermission( pInfo->unDstUIN ) ;
		}
		break;
	default:break;
	}
}

void CRoomParentEvent::ProcessKickUserNotify(Event const& evt ) 
{

}

void CRoomParentEvent::ProcessAddBlackRsp(Event const& evt ) 
{
	switch( evt.param1 )
	{
	case core::KICKRESULT_OK:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnAddBlackRsp_Success( evt.param2 ) ;
		//	m_pParentDlg->OnLeaveRoom( evt.param2 ) ;
		}
		break;
	case core::KICKRESULT_NO_PERMISSION:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnOperateNotPermission() ;
		}
		break;
	case core::KICKRESULT_OTHER_IS_KING:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnKickUserNotPermission( evt.param2 ) ;
		}
		break;
	default:break;
	}
}

void CRoomParentEvent::ProcessAddBlackNotify(Event const& evt ) 
{

}

void CRoomParentEvent::ProcessLockIpRsp(Event const& evt ) 
{
	switch( evt.param1 )
	{
	case core::KICKRESULT_OK:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnLockIpRsp_Success( evt.param2 ) ;
		}
		break;
	case core::KICKRESULT_NO_PERMISSION:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnOperateNotPermission() ;
		}
		break;
	case core::KICKRESULT_OTHER_IS_KING:
		{

		}
		break;
	default:break;
	}
}

void CRoomParentEvent::ProcessLockIpNotify(Event const& evt ) 
{

}

void CRoomParentEvent::ProcessShutUpRsp(Event const& evt ) 
{
	switch( evt.param1 )
	{
	case core::KICKRESULT_OK:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnShutUpRsp_Success( evt.param2 ) ;
		}
		break;
	case core::KICKRESULT_NO_PERMISSION:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnOperateNotPermission() ;
		}
		break;
	default:break;
	}
}

void CRoomParentEvent::ProcessShutUpNotify(Event const& evt ) 
{
	core::ShutUpNotifyEvent* pInfo = (core::ShutUpNotifyEvent*)evt.m_pstExtraInfo ;
	m_pParentDlg->GetHtmlOutPutManager()->OnShutUpNotifyEvent( pInfo->srcUIN , pInfo->dstUIN , pInfo->unLeftTime ) ;
}

void CRoomParentEvent::ProcessUnLockShutUpRsp(Event const& evt ) 
{
	switch( evt.param1 )
	{
	case core::KICKRESULT_OK:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnUnLockShutUpRsp_Success( evt.param2 ) ;
		}
		break;
	case core::KICKRESULT_NO_PERMISSION:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnOperateNotPermission() ;
		}
		break;
	default:break;
	}
}

void CRoomParentEvent::ProcessUnLockShutUpNotify(Event const&evt ) 
{
	ASSERT(evt.param2 != 0);
	m_pParentDlg->GetHtmlOutPutManager()->OnUnLockShutUpNotify( evt.param2 ) ;
}

void CRoomParentEvent::ProcessAddTitleRsp(Event const& evt ) 				//��ӹ���Ա
{
	core::AddTitleRspEvent* pInfo = (core::AddTitleRspEvent*)evt.m_pstExtraInfo ;
	switch( pInfo->enmResult )
	{
	case  core::CHANGETILERESULT_OK:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnAddTitleRsp_Success( pInfo->enmLevel , pInfo->unDstUIN ) ;
		}
		break;
	case core::CHANGETILERESULT_NO_PERMISSION:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnOperateNotPermission( ) ;
		}
		break;
	case core::CHANGETILERESULT_IS_FULL:  //����Ա��������
		{ 
			m_pParentDlg->GetHtmlOutPutManager()->OnAddTitleRsp_IsFull( pInfo->enmLevel , pInfo->unDstUIN ) ;
		}
		break;
	case core::CHANGETILERESULT_IS_ADMIN_INOTHER: //�Ѿ�����������Ĺ���Ա
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnAddTitleRsp_IsAdmin_InOther( pInfo->enmLevel , pInfo->unDstUIN ) ;
		}
		break;
	default: break;
	}
}

void CRoomParentEvent::ProcessRemoveTitleRsp( Event const& evt ) 			//ȡ������Ա
{
	core::RemoveTitleRspEvent* pInfo = (core::RemoveTitleRspEvent*)evt.m_pstExtraInfo ;
	switch( pInfo->enmResult )
	{
	case core::CHANGETILERESULT_OK:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnRemoveTitleRsp_Success( pInfo->enmLevel , pInfo->unDstUIN ) ;
		}
		break;
	case core::CHANGETILERESULT_NO_PERMISSION:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnOperateNotPermission( ) ;
		}
		break;
	default:break;
	}
}

void CRoomParentEvent::ProcessAddTitleNotify( Event const& evt ) 
{
	ASSERT( evt.m_pstExtraInfo != NULL ) ;
	core::AddTitleNotifyEvent* pInfo = (core::AddTitleNotifyEvent*)evt.m_pstExtraInfo ;
	m_pParentDlg->GetHtmlOutPutManager()->OnAddTitleNotify( pInfo->unSrcUIN , pInfo->unDstUIN , pInfo->enmLevel , m_pParentDlg->GetRoomBusiness()->GetRoomID() ) ;
	if (GetCurInfo().unUIN == pInfo->unDstUIN)
	{
		m_pParentDlg->AddBottomUserInfo();
	}
}

void CRoomParentEvent::ProcessRemoveTitleNotify( Event const& evt ) 
{
	ASSERT( evt.m_pstExtraInfo != NULL ) ;
	core::RemoveTitleNotifyEvent* pInfo = (core::RemoveTitleNotifyEvent*)evt.m_pstExtraInfo ;
	m_pParentDlg->GetHtmlOutPutManager()->OnRemoveTitleNotify( pInfo->unSrcUIN , pInfo->unDstUIN , pInfo->enmLevel, m_pParentDlg->GetRoomBusiness()->GetRoomID() ) ;
	if (GetCurInfo().unUIN == pInfo->unDstUIN)
	{
		m_pParentDlg->AddBottomUserInfo();
	}
}

//����
void CRoomParentEvent::ProcessSendGiftRsp(Event const& evt ) 					//����
{
	ASSERT(evt.m_pstExtraInfo != NULL);
	core::SendGiftRspEvent * pInfo = (core::SendGiftRspEvent*)evt.m_pstExtraInfo;
	switch( pInfo->enmResult )
	{
	case core::SENDGIFTRESULT_ALL_REBOT:
		pInfo->unSentCount = 1 ;
	case core::SENDGIFTRESULT_OK:
		{
			core::CurInfo myCurInfo = GetCurInfo() ;
			if ( myCurInfo.unUIN == pInfo->unDstUIN )
			{
				m_pParentDlg->GetHtmlOutPutManager()->OnLinkEnterGift(pInfo->unGiftID) ;		//���������ǳ����߳ɹ�
				g_RoomModule->UpdateAllRoomMoney(pInfo->unLeftMoney);			//����Ǯ�ҵ���ʾ
				return ;
			}
			if ( pInfo->enmType == core::GIFTTYPE_STAMP )
			{
				//����
				m_pParentDlg->GetHtmlOutPutManager()->OnUserStampChangeRsp( pInfo->unDstUIN, pInfo->unGiftID ) ;
			}
			else if ( core::GIFTTYPE_CHANGEVOICE == pInfo->enmType )
			{
				m_pParentDlg->GetHtmlOutPutManager()->OnUserChangeVoiceRsp( pInfo->unDstUIN, pInfo->unGiftID ) ;
			}
			else if ( core::GIFTTYPE_SHECHI == pInfo->enmType )
			{
				//�ݳ�Ʒ
				m_pParentDlg->GetHtmlOutPutManager()->OnPaodaoSheChiGift( myCurInfo.unUIN , pInfo->unDstUIN ,pInfo->strAttachMessage ,
					pInfo->unGiftID , pInfo->unSentCount ,pInfo->unTime );

				m_pParentDlg->GetHtmlOutPutManager()->SetPublicSheChiGift( myCurInfo.unUIN , pInfo->unDstUIN , pInfo->unGiftID , 
					pInfo->unSentCount  ) ;
			}
			else if ( core::GIFTTYPE_NORMAL == pInfo->enmType )
			{
				OnSendNomalGift( pInfo->enmDstType ,myCurInfo.unUIN , pInfo->unDstUIN , pInfo->unSentCount , 
					pInfo->unGiftID, pInfo->enmType, pInfo->unTime ) ;
			}
			
			m_pParentDlg->CreateLuckyInfoList( myCurInfo.unUIN, pInfo->unDstUIN, pInfo->unSentCount, 
				pInfo->unGiftID, pInfo->vecLuckyInfo, pInfo->unTime) ; //�н���Ϣ
			
			if ( pInfo->enmResult == core::SENDGIFTRESULT_OK )
			{
				g_RoomModule->UpdateAllRoomMoney(pInfo->unLeftMoney);			//����Ǯ�ҵ���ʾ
			}

			IUserItem * pDstUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN(pInfo->unDstUIN);
			IUserItem * pMyUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
			std::wstring strSrcUserName;
			std::wstring strDstUserName = L"";
			uint32 unDst179ID = 0;
			uint32 unSrc179ID = 0;
			if (pDstUserItem != NULL)
			{
				strDstUserName = pDstUserItem->GetUserName();
				unDst179ID = pDstUserItem->GetUser179ID();
			}
			if (pMyUserItem != NULL)
			{
				strSrcUserName = pMyUserItem->GetUserName();
				unSrc179ID = pMyUserItem->GetUser179ID();
			}
			m_pParentDlg->GetEffectManager()->ProcessSendGift(pInfo->unSentCount, pInfo->unGiftID, strSrcUserName, unSrc179ID, strDstUserName, unDst179ID);
		}
		break;
	case core::SENDGIFTRESULT_NOT_ENOUGH_MONEY:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnNotEnoughGold() ;
		}
		break;
	case core::SENDGIFTRESULT_IS_NOT_EXIST://���߲�����
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnSendGift_NotExist() ;
		}
		break;
	case core::SENDGIFTRESULT_UPDATE_ASSET_FAILED://�����ʲ�ʧ��
		{

		}
		break;
	case core::SENDGIFTRESULT_NO_PERMISSION://û��Ȩ��
		{

		}
		break;
	case core::SENDGIFTRESULT_CAN_NOT_SEND://������ʹ������
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnSendGift_CanNotSend( pInfo->unGiftID ) ;
		}
		break;
	case core::SENDGIFTRESULT_CAN_NOT_SEND2VISITOR:	//���ܶ��ο�ʹ��
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnSendGift_CanNotSendToVisitor( pInfo->enmType ) ;
		}
		break;
	case core::SENDGIFTRESULT_CAN_NOT_SEND2MANAGE://���ܶԳ��ܺ�Ѳ��ʹ�õ���
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnSendGift_CanNotSendToManage(  ) ;
		}
		break;
	case core::SENDGIFTRESULT_OTHER:
		{

		}
		break;
	default: break;
	}
}

void CRoomParentEvent::ProcessSendGiftNotify(Event const& evt ) 
{
	core::SendGiftNotifyEvent* pInfo = (core::SendGiftNotifyEvent*)evt.m_pstExtraInfo ;
	core::CurInfo myCurInfo = GetCurInfo() ;
	if ( pInfo->enmType == core::GIFTTYPE_STAMP )
	{
		//����
		m_pParentDlg->GetHtmlOutPutManager()->OnUserStampChangeNotify( pInfo->unSrcUIN ,pInfo->unDstUIN, pInfo->unGiftID ) ;
	}
	else if ( pInfo->enmType == core::GIFTTYPE_CHANGEVOICE )
	{
		m_pParentDlg->GetHtmlOutPutManager()->OnUserChangeVoiceNotify( pInfo->unSrcUIN, pInfo->unDstUIN, pInfo->unGiftID ) ;
	}
	else if ( pInfo->enmType == core::GIFTTYPE_SHECHI )
	{
		//�ݳ�
		m_pParentDlg->GetHtmlOutPutManager()->OnPaodaoSheChiGift(pInfo) ;

		if ( !CPersonalConfig::GetInstance()->GetIsBlockGiftMsg() )
		{
			m_pParentDlg->GetHtmlOutPutManager()->SetPublicSheChiGift( pInfo->unSrcUIN , pInfo->unDstUIN , pInfo->unGiftID , 
				pInfo->unSentCount ) ;
		}
		m_pParentDlg->GetHtmlOutPutManager()->SetPrivateNormalGift( pInfo->unSrcUIN , pInfo->unDstUIN ,  pInfo->unGiftID ,  pInfo->unSentCount );
	}
	else
	{
		OnSendNomalGiftNotify( pInfo->enmDstType ,pInfo->unSrcUIN , pInfo->unDstUIN , pInfo->unSentCount , 
			pInfo->unGiftID, pInfo->enmType, pInfo->unTime ) ;
	}
	if ( !CPersonalConfig::GetInstance()->GetIsBlockGiftMsg() )
	{
		m_pParentDlg->CreateLuckyInfoList( pInfo->unSrcUIN , pInfo->unDstUIN , pInfo->unSentCount , 
			pInfo->unGiftID , pInfo->vecLuckyInfo, pInfo->unTime ) ; //�н���Ϣ
	}		

	if (pInfo->enmType != core::GIFTTYPE_SHECHI)
	{
		m_pParentDlg->GetEffectManager()->ProcessSendGift(pInfo->unSentCount, pInfo->unGiftID, pInfo->strSrcName, pInfo->unSrc179ID, pInfo->strDstName, pInfo->unDst179ID);
	} 
}

void CRoomParentEvent::ProcessNotifyGiftOverTime(Event const& evt ) 			//���ﵽ��
{

}

void CRoomParentEvent::ProcessNotifyPlutusAward(Event const& evt ) 			//����	
{
	ASSERT( evt.m_pstExtraInfo != NULL ) ;
	core::NotifyPlutusAwardEvent* pInfo = (core::NotifyPlutusAwardEvent*)evt.m_pstExtraInfo ;
	m_pParentDlg->OnNotifyPlutusAward( pInfo->unSrcUIN , pInfo->un179ID , 
		common::utility::stringhelper::XMLEncode(pInfo->strName) ,pInfo->strRoomName , pInfo->vecMoneys , pInfo->unGiftID ) ;
}

void CRoomParentEvent::ProcessNotifyMoneyUpdate(Event const& evt ) 			//Ǯ�Ҹ���
{

}

void CRoomParentEvent::ProcessNotifyOfficeNotice(Event const& evt ) 			//�ٷ�����
{
	ASSERT( evt.m_pstExtraInfo != NULL ) ;
	core::NotifyOfficialNoticeEvent* pInfo = (core::NotifyOfficialNoticeEvent*)evt.m_pstExtraInfo ;
	m_pParentDlg->GetHtmlOutPutManager()->OnOfficialNocice( CString(pInfo->strMessage.c_str()) ) ;
}

//�Ƹ�����
void CRoomParentEvent::ProcessNotifyRichStar(Event const& evt ) 
{
	ASSERT( evt.m_pstExtraInfo != NULL ) ;
	core::NotifyRichStarEvent* pInfo = (core::NotifyRichStarEvent*)evt.m_pstExtraInfo ;
}

void CRoomParentEvent::OnSendNomalGift( core::ENM_GiftDstType enmDstType ,uint32 unSrcUIN ,uint32 unDstUIN , uint32 unSentCount ,
								   uint16 unGiftID, core::ENM_GiftType enmType, uint32 time ) 
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	switch( enmDstType )
	{
	case core::GIFTDSTTYPE_SINGLE://������+dstuin
		{
			m_pParentDlg->AddGiftInfo( unSrcUIN, unDstUIN, unSentCount,
				unGiftID, enmType, time) ;
		}
		break;
	case core::GIFTDSTTYPE_MANAGER://����Ա
		{
			std::vector<IUserItem*> vecManagerList ;
			m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetManagerList( vecManagerList ) ;
			IUserItem* pSelfItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem() ;
			if ( pSelfItem == NULL )
			{
				break;
			}
			if ( vecManagerList.empty() || (vecManagerList.size() == 1 && pSelfItem->GetUserTitleLevel() != core::TITLELEVEL_NONE) )
			{
				break;
			}
			if ( !vecManagerList.empty() )
			{
				m_pParentDlg->GetHtmlOutPutManager()->OnPublicGiftTip( unSrcUIN , unGiftID , enmDstType ) ;				
			}
			std::vector<IUserItem*>::iterator iter ;
			if ( GiftManager::GetInstance()->IsFirework( unGiftID ) )
			{
				//m_pParentDlg->DrawPng( DRAW_FIREWORK ) ;
				IUserItem* pUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( myCurInfo.unUIN ) ;
				if ( pUserItem != NULL && (pUserItem->GetUserTitleLevel() > core::TITLELEVEL_TEMP_MANAGER) )
				{
					m_pParentDlg->GetHtmlOutPutManager()->SetPrivateFireWork( unSrcUIN );
				}
			}
			else
			{
				for ( iter = vecManagerList.begin() ; iter != vecManagerList.end() ; ++iter )
				{
					IUserItem* pUserItem = *iter ;
					if ( pUserItem->GetUserUIN() !=  unSrcUIN && !pUserItem->IsHideLogin() )
					{
						m_pParentDlg->AddGiftInfo( unSrcUIN , pUserItem->GetUserUIN() , unSentCount , 
							unGiftID, enmType, time) ;
					}
				}
			}
		}
		break;
	case core::GIFTDSTTYPE_ALL://������
		{
			std::vector<IUserItem*> vecAllList ;
			m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetAllExceptGuest( vecAllList );
			if ( vecAllList.size()<= 1 )
			{
				break;
			}
			m_pParentDlg->GetHtmlOutPutManager()->OnPublicGiftTip( unSrcUIN , unGiftID , enmDstType ) ;
			if ( GiftManager::GetInstance()->IsSalute( unGiftID ) )
			{
				//m_pParentDlg->DrawPng( DRAW_SLAVO ) ;
				IUserItem* pUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( myCurInfo.unUIN ) ;
				if ( pUserItem != NULL && (pUserItem->GetUserTitleLevel() > core::TITLELEVEL_TEMP_MANAGER) )
				{
					m_pParentDlg->GetHtmlOutPutManager()->SetPrivateSlavo( unSrcUIN );
				}
			}
			else
			{
				std::vector<IUserItem*>::iterator iter ;
				for ( iter = vecAllList.begin() ; iter != vecAllList.end() ; ++iter )
				{
					IUserItem* pUserItem = *iter ;
					if ( pUserItem->GetUserUIN() != unSrcUIN  && !pUserItem->IsHideLogin() )
					{						
						m_pParentDlg->AddGiftInfo( unSrcUIN , pUserItem->GetUserUIN() , unSentCount ,
							unGiftID, enmType, time) ;
					}
				}
			}
		}
		break;
	default:break;
	}
}


void CRoomParentEvent::OnSendNomalGiftNotify( core::ENM_GiftDstType enmDstType ,uint32 unSrcUIN ,uint32 unDstUIN , uint32 unSentCount , 
										 uint16 unGiftID  , core::ENM_GiftType enmType, uint32 time )
{
	core::CurInfo myCurInfo = GetCurInfo() ;
	switch( enmDstType )
	{
	case core::GIFTDSTTYPE_SINGLE://������+dstuin
		{
			if ( !CPersonalConfig::GetInstance()->GetIsBlockGiftMsg() )
			{
				m_pParentDlg->AddGiftInfo( unSrcUIN ,unDstUIN, unSentCount ,
					unGiftID, enmType, time ) ;
			}
			m_pParentDlg->GetHtmlOutPutManager()->SetPrivateNormalGift( unSrcUIN , unDstUIN , unGiftID , unSentCount );
		}
		break;
	case core::GIFTDSTTYPE_MANAGER://����Ա
		{
			std::vector<IUserItem*> vecManagerList ;
			m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetManagerList( vecManagerList ) ;
			if ( vecManagerList.empty() )
			{
				break;
			}
			m_pParentDlg->GetHtmlOutPutManager()->OnPublicGiftTip( unSrcUIN , unGiftID , enmDstType ) ;
			std::vector<IUserItem*>::iterator iter ;
			if ( GiftManager::GetInstance()->IsFirework( unGiftID ) )
			{
				//m_pParentDlg->DrawPng( DRAW_FIREWORK ) ;
				IUserItem* pUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( myCurInfo.unUIN ) ;
				if ( pUserItem != NULL && (pUserItem->GetUserTitleLevel() > core::TITLELEVEL_TEMP_MANAGER) )
				{
					m_pParentDlg->GetHtmlOutPutManager()->SetPrivateFireWork( unSrcUIN );
				}
			}
			else
			{
				for ( iter = vecManagerList.begin() ; iter != vecManagerList.end() ; ++iter )
				{
					IUserItem* pUserItem = *iter ;
					if ( pUserItem->GetUserUIN() !=  unSrcUIN && !CPersonalConfig::GetInstance()->GetIsBlockGiftMsg() && !pUserItem->IsHideLogin() )
					{
						m_pParentDlg->AddGiftInfo( unSrcUIN , pUserItem->GetUserUIN() , unSentCount , 
							unGiftID, enmType, time) ;
					}
					if ( pUserItem->GetUserUIN() == myCurInfo.unUIN && !pUserItem->IsHideLogin() )
					{
						m_pParentDlg->GetHtmlOutPutManager()->SetPrivateNormalGift( unSrcUIN , myCurInfo.unUIN , unGiftID , unSentCount );
					}
				}
			}
		}
		break;
	case core::GIFTDSTTYPE_ALL://������
		{
			std::vector<IUserItem*> vecAllList ;
			m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetAllExceptGuest( vecAllList );

			m_pParentDlg->GetHtmlOutPutManager()->OnPublicGiftTip( unSrcUIN , unGiftID , enmDstType ) ;
			IUserItem* pSelfUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN( myCurInfo.unUIN ) ;
			if ( GiftManager::GetInstance()->IsSalute( unGiftID ) )
			{				
				if ( pSelfUserItem != NULL && (pSelfUserItem->GetUserTitleLevel() > core::TITLELEVEL_TEMP_MANAGER) )
				{
					m_pParentDlg->GetHtmlOutPutManager()->SetPrivateSlavo( unSrcUIN );
				}
			}
			else
			{
				if ( !CPersonalConfig::GetInstance()->GetIsBlockGiftMsg() )
				{
					std::vector<IUserItem*>::iterator iter ;
					for ( iter = vecAllList.begin() ; iter != vecAllList.end() ; ++iter )
					{
						IUserItem* pUserItem = *iter ;
						if ( pUserItem->GetUserUIN() != unSrcUIN && !pUserItem->IsHideLogin() )
						{					
							m_pParentDlg->AddGiftInfo( unSrcUIN , pUserItem->GetUserUIN() , unSentCount ,
								unGiftID, enmType, time ) ;
						}
					}
				}
				if ( pSelfUserItem != NULL && !pSelfUserItem->IsHideLogin() )
				{
					m_pParentDlg->GetHtmlOutPutManager()->SetPrivateNormalGift( unSrcUIN , myCurInfo.unUIN , unGiftID , unSentCount );
				}				
			}
		}
	default:break;
	}
}

void CRoomParentEvent::ProcessSendFlyWordsRsp( Event const& evt )
{
	core::SendFlyWordsRspEvent * pInfo = (core::SendFlyWordsRspEvent*)evt.m_pstExtraInfo;

	switch (pInfo->enmResult)
	{
	case core::SENDGIFTRESULT_OK:
		{
			g_RoomModule->UpdateAllRoomMoney( pInfo->unLeftMoney );
		}
		break;
	case core::SENDGIFTRESULT_NOT_ENOUGH_MONEY:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnNotEnoughGold() ;
		}
		break;
	case core::SENDGIFTRESULT_OTHER:
		{

		}
		break;
	case core::SENDGIFTRESULT_UNKNOWN:
		{

		}
		break;
	default:
		break;
	}

	//if (pInfo->enmResult == SENDGIFTRESULT_OK)
	//{
		//m_pParentDlg->GetEffectManager()->ProcessFlyingText(m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem()->GetUserName(), pInfo->strMessage);
		//g_RoomModule->UpdateAllRoomMoney(pInfo->unLeftMoney);
	//}
}

void CRoomParentEvent::ProcessSendFlyWordsNofity( Event const& evt )
{
	core::SendFlyWordsNotifyEvent * pInfo = (core::SendFlyWordsNotifyEvent*)evt.m_pstExtraInfo;
	std::wstring strContent = pInfo->strMessage;
	int nType = 0;
	ScreenEffectManager::DecodeFlyingText(strContent, nType);
	m_pParentDlg->GetEffectManager()->ProcessFlyingText(pInfo->strName, strContent, nType);

	m_pParentDlg->GetHtmlOutPutManager()->OnFlyTextNotify(pInfo->unSrcUIN, strContent);
}

void CRoomParentEvent::ProcessAnswerPushOnShowRsp( Event const& evt )
{
	core::PushOnShowAnswerRspEvent* pInfo = (core::PushOnShowAnswerRspEvent*)evt.m_pstExtraInfo ;
	switch (pInfo->enmResult)
	{
		case core::ANSWERPUSHONSHOWRESULT_OK:
			{
				//�����ɹ�
				if (pInfo->enmType == core::ANSWERPUSHONSHOW_ACCEPT)
				{
					//m_pParentDlg->GetHtmlOutPutManager()->OnPushOnShowRsp_Success( pInfo->unDstUIN ) ;
				}
				else if (pInfo->enmType == core::ANSWERPUSHONSHOW_REFUSE)
				{
					m_pParentDlg->GetHtmlOutPutManager()->OnPushOnShowRsp_Refuse();
				}	
			}
			break;
		case core::ANSWERPUSHONSHOWRESULT_IS_ONMIC:
			{
				//�Ѿ�������
				m_pParentDlg->GetHtmlOutPutManager()->OnPushOnShowRsp_OnMic();
			}
			break;
		case core::ANSWERPUSHONSHOWRESULT_MIC_ISLOCKED:
			{
				//���󱻹�
				m_pParentDlg->GetHtmlOutPutManager()->OnPushOnShowRsp_MicLocked();
			}
			break;
		case core::ANSWERPUSHONSHOWRESULT_MIC_HASPLAYER:
			{
				//��������
				m_pParentDlg->GetHtmlOutPutManager()->OnPushOnShowRsp_Mic_HasPlayer();
			}
			break;
		case core::ANSWERPUSHONSHOWRESULT_UNKNOWN:
			{
				
			}
			break;
		default:break;
	}
}

void CRoomParentEvent::ProcessGetSofaListRsp( Event const& evt )
{
	m_pParentDlg->InitSofaList();
}

void CRoomParentEvent::ProcessBuySofaRsp( Event const& evt )
{
	core::BuySofaRspEvent * pInfo = (core::BuySofaRspEvent*)evt.m_pstExtraInfo;
	switch (pInfo->enmResult)
	{
	case core::BuySofaRspEvent::BUYSOFARESULT_OK:
		{
			g_RoomModule->UpdateAllRoomMoney(pInfo->leftMoney);
		}
		break;
	case core::BuySofaRspEvent::BUYSOFARESULT_PRICE_TOO_LOW:
		{
			uint8 unIndex = pInfo->sofaIndex;
			CSofaItem * pSofaItem = m_pParentDlg->GetRoomBusiness()->GetSofaManager()->GetSofaItemByIndex(unIndex);
			if (pSofaItem != NULL)
			{
				CString strText;
				strText.Format(L"ɳ��ȯ�������㣬��ɳ��������Ҫ%d��", pSofaItem->GetPrice()+1);
				m_pParentDlg->GetHtmlOutPutManager()->InsertPrivateTips(  _T("����ʾ���� ") , strText , COLOR_OPERATE );
			}
			else
			{
				CString strText;
				strText.Format(L"ɳ��ȯ�������㣬��ɳ��������Ҫ%d��", 1);
				m_pParentDlg->GetHtmlOutPutManager()->InsertPrivateTips(  _T("����ʾ���� ") , strText , COLOR_OPERATE );
			}
		}
		break;
	case core::BuySofaRspEvent::BUYSOFARESULT_NOT_ENOUGH_MONEY:
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnNotEnoughGold();
		}
		break;
	case core::BuySofaRspEvent::BUYSOFARESULT_UNKNOWN:
		{

		}
		break;
	default:
		break;
	}
}

void CRoomParentEvent::ProcessBuySofaNotify( Event const& evt )
{
	core::BuySofaNotifyEvent * pInfo = (core::BuySofaNotifyEvent*)evt.m_pstExtraInfo;
	m_pParentDlg->UpdateSofa(pInfo->sofaIndex);
}

void CRoomParentEvent::ProcessNotifyClearSofaList( Event const& evt )
{
	m_pParentDlg->ClearSofaList();
}

void CRoomParentEvent::ProcessUpdateSongListRsp( Event const& evt )
{
	core::UpdateSongListRspEvent * pInfo = (core::UpdateSongListRspEvent*)evt.m_pstExtraInfo;
	switch (pInfo->enmResult)
	{
	case core::UpdateSongListRspEvent::UPDATESONGRESULT_OK:
		{
			IUserItem * pSelfItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
			if (pSelfItem != NULL)
			{
				//�Լ�������Ϊ0����ʾ�Ѿ����󣬵����ҳ����Ȼ���ţ��û������ʱ��Ҫˢ��
				bool bRefresh = (pSelfItem->GetPublicMicIndex() == 0);
				m_pParentDlg->UpdateSongList(pSelfItem->GetPublicMicIndex(), pSelfItem->GetUserUIN(), bRefresh);
			}
		}
		break;
	case core::UpdateSongListRspEvent::UPDATESONGRESULT_FULL:
		{

		}
		break;
	case core::UpdateSongListRspEvent::UPDATESONGRESULT_HOT_FULL:
		{

		}
		break;
	case core::UpdateSongListRspEvent::UPDATESONGRESULT_NO_PERMISSION:
		{

		}
		break;
	case core::UpdateSongListRspEvent::UPDATESONGRESULT_UNKNOWN:
		{
		}
		break;
	default:
		break;
	}
}

void CRoomParentEvent::ProcessGetSongListRsp( Event const& evt )
{
	core::GetSongListRspEvent * pInfo = (core::GetSongListRspEvent*)evt.m_pstExtraInfo;
	if (pInfo->result == 0)
	{
		IUserItem * pUserItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->SearchUserByUIN(pInfo->songerUin);
		if (pUserItem != NULL)
		{
			m_pParentDlg->UpdateSongList(pUserItem->GetPublicMicIndex(), pUserItem->GetUserUIN());
		}
	}
}

void CRoomParentEvent::ProcessOrderSongRsp( Event const& evt )
{
	switch (evt.param1)
	{
	case core::OrderSongEvent::ORDERSONGRESULT_OK:
		{
			m_pParentDlg->OnOrderSongRsp(evt.param2, true);
			//���ͻ�ȡ�ѵ�����б�������Ҫ�Ż�
			CSendEventManager::SendGetOrderListEvent(m_pParentDlg->GetRoomID());
		}
		break;
	case core::OrderSongEvent::ORDERSONGRESULT_MONEY_NOT_ENOUGH:
		{
			m_pParentDlg->OnOrderSongRsp(evt.param2, false);
		}
		break;
	default:
		break;
	}
}

void CRoomParentEvent::ProcessOrderSongNotify( Event const& evt )
{
	//core::OrderSongNotifyEvent * pInfo = (core::OrderSongNotifyEvent*)evt.m_pstExtraInfo;
	//���ͻ�ȡ�ѵ�����б�������Ҫ�Ż�
	CSendEventManager::SendGetOrderListEvent(m_pParentDlg->GetRoomID());
}

void CRoomParentEvent::ProcessTakeOrderRsp( Event const& evt )
{
	m_pParentDlg->OnSongTakeOrderRsp(evt.param1);
}

void CRoomParentEvent::ProcessTakeOrderNotify( Event const& evt )
{
	core::ProcessOrderNotifyEvent * pInfo = (core::ProcessOrderNotifyEvent*)evt.m_pstExtraInfo;
	//������Լ���ĸ�����ѵ�����б�
	if (GetCurInfo().unUIN == pInfo->order.uin)
	{
		//���ͻ�ȡ�ѵ�����б�������Ҫ�Ż�
		CSendEventManager::SendGetOrderListEvent(m_pParentDlg->GetRoomID());
	}

	if (pInfo->order.status == core::SongOrder::ORDER_STATUS_ACCEPTED)
	{
		//����ߺ�������179IDԤ���ӿڣ���ʱ�ȴ�0
		m_pParentDlg->GetEffectManager()->ProcessOrderSong(pInfo->order.nickName, pInfo->order.songerNickname, 0, 0, pInfo->order.songName, pInfo->order.attachWords);

		//������Լ���ĸ裬����˽��������ʾ
		if (GetCurInfo().unUIN == pInfo->order.uin)
		{
			m_pParentDlg->GetHtmlOutPutManager()->OnMarkNotify(CString(pInfo->order.songerNickname.c_str()));
		}
	}
	else if (pInfo->order.status == core::SongOrder::ORDER_STATUS_REJECTED)
	{
		//֪ͨ����û����ܾ�����Ϣ
		if (GetCurInfo().unUIN == pInfo->order.uin)
		{
			CString strText;
			strText.Format(L"���� %s ��������ĵ������ϵͳ�Ѿ��������÷����������˻�", pInfo->order.songerNickname.c_str());
			m_pParentDlg->GetHtmlOutPutManager()->InsertPrivateTips(  _T("����ʾ���� ") , strText , COLOR_OPERATE );
		}
	}
}

void CRoomParentEvent::ProcessGetOrderListRsp( Event const& evt )
{
	core::GetOrderListRspEvent * pInfo = (core::GetOrderListRspEvent*)evt.m_pstExtraInfo;
	if (pInfo->result == 0)
	{
		IUserItem * pSelfItem = m_pParentDlg->GetRoomBusiness()->GetUserManager()->GetSelfUserItem();
		if (pSelfItem != NULL)
		{
			m_pParentDlg->UpdateOrderList(pSelfItem->GetUserUIN(), pSelfItem->IsActor());
			m_pParentDlg->UpdateMarkList(pSelfItem->GetUserUIN());

			//�Լ��������ϵ�����������δ�������ʾ��
			if (pSelfItem->GetPublicMicIndex() != 0 && pSelfItem->IsActor())
			{
				m_pParentDlg->UpdateUndealCount();
			}
		}
	}
}

void CRoomParentEvent::ProcessMarkSongRsp( Event const& evt )
{
	//���ͻ�ȡ�ѵ�����б�������Ҫ�Ż�
	CSendEventManager::SendGetOrderListEvent(m_pParentDlg->GetRoomID());
}

void CRoomParentEvent::ProcessMarkSongNotify( Event const& evt )
{
	core::MarkSongNotifyEvent * pInfo = (core::MarkSongNotifyEvent*)evt.m_pstExtraInfo;
	//������Լ���ĸ�����ѵ�����б��Ѿ������б�
	if (GetCurInfo().unUIN == pInfo->order.uin)
	{
		//���ͻ�ȡ�ѵ�����б�������Ҫ�Ż�
		CSendEventManager::SendGetOrderListEvent(m_pParentDlg->GetRoomID());
	}

	//����������Ļ���������ʾ
	if (GetCurInfo().unUIN == pInfo->order.songerUin)
	{
		CString strMark = L"";
		switch (pInfo->order.status)
		{
		case core::SongOrder::ORDER_STATUS_MARK_GOOD:
			{
				strMark = L"����";
			}
			break;
		case core::SongOrder::ORDER_STATUS_MARK_BAD:
			{
				strMark = L"����";
			}
			break;
		case core::SongOrder::ORDER_STATUS_MARK_NONE:
			{
				strMark = L"����";
			}
			break;
		default:
			break;
		}
		m_pParentDlg->GetHtmlOutPutManager()->OnMarkSongNotify(CString(pInfo->order.nickName.c_str()), CString(pInfo->order.songName.c_str()), strMark);
	}
}