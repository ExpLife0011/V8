#pragma once
#include "stdafx.h"
#include "51ktv.h"
#include "coredefine.h"
#include "AvDefine.h"

namespace Room
{
	enum E_RoomEventValue
	{
		EVENT_VALUE_ROOM_MODULE_BEGIN = EVENT_VALUE_ROOM_BEGIN,

		EVENT_VALUE_ROOM_SHOW_REGISTER,			//��������ע���

		EVENT_VALUE_ROOM_MODULE_END,
	};
	enum 
	{
		service_value_room_module_begin = SERVICE_VALUE_ROOM_BEGIN ,
		SERVICE_ROOM_CREATE_AND_SHOW,
		SERVICE_ROOM_GETAUDIO_DEVICE_LIST,		//��ȡ��Ƶ��������豸�б�
		SERVICE_ROOM_GETVIDEO_DEVICE_LIST,		//��ȡ��Ƶ�豸�б�
		SERVICE_ROOM_SAVE_PHOTO_TOBMP,			//��������ΪBMP��ָ����·�� BMP��ʽ
		SERVICE_ROOM_GET_NET_STATE,				//��ȡ�Լ�������״̬
		SERVICE_ROOM_GET_ROOM_LIST,				//��ȡ�򿪵ķ����б�
		SERVICE_ROOM_CLOSE_A_ROOM,				//�ر�һ������
		SERVICE_ROOM_ACTIVE_A_ROOM,				//������ʾ��һ������
		SERVICE_ROOM_CLOSED_REGISTER_DLG,		//�ر���ע��Ի���

		SERVICE_ROOM_SHOW_SYSSETTING,                //��ʾϵͳ���öԻ���  &SysSettingType
		SERVICE_ROOM_GET_RICHLEVEL_INFO,		//��ø����ȼ���Ϣ�����֣�ͼƬ
		SERVICE_VALUE_ROOM_MODULE_END ,

	};
};

enum SysSettingDlgType
{
	Show_User_Info_Dlg      =  0,  //��������	
	Show_Basic_Setting_Dlg      ,  //��������
	Show_Audio_Setting_Dlg      ,  //��Ƶ����
	Show_PwdSafe_Setting_Dlg    ,  //���밲ȫ
	Show_MgrRoom_Setting_Dlg    ,  //�ҵķ���
	Show_BankAccount_Dlg		,  //�����˺�
	Show_My_Account_Dlg         ,  //�ҵ��˻�
	Show_Fans_Dlg				,  //��˿����
	Show_Sound_Setting_Dlg      ,  //��Ƶ����
	Show_Message_Setting_Dlg    ,  //��Ϣ����
};

struct SysSettingType
{
	SysSettingDlgType dlgType;
	HWND pParentWnd;
};

struct RoomShowRegister : public ExtraInfo
{		
	HWND m_parentHwnd;  
};

struct Room_Create_And_Show
{
	core::EnterRoomRspEvent stEnterRoom;
	core::GetRoomInfoRspEvent stRoomInfo;
};

#define MAX_AUDIO_DEVICE_NUM             10
#define MAX_VIDEO_DEVICE_NUM             10
#define DEVICE_NAME_LEN					128

struct Room_Get_Audio_Device_List		//��ȡ��Ƶ��������豸�б�
{
	int			iDeviceNum;
	wchar_t     wsDeviceName[MAX_AUDIO_DEVICE_NUM][DEVICE_NAME_LEN];
	bool		bInput;
};
struct  Room_Get_Video_Device_List		//��ȡ��Ƶ�豸�б�
{
	int         iDeviceNum;              //�豸����
	wchar_t     wsDeviceName[MAX_VIDEO_DEVICE_NUM][DEVICE_NAME_LEN];
};

struct Room_Get_Video_Device_Info_List
{
	int			iDeviceNum;
	Service_Video_Info stDeviceInfo[MAX_VIDEO_DEVICE_NUM];
};

struct Room_Show_Video_Ajust_Dlg   //��ʾ��Ƶ���Ե����Ի���
{
	HWND        hParentWnd;
	uint32      iDeviceID;
};

struct Room_Test_Set_Video_Device  //������Ƶ�豸
{
	int iDeviceId ;
};

struct Room_Test_Stop_Video_Device
{
	int iDeviceId ;
	HWND hWnd ;
};

struct Room_Save_Photo_ToBmp		//��������ΪBMP��ָ����·�� BMP��ʽ
{
	HWND hWnd ;
	std::wstring strPath ;
};

struct Room_Get_Net_State			//��ȡ�Լ�������״̬
{
	float fRate ;
};

struct Room_Get_Room_List			//��ȡ�򿪵ķ����б�
{
	std::vector<uint32> vecRoomList;
};

struct Room_Get_Rich_Level_Info
{
	uint8 unRichLevel;
	std::wstring strLevelName;
	std::wstring strImgPath;
};
