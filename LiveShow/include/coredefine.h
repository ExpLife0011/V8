#pragma once

#include "51ktv.h"

namespace core
{
	enum
	{
		EVENT_VALUE_CORE_MODULE_BEGIN = EVENT_VALUE_CORE_BEGIN,		
		
		EVENT_VALUE_CORE_LOGIN,
		EVENT_VALUE_CORE_LOGIN_RSP,

		EVENT_VALUE_CORE_LOGOUT,//û�ж������

		EVENT_VALUE_CORE_GET_SELFINFO,//û�ж������
		EVENT_VALUE_CORE_GET_SELFINFO_RSP,//û�ж������

		EVENT_VALUE_CORE_SET_SELFINFO,//��ʱû�õ�
		EVENT_VALUE_CORE_SET_SELFINFO_RSP,//param0:ENM_SetSelfInfoResult ��ʱû�õ�
		EVENT_VALUE_CORE_SET_SELFINFO_NOTIFY,//��ʱû�õ�

		EVENT_VALUE_CORE_BE_KICKED_NOTIFY,
		EVENT_VALUE_CORE_DISCONNECTED_NOTIFY,

		EVENT_VALUE_CORE_ENTER_ROOM,
		EVENT_VALUE_CORE_ENTER_ROOM_RSP,
		EVENT_VALUE_CORE_ENTER_ROOM_NOTIFY,

		EVENT_VALUE_CORE_LEAVE_ROOM,//param0:roomid
		EVENT_VALUE_CORE_LEAVE_ROOM_NOTIFY,//param0:uin param1:roomid

		EVENT_VALUE_CORE_GET_USERLIST,//param0:roomid
		EVENT_VALUE_CORE_GET_USERLIST_RSP,

		EVENT_VALUE_CORE_GET_WAITTINGLIST,//param0:roomid
		EVENT_VALUE_CORE_GET_WAITTINGLIST_RSP,

		EVENT_VALUE_CORE_SEND_MESSAGE,
		EVENT_VALUE_CORE_SEND_MESSAGE_RSP,
		EVENT_VALUE_CORE_SEND_MESSAGE_NOTIFY,

		EVENT_VALUE_CORE_SEND_GIFT,
		EVENT_VALUE_CORE_SEND_GIFT_RSP,
		EVENT_VALUE_CORE_SEND_GIFT_NOTIFY,

		EVENT_VALUE_CORE_SEND_LOUDSPEAKER,
		EVENT_VALUE_CORE_SEND_LOUDSPEAKER_RSP,
		EVENT_VALUE_CORE_SEND_LOUDSPEAKER_NOTIFY,

		EVENT_VALUE_CORE_SEND_FLYWORDS,
		EVENT_VALUE_CORE_SEND_FLYWORDS_RSP,
		EVENT_VALUE_CORE_SEND_FLYWORDS_NOTIFY,

		EVENT_VALUE_CORE_REQUEST_SHOW,//param0:roomid param1:ENM_RequestShowType
		EVENT_VALUE_CORE_REQUEST_SHOW_RSP,
		EVENT_VALUE_CORE_REQUEST_SHOW_NOTIFY,

		EVENT_VALUE_CORE_EXIT_SHOW,//param0:roomid param1:type(0:1v1 1:����)
		EVENT_VALUE_CORE_EXIT_SHOW_NOTIFY,//param0:roomid param1:srcuin param2:type(0:1v1 1:����)

		EVENT_VALUE_CORE_OPERATE_VIDEO_AUDIO,//param0:roomid param1:ENM_OperateAVType param2:dstuin
		EVENT_VALUE_CORE_OPERATE_VIDEO_AUDIO_RSP,
		EVENT_VALUE_CORE_OPERATE_VIDEO_AUDIO_NOTIFY,//param0:roomid param1:ENM_OperateAVType param2:srcuin

		EVENT_VALUE_CORE_KICK_USER,
		EVENT_VALUE_CORE_KICK_USER_RSP,
		EVENT_VALUE_CORE_KICK_USER_NOTIFY,	

		EVENT_VALUE_CORE_ADD_BLACK,//param0:roomid param1:dstuin
		EVENT_VALUE_CORE_ADD_BLACK_RSP,//param0:roomid param1:ENM_KickResult param2:dstuin
		EVENT_VALUE_CORE_ADD_BLACK_NOTIFY,//param0:roomid param1:srcuin param2:dstuin

		EVENT_VALUE_CORE_LOCK_IP,
		EVENT_VALUE_CORE_LOCK_IP_RSP,//param0:roomid param1:ENM_KickResult param2:dstuin
		EVENT_VALUE_CORE_LOCK_IP_NOTIFY,

		EVENT_VALUE_CORE_SHUT_UP,//param0:roomid param1:dstuin
		EVENT_VALUE_CORE_SHUT_UP_RSP,//param0:roomid param1:ENM_KickResult param2:dstuin
		EVENT_VALUE_CORE_SHUT_UP_NOTIFY,

		EVENT_VALUE_CORE_UNLOCK_SHUTUP,//param0:roomid param1:dstuin
		EVENT_VALUE_CORE_UNLOCK_SHUTUP_RSP,//param0:roomid param1:ENM_KickResult param2:dstuin
		EVENT_VALUE_CORE_UNLOCK_SHUTUP_NOTIFY,//param0:roomid param1:srcuin param2:dstuin

		EVENT_VALUE_CORE_PUSH_ON_SHOW,//param0:roomid param1:dstuin param2:index
		EVENT_VALUE_CORE_PUSH_ON_SHOW_RSP,
		EVENT_VALUE_CORE_PUSH_ON_SHOW_NOTIFY,

		EVENT_VALUE_CORE_PULL_OFF_SHOW,//param0:roomid param1:dstuin
		EVENT_VALUE_CORE_PULL_OFF_SHOW_RSP,//param0:roomid param1:ENM_PullOffResult param2:dstuin
		EVENT_VALUE_CORE_PULL_OFF_SHOW_NOTIFY,//param0:roomid param1:srcuin param2:dstuin

		EVENT_VALUE_CORE_ADD_TITLE,//param0:roomid param1:ENM_TitleLevel param2:dstuin
		EVENT_VALUE_CORE_ADD_TITLE_RSP,
		EVENT_VALUE_CORE_ADD_TITLE_NOTIFY,

		EVENT_VALUE_CORE_REMOVE_TITLE,//param0:roomid param1:ENM_TitleLevel param2:dstuin
		EVENT_VALUE_CORE_REMOVE_TITLE_RSP,
		EVENT_VALUE_CORE_REMOVE_TITLE_NOTIFY,

		EVENT_VALUE_CORE_OPEN_PRIVATE,//param0:roomid param1:dstuin
		EVENT_VALUE_CORE_OPEN_PRIVATE_RSP,//param0:roomid param1:ENM_OpenPrivateResult param2:dstuin

		EVENT_VALUE_CORE_CLOSE_PRIVATE,//param0:roomid param1:dstuin

		EVENT_VALUE_CORE_REQUEST_P2P,//param0:roomid param1:dstuin
		EVENT_VALUE_CORE_REQUEST_P2P_RSP,//param0:roomid param1:ENM_ConnectP2PResult param2:dstuin
		EVENT_VALUE_CORE_REQUEST_P2P_NOTIFY,//param0:roomid param1:srcuin

		EVENT_VALUE_CORE_RESPONSE_P2P,//param0:roomid param1:ENM_ResponseP2PType param2:dstuin
		EVENT_VALUE_CORE_RESPONSE_P2P_RSP,
		EVENT_VALUE_CORE_RESPONSE_P2P_NOTIFY,

		EVENT_VALUE_CORE_REPORT_CLIENTINFO,
		EVENT_VALUE_CORE_REPORT_CLIENTINFO_NOTIFY,

		EVENT_VALUE_CORE_QUERY_CLIENTINFO,
		EVENT_VALUE_CORE_QUERY_CLIENTINFO_RSP,

		EVENT_VALUE_CORE_SET_ROOMINFO,
		EVENT_VALUE_CORE_SET_ROOMINFO_RSP,//param0:roomid param1:ENM_SetRoomInfoResult
		EVENT_VALUE_CORE_SET_ROOMINFO_NOTIFY,

		EVENT_VALUE_CORE_GET_ROOMINFO,//param0:roomid
		EVENT_VALUE_CORE_GET_ROOMINFO_RSP,

		EVENT_VALUE_CORE_MIC_SET_MIC_STATUS,//param0:roomid param1: (high16:mic_index(1,2,3) low16:status(0:open 1:close))
		EVENT_VALUE_CORE_MIC_SET_MIC_STATUS_RSP,//param0:roomid param1: (high16:mic_index(1,2,3) low16:status(0:open 1:close)) param2:ENM_SetMicStatusResult
		EVENT_VALUE_CORE_MIC_SET_MIC_STATUS_NOTIFY,//param0:roomid param1: (high16:mic_index(1,2,3) low16:status(0:open 1:close)) param2:srcuin

		EVENT_VALUE_CORE_ANSWER_PUSH_ON_SHOW,
		EVENT_VALUE_CORE_ANSWER_PUSH_ON_SHOW_RSP,

		EVENT_VALUE_CORE_REPORT_COLLECT_INFO,

		EVENT_VALUE_CORE_GET_TASK_REWARD,//��ȡ������ param0:taskID

		EVENT_VALUE_CORE_GET_FANS,//param0:uin
		EVENT_VALUE_CORE_GET_FANS_RSP,

		EVENT_VALUE_CORE_GET_SOFA_LIST,//param0:roomid
		EVENT_VALUE_CORE_GET_SOFA_LIST_RSP,

		EVENT_VALUE_CORE_BUY_SOFA,//param0:roomid param1:sofaindex(1��ʼ) param2:price(��λɳ��)
		EVENT_VALUE_CORE_BUY_SOFA_RSP,
		EVENT_VALUE_CORE_BUY_SOFA_NOTIFY,

		//////////////////////////////////////////////////////////////////////////
		//���ϵͳ

		EVENT_VALUE_UPDATE_SONGLIST,
		EVENT_VALUE_UPDATE_SONGLIST_RSP,

		EVENT_VALUE_GET_SONGLIST,//param0:roomid param1:songerUin
		EVENT_VALUE_GET_SONGLIST_RSP,

		EVENT_VALUE_ORDER_SONG,
		EVENT_VALUE_ORDER_SONG_RSP,//param0:roomid param1:ENM_OrderSongResult param2:songeruin
		EVENT_VALUE_ORDER_SONG_NOTIFY,

		EVENT_VALUE_PROCESS_ORDER,//param0:roomid param1:orderId param2:1(����) 2(�ܾ�)
		EVENT_VALUE_PROCESS_ORDER_RSP,//param0:roomid param1:result 0(�ɹ�) 1(ʧ��) 2(15��)
		EVENT_VALUE_PROCESS_ORDER_NOTIFY,

		EVENT_VALUE_GET_ORDERLIST,//param0:roomid
		EVENT_VALUE_GET_ORDERLIST_RSP,

		EVENT_VALUE_MARK_SONG,//param0:roomid param1:orderId param2:1(����) 2(����) 0(����)
		EVENT_VALUE_MARK_SONG_RSP,//param0:roomid param1:result
		EVENT_VALUE_MARK_SONG_NOTIFY,

		//////////////////////////////////////////////////////////////////////////
		//������

		EVENT_VALUE_CORE_OPEN_BOX_REQ,//param0:roomid param1:isfree
		EVENT_VALUE_CORE_OPEN_BOX_RSP,

		EVENT_VALUE_CORE_REWARD_BOX_KEY_NOTIFY,

		//////////////////////////////////////////////////////////////////////////
		//���������б�

		EVENT_VALUE_CORE_GET_OFFLINE_ACTOR_REQ,//param0:roomid
		EVENT_VALUE_CORE_GET_OFFLINE_ACTOR_RSP,

		//////////////////////////////////////////////////////////////////////////

		EVENT_VALUE_CORE_NOTIFY_ROOM_USER_INFO_UPDATE,
		EVENT_VALUE_CORE_NOTIFY_GIFT_RESOURCE_UPDATE,//������Դ�и���
		EVENT_VALUE_CORE_NOTIFY_SYSTEM_MESSAGE,//����֪ͨ��Ϣ
		EVENT_VALUE_CORE_NOTIFY_GIFT_OVER_TIME,//���ﵽ�� param0:roomid param1:dstuin param2:giftid
		EVENT_VALUE_CORE_NOTIFY_PRIVATE_SHOW,
		EVENT_VALUE_CORE_NOTIFY_PLUTUS_AWARD,//����
		EVENT_VALUE_CORE_NOTIFY_MONEY_UPDATE,//Ǯ�Ҹ��� param0:money
		EVENT_VALUE_CORE_NOTIFY_OFFICIAL_NOTICE,//�ٷ�����
		EVENT_VALUE_CORE_NOTIFY_ROOM_LOCKED,//���䱻��
		EVENT_VALUE_CORE_NOTIFY_PASSWORD_SAFE,//�û��������ܱ�
		EVENT_VALUE_CORE_NOTIFY_MY_INFO_UPDATE,//�ҵ���Ϣ���(�ǳƣ��Ա�)
		EVENT_VALUE_CORE_NOTIFY_MEDIA_SERVER_RESET,//ý����ת���������
		EVENT_VALUE_CORE_NOTIFY_RICH_STAR,//�Ƹ��������
		EVENT_VALUE_CORE_NOTIFY_RICH_UPDATE_MONEY_CHANGE,//��������Ǯ�Ҹ���
		EVENT_VALUE_CORE_NOTIFY_TASK_INFO_UPDATE,//����ϵͳ����
		EVENT_VALUE_CORE_NOTIFY_CLEAR_SOFA_LIST,//���ɳ���б� param0:roomid

		EVENT_VALUE_CORE_ASYN_LOGOUT,//(��m_circleBuffer.Read()�ĵ���ջ��)�첽Logout
		EVENT_VALUE_CORE_RELOGIN,//�Զ�����

		EVENT_VALUE_CORE_MODULE_END,
	};

	enum
	{
		MESSAGE_VALUE_CORE_MODULE_BEGIN = MESSAGE_VALUE_CORE_BEGIN,

		MESSAGE_VALUE_CORE_PRE_LOGIN,//׼��Ҫ��½��
		MESSAGE_VALUE_CORE_BE_KICKED,//��������
		MESSAGE_VALUE_CORE_DISCONNECTED,//������
		MESSAGE_VALUE_CORE_LOGIN_COMPLETE,//param0:ENM_LoginErrorCode
		MESSAGE_VALUE_CORE_RICHINFO_COMPLETE,//��ȡ�Լ��ķḻ��Ϣ���
		MESSAGE_VALUE_CORE_ISP_CHANGE,//ISP��� param0: 0:���� 1:��ͨ
		MESSAGE_VALUE_CORE_GIFT_STAR_INFO,//��ȡ������֮����Ϣ
		MESSAGE_VALUE_CORE_MY_GODS,//��ȡ���ҵ���Ʒ
		MESSAGE_VALUE_CORE_MY_GODS_UPDATE,//�ҵ���Ʒ���(��ʱ��������)
		MESSAGE_VALUE_CORE_MY_INFO_UPDATE,//�ҵ���Ϣ���
		MESSAGE_VALUE_CORE_MY_VIPLEVEL_UPDATE,//vip�ȼ����
		MESSAGE_VALUE_CORE_MY_RICHLEVEL_UPDATE,//�����ȼ����

		MESSAGE_VALUE_CORE_MODULE_END,
	};

	enum
	{
		SERVICE_VALUE_CORE_MODULE_BEGIN = SERVICE_VALUE_CORE_BEGIN,

		SERVICE_VALUE_CORE_GET_CUR_INFO, //param: &CurInfo
		SERVICE_VALUE_CORE_SWITCH_ISP,//�л�isp(param: 1:���� 0:��ͨ)
		SERVICE_VALUE_CORE_UPDATE_MONEY,//param: int ����ʾ��Ǯ������ʾ��Ǯ
		SERVICE_VALUE_CORE_GET_GIFT_STAR_INFO,//param: &GetGiftStarInfo
		SERVICE_VALUE_CORE_GET_MY_GOODS,//param: &GetMyGoods

		SERVICE_VALUE_CORE_END,
	};

	enum ENM_AccountType
	{
		ACCOUNTTYPE_VISITOR	=	0x00,
		ACCOUNTTYPE_179		=	0x01,
		ACCOUNTTYPE_QQ		=	0x02,
	};

	struct RichInfo
	{
		uint16 unYear;
		uint8 unMonth;
		uint8 unDay;
		std::wstring strProvince;
		std::wstring strCity;
	};

	enum ENM_VipLevel
	{
		VIPLEVEL_NONE			=	0x00,	//δע��
		VIPLEVEL_REGISTER		=	0x01,	//��ע��
		VIPLEVEL_VIP			=	0x02,	//vip
		VIPLEVEL_HONOR			=	0x04,	//��ҫvip
		VIPLEVEL_SILVER			=	0x08,	//����
		VIPLEVEL_GOLDEN			=	0x10,	//���
		VIPLEVEL_CRYSTAL		=	0x20,	//ˮ���ʹ�
		VIPLEVEL_DIAMOND		=	0x40,	//��ʯ�ʹ�
		VIPLEVEL_BLACKDIAMOND	=	0x60,	//����ʹ�
		VIPLEVEL_TOP			=	0x80,	//����ʹ�
	};

	enum ENM_BusinessType
	{
		BUSINESSTYPE_SONGER		=	0x0001,	//��������
		BUSINESSTYPE_DANCER		=	0x0002,	//���豦��
		BUSINESSTYPE_HOST		=	0x0004,	//��������
		BUSINESSTYPE_OPERATOR	=	0x0008,	//������Ӫ
		BUSINESSTYPE_AGENT		=	0x0010,	//�ٷ�����
		BUSINESSTYPE_PATROLMAN	=	0x0020,	//Ѳ��
		BUSINESSTYPE_AD_CLEANER	=	0x0040,	//��洦��
		BUSINESSTYPE_LUCKY_STAR	=	0x0080,	//����������
	};

	enum ENM_TitleLevel
	{
		TITLELEVEL_NONE				=	0x00,
		TITLELEVEL_TEMP_MANAGER		=	0x01,
		TITLELEVEL_MANAGER			=	0x02,
		TITLELEVEL_SECOND_OWNER		=	0x04,
		TITLELEVEL_OWNER			=	0x08,
		TITLELEVEL_SUPER_MANAGER	=	0x10,
	};

	enum ENM_InfoType
	{
		INFOTYPE_NAME				=	0x00,	//string
		INFOTYPE_179ID				=	0x01,	//uint32
		INFOTYPE_GENDER				=	0x02,	//uint8
		INFOTYPE_VIP_LEVEL			=	0x03,	//uint8
		INFOTYPE_USR_LEVEL			=	0x04,	//uint8
		INFOTYPE_ONLINE_TIME		=	0x05,	//uint16
		INFOTYPE_LEFT_TIME			=	0x06,	//uint16
		INFOTYPE_BIRTHDAY_YEAR		=	0x07,	//uint16
		INFOTYPE_BIRTHDAY_MONTH		=	0x08,	//uint8
		INFOTYPE_BIRTHDAY_DAY		=	0x09,	//uint8
		INFOTYPE_HOME_PROVINCE		=	0x0a,	//string
		INFOTYPE_HOME_CITY			=	0x0b,	//string
		INFOTYPE_SELF_SETTING		=	0x0c,	//uint32
		INFOTYPE_RICH_LEVEL			=	0x0d,	//uint8

		//room����ֶ�(for notify)
		USERINFO_ROOM_TITLELEVEL	=	0x20,	//uint16�����ֻ�ȫ���ߵ�����֪ͨ��***����***Ϊ�ٹܣ�
		USERINFO_ROOM_JIAZU			=	0x21,	//string
		USERINFO_ROOM_CLIENTINFO	=	0x22,	//uint16
		USERINFO_ROOM_STATUS		=	0x23,	//uint16�����ֻ�ȫ���ߵ�����֪ͨ��***ȡ��***���󣿣�
	};

	enum ENM_SelfSetting
	{
		SELFSETTING_MESSAGE_NO_PUBLIC				=	0x0001,//���ι���(0:������)
		SELFSETTING_MESSAGE_NO_PRIVATE				=	0x0002,//����˽��(0:������)
		SELFSETTING_MESSAGE_AUTO_SCROLL				=	0x0004,//��Ϣ�Զ�����(0:����)
		SELFSETTING_MESSAGE_AUTO_REPLY				=	0x0008,//��Ϣ�Զ��ظ�(0:���ظ�)
		SELFSETTING_MESSAGE_NO_LOUDSPEAKER_AUDIO	=	0x0010,//������������(0:������)
		SELFSETTING_MESSAGE_NO_GIFT					=	0x0020,//����������Ϣ(0:������)
		SELFSETTING_MESSAGE_NO_ENTER_LEAVE			=	0x0040,//�����û�������Ϣ(0:����)		

		SELFSETTING_P2PSHOW_MASK					=	0x0180,//1��1��Ƶ����mask
		SELFSETTING_P2PSHOW_VIP						=	0x0180,//1��1��Ƶ����->vip����
		SELFSETTING_P2PSHOW_KING					=	0x0100,//1��1��Ƶ����->�ʹ�
		SELFSETTING_P2PSHOW_CLOSE					=	0x0080,//1��1��Ƶ����->�ܾ��κ���

		SELFSETTING_MESSAGE_LOUDSPEAKER_SCROLL		=	0x0200,//�����Զ�����(0:����)
		SELFSETTING_MESSAGE_NO_LUCKY_AUDIO			=	0x0400,//�����н�����(0:������)

		//�����￪ʼ���µ�
	};

	enum ENM_TaskData
	{
		TASK_SYSTEM_TASKNUM			=	 9,	  //�������

		TASKSTATTYPE_UNOPEN			= 0x00,   //δ����
		TASKSTATTYPE_UNFINISH		= 0x01,   //δ���
		TASKSTATTYPE_CANNOT_REWARD 	= 0x02,   //����ɣ�������ȡ״̬
		TASKSTATTYPE_CAN_REWARD		= 0x03,   //����ɣ�����ȡ����״̬
		TASKSTATTYPE_ISREWARD		= 0x04,   //����ɣ�����ȡ����״̬
		TASKSTATTYPE_ERROR   	 	= 0x10,   //��������
	};
	
	struct CurInfo
	{
		uint32 unUIN;		
		uint32 un179id;
		std::wstring str179EMail;		
		bool bMan;
		std::wstring strName;
		std::wstring strToken;
		bool bLogined;
		ENM_AccountType enmAccountType;		//��½���˺�����
		std::wstring strLoginAccount;		//��½ʱ����˺�(179id��179�˺ţ����䣩)

		ENM_VipLevel enmVIPLevel;
		uint8 unUserLevel;
		uint16 unOnlineTime;			//����ʱ��
		uint16 unLeftTime;				//����ʣ��ʱ��
		uint32 unLeftMoney;				//ʣ���
		uint32 unSelfSetting;			//��������(ENM_SelfSetting)
		uint32 unSystemTime;			//ϵͳʱ��
		uint32 unBusiness;				//ENM_BusinessType

		bool bFirstLogin;//�Ƿ��״ε�½
		bool bRmbUser;//�Ƿ��ֵ��
		bool bPasswordSafe;//�Ƿ����ù��ܱ�		

		uint8 unRichLevel;			//�����ȼ�
		uint32 unRichUpdateMoney;	//�������������

		uint8 unarrTaskStat[TASK_SYSTEM_TASKNUM];//9������״̬ENM_TaskStatType

		bool bGetRichInfo;
		RichInfo stRichInfo;

		bool bUseDianxin;//��ǰ�Ƿ�ʹ�õ��ŷ�����
		bool bInBlacklist;//�Ƿ��ں�������(��ֹ����)

		CurInfo():unUIN(0),bLogined(false),bGetRichInfo(false),enmVIPLevel(VIPLEVEL_NONE),
			bUseDianxin(true),bInBlacklist(false)
		{
			memset(unarrTaskStat, 0, sizeof(unarrTaskStat));
		}

		void Init()
		{
			unUIN = un179id = 0;
			bLogined = bGetRichInfo = bInBlacklist = false;
			bUseDianxin = true;
			memset(unarrTaskStat, 0, sizeof(unarrTaskStat));
		}
	};
	

	//////////////////////////////////////////////////////////////////////////

	struct LoginEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_LOGIN

		ENM_AccountType enmAccountType;//��½���˺�����
		std::wstring strAccount;
		std::string strPassword;//����md5
		bool bVerify;
		std::string strVerifyKey;
		std::wstring strVerifyCode;

		LoginEvent():bVerify(false)
		{
		}
	};

	/**
	* ��¼����ֵ
	*/
	enum ENM_LoginErrorCode
	{
		LOGIN_ERROR_SUCCESS,					//��½�ɹ�

		LOGIN_ERROR_CLIENT_GET_TOKEN_HOST_ERROR,//token��������ʧ��
		LOGIN_ERROR_CLIENT_GET_HALL_HOST_ERROR, //hall��������ʧ��
		LOGIN_ERROR_CLIENT_STATE_ERROR,			//״̬���������ظ���½(�ͻ���bug)
		LOGIN_ERROR_CLIENT_TOKEN_CONNECT_ERROR,	//token����ʧ��
		LOGIN_ERROR_CLIENT_TOKEN_TIMEOUT_ERROR,	//token��¼��ʱ
		LOGIN_ERROR_CLIENT_HALL_CONNECT_ERROR,	//hall����ʧ��
		LOGIN_ERROR_CLIENT_HALL_TIMEOUT_ERROR,	//hall��¼��ʱ
		LOGIN_ERROR_CLIENT_NET_TYPE_ERROR,		//��ȡ�������ͳ���(����δ��������)

		LOGIN_ERROR_TOKEN_ERROR,				//�˺���֤ʧ��
		LOGIN_ERROR_TOKEN_PASSWORD_ERROR,		//�������
		LOGIN_ERROR_TOKEN_ACCOUNT_ERROR,		//�˺Ŵ���
		LOGIN_ERROR_TOKEN_ACCOUNT_FORBIDE,		//�����˺��ѱ�����,��������,����ϵ�ͷ�
		LOGIN_ERROR_TOKEN_REFUSED,			    //(����token����������)
		LOGIN_ERROR_TOKEN_NEED_VERIFY,		    //��Ҫ��֤����֤
		LOGIN_ERROR_TOKEN_VERIFY_ERROR,			//��֤����֤ʧ��
		LOGIN_ERROR_TOKEN_VERIFY_TIMEOUT,	    //��֤�����
		LOGIN_ERROR_TOKEN_EMAIL_NOT_ACTIVATE,   //����δ����뼤����ٵ�¼
		LOGIN_ERROR_TOKEN_OTHER_ERROR,			//��������

		LOGIN_ERROR_179_ERROR_BEGIN		= 	1000,
		LOGIN_ERROR_179_ACCOUNT_LOCK	= 	LOGIN_ERROR_179_ERROR_BEGIN+0x01,	//�˺ű�����
		LOGIN_ERROR_179_IP_LOCK			= 	LOGIN_ERROR_179_ERROR_BEGIN+0x02,	//ip������
		LOGIN_ERROR_179_MAC_LOCK		= 	LOGIN_ERROR_179_ERROR_BEGIN+0x03,	//mac������
		LOGIN_ERROR_179_TIMEOUT			= 	LOGIN_ERROR_179_ERROR_BEGIN+0x04,	//��½��ʱ
		LOGIN_ERROR_179_VERSION_ERROR	= 	LOGIN_ERROR_179_ERROR_BEGIN+0x05,	//�汾��ƥ��
		LOGIN_ERROR_179_OTHER			= 	LOGIN_ERROR_179_ERROR_BEGIN+0x10,	
		LOGIN_ERROR_179_MAINTAN			= 	LOGIN_ERROR_179_ERROR_BEGIN+0x11,	//��������ά��
		LOGIN_ERROR_179_UNKNOWN			= 	LOGIN_ERROR_179_ERROR_BEGIN+0xff,
	};

	struct LoginRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_LOGIN_RSP

		ENM_LoginErrorCode enmLoginResult;
		std::wstring strFailReason;
		uint16 lockDays;//��������
		std::wstring strUnlockDate;//�������
		uint32 latestversion;
		uint32 lastlogin_time_high,lastlogin_time_low;
	};

	//////////////////////////////////////////////////////////////////////////

	struct SetSelfInfoEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SET_SELFINFO
		//EVENT_VALUE_CORE_SET_SELFINFO_NOTIFY

		std::map<ENM_InfoType, uint8>			uint8Map;
		std::map<ENM_InfoType, uint16>			uint16Map;
		std::map<ENM_InfoType, uint32>			uint32Map;
		std::map<ENM_InfoType, std::wstring>	stringMap;
	};

	//EVENT_VALUE_CORE_SET_SELFINFO_RSP

	enum ENM_SetSelfInfoResult
	{
		SETSELFINFO_OK				=	0x00,	//�ɹ�
		SETSELFINFO_OK_NOT_ALLOWED	=	0x01,	//���ֶβ������޸�
		SETSELFINFO_OK_UNKNOWN		=	0xff,
	};

	//////////////////////////////////////////////////////////////////////////

	struct BeKickedNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_BE_KICKED_NOTIFY

		enum ENM_KICK_RESULT
		{
			KICK_RE_LOGIN		= 0x00,	//�˺��ص�½
			KICK_SEND_AD		= 0x01,	//���䷢���
			KICK_ACCOUNT_LOCK	= 0x10,	//�˺ű����� +lockDays+strUnlockDate
			KICK_IP_LOCK		= 0x11,	//ip������ +lockDays+strUnlockDate
			KICK_MAC_LOCK		= 0x12,	//mac������ +lockDays+strUnlockDate
			KICK_OTHER			= 0xff, //����
		};

		ENM_KICK_RESULT result;
		std::wstring strReason;
		uint16 lockDays;
		std::wstring strUnlockDate;//�������
	};

	//////////////////////////////////////////////////////////////////////////

	enum ENM_UserStatusType
	{
		USERSTATUSTYPE_PUBLIC_1		=	0x01,	//1�Ź���
		USERSTATUSTYPE_PUBLIC_2		=	0x02,	//2�Ź���
		USERSTATUSTYPE_PUBLIC_3		=	0x04,	//3�Ź���
		USERSTATUSTYPE_PRIVATE		=	0x08,	//˽��
		USERSTATUSTYPE_P2P			=	0x10,	//һ��һ��Ƶ
		USERSTATUSTYPE_FORBIDDEN	=	0x20,	//������
		USERSTATUSTYPE_VIDEO		=	0x40,	//��Ƶ��
		USERSTATUSTYPE_AUDIO		=	0x80,	//��Ƶ��
	};

	struct ClientInfo
	{
		//								 ���λ	
		//  f e d c b a 9 8 7 6 5 4 3 2 1 0
		//	* * * * * * * * * * * * * * * *
		//								| |  -> �ͻ�������
		//                            | -> �Ƿ�������ͷ
		//                          | -> �Ƿ������½


	public:
		ClientInfo():data(0){}

		ClientInfo(bool haveCamera)
		{
			data = 0;
			if(haveCamera)
			{
				data |= 0x04;
			}
		}

		void setData(uint16 data)
		{
			this->data = data;
		}

		operator uint16()
		{
			return data;
		}

		void setHideLogin()
		{
			data |= 0x08;
		}

		bool isHideLogin()
		{
			return (data & 0x08) != 0;
		}

		bool haveCamera()
		{
			return (data & 0x04) != 0;
		}

	private: 
		uint16 data;
	};

	struct room_user_info
	{
		uint32 unUIN;
		bool bMan;
		uint32 un179id;
		std::wstring strName;
		uint8 unVipLevel;
		uint8 unUsrLevel;
		uint8 unRichLevel;
		uint16 unTitleLevel;
		uint32 unBusiness; //ENM_BusinessType
		ClientInfo stClientInfo;
		uint16 unStatus;	//ENM_UserStatusType
		std::vector<uint16> vecItemID;
	};
	
	//////////////////////////////////////////////////////////////////////////

	struct EnterRoomEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_ENTER_ROOM

		uint32 roomid;
		ClientInfo stClientInfo;
		std::wstring password;
	};

	struct EnterRoomRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_ENTER_ROOM_RSP

		enum ENM_EnterRoomResult
		{
			ENTERROOM_ERROR_OK					=	0x00,
			ENTERROOM_ERROR_NOT_EXIST			=	0x01,
			ENTERROOM_ERROR_ROOM_FULL			=	0x02,
			ENTERROOM_ERROR_BLACKLIST			=	0x03,	//�ں�������
			ENTERROOM_ERROR_KICKED				=	0x04,	//���ߣ����unKickTimeLeft
			ENTERROOM_ERROR_NEED_PASSWORD		=	0x05,
			ENTERROOM_ERROR_PASSWORD_WRONG		=	0x06,
			ENTERROOM_ERROR_MAX_ROOM_NUM		=	0x07,	//�����������������unMaxRoomNum
			ENTERROOM_ERROR_ALREADY_IN_ROOM		= 	0x08,	//�Ѿ��ڷ�����
			ENTERROOM_ERROR_TIMEOUT				=	0x09,	//��ʱ
			ENTERROOM_ERROR_OTHER				=	0x0a,	
			ENTERROOM_ERROR_IP_LOCKED			=	0x0b,	//ip���⣬���unKickTimeLeft
			ENTERROOM_ERROR_CLOSED				=	0x0c,	//�����ѹر�
			ENTERROOM_ERROR_ROOM_LOCKED			=	0x0d,	//���䱻�⣬���unLockDaysLeft
			ENTERROOM_ERROR_ROOM_CREATE_FAIL	=	0x0e,
			ENTERROOM_ERROR_SESSION_CREATE_FAIL =	0x10,
			ENTERROOM_ERROR_DECODE_CONNUIN_FAIL =	0x11,
			ENTERROOM_ERROR_GETITEM_TIMEOUT		=	0x12,
			ENTERROOM_ERROR_GETITEM_ERROR		=	0x13,
			ENTERROOM_ERROR_OPNE_ROOM_TOOBIG	=	0x14,	////���뷿��ﵽ�����������
			ENTERROOM_ERROR_UNKNOWN				=	0xff,
		};

		uint32 unRoomID;
		ENM_EnterRoomResult enmResult;
		std::wstring strFailReason;
		uint16 unKickTimeLeft;//���߻򱻷�ip,ʣ��ʱ��(����)
		uint16 unLockDaysLeft;//���䱻��,ʣ��ʱ��(����)
		uint16 unMaxRoomNum;//��ǰ�����������
		std::wstring strRoomName;
		std::wstring strSignature;
		uint32 relayIP_dianxin;
		uint16 relayPort_dianxin;
		uint32 relayIP_wangtong;
		uint16 relayPort_wangtong;
		std::wstring strOwnerName;
		uint32 unOwner179ID;
		bool bOwnerMan;
		uint32 unAVKey;
		std::vector<room_user_info> vecPubMic;//����������Ϣ
		bool bCollected;//�����Ƿ��ղ�
	};

	struct EnterRoomNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_ENTER_ROOM_NOTIFY

		uint32 unRoomID;
		room_user_info stUserInfo;
	};

	//////////////////////////////////////////////////////////////////////////

	struct GetUserListRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_GET_USERLIST_RSP

		bool bcomplete;
		uint32 roomid;
		std::vector<room_user_info> vecUsrList;
	};

	//////////////////////////////////////////////////////////////////////////

	struct GetWaittinglistRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_GET_WAITTINGLIST_RSP

		uint32 roomid;
		std::vector<uint32> vecWaittinglist;
	};

	//////////////////////////////////////////////////////////////////////////

	enum ENM_FontStyleType
	{
		FONTSTYLETYPE_NONE		=	0x00,
		FONTSTYLETYPE_BOLD		=	0x01,	//����
		FONTSTYLETYPE_UNDERLINE	=	0x02,	//�»���
		FONTSTYLETYPE_ITALICS	=	0x04, 	//б��
		FONTSTYLETYPE_COLORTEXT	=	0x08,	//����
	};

	enum ENM_SendMessageType
	{
		SENDMESSAGETYPE_PUBLIC		=	0x00,	//������dstuinΪ0��ʾ������
		SENDMESSAGETYPE_PRIVATE		=	0x01,	//���Ļ�
		SENDMESSAGETYPE_TEMP_NOTICE	=	0x02,	//��ʱ����
		SENDMESSAGETYPE_NOTICE		=	0x03,	//����
	};

	enum ENM_SendMessageResult
	{
		SENDMESSAGERESULT_OK				=	0x00,
		SENDMESSAGERESULT_TOO_FAST			=	0x01,	//����̫��
		SENDMESSAGERESULT_PUBLICCHAT_CLOSED	=	0x02,	//���ı���ֹ
		SENDMESSAGERESULT_COLORTEXT_CLOSED	=	0x03,	//��������ֹ
		SENDMESSAGERESULT_USER_SHUTUP		=	0x04,	//�û�������
		SENDMESSAGERESULT_NO_PERMISSION		=	0x05,	//û��Ȩ��
		SENDMESSAGERESULT_OTHER				=	0x10,
		SENDMESSAGERESULT_PUBLICCHAT_VIP	=	0x11,	//VIP���Ͽ��Թ���
		SENDMESSAGERESULT_PUBLICCHAT_REG	=	0x12,	//ע���û����ϲſɹ���
		SENDMESSAGERESULT_UNKNOWN			=	0xff,
	};

	struct MessageFont
	{
		uint8 font_size;
		uint32 font_color;
		uint8 font_style;//ENM_FontStyleType
		std::wstring font_type;
	};

	struct SendMessageEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SEND_MESSAGE

		uint32 roomid;
		ENM_SendMessageType enmType;
		uint32 dstuin;
		std::wstring message;
		MessageFont stFont;
		bool bIsAutoMsg;//�Ƿ����Զ��ظ�
		bool bRejectAutoMsg;//�ܾ������Զ��ظ�(Ӧ�𱾴���Ϣ)
	};

	struct SendMessageRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SEND_MESSAGE_RSP

		uint32 roomid;
		ENM_SendMessageResult enmResult;
		std::wstring strFailReason;
		uint32 unLeftTime ;
	};

	struct SendMessageNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SEND_MESSAGE_NOTIFY

		uint32 roomid;
		ENM_SendMessageType enmType;
		uint32 srcuin;
		uint32 dstuin;
		std::wstring message;
		MessageFont stFont;
		bool bIsAutoMsg;//�Ƿ����Զ��ظ�
		bool bRejectAutoMsg;//�ܾ������Զ��ظ�(Ӧ�𱾴���Ϣ)
	};	

	//////////////////////////////////////////////////////////////////////////

	enum ENM_GiftType
	{
		GIFTTYPE_NORMAL			=	0x00, //��ͨ����
		GIFTTYPE_STAMP			=	0x01, //���µ���
		GIFTTYPE_SHECHI			=	0x02, //�ݳ޵���
		GIFTTYPE_CHANGEVOICE	=	0x03, //��������
	};

	enum ENM_SendGiftResult
	{
		SENDGIFTRESULT_OK					=	0x00,	//�������һ����Ҳ��ɹ�
		SENDGIFTRESULT_NOT_ENOUGH_MONEY		=	0x01,	//����
		SENDGIFTRESULT_IS_NOT_EXIST			=   0X02,	//���߲�����
		SENDGIFTRESULT_UPDATE_ASSET_FAILED	=	0X03,	//�����ʲ�ʧ��
		SENDGIFTRESULT_NO_PERMISSION		=	0X04,	//û��Ȩ��
		SENDGIFTRESULT_CAN_NOT_SEND			=	0x05,	//������ʹ������
		SENDGIFTRESULT_UPDATEASSET_TIMEOUT	=   0x06 ,	//�����ʲ���ʱ
		SENDGIFTRESULT_ALL_REBOT			=	0x07,	//���ǻ�����
		SENDGIFTRESULT_CAN_NOT_SEND2VISITOR =	0x08,	//���ܶ��ο�ʹ�õ���
		SENDGIFTRESULT_CAN_NOT_SEND2MANAGE  =	0x09,	//���ܶԳ��ܺ�Ѳ��ʹ�õ���
		SENDGIFTRESULT_OTHER				=	0x10, 	
		SENDGIFTRESULT_UNKNOWN				=	0xff,
	};

	enum ENM_GiftDstType
	{
		GIFTDSTTYPE_SINGLE	=	0x00,	//������+dstuin
		GIFTDSTTYPE_MANAGER	=	0x01,	//����Ա
		GIFTDSTTYPE_ALL		=	0x02,	//������
	};

	struct SendGiftEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SEND_GIFT

		uint32			unRoomID;
		ENM_GiftType	enmType;
		uint16			unGiftID;
		uint32			unCount;//�����ͳ�������
		ENM_GiftDstType	enmDstType;
		uint32			unDstUIN;//Ϊ0��ʾ������
		std::wstring	strAttachMessage;//����
	};

	struct SendGiftLuckyInfo
	{
		uint16	unLuckyIndex;
		uint16	unLuckyTimes;
		uint32	unLuckyMoney;
	};

	struct SendGiftRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SEND_GIFT_RSP

		uint32				unRoomID;
		ENM_SendGiftResult	enmResult;
		std::wstring		strFailReason;
		uint32				unTime;
		ENM_GiftType		enmType;
		uint16				unGiftID;
		uint32				unSentCount;//ʵ���ͳ�������
		ENM_GiftDstType		enmDstType;
		uint32				unDstUIN;
		std::wstring		strAttachMessage;//����
		uint32				unLeftMoney;
		uint32				unRichUpdateMoney;
		std::vector<SendGiftLuckyInfo> vecLuckyInfo;
	};

	struct SendGiftNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SEND_GIFT_NOTIFY

		uint32			unRoomID;
		uint32			unTime;
		ENM_GiftType	enmType;
		uint16			unGiftID;
		uint32			unSentCount;//ʵ���ͳ�������
		uint32			unTodayGiftCount;//����������Ѿ��ۼ��յ�������
		uint32			unSrcUIN;
		uint32			unSrc179ID;
		std::wstring	strSrcName;
		ENM_GiftDstType	enmDstType;
		uint32			unDstUIN;
		uint32			unDst179ID;
		std::wstring	strDstName;
		std::wstring	strAttachMessage;//����
		bool			bAttachFlyEffect;//��������Ч��
		std::vector<SendGiftLuckyInfo> vecLuckyInfo;
	};

	//////////////////////////////////////////////////////////////////////////

	enum ENM_LoudSpeakerType
	{
		LOUDSPEAKERTYPE_SMALL	=	0x00,
		LOUDSPEAKERTYPE_BIG		=	0x01,
		LOUDSPEAKERTYPE_SUPER	=	0x02,
	};

	struct SendLoudSpeakerEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SEND_LOUDSPEAKER

		uint32				unRoomID;
		uint16				unGiftID;
		ENM_LoudSpeakerType enmType;
		std::wstring		strMessage;
	};

	struct SendLoudSpeakerRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SEND_LOUDSPEAKER_RSP

		uint32				unRoomID;
		ENM_SendGiftResult	enmResult;
		uint32				unLeftMoney;
		std::wstring		strMessage;
		ENM_LoudSpeakerType enmType;
		std::wstring		strFailReason;
		uint32				unRichUpdateMoney;
	};

	struct SendLoudSpeakerNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SEND_LOUDSPEAKER_NOTIFY

		enum SpeakerMessageType
		{
			SPEAKERMESSAGETYPE_LOUD			= 0x00,//������Ϣ
			SPEAKERMESSAGETYPE_LUCKY		= 0x01,//������Ʒ��500��1000����Ϣ
			SPEAKERMESSAGETYPE_SYSTEM		= 0x02,//ϵͳ������Ϣ
			SPEAKERMESSAGETYPE_PLUTUSAWARD	= 0x03,//����
			SPEAKERMESSAGETYPE_GAMEREWARD	= 0x04,//��Ϸ֪ͨ��Ϣ
			SPEAKERMESSAGETYPE_LUXURY		= 0x05,//�ݳ�������Ϣ
		};

		uint32				unRoomID;
		uint32				unSrcUIN;
		std::wstring		strName;
		uint32				un179id;
		uint8				unVipLevel;
		uint8				unRichLevel;
		std::vector<uint16>	vecGiftID;
		SpeakerMessageType	enmMessageType;
		ENM_LoudSpeakerType enmType;
		uint16				unGiftID;
		std::wstring		strMessage;
		uint8				unCache;		//���������Ƿ����µ� 0:�µ� 1:�����
	};

	//////////////////////////////////////////////////////////////////////////

	struct SendFlyWordsEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SEND_FLYWORDS

		uint32				unRoomID;
		uint16				unGiftID;
		std::wstring		strMessage;
	};

	struct SendFlyWordsRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SEND_FLYWORDS_RSP

		uint32				unRoomID;
		ENM_SendGiftResult	enmResult;
		uint32				unLeftMoney;
		std::wstring		strMessage;
		std::wstring		strFailReason;
		uint32				unRichUpdateMoney;
	};

	struct SendFlyWordsNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SEND_FLYWORDS_NOTIFY

		uint32				unRoomID;
		uint32				unSrcUIN;
		std::wstring		strName;
		uint32				un179id;
		uint16				unGiftID;
		std::wstring		strMessage;
	};

	//////////////////////////////////////////////////////////////////////////

	enum ENM_RequestShowType
	{
		REQUESTSHOWTYPE_ANY			=	0x00,	//����
		REQUESTSHOWTYPE_PUBLIC		=	0x01,	//�Ź���
		REQUESTSHOWTYPE_PRIVATE		=	0x02,	//��˽��
	};

	enum ENM_RequestShowResult
	{
		REQUESTSHOWRESULT_NEED_SELECT			=	0x00,	//��Ҫѡ������˽��
		REQUESTSHOWRESULT_FULL					=	0x01,	//������
		REQUESTSHOWRESULT_PUBLIC				=	0x02,	//���Ϲ���+index+time(sec)
		REQUESTSHOWRESULT_WAITTINGLIST			=	0x03,	//�����������+freeshow_opened
		REQUESTSHOWRESULT_PRIVATE				=	0x04,	//����˽��
		REQUESTSHOWRESULT_PRIVATE_CLOSED		=	0x05,	//����˽���ѹر�
		REQUESTSHOWRESULT_FAIL					=	0x06,	//����ʧ��
		REQUESTSHOWRESULT_ALREADY_ON_SHOW		=	0x07,
		REQUESTSHOWRESULT_ONMIC_IN_OTHERROOM 	=	0x08,	//���������������
		REQUESTSHOWRESULT_WAIT_BUT_ONMIC		=	0x09,	//�����������ʱ����������������
		REQUESTSHOWRESULT_WAITTING_ONMIC		=   0x0a,   //�������������󣬹�������
	};

	struct RequestShowRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_REQUEST_SHOW_RSP

		uint32 unRoomID;
		ENM_RequestShowResult enmResult;
		uint8 unIndex;
		uint16 unTime;//0��ʾ����ʱ�䲻������,��
		bool bFreeShowOpened;
	};

	struct RequestShowNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_REQUEST_SHOW_NOTIFY

		uint32 unRoomID;
		uint32 unSrcUIN;
		ENM_RequestShowResult enmResult;
		uint8 unIndex;
		uint16 unTime;//0��ʾ����ʱ�䲻������,��
	};	

	//////////////////////////////////////////////////////////////////////////

	enum ENM_OperateAVType
	{
		OPERATEAVTYPE_OPEN_VIDEO	=	0x00,
		OPERATEAVTYPE_OPEN_AUDIO	=	0x01,
		OPERATEAVTYPE_CLOSE_VIDEO	=	0x02,
		OPERATEAVTYPE_CLOSE_AUDIO	=	0x03,
	};

	enum ENM_OperateAVResult
	{
		OPERATEAVRESULT_OK			=	0x00,
		OPERATEAVRESULT_NOT_ON_SHOW	=	0x01,
		OPERATEAVRESULT_UNKNOWN		=	0xff,
	};

	struct OperateVideoAudioRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_OPERATE_VIDEO_AUDIO_RSP

		uint32 unRoomID;
		uint32 unDstUIN;
		ENM_OperateAVType enmType;
		ENM_OperateAVResult enmResult;
	};

	//////////////////////////////////////////////////////////////////////////

	enum ENM_KickResult
	{
		KICKRESULT_OK				=	0x00,	//���ˣ����ڳɹ�
		KICKRESULT_NO_PERMISSION	=	0x01,	//Ȩ�޲���
		KICKRESULT_OTHER_IS_KING	=	0x02,	//�Է��ǹ��û�
		KICKRESULT_UNKNOWN			=	0xff,
	};

	struct KickUserEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_KICK_USER

		uint32 unRoomID;
		bool bKickAllVisitor;//�Ƿ��������ο�
		uint32 unDstUIN;//bKickAllVisitorΪfalseʱ��Ч���ߵ�����
		std::wstring strReason;
		uint16 unTime;//��
	};

	struct KickUserRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_KICK_USER_RSP

		uint32 unRoomID;
		ENM_KickResult enmKickResult;
		bool bKickAllVisitor;//�Ƿ��������ο�
		uint32 unDstUIN;//bKickAllVisitorΪfalseʱ��Ч���ߵ�����		
	};

	struct KickUserNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_KICK_USER_NOTIFY

		enum ENM_KickType
		{
			KICKTYPE_ONE					=	0x00,	//�ߵ�����
			KICKTYPE_VISITOR				=	0x01,	//���ο�
			KICKTYPE_FOR_MODIFY_CAPACITY	=	0x02,	//���ڼ��ݱ���
		};

		uint32 unRoomID;
		uint32 unSrcUIN;
		ENM_KickType enmType;
		uint32 unDstUIN;//KICKTYPE_ONEʱ��Ч
		std::wstring strReason;//KICKTYPE_ONEʱ��Ч
		uint16 unTime;//�� KICKTYPE_ONEʱ��Ч
	};

	//////////////////////////////////////////////////////////////////////////

	struct LockIPEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_LOCK_IP

		uint32 unRoomID;
		uint32 unDstUIN;
		std::wstring strReason;
		uint8 unTime;//����
	};

	struct LockIPNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_LOCK_IP_NOTIFY

		uint32 unRoomID;
		uint32 unSrcUIN;
		uint32 unDstUIN;
		std::wstring strReason;
		uint8 unTime;//����
	};
	
	//////////////////////////////////////////////////////////////////////////

	struct PushOnShowNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_PUSH_ON_SHOW_NOTIFY

		uint32 unRoomID;
		uint32 unSrcUIN;
		uint32 unDstUIN;
		uint8 unType;
		uint8 unIndex;
	};

	enum ENM_PushOnResult
	{
		PUSHONRESULT_OK				=	0x00,	//�����ɹ�
		PUSHONRESULT_NO_PERMISSION	=	0x01,	//Ȩ�޲���
		PUSHONRESULT_IS_ON_SHOW		=	0x02,	//�Ѿ�������
		PUSHONRESULT_MIC_IS_LOCKED	=	0x03,	//���󱻹�
		PUSHONRESULT_NEED_ANSWER	=	0x04,	//��Ҫ�Է�Ӧ��
		PUSHONRESULT_UNKNOWN		=	0xff,
	};

	enum ENM_PushOnNotifyType
	{
		PUSHONNOTIFY_TYPE_NEEDANSWER	=	0x00,	//��ҪӦ��
		PUSHONNOTIFY_TYPE_CONNECT		=	0x01,	//�������
		PUSHONNOTIFY_TYPE_REJECT		=	0x02,	//�ܾ�
	};

	enum ENM_PullOffResult
	{
		PULLOFFRESULT_OK			=	0x00,	//�����ɹ�
		PULLOFFRESULT_NO_PERMISSION	=	0x01,	//Ȩ�޲���
		PULLOFFRESULT_IS_OFF_SHOW	=	0x02,	//��������
		PULLOFFRESULT_UNKNOWN		=	0xff,
	};

	struct PushOnShowRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_PUSH_ON_SHOW_RSP

		uint32	unRoomID;
		uint32	unDstUIN;
		uint8	unIndex;
		ENM_PushOnResult enmResult;
	};

	enum ENM_AnswerPushOnShowType
	{
		ANSWERPUSHONSHOW_ACCEPT	=	0x00,
		ANSWERPUSHONSHOW_REFUSE	=	0x01,
	};

	struct PushOnShowAnswerEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_ANSWER_PUSH_ON_SHOW

		uint32	unRoomID;
		uint32	unDstUIN;
		ENM_AnswerPushOnShowType enmType;
		uint8	unIndex;
	};

	enum ENM_AnswerPushOnShowResult
	{
		ANSWERPUSHONSHOWRESULT_OK				=	0x00,	//�����ɹ�
		ANSWERPUSHONSHOWRESULT_IS_ONMIC			=	0x01,	//�Ѿ�������
		ANSWERPUSHONSHOWRESULT_MIC_ISLOCKED		=	0x02,	//���󱻹�
		ANSWERPUSHONSHOWRESULT_MIC_HASPLAYER	=	0x03,	//����������
		ANSWERPUSHONSHOWRESULT_UNKNOWN			=	0xff,	
	};

	struct PushOnShowAnswerRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_ANSWER_PUSH_ON_SHOW_RSP

		uint32 unRoomID;
		uint32 unDstUIN;
		uint8  unIndex;
		ENM_AnswerPushOnShowType enmType;
		ENM_AnswerPushOnShowResult enmResult;
	};

	//////////////////////////////////////////////////////////////////////////

	enum ENM_ChangeTitleResult
	{
		CHANGETILERESULT_OK					=	0x00,
		CHANGETILERESULT_NO_PERMISSION		=	0x01,
		CHANGETILERESULT_IS_FULL			=	0x02,
		CHANGETILERESULT_IS_ADMIN_INOTHER	=	0x03,
		CHANGETILERESULT_UNKNOWN			=	0xff,
	};

	struct AddTitleRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_ADD_TITLE_RSP

		uint32 unRoomID;
		uint32 unDstUIN;
		ENM_TitleLevel enmLevel;
		ENM_ChangeTitleResult enmResult;
	};

	struct AddTitleNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_ADD_TITLE_NOTIFY

		uint32 unRoomID;
		uint32 unSrcUIN;
		uint32 unDstUIN;
		ENM_TitleLevel enmLevel;
	};

	struct RemoveTitleRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_REMOVE_TITLE_RSP

		uint32 unRoomID;
		uint32 unDstUIN;
		ENM_ChangeTitleResult enmResult;
		ENM_TitleLevel enmLevel;
	};	

	struct RemoveTitleNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_REMOVE_TITLE_NOTIFY

		uint32 unRoomID;
		uint32 unSrcUIN;
		uint32 unDstUIN;
		ENM_TitleLevel enmLevel;
	};

	//////////////////////////////////////////////////////////////////////////

	enum ENM_OpenPrivateResult
	{
		OPENPRIVATERESULT_OK				=	0x00,
		OPENPRIVATERESULT_NOT_OPEN			=	0x01,//�Է�˽��û�д�
		OPENPRIVATERESULT_NO_PERMISSION		=	0x02,//û��Ȩ��(����ɫvip�Լ�����)
		OPENPRIVATERESULT_IS_FULL			=	0x03,//�ﵽ˽������
		OPENPRIVATERESULT_ALREADY_OPENED	=	0x04,//�Ѿ��򿪹���
		OPENPRIVATERESULT_IS_SELF			=	0x05,//���Լ�
		OPENPRIVATERESULT_UNKNOWN			=	0xff,
	};

	//////////////////////////////////////////////////////////////////////////

	enum ENM_ConnectP2PResult
	{
		CONNECTP2PRESULT_OK					=	0x00,	//�ȴ��Է�ͬ��
		CONNECTP2PRESULT_SELF_ON_PUBLIC		=	0x01,	//�Լ��Ѿ��ڹ�����
		CONNECTP2PRESULT_SELF_ON_PRIVATE	=	0x02,	//�Լ��Ѿ���˽����
		CONNECTP2PRESULT_SELF_ON_P2P		=	0x03,	//�Լ��Ѿ���1v1��
		CONNECTP2PRESULT_OTHER_ON_PUBLIC	=	0x04,	//�Է��Ѿ��ڹ�����
		CONNECTP2PRESULT_OTHER_ON_PRIVATE	=	0x05,	//�Է��Ѿ���˽����
		CONNECTP2PRESULT_OTHER_ON_P2P		=	0x06,	//�Է��Ѿ���1v1��
		CONNECTP2PRESULT_OTHER_NEED_VIP		=	0x07,	//�Է�ֻ����vip���ϵ�(Ӧ���ò���)
		CONNECTP2PRESULT_OTHER_NEED_KING	=	0x08,	//�Է�ֻ���ܻʹ����ϵ�
		CONNECTP2PRESULT_OTHER_CLOSE		=	0x09,	//�Է��ر�һ��һ
		CONNECTP2PRESULT_SELF_NOT_VIP		=	0x10,	//����һ��һ�ı�����vip����

		CONNECTP2PRESULT_UNKNOWN			=	0xff,
	};	

	//////////////////////////////////////////////////////////////////////////

	enum ENM_ResponseP2PType
	{
		RESPONSEP2PTYPE_ACCEPT	=	0x00,
		RESPONSEP2PTYPE_REFUSE	=	0x01,
	};

	//////////////////////////////////////////////////////////////////////////

	struct ResponseP2PRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_RESPONSE_P2P_RSP

		uint32 unRoomID;
		ENM_ResponseP2PType enmType;
		ENM_ConnectP2PResult enmResult;
		uint32 unDstUIN;
	};

	struct ResponseP2PNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_RESPONSE_P2P_NOTIFY

		uint32 unRoomID;
		ENM_ResponseP2PType enmType;
		uint32 unSrcUIN;//�������
		uint32 unDstUIN;//�����ߣ�ΪRESPONSEP2PTYPE_ACCEPTʱ��Ч
	};	

	struct ShutUpNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SHUT_UP_NOTIFY
		uint32 unRoomID;
		uint32 srcUIN;
		uint32 dstUIN;
		uint32 unLeftTime ;
	};
	//////////////////////////////////////////////////////////////////////////

	struct ReportClientInfoEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_REPORT_CLIENTINFO

		uint32 unRoomID;

		bool bVideoInfo;//�Ƿ����bHaveVideo��Ϣ
		bool bHaveVideo;

		bool bNetInfo;//�Ƿ����bNetInfo��Ϣ
		uint8 unPacketLost;//eg: 123 -> 12.3%
		uint8 unTimeout;//eg:  23 -> 23ms

		bool bHardwareInfo;//�Ƿ����Ӳ����Ϣ
		std::wstring strCPUType;
		uint16 unCPUUse;//eg: 1234 -> 12.34%
		uint16 unMemSize;//eg: 250 -> 2.5G
		uint16 unMemUse;//eg: 2345 -> 23.45%
	};

	struct ReportClientInfoNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_REPORT_CLIENTINFO_NOTIFY

		uint32 unRoomID;
		uint32 unSrcUIN;

		bool bVideoInfo;//�Ƿ����bHaveVideo��Ϣ
		bool bHaveVideo;

		bool bNetInfo;//�Ƿ����bNetInfo��Ϣ
		uint8 unPacketLost;
		uint8 unTimeout;

		bool bHardwareInfo;//�Ƿ����Ӳ����Ϣ
		std::wstring strCPUType;
		uint16 unCPUUse;//eg: 1234 -> 12.34%
		uint16 unMemSize;//eg: 250 -> 2.5G
		uint16 unMemUse;//eg: 2345 -> 23.45%
	};

	//////////////////////////////////////////////////////////////////////////

	struct QueryClientInfoEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_QUERY_CLIENTINFO

		uint32 unRoomID;
		uint32 unDstUIN;
		bool bVideoInfo;//�Ƿ����bHaveVideo��Ϣ
		bool bNetInfo;//�Ƿ����bNetInfo��Ϣ
		bool bHardwareInfo;//�Ƿ����Ӳ����Ϣ		
	};

	struct QueryClientInfoRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_QUERY_CLIENTINFO_RSP

		uint32 unRoomID;
		
		bool bVideoInfo;//�Ƿ����bHaveVideo��Ϣ
		bool bHaveVideo;

		bool bNetInfo;//�Ƿ����bNetInfo��Ϣ
		uint8 unPacketLost;
		uint8 unTimeout;

		bool bHardwareInfo;//�Ƿ����Ӳ����Ϣ
		std::wstring strCPUType;
		uint16 unCPUUse;//eg: 1234 -> 12.34%
		uint16 unMemSize;//eg: 250 -> 2.5G
		uint16 unMemUse;//eg: 2345 -> 23.45%
	};

	//////////////////////////////////////////////////////////////////////////

	enum ENM_RoomOptionType
	{
		ROOMOPTIONTYPE_STATUS					=	0x0001, //(0:�򿪷���)
		ROOMOPTIONTYPE_PUBLICCHAT				=	0x0002, //(0:���Ĵ�)
		ROOMOPTIONTYPE_COLORTEXT				=	0x0004, //(0:������)
		ROOMOPTIONTYPE_USER_INOUT				=	0x0008, //(0:�û�������Ϣ�ر�)
		ROOMOPTIONTYPE_FREESHOW_STATUS			=	0x0010, //(0:��������ر�)
		ROOMOPTIONTYPE_FREESHOW_FOR_MANAGER		=	0x0020, //(0:�����ƹ���Ա��ʱ)
		ROOMOPTIONTYPE_FREESHOW_EDIT_TIME		=	0x0040, //(0:�������Ա�޸���ʱ)
		ROOMOPTIONTYPE_PRIVATESHOW_ENABLE		=	0x0080, //(0:˽��disable)(�Ƿ���˽��)
		ROOMOPTIONTYPE_PRIVATESHOW_STATUS		=	0x0100, //(0:��)(��˽��ʱ�Ƿ��)
		ROOMOPTIONTYPE_AUTO_WELCOME				=	0x0200, //(0:�Զ�����ӭ��)
		ROOMOPTIONTYPE_SHOW_ROOMNAME			=	0x0400, //(0:�ǳ�ǰ��ʾ������)
	};

	enum ENM_RoomInfoType
	{
		ROOMINFOTYPE_NAME				=	0x00, //string��������
		ROOMINFOTYPE_SIGNATURE			=	0x01, //string ��������
		ROOMINFOTYPE_PASSWORD			=	0x02, //string(�մ���û������)
		ROOMINFOTYPE_FREESHOW_TIME		=	0x03, //uint8(��������ʱ����ʱ��,min)
		ROOMINFOTYPE_WELCOME_WORDS		=	0x04, //string(��ӭ��)
		ROOMINFOTYPE_NOTICE				=	0x05, //string(����)
		ROOMINFOTYPE_OPTION				=	0x06, //uint32(RoomOptionType)
		ROOMINFOTYPE_MIC_FIRST_STATUS	=	0x07, //uint8 (һ�����״̬��0��open)
		ROOMINFOTYPE_MIC_SECOND_STATUS	=	0x08, //uint8 (�������״̬)
		ROOMINFOTYPE_MIC_THIRD_STATUS	=	0x09, //uint8 (�������״̬)
	};

	struct SetRoomInfoEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SET_ROOMINFO

		uint32 unRoomID;
		std::map<ENM_RoomInfoType, std::wstring>	map_key2string;
		std::map<ENM_RoomInfoType, uint8>			map_key2uin8;
		std::map<ENM_RoomInfoType, uint32>			map_key2uin32;
	};

	enum ENM_SetRoomInfoResult
	{
		SETROOMINFORESULT_OK			=	0x00,
		SETROOMINFORESULT_NO_PERMISSION	=	0x01,
		SETROOMINFORESULT_UNKNOWN		=	0xff,
	};

	struct SetRoomInfoNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_SET_ROOMINFO_NOTIFY

		uint32 unRoomID;
		uint32 unSrcUIN;

		std::map<ENM_RoomInfoType, std::wstring>	map_key2string;
		std::map<ENM_RoomInfoType, uint8>			map_key2uin8;
		std::map<ENM_RoomInfoType, uint32>			map_key2uin32;
	};

	//////////////////////////////////////////////////////////////////////////

	struct GetRoomInfoRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_GET_ROOMINFO_RSP

		uint32 unRoomID;
		std::map<ENM_RoomInfoType, std::wstring>	map_key2string;
		std::map<ENM_RoomInfoType, uint8>			map_key2uin8;
		std::map<ENM_RoomInfoType, uint32>			map_key2uin32;
	};

	//////////////////////////////////////////////////////////////////////////

	enum ENM_SetMicStatusResult
	{
		SETMICSTATUSRESULT_OK				=	0x00,
		SETMICSTATUSRESULT_NO_PERMISSION	=	0x01,
		SETMICSTATUSRESULT_UNKNOWN			=	0xff,
	};

	//////////////////////////////////////////////////////////////////////////

	struct NotifyUserInfoUpdateEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_NOTIFY_ROOM_USER_INFO_UPDATE

		uint32 unRoomID;
		uint32 unSrcUIN;
		std::map<ENM_InfoType, std::wstring>	map_key2string;
		std::map<ENM_InfoType, uint8>			map_key2uin8;
		std::map<ENM_InfoType, uint16>			map_key2uin16;
		std::map<ENM_InfoType, uint32>			map_key2uin32;
	};

	//////////////////////////////////////////////////////////////////////////	

	struct NotifySystemMessageEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_NOTIFY_SYSTEM_MESSAGE

		enum ENM_SystemMessageType
		{
			SYSTEMMESSAGETYPE_SYSTEM		=	0x00,//ϵͳ��Ϣ
			SYSTEMMESSAGETYPE_TEXT			=	0x01,//���ı�(����)
			SYSTEMMESSAGETYPE_WITHOUT_TITLE	=	0x20,//�ͻ��˼��ϡ��𾴵�***��(����)
		};

		struct MessageInfo
		{
			std::wstring strMessage;
			std::wstring strTipsText;
			std::wstring strTipsURL;
		};

		std::wstring strWindowTitle;//����title
		ENM_SystemMessageType enmType;
		std::vector<MessageInfo> strMessage;
	};

	//////////////////////////////////////////////////////////////////////////
	
	struct NotifyPrivateShowEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_NOTIFY_PRIVATE_SHOW

		uint32 unRoomID;
		std::vector<uint32> vecUIN;
	};

	//////////////////////////////////////////////////////////////////////////

	struct NotifyOfficialNoticeEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_NOTIFY_OFFICIAL_NOTICE

		uint32 unRoomID; //Ϊ0ʱ����ʾ�����з���
		std::wstring strMessage;
	};

	//////////////////////////////////////////////////////////////////////////

	struct NotifyPlutusAwardEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_NOTIFY_PLUTUS_AWARD

		uint32 unRoomID;
		uint16 unGiftID;
		std::wstring strRoomName;
		std::wstring strName;
		uint32 un179ID;
		uint32 unSrcUIN;//����������
		std::vector<uint16> vecMoneys;
	};	

	//////////////////////////////////////////////////////////////////////////
	
	struct NotifyRoomLockedEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_NOTIFY_ROOM_LOCKED

		uint32 unRoomID;
		std::wstring strReason;
		uint16 lockdays;//��ͣ����
		uint32 unlockdate;//�������
	};	

	//////////////////////////////////////////////////////////////////////////

	struct NotifyMediaServerResetEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_NOTIFY_MEDIA_SERVER_RESET

		uint32 unRoomID;
		uint32 relayIP_dianxin;
		uint16 relayPort_dianxin;
		uint32 relayIP_wangtong;
		uint16 relayPort_wangtong;
	};

	//////////////////////////////////////////////////////////////////////////

	struct NotifyRichStarEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_NOTIFY_RICH_STAR

		uint32				unRoomID;
		uint32				unSrcUIN;
		std::wstring		strName;
		uint32				un179id;
		uint32				unMoney;
	};	

	//////////////////////////////////////////////////////////////////////////	

	//SERVICE_VALUE_CORE_GET_GIFT_STAR_INFO
	
	struct GiftStarInfo
	{
		uint16 unGiftID;
		uint32 unCount;
	};

	struct GetGiftStarInfo
	{
		uint32 unUIN;
		std::vector<GiftStarInfo> vecInfo;
	};

	//////////////////////////////////////////////////////////////////////////	

	//SERVICE_VALUE_CORE_GET_MY_GOODS

	struct GetMyGoods
	{
		std::map<uint16, uint16> mapItem2Count;
	};

	//////////////////////////////////////////////////////////////////////////

	struct ReportCollectInfoEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_REPORT_COLLECT_INFO

	#define COLLECT_INFO_UPLOST		L"UpPackLost"
	#define COLLECT_INFO_DOWN		L"DownPackLost"
	#define COLLECT_INFO_PROCESS	L"Process"

		struct Key2Value
		{
			std::wstring key;
			std::wstring value;
		};

		std::vector<Key2Value> vecCollecInfo;
	};

	//////////////////////////////////////////////////////////////////////////

	struct GetFansRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_GET_FANS_RSP

		struct FansInfo
		{
			uint32 uin;
			std::wstring nickname;
			uint32 money;

			FansInfo():uin(0){}
		};

		uint32 result;
		uint32 uin;
		FansInfo day[5];
		FansInfo month[5];
		FansInfo all[5];
	};

	//////////////////////////////////////////////////////////////////////////

	struct GetSofaListRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_GET_SOFA_LIST_RSP

		struct SofaInfo
		{
			uint32 uin;
			bool   bman;
			uint32 un179ID;
			std::wstring nickname;
			uint32 price;
			uint8 vipLevel;
			uint8 richLevel;

			SofaInfo():uin(0){}
		};

		uint32 roomID;
		uint32 result;
		SofaInfo sofa[5];
	};

	//////////////////////////////////////////////////////////////////////////

	struct BuySofaRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_BUY_SOFA_RSP

		enum ENM_BuySofaResult
		{
			BUYSOFARESULT_OK				=	  0x00,	//�����ɹ�
			BUYSOFARESULT_PRICE_TOO_LOW		=	  0x01,	//����̫��
			BUYSOFARESULT_NOT_ENOUGH_MONEY   =	  0x02,	//����
			BUYSOFARESULT_UNKNOWN			=	  0xff,
		};

		uint32 roomid;
		uint8  sofaIndex;//1,2,3,4,5
		ENM_BuySofaResult enmResult;
		uint32 price;//��λɳ��
		uint32 leftMoney;
		uint32 nextMagnateLevelSpend;
	};

	struct BuySofaNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_BUY_SOFA_NOTIFY

		uint32 roomid;
		uint32 uin;
		uint8  sofaIndex;//1,2,3,4,5
		uint32 price;//��λɳ��
	};

	//////////////////////////////////////////////////////////////////////////

	struct Song
	{
		std::wstring songName;
		uint8 songType;//1:hot
	};

	struct UpdateSongListEvent : public ExtraInfo
	{
		//EVENT_VALUE_UPDATE_SONGLIST

		uint32 roomid;
		std::vector<Song> vecSongList;
	};

	struct UpdateSongListRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_UPDATE_SONGLIST_RSP

		enum ENM_UpdateSonglistResult
		{
			UPDATESONGRESULT_OK				= 0x00,   //�ɹ�
			UPDATESONGRESULT_FULL			= 0x01,   //�赥����
			UPDATESONGRESULT_HOT_FULL		= 0x02,   //���Ƹ�����
			UPDATESONGRESULT_NO_PERMISSION	= 0x03,   //û��Ȩ��(��������..)
			UPDATESONGRESULT_UNKNOWN		= 0xff,   
		};

		uint32 roomid;
		ENM_UpdateSonglistResult enmResult;
		std::vector<Song> vecSongList;
	};

	//////////////////////////////////////////////////////////////////////////

	struct GetSongListRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_GET_SONGLIST_RSP

		uint32 result;//0:�ɹ�
		uint32 roomid;
		uint32 songerUin;
		std::vector<Song> vecSongList;
	};	

	//////////////////////////////////////////////////////////////////////////

	struct OrderSongEvent : public ExtraInfo
	{
		//EVENT_VALUE_ORDER_SONG

		uint32 roomid;
		uint32 songerUin;
		std::wstring songName;
		std::wstring attachWords;
		uint16 count;

		enum ENM_OrderSongResult
		{
			ORDERSONGRESULT_OK					= 0x00,   //�ɹ�
			ORDERSONGRESULT_MONEY_NOT_ENOUGH	= 0x01,   //�Ҳ���
			ORDERSONGRESULT_NO_PERMISSION		= 0x02,   //�Է���������
			ORDERSONGRESULT_TIMEOUT				= 0x03,   //��ʱ
			ORDERSONGRESULT_UNKNOWN				= 0x04,   //δ֪����
		};
	};

	struct SongOrder
	{
		uint32 orderId;
		uint32 orderTime;
		uint32 songerUin;
		std::wstring songerNickname;
		uint32 uin;
		std::wstring nickName;
		std::wstring songName;
		std::wstring attachWords;
		uint16 count;

		enum ENM_OrderStatus
		{
			ORDER_STATUS_TODO,//����������
			ORDER_STATUS_ACCEPTED,//������ͬ�⣬������
			ORDER_STATUS_REJECTED,//�����Ѿܾ�
			ORDER_STATUS_MARK_GOOD,//����ߺ���
			ORDER_STATUS_MARK_BAD,//����߲���
			ORDER_STATUS_MARK_NONE,//���������
		};

		ENM_OrderStatus status;

		SongOrder()
		{
			orderId = orderTime = songerUin = uin = 0;
			status = ORDER_STATUS_TODO;
		}
	};

	struct OrderSongNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_ORDER_SONG_NOTIFY

		uint32 roomid;
		SongOrder order;
	};	

	//////////////////////////////////////////////////////////////////////////

	struct ProcessOrderNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_PROCESS_ORDER_NOTIFY

		uint32 roomid;
		SongOrder order;
	};

	//////////////////////////////////////////////////////////////////////////
	
	struct GetOrderListRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_GET_ORDERLIST_RSP

		uint32 roomid;
		uint32 result;//0:�ɹ�
		std::vector<SongOrder> orderList;
	};
	
	//////////////////////////////////////////////////////////////////////////

	struct MarkSongNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_MARK_SONG_NOTIFY

		uint32 roomid;
		SongOrder order;
	};	

	//////////////////////////////////////////////////////////////////////////

	struct OpenBoxRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_OPEN_BOX_RSP

		enum ENM_OpenBoxResult
		{
			OPENBOXRESULT_OK				= 0x00,   //�ɹ�
			OPENBOXRESULT_NO_FREE_CHANCE	= 0x01,   //û������ʸ�
			OPENBOXRESULT_MONEY_NOT_ENOUGH	= 0x02,   //�Ҳ���
			OPENBOXRESULT_UNKNOWN			= 0x10,   //(δ֪����)
		};

		struct RewardItem
		{
			uint16 itemid;
			uint16 itemcount;
		};

		uint32 roomid;
		ENM_OpenBoxResult result;
		std::vector<RewardItem> vecReward;
	};

	struct RewardBoxKeyNotifyEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_REWARD_BOX_KEY_NOTIFY

		uint8 count;
		std::wstring reason;
		uint8 isFirstTime;
	};

	//////////////////////////////////////////////////////////////////////////

	struct GetOfflineActorRspEvent : public ExtraInfo
	{
		//EVENT_VALUE_CORE_GET_OFFLINE_ACTOR_RSP

		uint32 roomID;
		std::vector<room_user_info> offlineActor;
	};
}
