#pragma once
#include "MixerDefine.h"
#include <mmsystem.h>

class CMixerLine;

class CMixer
{
public:
	CMixer(void);
	~CMixer(void);
	
	//�������
	enum HandleTypes {
		h_MIDI_IN  = MIXER_OBJECTF_HMIDIIN, 	
		h_MIDI_OUT = MIXER_OBJECTF_HMIDIOUT, 	
		h_Wave_IN  = MIXER_OBJECTF_HWAVEIN, 	
		h_Wave_OUT = MIXER_OBJECTF_HWAVEOUT 	 
	} ;
	
	//�豸����
	enum DeviceTypes {
		Aux      = MIXER_OBJECTF_AUX, 		
		MIDI_IN  = MIXER_OBJECTF_MIDIIN, 	
		MIDI_OUT = MIXER_OBJECTF_MIDIOUT, 	
		Wave_IN  = MIXER_OBJECTF_WAVEIN, 	
		Wave_OUT = MIXER_OBJECTF_WAVEOUT 
	} ;
	
	//��ʼ����������nIndex�����豸��� hWnd���ջ����ؼ��仯��Ϣ�Ĵ��ھ��
	int Init( unsigned int nIndex, HWND hWnd );
	//��ʼ����������devHandle�豸�����handleType�豸������ͣ�hWnd���ջ����豸�仯��Ϣ�Ĵ��ھ��
	int InitWithDevHandle( unsigned int devHandle, HandleTypes handleType, HWND hWnd ) ;
	//��ʼ����������devID�豸��ʶ��devType�豸���ͣ���hWnd���ջ����豸�仯��Ϣ�Ĵ��ھ��
	int InitWithDevID(  unsigned int devID, DeviceTypes devType, HWND hWnd ) ;

	//��ȡ�������豸��ʶ  ��Init��ʼ����ɺ����ʹ��
	int GetMixerDevId(unsigned int devID);

	//��ȡ�������Ϣ
	int GetMixerCaps( MIXERCAPS* pMixerCaps ) ;
	
	//��ȡ��·����
	int GetLineCount() ;
	//��ȡ��·���Ƹ���
	int GetLineControlCount( int lineIndex ) ;
	//��ȡ���Ӹ���
	int GetConnectionCount( int lineIndex ) ;
	//��ȡ���ӿ��Ƹ���
	int GetConnectionControlCount( int lineIndex, int connectionIndex ) ;

	//��ȡLine��MIXERLINE��Ϣ
	int GetLineInfo( int lineIndex, MIXERLINE* pMixerLine ) ;
	//��ȡConnection��MIXERLINE��Ϣ
	int GetConnectionInfo( int lineIndex, int connectionIndex, MIXERLINE* pMixerLine ) ;
	
	//��ȡ��·����ID
	int GetLineControlDwID( int lineIndex, int ctrlIndex ) ;
	//��ȡ���ӿ���ID
	int GetConnControlDwID( int lineIndex, int connIndex, int ctrlIndex ) ;

	//ͨ��control ID��ȡMIXERCONTROL
	int GetControlMetrics( DWORD dwID, MIXERCONTROL* pMC ) ;
	//ͨ��control ID��ȡ����״̬����
	int GetControlState( DWORD dwID, sChannelData* pStateData, unsigned int* nBuffSize ) ;
	//ͨ��control ID���ÿ���״̬����
	int SetControlState( DWORD dwID, sChannelData* pStateData, unsigned int* nBuffSize ) ;
	//ͨ��control ID���ÿ����Ƿ�Ϊѡ��״̬
	int SetControlSelState(DWORD dwID,DWORD dwLineId,unsigned int index,sChannelData* pStateData, unsigned int* nBuffSize );
	//ͨ��control ID LineId ��ȡ�Ƿ�Ϊѡ��״̬
	int GetControlSelState(DWORD dwID,DWORD dwLineId,unsigned int index,sChannelData* pStateData, unsigned int* nBuffSize );
	//��ȡ������������
	int GetControlChannelCount( DWORD dwID ) ; 

	//��ȡ��·��������
	int GetLineControlMetrics( int lineIndex, int controlIndex, MIXERCONTROL* pMC ) ;
	//������·��������
	int GetConnectionControlMetrics( int lineIndex, int connectionIndex, int controlIndex, MIXERCONTROL* pMC ) ;
	
	//��ȡ��·����״̬
	int GetLineControlState( unsigned int lineIndex, unsigned int controlIndex,  sChannelData* pChannelData, unsigned int* nBuffSize ) ;
	//������·����״̬
	int SetLineControlState( unsigned int lineIndex, unsigned int controlIndex,  sChannelData* pChannelData, unsigned int* nBuffSize ) ;	
	
	//��ȡ���ӿ���״̬
	int GetConnectionControlState( unsigned int lineIndex, unsigned int connectionIndex, 
		unsigned int controlIndex, sChannelData* pChannelData, unsigned int* nBuffSize ) ;
	//�������ӿ���״̬
	int SetConnectionControlState( unsigned int lineIndex, unsigned int connectionIndex, 
		unsigned int controlIndex, sChannelData* pChannelData, unsigned int* nBuffSize ) ;
private:
	//��ȡ��·��ϸ��Ϣ
	int GetLineDetails(void);
	//��ȡ��������ϸ
	int GetMixerDetails(void);
	//��ȡ��·��Ϣ
	CMixerLine* GetCLine( unsigned int lineIndex ) ;
private:
	UINT			muMxId;//�������豸��ʶ
	HMIXER			mhMixer ;//���������
	int				mnMixerCount ; //�����豸�������
	unsigned int	mnMixerNumber ;//�������豸��� 0 - mnMixerCount-1
	MIXERCAPS		mMixerCaps ;//������������Ϣ
	unsigned int	mnLineNums ;//�����ϻ�������Ŀ����·��
	CMixerLine*		mpMixerLines ;	// ��������·��ϸ��Ϣ��װ��
};
