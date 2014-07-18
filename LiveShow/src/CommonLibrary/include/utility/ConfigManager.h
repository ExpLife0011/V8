#pragma once

#ifdef _SUPPORT_COMMON_EXPORT
#define COMMON_INTERFACE __declspec(dllexport)
#else
#define COMMON_INTERFACE __declspec(dllimport)
#endif
#include <string>
#include <vector>
#include <list>
using namespace std;
#include "..\..\..\Hall\UserInfo.h"
#include <windows.h>

#define USERLIST_LOGIN_179KEY   _T("list179")
#define USERLIST_LOGIN_NICKNAME     _T("nickName")
#define USERLIST_LOGIN_UIN      _T("uin")
#define USERLIST_LOGIN_ACCOUNT  _T("name")
#define USERLIST_LOGIN_COUNT    _T("count")
#define USERLIST_LOGIN_BMAN      _T("bMan")
#define USERINFO_LOGIN_AUTOLGOIN _T("AutoLogin")
#define USERINFO_LOGIN_SAVEPASSWORD _T("SavePassword")
#define USERINFO_LOGIN_OPENSOUND _T("OpenSound")
#define USERINFO_LOGIN_PASSWORD _T("Password")

#define USERINFO_PERSONALSETTING_ONMICPURPOSE		_T("OnMicPurpose")
#define USERINFO_PERSONALSETTING_GENERALVOLUME		_T("GeneralVolume")
#define USERINFO_PERSONALSETTING_ACCOMPANYVOLUME	_T("AccompanyVolume")
#define USERINFO_PERSONALSETTING_MICVOLUME			_T("MicVolume")
#define USERINFO_PERSONALSETTING_STRENGTHENMIC		_T("StrengthenMic")
#define USERINFO_PERSONALSETTING_RECORDMIXVOLUME	_T("RecordMixVolume")
#define USERINFO_PERSONALSETTING_RECORDMICVOLUME	_T("RecordMicVolume")
#define USERINFO_PERSONALSETTING_USEVIDEODEVICE		_T("UseVideoDevice")
#define USERINFO_PERSONALSETTING_USEAUDIODEVICE		_T("UseAudioDevice")
#define USERINFO_PERSONALSETTING_AUTOVIRTUALVIDEO	_T("AutoVirtualVideo")
#define USERINFO_PERSONALSETTING_ROOMSPEAKERVOLUME	_T("RoomSpeakerVolume")
#define USERINFO_PERSONALSETTING_ROOMMICVOLUME		_T("RoomMicVolume")
#define USERINFO_PERSONALSETTING_SAFECENTERTIP		_T("SafeCenterTip")
#define USERINFO_PERSONALSETTING_TEMPFONTSIZE		_T("TempFontSize")
#define USERINFO_PERSONALSETTING_TEMPFONTNAME		_T("TempFontName")
#define USERINFO_PERSONALSETTING_TEMPFONTSTYLE		_T("TempFontStyle")
#define USERINFO_PERSONALSETTING_TEMPFONTCOLOR		_T("TempFontColor")
#define USERINFO_PERSONALSETTING_CHATFONTSIZE       _T("ChatFontSize")
#define USERINFO_PERSONALSETTING_CHATFONTNAME       _T("ChatFontName")
#define USERINFO_PERSONALSETTING_CHATFONTSTYLE      _T("ChatFontStyle")
#define USERINFO_PERSONALSETTING_CHATFONTCOLOR      _T("ChatFontColor")
#define USERINFO_FLYTEXT_PROMPT						_T("FlyTextPrompt")
#define USERINFO_MODIFY_NAME                        _T("ModifyName")
#define USERINFO_BEGINNER_GUIDE						_T("BeginnerGuide")
//#define USERINFO_CHATWITHME_FLASHFRAME              _T("ChatWithMe")

#define SECTION_QQSELECTTIP  _T("QQSelectTip")
#define KEY_QQTIPISSHOW      _T("QQTipIsShow")
#define KEY_QQLOGINTIP         _T("QQLoginTip")


class COMMON_INTERFACE CConfigManager
{
private:
	CConfigManager(void);
	virtual ~CConfigManager(void);
	static CConfigManager *m_pInstance;
	//�����ļ�������
	CString m_strConfigFileName;

public:
	static CConfigManager *Instance();

	//��ʼ�������ļ�����������������ļ��ʹ�����
	//�������ļ��м������е��û���Ϣ
	void Init();	

	/************************�û���ص���Ϣ************************************/

//////////////////////////////////////////////////////////////////////////	
	void GetUserInfo_Login(unsigned int  unUIN,UserInfoLogin &info_Login);
	void GetUserInfo_List(list<UserInfoHead> &info_List);
	void GetUserInfo_Head(CString strAccount,UserInfoHead &info_Head);
	void GetUserInfo_PersonalSetting(unsigned int unUIN,UserInfo_PersonalSetting &info_PersonalSetting);	
	void GetUserInfo_Setting(unsigned int unUIN, CString strKey, CString &strValue);
	void GetKeyValue(CString sectionKey, CString strKey, CString &strValue,CString strDefault = _T(""));  //�л�QQ��ʾ��ǩ�Ƿ������ʾ
	
	
//////////////////////////////////////////////////////////////////////////	
	void SetUserInfo_Login(const UserInfoLogin &info_Login); //�����¼�û���Ϣ�������ļ�
	void SetUserInfo_List(list<UserInfoHead> &info_List);
	void SetUserInfo_PersonalSetting(unsigned int unUIN,const UserInfo_PersonalSetting &info_PersonalSetting);	
	void SetUserInfo_Setting(unsigned int unUIN, CString strKey, CString strValue);
	void SetKeyValue(CString sectionKey, CString strKey, CString strValue);  //����QQ��ʾ��ǩ�Ƿ������ʾ

	
	void RemoveUserInfo(unsigned int unUIN);//�������ļ���ɾ�����û���Ӧ������
	
//////////////////////////////////////////////////////////////////////////	

private:
	class CGarbageCollector //��������ʱɾ��CConfigManager��ʵ�� 
	{
	public:
		~CGarbageCollector()
		{ 
			if (CConfigManager::m_pInstance)
				delete CConfigManager::m_pInstance;
		}
	};
	static CGarbageCollector Garbo; 
	
};
