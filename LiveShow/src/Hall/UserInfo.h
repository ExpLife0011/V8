#pragma once

#include <vector>
#include <string>
#include <afxwin.h>
using namespace std;
#include "coredefine.h"


struct UserInfoHead
{
	UserInfoHead()
	{
		strLoginAccount=_T("");
		nickName=_T("");
		unUIN = 0;
	}
	unsigned int  unUIN;
	CString strLoginAccount;
	CString nickName;
	bool bMan;	

	bool operator ==(const UserInfoHead &head2)
	{		
		return unUIN == head2.unUIN;
	}

	
};

struct UserInfoLogin
{
	UserInfoLogin()
	{		
		bOpenSound = true;
		unUIN = 0;
	}	
	
	unsigned int  unUIN;
	CString strLoginPassword;
	bool bAutoLogin;   //�Ƿ��Զ���¼
	bool bSavePassword; //�Ƿ񱣴�����
	bool bOpenSound;   //�Ƿ������
};
struct UserInfo_PersonalSetting
{
	unsigned int unOnMicPurpose;
	unsigned int unGeneralVolume;
	unsigned int unAccompanyVolume;
	unsigned int unMicVolume;
	bool bStrengthenMic;
	unsigned int unRecordMixVolume;
	unsigned int unRecordMicVolume;
	CString strUseVideoDevice;
	CString strUseAudioDevice;
	bool bAutoVirtualVideo;
	unsigned int unRoomSpeakerVolume;
	unsigned int unRoomMicVolume;
	core::MessageFont TempMessageFont ;
	core::MessageFont ChatMessageFont;
	UserInfo_PersonalSetting()
	{
		unOnMicPurpose = 2;
		unGeneralVolume = 0;
		unAccompanyVolume = 0;
		unMicVolume = 0;
		bStrengthenMic = false;
		unRecordMixVolume = 0;
		unRecordMicVolume = 0;
		strUseVideoDevice = _T("");
		strUseAudioDevice = _T("");
		TempMessageFont.font_type = L"����" ;
		TempMessageFont.font_size = 14 ;
		ChatMessageFont.font_type = L"����";
		ChatMessageFont.font_size = 14;
		bAutoVirtualVideo = true;
		unRoomSpeakerVolume = 255;
		unRoomMicVolume = 255;
	}
};

