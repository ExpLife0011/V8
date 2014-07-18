#include "StdAfx.h"
#include "MixerManager.h"
#include "MixerTools.h"
#include "MixerOther.h"
#include "MyAssert.h"
#include <tchar.h>

CMixerManager::CMixerManager(void)
{
	m_pMixerChannel = NULL;
}

CMixerManager::~CMixerManager(void)
{
	if (m_pMixerChannel) delete m_pMixerChannel;
}

void CMixerManager::Init(HWND hWnd)
{
	if (!m_pMixerChannel) m_pMixerChannel = new CMixerChannel;
	m_pMixerChannel->Init(hWnd);
	m_MixerTools.LoadDll();
}

void CMixerManager::GetMixerLineParam(EnMixerControlType sType,StrucMixerParam& sMixerParam)
{
	switch(sType)
	{
	case MIXER_CONTROL_TOTAL_TYPE://������
		sMixerParam.dwLineType = MIXERLINE_TARGETTYPE_WAVEOUT;
		sMixerParam.nControlType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
		sMixerParam.enType = MIXER_OUT;
		break;
	case MIXER_CONTROL_WAVOUT_TYPE://���� ����
		sMixerParam.dwLineType = MIXERLINE_TARGETTYPE_WAVEOUT;
		sMixerParam.nControlType = MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT;
		sMixerParam.enType = MIXER_OUT;
		break;
	case MIXER_CONTROL_OUTMIC_TYPE1://��˷� --���  ���������
		sMixerParam.dwLineType = MIXERLINE_TARGETTYPE_UNDEFINED;
		sMixerParam.nControlType = MIXERLINE_COMPONENTTYPE_SRC_LINE;
		sMixerParam.enType = MIXER_OUT;
		break;
	case MIXER_CONTROL_OUTMIC_TYPE0://���������е���˷�
		sMixerParam.dwLineType = MIXERLINE_TARGETTYPE_UNDEFINED;
		sMixerParam.nControlType = MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE;
		sMixerParam.enType = MIXER_OUT;
		break;
	case MIXER_CONTROL_MIXER_TYPE://����������  --����  ����·����
		sMixerParam.dwLineType = MIXERLINE_TARGETTYPE_UNDEFINED;
		sMixerParam.nControlType = MIXERLINE_COMPONENTTYPE_SRC_LINE;
		sMixerParam.enType = MIXER_IN;
		break;
	case MIXER_CONTROL_INMIC_TYPE://��˷�   --����˷�
		sMixerParam.dwLineType = MIXERLINE_TARGETTYPE_WAVEIN;
		sMixerParam.nControlType = MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE;
		sMixerParam.enType = MIXER_IN;
		break;
	case MIXER_CONTROL_SOFT_TYPE://����ϳ���
		sMixerParam.dwLineType = MIXERLINE_TARGETTYPE_MIDIOUT;
		sMixerParam.nControlType = MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER;
		sMixerParam.enType = MIXER_OUT;
		break;
	case MIXER_CONTROL_FRONT_TYPE://ǰ������
		sMixerParam.dwLineType = MIXERLINE_TARGETTYPE_WAVEIN;
		sMixerParam.nControlType = MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE;
		sMixerParam.enType = MIXER_IN;
		break;
	case MIXER_CONTROL_TREE_TYPE://���������� --����  Stereo  Mix
		sMixerParam.dwLineType = MIXERLINE_TARGETTYPE_WAVEOUT;
		sMixerParam.nControlType = MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT;
		sMixerParam.enType = MIXER_OTHER;
		break;
	default:
		sMixerParam.dwLineType = -1;
		sMixerParam.nControlType = -1;
	}
}

//�������� 0 ~ 255 
//����������
bool CMixerManager::SetMixerControlTotalVolume(unsigned int nVolume)
{
	//Win7 Or Vistaϵͳ
	if (GetOsVistaOrWin7()) 
	{
		return g_mixerOther.SetMixerSpeakerVolume(nVolume);
	}
	
	//XP��ϵͳ
	if (!GetMixerControlTotalEnable()) 
		return false;
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	GetMixerLineParam(MIXER_CONTROL_TOTAL_TYPE,sMixerParam); //��ȡ����������
	nTotalVolume = nVolume * 0xffff / 255;
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;
		sSet.stateData.Left.dwValue = sSet.stateData.Right.dwValue = nTotalVolume;
		m_pMixerChannel->UpdateMixerControlState(nGroupId,sSet);
		return true;
	}
	return false;
}

//��ȡ������
bool CMixerManager::GetMixerControlTotalVolume(unsigned int& nVolume)
{
	//Win7 Or Vistaϵͳ
	if (GetOsVistaOrWin7()) 
	{
		return g_mixerOther.GetMixerSpeakerVolume(nVolume);
	}

	if (!GetMixerControlTotalEnable()) 
		return false;
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	GetMixerLineParam(MIXER_CONTROL_TOTAL_TYPE,sMixerParam); //��ȡ����������
	if(m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;	
		m_pMixerChannel->GetMixerControlState(nGroupId,sSet);
		nTotalVolume = sSet.stateData.Left.dwValue;
		nVolume = nTotalVolume *  255/ 0xffff;
		return true;
	}
	return false;
}

//��������������
bool CMixerManager::SetMixerControlTotalMute(bool bEnable)
{
	//Win7 Or Vistaϵͳ
	if (GetOsVistaOrWin7()) 
	{
		return g_mixerOther.SetMixerSpeakerMute(bEnable);
	}

	//XP��ϵͳ
	if (!GetMixerControlTotalEnable()) 
		return false;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Mute;
	GetMixerLineParam(MIXER_CONTROL_TOTAL_TYPE,sMixerParam); 
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;
		sSet.bChecked = bEnable;
		m_pMixerChannel->UpdateMixerControlState(nGroupId,sSet);
		return true;
	}
	return false;
}

//��ȡ��ǰ�������Ƿ����
bool CMixerManager::GetMixerControlTotalEnable()
{
	switch(GetOsType())
	{
	case OsWindowsUnKnown:
	case OsWindowsXP:
	case OsWindowsVista:
	case OsWindows7:
		{
			return true;
		}
		break;
	default:
		return false;
	}
}

//��ȡ�������Ƿ���
bool CMixerManager::GetMixerControlTotalMute(bool& bEnable)
{
	//Win7 Or Vistaϵͳ
	if (GetOsVistaOrWin7()) 
	{
		BOOL bEnabled = FALSE;
		bool bret= g_mixerOther.GetMixerSpeakerMute(bEnabled);
		bEnable = bEnabled;
		return bret;
	}

	//XP��ϵͳ
	if (!GetMixerControlTotalEnable()) 
		return false;
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Mute;
	GetMixerLineParam(MIXER_CONTROL_TOTAL_TYPE,sMixerParam); 
	if(m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;	
		m_pMixerChannel->GetMixerControlState(nGroupId,sSet);
		bEnable = sSet.bChecked;
		return true;
	}
	return false;
}

//���ð���
bool CMixerManager::SetMixerControlWavoutVolume(unsigned int nVolume)
{
	if (!GetMixerControlWavoutEnable())
		return false;
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	GetMixerLineParam(MIXER_CONTROL_WAVOUT_TYPE,sMixerParam); //��ȡ����������
	nTotalVolume = nVolume * 0xffff / 255;
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;
		sSet.stateData.Left.dwValue = sSet.stateData.Right.dwValue = nTotalVolume;
		m_pMixerChannel->UpdateMixerControlState(nGroupId,sSet);
		return true;
	}
	return false;
}

//��ȡ��������
bool CMixerManager::GetMixerControlWavoutVolume(unsigned int& nVolume)
{
	if (!GetMixerControlWavoutEnable())
		return false;
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	GetMixerLineParam(MIXER_CONTROL_WAVOUT_TYPE,sMixerParam); //��ȡ����������
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;	
		m_pMixerChannel->GetMixerControlState(nGroupId,sSet);
		nTotalVolume = sSet.stateData.Left.dwValue;
		nVolume = nTotalVolume *  255/ 0xffff;
		return true;
	}
	return false;
}


//���ð�������
bool CMixerManager::SetMixerControlWavoutMute(bool bEnable)
{
	if (!GetMixerControlWavoutEnable())
		return false;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Mute;
	GetMixerLineParam(MIXER_CONTROL_WAVOUT_TYPE,sMixerParam); 
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;
		sSet.bChecked = bEnable;
		m_pMixerChannel->UpdateMixerControlState(nGroupId,sSet);
		return true;
	}
	return false;
}

//��ȡ�����Ƿ����
bool CMixerManager::GetMixerControlWavoutEnable()
{
	switch(GetOsType())
	{
	case OsWindowsUnKnown:
	case OsWindowsXP:
		{
			return true;
		}
		break;
	case OsWindowsVista:
	case OsWindows7:
		{
			return false;
		}
		break;
	default:
		return false;
	}	
}

//��ȡ�����Ƿ���
bool CMixerManager::GetMixerControlWavoutMute(bool& bEnable)
{
	if (!GetMixerControlWavoutEnable())
		return false;
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Mute;
	GetMixerLineParam(MIXER_CONTROL_WAVOUT_TYPE,sMixerParam); 
	if(m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;	
		m_pMixerChannel->GetMixerControlState(nGroupId,sSet);
		bEnable = sSet.bChecked;
		return true;
	}
	return false;
}


//�������������е���˷�
bool CMixerManager::SetMixerControlOutmicVolume(unsigned int nVolume)
{
	if (!GetMixerControlOutmicEnable())
		return false;
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	sMixerParam.enType = MIXER_OUT;

	std::wstring str = _T("��˷�");
	std::wstring str1 = _T("Microphone");
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,str,sMixerParam) == -1 && 
		m_pMixerChannel->GetMixerGroupId(nGroupId,str1,sMixerParam) == -1)//���ݡ���˷硱����
	{
		GetMixerLineParam(MIXER_CONTROL_OUTMIC_TYPE0,sMixerParam); //��·���Ʋ���
		if(m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam) == -1)
		{
			GetMixerLineParam(MIXER_CONTROL_OUTMIC_TYPE1,sMixerParam); //��·�������
			if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam) == -1)
			{
				return false;
			}
		}	
	}
	strucChannelSet sSet;
	nTotalVolume = nVolume * 0xffff / 255;
	sSet.stateData.Left.dwValue = sSet.stateData.Right.dwValue = nTotalVolume;
	m_pMixerChannel->UpdateMixerControlState(nGroupId,sSet);
	return true;
}

//��ȡ���������е���˷��Ƿ����
bool CMixerManager::GetMixerControlOutmicEnable()
{
	switch(GetOsType())
	{
	case OsWindowsUnKnown:
	case OsWindowsXP:
		{
			return true;
		}
		break;
	case OsWindowsVista:
	case OsWindows7:
		{
			return false;
		}
		break;
	default:
		return false;
	}	
}

//��ȡ���������е���˷�����
bool CMixerManager::GetMixerControlOutmicVolume(unsigned int& nVolume)
{
	if (!GetMixerControlOutmicEnable())
		return false;
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	sMixerParam.enType = MIXER_OUT;

	std::wstring str = _T("��˷�");
	std::wstring str1 = _T("Microphone");
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,str,sMixerParam) == -1 && 
		m_pMixerChannel->GetMixerGroupId(nGroupId,str1,sMixerParam) == -1)//���ݡ���˷硱����
	{
		GetMixerLineParam(MIXER_CONTROL_OUTMIC_TYPE0,sMixerParam); //��·���Ʋ���
		if(m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam) == -1)
		{
			GetMixerLineParam(MIXER_CONTROL_OUTMIC_TYPE1,sMixerParam); //��·�������
			if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam) == -1)
			{
				return false;
			}
		}	
	}

	strucChannelSet sSet;	
	m_pMixerChannel->GetMixerControlState(nGroupId,sSet);
	nTotalVolume = sSet.stateData.Left.dwValue;
	nVolume = nTotalVolume *  255/  0xffff;
	return true;
}

//�������������е���˷�ľ���
bool CMixerManager::SetMixerControlOutmicMute(bool bEnable)
{
	if (!GetMixerControlOutmicEnable())
		return false;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Mute;
	sMixerParam.enType = MIXER_OUT;

	std::wstring str = _T("��˷�");
	std::wstring str1 = _T("Microphone");
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,str,sMixerParam) == -1 && 
		m_pMixerChannel->GetMixerGroupId(nGroupId,str1,sMixerParam) == -1)//���ݡ���˷硱����
	{
		GetMixerLineParam(MIXER_CONTROL_OUTMIC_TYPE0,sMixerParam); //��·���Ʋ���
		if(m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam) == -1)
		{
			GetMixerLineParam(MIXER_CONTROL_OUTMIC_TYPE1,sMixerParam); //��·�������
			if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam) == -1)
			{
				return false;
			}
		}	
	}

	strucChannelSet sSet;
	sSet.bChecked = bEnable;
	m_pMixerChannel->UpdateMixerControlState(nGroupId,sSet);
	return true;
}

//��ȡ���������е���˷�ľ���
bool CMixerManager::GetMixerControlOutmicMute(bool& bEnable)
{
	if (!GetMixerControlOutmicEnable())
		return false;
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Mute;
	sMixerParam.enType = MIXER_OUT;

	std::wstring str = _T("��˷�");
	std::wstring str1 = _T("Microphone");
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,str,sMixerParam) == -1 && 
		m_pMixerChannel->GetMixerGroupId(nGroupId,str1,sMixerParam) == -1)//���ݡ���˷硱����
	{
		GetMixerLineParam(MIXER_CONTROL_OUTMIC_TYPE0,sMixerParam); //��·���Ʋ���
		if(m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam) == -1)
		{
			GetMixerLineParam(MIXER_CONTROL_OUTMIC_TYPE1,sMixerParam); //��·�������
			if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam) == -1)
			{
				return false;
			}
		}	
	}

	strucChannelSet sSet;	
	m_pMixerChannel->GetMixerControlState(nGroupId,sSet);
	bEnable = sSet.bChecked;
	return true;
}

//¼������0~255
//����������
bool CMixerManager::SetMixerControlMixerVolume(unsigned int nVolume)
{
	if (!GetMixerControlMixerEnable())
		return false;
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	sMixerParam.enType = MIXER_OTHER;

	std::wstring str = _T("������");
	std::wstring str1 = _T("Stereo");
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,str,sMixerParam) == -1 && 
		m_pMixerChannel->GetMixerGroupId(nGroupId,str1,sMixerParam) == -1)//���ݡ���˷硱����
	{
		GetMixerLineParam(MIXER_CONTROL_MIXER_TYPE,sMixerParam); //��ȡ����������
		if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)==-1)
		{
			return false;
		}
	}

	strucChannelSet sSet;
	nTotalVolume = nVolume * 0xffff / 255;
	sSet.stateData.Left.dwValue = sSet.stateData.Right.dwValue = nTotalVolume;
	m_pMixerChannel->UpdateMixerControlState(nGroupId,sSet);
	return true;
}

//��ȡ��������������
bool CMixerManager::GetMixerControlMixerVolume(unsigned int& nVolume)
{
	if (!GetMixerControlMixerEnable())
		return false;
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	sMixerParam.enType = MIXER_OTHER;

	std::wstring str = _T("������");
	std::wstring str1 = _T("Stereo");
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,str,sMixerParam) == -1 && 
		m_pMixerChannel->GetMixerGroupId(nGroupId,str1,sMixerParam) == -1)//���ݡ���˷硱����
	{
		GetMixerLineParam(MIXER_CONTROL_MIXER_TYPE,sMixerParam); //��ȡ����������
		if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)==-1)
		{
			return false;
		}
	}
	strucChannelSet sSet;	
	m_pMixerChannel->GetMixerControlState(nGroupId,sSet);
	nTotalVolume = sSet.stateData.Left.dwValue;
	nVolume = nTotalVolume *  255/ 0xffff;
	return true;

}

//��ȡ�����������Ƿ����
bool CMixerManager::GetMixerControlMixerEnable()
{
	switch(GetOsType())
	{
	case OsWindowsUnKnown:
	case OsWindowsXP:
		{
			return true;
		}
		break;
	case OsWindowsVista:
	case OsWindows7:
		{
			return false;
		}
		break;
	default:
		return false;
	}	
}

//��������������
bool CMixerManager::SetMixerControlMixerMute(bool bEnable)
{
	if (!GetMixerControlMixerEnable())
		return false;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	sMixerParam.enType = MIXER_OTHER;

	std::wstring str = _T("������");
	std::wstring str1 = _T("Stereo");
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,str,sMixerParam) == -1 && 
		m_pMixerChannel->GetMixerGroupId(nGroupId,str1,sMixerParam) == -1)//���ݡ���˷硱����
	{
		GetMixerLineParam(MIXER_CONTROL_MIXER_TYPE,sMixerParam); //��ȡ����������
		if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)==-1)
		{
			return false;
		}
	}
	
	if (m_pMixerChannel->IsMixerControlSelState(nGroupId))
	{
		strucChannelSet sSet;
		sSet.bChecked = bEnable;
		m_pMixerChannel->SetMixerControlSelState(nGroupId,sSet);
	}
	else
	{
		sMixerParam.enctrlType = Mute;
		if (m_pMixerChannel->GetMixerGroupId(nGroupId,str,sMixerParam) == -1 && 
			m_pMixerChannel->GetMixerGroupId(nGroupId,str1,sMixerParam) == -1)//���ݡ���˷硱����
		{
			GetMixerLineParam(MIXER_CONTROL_MIXER_TYPE,sMixerParam); //��ȡ����������
			if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)==-1)
			{
				return false;
			}
		}

		strucChannelSet sSet;
		sSet.bChecked = bEnable;
		m_pMixerChannel->UpdateMixerControlState(nGroupId,sSet);
	}
	return true;
}

//��ȡ��������Ӧ�Ƿ���
bool CMixerManager::GetMixerControlMixerMute(bool& bEnable)
{
	if (!GetMixerControlMixerEnable())
		return false;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	sMixerParam.enType = MIXER_OTHER;

	std::wstring str = _T("������");
	std::wstring str1 = _T("Stereo");
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,str,sMixerParam) == -1 && 
		m_pMixerChannel->GetMixerGroupId(nGroupId,str1,sMixerParam) == -1)//���ݡ���˷硱����
	{
		GetMixerLineParam(MIXER_CONTROL_MIXER_TYPE,sMixerParam); //��ȡ����������
		if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)==-1)
		{
			return false;
		}
	}
	
	if (m_pMixerChannel->IsMixerControlSelState(nGroupId))
	{
		strucChannelSet sSet;
		m_pMixerChannel->GetMixerControlSelState(nGroupId,sSet);
		bEnable = sSet.bChecked;
	}
	else
	{
		sMixerParam.enctrlType = Mute;
		if (m_pMixerChannel->GetMixerGroupId(nGroupId,str,sMixerParam) == -1 && 
			m_pMixerChannel->GetMixerGroupId(nGroupId,str1,sMixerParam) == -1)//���ݡ���˷硱����
		{
			GetMixerLineParam(MIXER_CONTROL_MIXER_TYPE,sMixerParam); //��ȡ����������
			if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)==-1)
			{
				return false;
			}
		}

		strucChannelSet sSet;	
		m_pMixerChannel->GetMixerControlState(nGroupId,sSet);
		bEnable = sSet.bChecked;
	}
	return true;
}

//�жϿ������� ѡ�� ���� ����״̬
bool CMixerManager::IsMixerControlSelect(bool& bSel)
{
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	sMixerParam.enType = MIXER_OTHER;

	std::wstring str = _T("������");
	std::wstring str1 = _T("Stereo");
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,str,sMixerParam) == -1 && 
		m_pMixerChannel->GetMixerGroupId(nGroupId,str1,sMixerParam) == -1)//���ݡ���˷硱����
	{
		GetMixerLineParam(MIXER_CONTROL_MIXER_TYPE,sMixerParam); //��ȡ����������
		if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)==-1)
		{
			bSel = false;
			return false;
		}
	}

	bSel = m_pMixerChannel->IsMixerControlSelState(nGroupId);
	return true;
}



//���ú���˷羲��
bool CMixerManager::SetMixerControlInmicMute(bool bEnable)
{
	//Win7 Or Vistaϵͳ
	if (GetOsVistaOrWin7()) 
	{
		return g_mixerOther.SetMixerMicMute(bEnable);
	}

	if (!GetMixerControlInmicEnable())
		return false;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	GetMixerLineParam(MIXER_CONTROL_INMIC_TYPE,sMixerParam); 
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)==-1)
	{
		return false;
	}

	strucChannelSet sSet;
	sSet.bChecked = bEnable;
	if (m_pMixerChannel->IsMixerControlSelState(nGroupId))
	{
		m_pMixerChannel->SetMixerControlSelState(nGroupId,sSet);
	}
	else
	{
		m_pMixerChannel->UpdateMixerControlState(nGroupId,sSet);
	}
	return true;
}

//��ȡ¼�������е���˷��Ƿ���
bool CMixerManager::GetMixerControlInmicMute(bool& bEnable)
{
	//Win7 Or Vistaϵͳ
	if (GetOsVistaOrWin7()) 
	{
		BOOL bEnabled = FALSE;
		bool bRet = g_mixerOther.GetMixerMicMute(bEnabled);
		bEnable = bEnabled;
		return bRet;
	}

	if (!GetMixerControlInmicEnable())
		return false;
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	GetMixerLineParam(MIXER_CONTROL_INMIC_TYPE,sMixerParam); 
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)==-1)
	{
		return false;
	}
	
	strucChannelSet sSet;	
	if (m_pMixerChannel->IsMixerControlSelState(nGroupId))
	{
		m_pMixerChannel->GetMixerControlSelState(nGroupId,sSet);
	}
	else
	{
		m_pMixerChannel->GetMixerControlState(nGroupId,sSet);
	}
	bEnable = sSet.bChecked;
	return true;
}

//¼�������е���˷�
bool CMixerManager::SetMixerControlInmicVolume(unsigned int nVolume)
{
	//Win7 Or Vistaϵͳ
	if (GetOsVistaOrWin7()) 
	{
		return g_mixerOther.SetMixerMicVolume(nVolume);
	}

	if (!GetMixerControlInmicEnable())
		return false;
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	GetMixerLineParam(MIXER_CONTROL_INMIC_TYPE,sMixerParam); //��ȡ����������
	nTotalVolume = nVolume * 65535 / 255;
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;
		sSet.stateData.Left.dwValue = sSet.stateData.Right.dwValue = nTotalVolume;
		m_pMixerChannel->UpdateMixerControlState(nGroupId,sSet);
		return true;
	}
	return false;
}

//��ȡ¼�������е���˷�����
bool CMixerManager::GetMixerControlInmicVolume(unsigned int& nVolume)
{
	//Win7 Or Vistaϵͳ
	if (GetOsVistaOrWin7()) 
	{
		return g_mixerOther.GetMixerMicVolume(nVolume);
	}

	if (!GetMixerControlInmicEnable())
		return false;
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Volume;
	GetMixerLineParam(MIXER_CONTROL_INMIC_TYPE,sMixerParam); //��ȡ����������
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;	
		m_pMixerChannel->GetMixerControlState(nGroupId,sSet);
		nTotalVolume = sSet.stateData.Left.dwValue;
		nVolume = nTotalVolume *  255/ 65535;
		return true;
	}
	return false;
}

//��ȡ��Ƶ�����豸��������С
bool CMixerManager::GetMixerControlInmicEnable()
{
	switch(GetOsType())
	{
	case OsWindowsUnKnown:
	case OsWindowsXP:
		{
			return true;
		}
		break;
	case OsWindowsVista:
	case OsWindows7:
		{
			return false;
		}
		break;
	default:
		return false;
	}	
}

//������Ƶ�����豸������С
bool CMixerManager::SetMixerControlWavInVolume(unsigned int nVolume)
{
	//Win7 Or Vistaϵͳ
	if (GetOsVistaOrWin7()) 
	{
		return g_mixerOther.SetMixerMicBoostVolume(nVolume);
	}
	if (!GetMixerControlWavInEnable())
		return false;
	unsigned int nGroupId = -1;
	unsigned int nTotalVolume = 0;
	if (m_pMixerChannel->GetMixerControlSelGroupId(nGroupId)!=-1)
	{
		strucChannelSet sSet;
		nTotalVolume = nVolume * 0xffff / 255;
		sSet.stateData.Left.dwValue = sSet.stateData.Right.dwValue = nTotalVolume;
		m_pMixerChannel->UpdateMixerControlState(nGroupId,sSet);
		return true;
	}
	return false;
}

//������Ƶ�����豸������С
bool CMixerManager::GetMixerControlWavInVolume(unsigned int& nVolume)
{
	//Win7 Or Vistaϵͳ
	if (GetOsVistaOrWin7()) 
	{
		return g_mixerOther.GetMixerMicBoostVolume(nVolume);
	}
	if (!GetMixerControlWavInEnable())
		return false;
	unsigned int nGroupId = -1;
	unsigned int nTotalVolume = 0;
	if (m_pMixerChannel->GetMixerControlSelGroupId(nGroupId)!=-1)
	{
		strucChannelSet sSet;	
		m_pMixerChannel->GetMixerControlState(nGroupId,sSet);
		nTotalVolume = sSet.stateData.Left.dwValue;
		nVolume = nTotalVolume *  255/ 0xffff;
		return true;
	}
	return false;
}

//��ȡ������˷�������С�Ƿ����
bool CMixerManager::GetMixerControlWavInEnable()
{
	switch(GetOsType())
	{
	case OsWindowsUnKnown:
	case OsWindowsXP:
	case OsWindowsVista:
	case OsWindows7:
		{
			return true;
		}
		break;
	default:
		return false;
	}
}

//��������ϳ������� //MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER
bool CMixerManager::SetMixerControlSoftMute(bool bEnable)
{
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Mute;
	GetMixerLineParam(MIXER_CONTROL_SOFT_TYPE,sMixerParam); 
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;
		sSet.bChecked = bEnable;
		m_pMixerChannel->UpdateMixerControlState(nGroupId,sSet);
		return true;
	}
	return false;
}

//��ȡ����ϳ����Ƿ���
bool CMixerManager::GetMixerControlSoftMute(bool& bEnable)
{
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Mute;
	GetMixerLineParam(MIXER_CONTROL_SOFT_TYPE,sMixerParam); 
	if(m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;	
		m_pMixerChannel->GetMixerControlState(nGroupId,sSet);
		bEnable = sSet.bChecked;
		return true;
	}
	return false;
}

//����ǰ�����뾲��
bool CMixerManager::SetMixerControlFrontMute(bool bEnable)
{
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Mute;
	GetMixerLineParam(MIXER_CONTROL_FRONT_TYPE,sMixerParam); 
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;
		sSet.bChecked = bEnable;
		m_pMixerChannel->UpdateMixerControlState(nGroupId,sSet);
		return true;
	}
	return false;
}

//��ȡǰ�������Ƿ���
bool CMixerManager::GetMixerControlFontMute(bool& bEnable)
{
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Mute;
	GetMixerLineParam(MIXER_CONTROL_FRONT_TYPE,sMixerParam); 
	if(m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;	
		m_pMixerChannel->GetMixerControlState(nGroupId,sSet);
		bEnable = sSet.bChecked;
		return true;
	}
	return false;
}

//������������������
bool CMixerManager::SetMixerControlTreeMute(bool bEnable)
{
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Mute;
	GetMixerLineParam(MIXER_CONTROL_TREE_TYPE,sMixerParam); 
	if (m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;
		sSet.bChecked = bEnable;
		m_pMixerChannel->UpdateMixerControlState(nGroupId,sSet);
		return true;
	}
	return false;
}

//��ȡ�����������Ƿ���
bool CMixerManager::GetMixerControlTreeMute(bool& bEnable)
{
	unsigned int nTotalVolume = 0;
	unsigned int nGroupId = -1;
	StrucMixerParam sMixerParam;
	sMixerParam.enctrlType = Mute;
	GetMixerLineParam(MIXER_CONTROL_TREE_TYPE,sMixerParam); 
	if(m_pMixerChannel->GetMixerGroupId(nGroupId,sMixerParam)>0)
	{
		strucChannelSet sSet;	
		m_pMixerChannel->GetMixerControlState(nGroupId,sSet);
		bEnable = sSet.bChecked;
		return true;
	}
	return false;
}

//���ó���
bool CMixerManager::SetMixerControlSingMode()
{
	bool bSel = FALSE;
	if (IsMixerControlSelect(bSel))
	{
		if (bSel) //��ǰϵͳ֧�ֻ���ģʽ
		{
			//��������������ѡ��
			if (!SetMixerControlMixerMute(TRUE))
			{
				return FALSE;
			}
			//���ò��� ������
			if (!SetMixerControlWavoutMute(FALSE))
			{
				return FALSE;
			}
			//������˷粻����
			if (!SetMixerControlOutmicMute(FALSE))
			{
				return FALSE;
			}

		}
		else
		{
			//��������������������
			if (!SetMixerControlMixerMute(FALSE))
			{
				return FALSE;
			}
			//���ò��� ������
			if (!SetMixerControlWavoutMute(FALSE))
			{
				return FALSE;
			}
			//������˷粻����
			if (!SetMixerControlOutmicMute(FALSE))
			{
				return FALSE;
			}
		}
		return true;
	}
	return false;
}

//��ȡ�Ƿ��ڳ���ģʽ
bool CMixerManager::GetMixerControlSingMode(bool& bEnable)
{
	bool bSel = FALSE;
	if (IsMixerControlSelect(bSel))
	{
		if (bSel) //֧�ֻ���ģʽ
		{
			bool bEnabled = false;
			//��ȡ�����������Ƿ�ѡ��
			if (!GetMixerControlMixerMute(bEnabled))
			{
				return FALSE;
			}
			if(!bEnabled) //ѡ��
			{
				bEnable = FALSE;
				return TRUE;
			}
			//���ò��� ������
			if (!GetMixerControlWavoutMute(bEnabled))
			{
				return FALSE;
			}
			if(bEnabled)//������
			{
				bEnable = FALSE;
				return TRUE;
			}
			//������˷粻����
			if (!GetMixerControlOutmicMute(bEnabled))
			{
				return FALSE;
			}
			if(bEnabled)//������
			{
				bEnable = FALSE;
				return TRUE;
			}
			bEnable = TRUE;

		}
		else //��֧�ֻ���ģʽ
		{
			bool bEnabled = false;
			//��ȡ�����������Ƿ�ѡ��
			if (!GetMixerControlMixerMute(bEnabled))
			{
				return FALSE;
			}
			if(bEnabled) //������
			{
				bEnable = FALSE;
				return TRUE;
			}
			//���ò��� ������
			if (!GetMixerControlWavoutMute(bEnabled))
			{
				return FALSE;
			}
			if(bEnabled)//������
			{
				bEnable = FALSE;
				return TRUE;
			}
			//������˷粻����
			if (!GetMixerControlOutmicMute(bEnabled))
			{
				return FALSE;
			}
			if(bEnabled)//������
			{
				bEnable = FALSE;
				return TRUE;
			}
			bEnable = TRUE;
		}
		return TRUE;
	}
	return false;
}

//������������
bool CMixerManager::SetMixerControlChatMode()
{
	bool bSel = FALSE;
	if (IsMixerControlSelect(bSel))
	{
		if (bSel) //��ǰϵͳ֧�ֻ���ģʽ
		{
			//��������������ѡ��
			if (!SetMixerControlMixerMute(TRUE))
			{
				return FALSE;
			}
			//���ò��� ����
			if (!SetMixerControlWavoutMute(TRUE))
			{
				return FALSE;
			}
			//������˷粻����
			if (!SetMixerControlOutmicMute(FALSE))
			{
				return FALSE;
			}

		}
		else
		{
			//��������������������
			if (!SetMixerControlMixerMute(FALSE))
			{
				return FALSE;
			}
			//���ò��� ����
			if (!SetMixerControlWavoutMute(TRUE))
			{
				return FALSE;
			}
			//������˷粻����
			if (!SetMixerControlOutmicMute(FALSE))
			{
				return FALSE;
			}
		}
		return true;
	}
	return false;
}

//��ȡ�Ƿ���������ģʽ
bool CMixerManager::GetMixerControlChatMode(bool& bEnable)
{
	bool bSel = FALSE;
	if (IsMixerControlSelect(bSel))
	{
		if (bSel) //֧�ֻ���ģʽ
		{
			bool bEnabled = false;
			//��ȡ�����������Ƿ�ѡ��
			if (!GetMixerControlMixerMute(bEnabled))
			{
				return FALSE;
			}
			if(!bEnabled) //ѡ��
			{
				bEnable = FALSE;
				return TRUE;
			}
			//���ò��� ������
			if (!GetMixerControlWavoutMute(bEnabled))
			{
				return FALSE;
			}
			if(!bEnabled)//����
			{
				bEnable = FALSE;
				return TRUE;
			}
			//������˷粻����
			if (!GetMixerControlOutmicMute(bEnabled))
			{
				return FALSE;
			}
			if(bEnabled)//������
			{
				bEnable = FALSE;
				return TRUE;
			}
			bEnable = TRUE;

		}
		else //��֧�ֻ���ģʽ
		{
			bool bEnabled = false;
			//��ȡ�����������Ƿ�ѡ��
			if (!GetMixerControlMixerMute(bEnabled))
			{
				return FALSE;
			}
			if(bEnabled) //������
			{
				bEnable = FALSE;
				return TRUE;
			}
			//���ò��� ������
			if (!GetMixerControlWavoutMute(bEnabled))
			{
				return FALSE;
			}
			if(!bEnabled)//����
			{
				bEnable = FALSE;
				return TRUE;
			}
			//������˷粻����
			if (!GetMixerControlOutmicMute(bEnabled))
			{
				return FALSE;
			}
			if(bEnabled)//������
			{
				bEnable = FALSE;
				return TRUE;
			}
			bEnable = TRUE;
		}
		return TRUE;
	}
	return false;
}

//�����ϷŸ�
bool CMixerManager::SetMixerControlPlayMode()
{
	bool bSel = FALSE;
	if (IsMixerControlSelect(bSel))
	{
		if (bSel) //��ǰϵͳ֧�ֻ���ģʽ
		{
			//��������������ѡ��
			if (!SetMixerControlMixerMute(TRUE))
			{
				return FALSE;
			}
			//���ò��� ������
			if (!SetMixerControlWavoutMute(FALSE))
			{
				return FALSE;
			}
			//������˷羲��
			if (!SetMixerControlOutmicMute(TRUE))
			{
				return FALSE;
			}

		}
		else
		{
			//��������������������
			if (!SetMixerControlMixerMute(FALSE))
			{
				return FALSE;
			}
			//���ò��� ������
			if (!SetMixerControlWavoutMute(FALSE))
			{
				return FALSE;
			}
			//������˷粻����
			if (!SetMixerControlOutmicMute(TRUE))
			{
				return FALSE;
			}
		}
		return true;
	}
	return false;
}

//��ȡ�Ƿ������ϷŸ�ģʽ
bool CMixerManager::GetMixerControlPlayMode(bool& bEnable)
{
	bool bSel = FALSE;
	if (IsMixerControlSelect(bSel))
	{
		if (bSel) //֧�ֻ���ģʽ
		{
			bool bEnabled = false;
			//��ȡ�����������Ƿ�ѡ��
			if (!GetMixerControlMixerMute(bEnabled))
			{
				return FALSE;
			}
			if(!bEnabled) //ѡ��
			{
				bEnable = FALSE;
				return TRUE;
			}
			//���ò��� ������
			if (!GetMixerControlWavoutMute(bEnabled))
			{
				return FALSE;
			}
			if(bEnabled)//������
			{
				bEnable = FALSE;
				return TRUE;
			}
			//������˷粻����
			if (!GetMixerControlOutmicMute(bEnabled))
			{
				return FALSE;
			}
			if(!bEnabled)//����
			{
				bEnable = FALSE;
				return TRUE;
			}
			bEnable = TRUE;

		}
		else //��֧�ֻ���ģʽ
		{
			bool bEnabled = false;
			//��ȡ�����������Ƿ�ѡ��
			if (!GetMixerControlMixerMute(bEnabled))
			{
				return FALSE;
			}
			if(bEnabled) //������
			{
				bEnable = FALSE;
				return TRUE;
			}
			//���ò��� ������
			if (!GetMixerControlWavoutMute(bEnabled))
			{
				return FALSE;
			}
			if(bEnabled)//������
			{
				bEnable = FALSE;
				return TRUE;
			}
			//������˷粻����
			if (!GetMixerControlOutmicMute(bEnabled))
			{
				return FALSE;
			}
			if(!bEnabled)//����
			{
				bEnable = FALSE;
				return TRUE;
			}
			bEnable = TRUE;
		}
		return TRUE;
	}
	return false;
}

//��ȡ��ǰ������ģʽ
bool CMixerManager::GetMixerControlMode(EnMixerControlMode& eMode)
{
	eMode = MIXER_CONTROL_OTHER;
	bool bEnable = FALSE;
	if (!GetMixerControlSingMode(bEnable))//�ж��Ƿ񳪸�ģʽ
	{
		return false;
	}
	if (bEnable)
	{
		eMode = MIXER_CONTROL_SING;
		return true;
	}
	if (!GetMixerControlChatMode(bEnable))//�ж��Ƿ�����ģʽ
	{
		return false;
	}
	if (bEnable)
	{
		eMode = MIXER_CONTROL_CHAT;
		return true;
	}
	if (!GetMixerControlPlayMode(bEnable))//�ж��Ƿ�Ÿ�ģʽ
	{
		return false;
	}
	if (bEnable)
	{
		eMode = MIXER_CONTROL_PLAY;
		return true;
	}
	return true;
}

//��ȡ����ϵͳ����
EnOsType CMixerManager::GetOsType()
{
	OSVERSIONINFO osInfo;
	memset(&osInfo, 0, sizeof(OSVERSIONINFO));
	osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	EnOsType eType = OsWindowsUnKnown;
	//��ȡ�汾����
	if(::GetVersionEx(&osInfo))
	{
		Trace("CMixerManager::GetOsType  dwMajorVersion= %d, dwMinorVersion = %d, dwBuildNumber = %d \n", osInfo.dwMajorVersion, osInfo.dwMinorVersion, osInfo.dwBuildNumber);

		if(osInfo.dwMajorVersion <= 5)//XP or early
		{
			eType = OsWindowsXP;
		}
		else
		{
			if(osInfo.dwMinorVersion == 0)
			{
				eType = OsWindowsVista;
			}
			else
			{
				eType = OsWindows7;
			}
		}

	}
	return eType;
}

bool CMixerManager::GetOsVistaOrWin7()
{
	switch(GetOsType())
	{
	case OsWindowsVista:
	case OsWindows7:
		{
			return true;
		}
		break;
	default:
		return false;
	}
}