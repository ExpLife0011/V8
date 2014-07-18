#pragma once
#include <MMSystem.h>
#include "Mixer.h"
#include "MixerDefine.h"
#include <string>

class CMixerChannel
{
public:
	CMixerChannel(void);
	~CMixerChannel(void);

public:
	//��ʼ������ͨ��
	void Init(HWND hWnd);
// 	//��ʾ��������·�� nIDΪCCombox��ID
// 	void ShowMixerCaps(CComboBox* pMixerCombo);
// 	//��ʾָ����·�ϵĿ�������Ϣ
// 	void ShowMixerLineControl(unsigned int nMixerLine,CComboBox* pMixerCombo);
	//��ȡgroupId
	int GetMixerGroupId(unsigned int& groupId, const StrucMixerParam& sMixerParam);
	//���û�����Blance Volume Mute
	int UpdateMixerControlState( unsigned int groupId,const strucChannelSet& sSet) ;
	//��ȡ������Blance Volume Mute
	int GetMixerControlState( unsigned int groupId,strucChannelSet& sSet );
	//��ȡgroupId �������ֹؼ���
	int GetMixerGroupId(unsigned int& groupId,const std::wstring& str,const StrucMixerParam& sMixerParam);
	//���û������Ƿ�Ϊѡ��ѡ��״̬
	int SetMixerControlSelState(unsigned int groupId,const strucChannelSet& sSet);
	//��ȡ�������Ƿ�ѡ��ѡ��״̬
	int GetMixerControlSelState(unsigned int groupId,strucChannelSet& sSet);
	//�ж�ָ����groupId�Ƿ�Ϊѡ�� TRUE Ϊѡ��
	bool IsMixerControlSelState(unsigned int groupId);
	//��ȡ��Ƶ�����豸��ѡ�е��豸
	int GetMixerControlSelGroupId(unsigned int& groupId);

protected:
	//��ȡ��·�����ַ���
	/*
	#define MIXERLINE_TARGETTYPE_UNDEFINED      0
	#define MIXERLINE_TARGETTYPE_WAVEOUT        1
	#define MIXERLINE_TARGETTYPE_WAVEIN         2
	#define MIXERLINE_TARGETTYPE_MIDIOUT        3
	#define MIXERLINE_TARGETTYPE_MIDIIN         4
	#define MIXERLINE_TARGETTYPE_AUX            5
	*/
	void GetLineTargetTypeStr( DWORD dwType, std::string& strType ) ;
protected:
	HMIXER	mhMixer; //���������
	unsigned int mMixerCount;//��������Ŀ
	bool bMixerInit;//�������Ƿ��ʼ��
	CMixer* mpCMixer ;//������
	HWND hMixerWnd;//��ǰ��������Ϣ֪ͨ�Ĵ��ھ��

	unsigned int nextResourceID ;//��ԴID��ʶ��

	//�洢���� ����������
	struct strucChannelData {
		struct sChannelData stateData ;
		int nChannels ;
	};
	
	/*  mcomponentType
	#define MIXERLINE_COMPONENTTYPE_DST_FIRST       0x00000000L
	#define MIXERLINE_COMPONENTTYPE_DST_UNDEFINED   (MIXERLINE_COMPONENTTYPE_DST_FIRST + 0)
	#define MIXERLINE_COMPONENTTYPE_DST_DIGITAL     (MIXERLINE_COMPONENTTYPE_DST_FIRST + 1)
	#define MIXERLINE_COMPONENTTYPE_DST_LINE        (MIXERLINE_COMPONENTTYPE_DST_FIRST + 2)
	#define MIXERLINE_COMPONENTTYPE_DST_MONITOR     (MIXERLINE_COMPONENTTYPE_DST_FIRST + 3)
	#define MIXERLINE_COMPONENTTYPE_DST_SPEAKERS    (MIXERLINE_COMPONENTTYPE_DST_FIRST + 4)
	#define MIXERLINE_COMPONENTTYPE_DST_HEADPHONES  (MIXERLINE_COMPONENTTYPE_DST_FIRST + 5)
	#define MIXERLINE_COMPONENTTYPE_DST_TELEPHONE   (MIXERLINE_COMPONENTTYPE_DST_FIRST + 6)
	#define MIXERLINE_COMPONENTTYPE_DST_WAVEIN      (MIXERLINE_COMPONENTTYPE_DST_FIRST + 7)
	#define MIXERLINE_COMPONENTTYPE_DST_VOICEIN     (MIXERLINE_COMPONENTTYPE_DST_FIRST + 8)
	#define MIXERLINE_COMPONENTTYPE_DST_LAST        (MIXERLINE_COMPONENTTYPE_DST_FIRST + 8)

	#define MIXERLINE_COMPONENTTYPE_SRC_FIRST       0x00001000L
	#define MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED   (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 0)
	#define MIXERLINE_COMPONENTTYPE_SRC_DIGITAL     (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 1)
	#define MIXERLINE_COMPONENTTYPE_SRC_LINE        (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 2)
	#define MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE  (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 3)
	#define MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 4)
	#define MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 5)
	#define MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE   (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 6)
	#define MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER   (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 7)
	#define MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT     (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 8)
	#define MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY   (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 9)
	#define MIXERLINE_COMPONENTTYPE_SRC_ANALOG      (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 10)
	#define MIXERLINE_COMPONENTTYPE_SRC_LAST        (MIXERLINE_COMPONENTTYPE_SRC_FIRST + 10)
	*/
	//�������ƽڵ���Ϣ
	struct strucCtrlUT {
		DWORD dwMixerCtrlID ;
		DWORD   dwType;                 /* MIXERLINE_TARGETTYPE_xxxx */
		DWORD   dwDeviceID;             /* target device ID of device type */
		DWORD   cMultipleItems;
		DWORD   dwLineId;
		unsigned int groupIndex ;
		unsigned int mixerIndex;
		unsigned int lineIndex;
		unsigned int ascIndex;//˳��
		unsigned int desIndex;//����
		unsigned int mcomponentType;
		unsigned int connIndex;
		unsigned int controlIndex;
		enCtrlType	 ctrlType ;
		enMuteType   muteType;
		strucChannelData sChannelData;
		WCHAR szName[MIXER_LONG_NAME_CHARS];
	} ;
	
	//�洢�������ƽڵ���Ϣ
	strucCtrlUT* mpCtrlUT ;
	//��ǰ�������ƽڵ�����
	unsigned int nCtrlUTIndex ;
	//�������ƽڵ���Ŀ
	unsigned int nCtrlUTCount ;
};
