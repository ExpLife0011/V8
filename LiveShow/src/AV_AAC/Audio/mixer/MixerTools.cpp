#include "StdAfx.h"
#include <string>
#include <iostream>
#include <fstream>
#include "MixerTools.h"
#include "MixerManager.h"

using namespace std;

CMixerTools m_MixerTools;

CMixerTools::CMixerTools(void)
{
	hInstance = NULL;
	bLoad = false;
	bSucc = false;
	funMixerControlMuteOrSelect = NULL;
	funMixerControlMuteOrSelect= NULL;
	funSetMixerControlMuteOrSelect= NULL;
	funSetMixerControlSingMode= NULL;
	funSetMixerControlChatMode= NULL;
	funSetMixerControlPlayMode= NULL;
	funGetMixerControlSingMode=NULL;
	funGetMixerControlChatMode=NULL;
	funGetMixerControlPlayMode=NULL;
	funGetMixerControlMode=NULL;
}

CMixerTools::~CMixerTools(void)
{
try
{
	if (hInstance)
	{
		FreeLibrary(hInstance);
	}
}
catch (...)
{
	OutputDebugStr(L"Audio Tools DLL is error!\n");
}
}

//����DLL
void CMixerTools::LoadDll()
{
	return;
	if(bLoad) return;
	bLoad = true;
	wstring str = GetCurrPath();
	str.append(MIXERTOOLSNAME);
	fstream _file;
	_file.open(str.c_str(),ios::in);
	if(!_file)
	{
		bSucc = false;
		return;
	}
	try
	{
		hInstance=LoadLibrary(MIXERTOOLSNAME);
		if (!hInstance)
		{
			bSucc = false;
			return;
		}
		//ָ�������� ѡ�� �� ��������
		funMixerControlMuteOrSelect=(pfIsMixerControlMuteOrSelect)GetProcAddress(hInstance, "IsMixerControlMuteOrSelect");
		funSetMixerControlMuteOrSelect = (pfSetMixerControlMuteOrSelect)GetProcAddress(hInstance, "SetMixerControlMuteOrSelect");
		funSetMixerControlSingMode=(pfSetMixerControlSingMode)GetProcAddress(hInstance, "SetMixerControlSing");
		funSetMixerControlChatMode=(pfSetMixerControlSingMode)GetProcAddress(hInstance, "SetMixerControlChat");
		funSetMixerControlPlayMode=(pfSetMixerControlSingMode)GetProcAddress(hInstance, "SetMixerControlPlay");
		funGetMixerControlSingMode=(pfGetMixerControlSingMode)GetProcAddress(hInstance, "GetMixerControlSing");
		funGetMixerControlChatMode=(pfGetMixerControlSingMode)GetProcAddress(hInstance, "GetMixerControlChat");
		funGetMixerControlPlayMode=(pfGetMixerControlSingMode)GetProcAddress(hInstance, "GetMixerControlPlay");
		funGetMixerControlMode=(pfGetMixerControlMode)GetProcAddress(hInstance, "GetMixerControlMode");
		bSucc = true;
	}
	catch (...)
	{
		bSucc = false;
	}
}

bool CMixerTools::IsLoad()
{
// 	if (!bLoad) LoadDll();    ���������ʵ��
// 	if (!bSucc) return false;
	return true;
}

//��ȡ��ǰ·��
wstring CMixerTools::GetCurrPath()
{
	WCHAR buf[5000] = {0}; 
	int nlen =  ::GetModuleFileName(NULL,buf,5000); 

	while(TRUE) 
	{ 
		if   (buf[nlen--]== '\\') 
			break; 
	} 
	++nlen;
	buf[++nlen] = '\0'; 
	wstring path = buf; 
	return path; 
}

//�ж�ָ��������� ѡ���� ѡ�� ���Ǿ���
bool CMixerTools::IsMixerControlMuteOrSelect(int componentType,int lineType,bool& bSel)
{
	if (IsLoad() && funMixerControlMuteOrSelect)
	{
		return (funMixerControlMuteOrSelect(componentType,lineType,&bSel) == 0);
	}
	else
	{
		return false;
	}
}

//����ָ�������ѡ�� ѡ�� �� ���� ѡ�� �� ��ѡ��
bool CMixerTools::SetMixerControlInmicMuteOrSelect(bool bSel)
{
	if (IsLoad() && funSetMixerControlMuteOrSelect)
	{
		return (funSetMixerControlMuteOrSelect(GetComponentType(MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT),(int)MIXER_ALL,bSel) == 0);
	}
	else
	{
		return false;
	}
}

//��ǰϵͳ��Ƶ�Ƿ�֧�ֻ�������  ͨ���������������ѡ���Ƿ���ѡ�� ���ж�
bool CMixerTools::IsMixerControlSupportSelect(bool& bSel)
{
	return 	IsMixerControlMixerSelect(bSel);
}

//�������������͵�ѡ���� ѡ�� ���� ����
bool CMixerTools::IsMixerControlMixerSelect(bool& bSel)
{
	if (IsLoad() && funMixerControlMuteOrSelect)
	{
		return (funMixerControlMuteOrSelect(GetComponentType(MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT),(int)MIXER_ALL,&bSel) == 0);
	}
	else
	{
		return false;
	}
}

//�������������� ѡ�� ��ѡ��״̬
bool CMixerTools::SetMixerControlMixerMuteOrSelect(bool bSel)
{
	if (IsLoad() && funMixerControlMuteOrSelect)
	{
		return (funSetMixerControlMuteOrSelect(GetComponentType(MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT),(int)MIXER_ALL,bSel) == 0);
	}
	else
	{
		return false;
	}
}

//����˷����͵�ѡ����ѡ�� ���� ����
bool CMixerTools::IsMixerControlInmicSelect(bool& bSel)
{
	if (IsLoad() && funMixerControlMuteOrSelect)
	{
		return (funMixerControlMuteOrSelect(GetComponentType(MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE),(int)MIXER_IN,&bSel) == 0);
	}
	else
	{
		return false;
	}
}

//����ָ�������ѡ�� ѡ�� �� ���� ѡ�� �� ��ѡ��
bool CMixerTools::SetMixerControlMuteOrSelect(int componentType,int lineType,bool bSel)
{
	if (IsLoad() && funMixerControlMuteOrSelect)
	{
		return (funSetMixerControlMuteOrSelect(componentType,lineType,bSel) == 0);
	}
	else
	{
		return false;
	}
}

//��ȡ�ؼ����� EnMixerComponentType 
int CMixerTools::GetComponentType(unsigned int nComponentType)
{
	EnMixerComponentType enType =(EnMixerComponentType)NULL;
	switch(nComponentType)
	{
	case MIXERLINE_COMPONENTTYPE_DST_SPEAKERS://��������
		{
			enType = ctDstSpeakers;
		}
	case MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT://����,����������
		{
			enType = ctSrcWaveOut;
		}
		break;
	case MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER://��������
		{
			enType = ctSrcSynthesizer;
		}
		break;
	case MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC://CD
		{
			enType = ctSrcCD;
		}
		break;
	case MIXERLINE_COMPONENTTYPE_SRC_LINE://���������,��������
		{
			enType = ctSrcLine;
		}
		break;
	case MIXERLINE_COMPONENTTYPE_DST_WAVEIN://¼������
		{
			enType = ctDstWaveIn;
		}
		break;
	case MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE://����˷� ǰ����
		{
			enType = ctSrcMicrophone;
		}
		break;
	case MIXERLINE_COMPONENTTYPE_DST_TELEPHONE:
		{
			enType = ctDstTelephone;
		}
		break;
	case MIXERLINE_COMPONENTTYPE_DST_UNDEFINED:
		{
			enType = ctDstUndefined;
		}
		break;
	case MIXERLINE_COMPONENTTYPE_DST_VOICEIN:
		{
			enType = ctDstVoiceIn;
		}
		break;
	case MIXERLINE_COMPONENTTYPE_SRC_ANALOG: //����������
		{
			enType = ctSrcAnalog;
		}
		break;
	case MIXERLINE_COMPONENTTYPE_SRC_DIGITAL:
		{
			enType = ctSrcDigital;
		}
		break;
	case MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER:
		{
			enType = ctSrcPCSpeaker;
		}
		break;
	case MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE:
		{
			enType = ctSrcTelephone;
		}
		break;
	case MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED:
		{
			enType = ctSrcUndefined;
		}
		break;
	default:
		{
			enType = ctDstSpeakers;
		}
	}
	return enType;
}

//���ó���ģʽ
bool CMixerTools::SetMixerControlSingMode()
{
	if (IsLoad() && funSetMixerControlSingMode)
	{
		return (funSetMixerControlSingMode()==0);
	}
	else
	{
		return false;
	}
}
//��������ģʽ
bool CMixerTools::SetMixerControlChatMode()
{
	if (IsLoad() && funSetMixerControlChatMode)
	{
		return (funSetMixerControlChatMode()==0);
	}
	else
	{
		return false;
	}
}
//���÷Ÿ�ģʽ
bool CMixerTools::SetMixerControlPlayMode()
{
	if (IsLoad() && funSetMixerControlPlayMode)
	{
		return (funSetMixerControlPlayMode()==0);
	}
	else
	{
		return false;
	}
}

//��ȡ�Ƿ񳪸�ģʽ
bool CMixerTools::GetMixerControlSingMode(bool& bEnable)
{
	if (IsLoad() && funGetMixerControlSingMode)
	{
		return (funGetMixerControlSingMode(&bEnable)==0);
	}
	else
	{
		return false;
	}
}

//��ȡ�Ƿ�����ģʽ
bool CMixerTools::GetMixerControlChatMode(bool& bEnable)
{
	if (IsLoad() && funGetMixerControlChatMode)
	{
		return (funGetMixerControlChatMode(&bEnable)==0);
	}
	else
	{
		return false;
	}
}

//��ȡ�Ƿ�Ÿ�ģʽ
bool CMixerTools::GetMixerControlPlayMode(bool& bEnable)
{
	if (IsLoad() && funGetMixerControlPlayMode)
	{
		return (funGetMixerControlPlayMode(&bEnable)==0);
	}
	else
	{
		return false;
	}
}

//��ȡ��ǰϵͳģʽ 0:����ģʽ 1����ģʽ 2��������ģʽ 3����ģʽ
bool CMixerTools::GetMixerControlMode(int* pnMode)
{
	if (IsLoad() && funGetMixerControlMode)
	{
		return (funGetMixerControlMode(pnMode)==0);
	}
	else
	{
		return false;
	}
}
