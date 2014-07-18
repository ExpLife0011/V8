#pragma once
#ifdef _DEBUG
//#include <vld.h>
#endif
#include "CommonPacket.h"

#define BUFFER_OUTPUT_ONMIC_AUDIO_MIN_LIMIT		2500//500//300  //�����û�֮����Ƶ�������������
#define BUFFER_OUTPUT_ONMIC_AUDIO_MAX_LIMIT		2500//800//500
#define BUFFER_OUTPUT_UNMIC_AUDIO_MIN_LIMIT		2500//1000//300  //�����û�֮������Ƶ�������������
#define BUFFER_OUTPUT_UNMIC_AUDIO_MAX_LIMIT		2500//3000
#define BUFFER_OUTPUT_ONMIC_VIDEO_MIN_LIMIT		2000//500  //�����û�֮����Ƶ�������������
#define BUFFER_OUTPUT_ONMIC_VIDEO_MAX_LIMIT		2000//800
#define BUFFER_OUTPUT_UNMIC_VIDEO_MIN_LIMIT		2000//1000//500  //�����û�֮����Ƶ�������������
#define BUFFER_OUTPUT_UNMIC_VIDEO_MAX_LIMIT		2000//3000 
#define BUFFER_OUTPUT_RATECALC_MIN_INTERVAL		5000//����������ݰ����ʵ�ʱ���� ��С
#define BUFFER_OUTPUT_RATECALC_MAX_INTERVAL		5000//����������ݰ����ʵ�ʱ���� ���
#define BUFFER_OUTPUT_PLAYRATE_CAL_INTERVAL     1000  //�����ٶȼ�����ʱ�� --��Ƶ
#define BUFFER_OUTPUT_PLAYRATE_CAL_INTERVAS     300 //�����ٶȼ�����ʱ�� ��Ƶ
// #define BUFFER_OUTPUT_PLAYRATE_ALLOW__SHAKE		1.5f //���㲥���ٶ�ʱ���������е����ݸ�����������ֵ
#define BUFFER_OUTPUT_FRESHPACK_MS_INTERVAL		1000 //�������ݼ�ʱˢ��ʱ����
// #define BUFFER_OUTPUT_FRESHPACK_AO_INTERVAL     2000 //����������Ƶˢ��ʱ����
#define BUFFER_OUTPUT_FRAMEPLAY_MS_INTERVAL     1000 //��������֡ʱ ��ʱˢ��ʱ����
// #define BUFFER_OUTPUT_PLAYRATE_CHANGE_LIMIT		5    //�������ݶ�����Χ
// #define BUFFER_OUTPUT_PLAYAUDIO_INTER_LIMIT     2    //������Ƶ���ݶ�����Χ
#define BUFFER_OUTPUT_BUFFER_SHAKE_INTERVAL     500  //Buffer�仯��ʱ����
#define BUFFER_OUTPUT_BUFFER_SHAKE_LOSTRATE     1000*30 //���㶪���ʼ��ʱ��
#define BUFFER_OUTPUT_BUFFER_RECVRATE_SHAKE		1000  //�����հ����ʵļ��ʱ��
// #define BUFFER_OUTPUT_VIDEO_FRAMEPACK_INTER		50 //Ĭ�ϲ���֡�����ݼ��ʱ��
#define BUFFER_OUTPUT_BUFFER_CALC_AUDIO_PARAM   100   //��ȡ��Ƶ������ʱ����

#define BUFFER_OUTPUT_AUDIO_LOSTRATE_MINMUM     0.001f//��Ƶ���������� 1/1000
#define BUFFER_OUTPUT_AUDIO_LOSTRATE_MIDDLE		0.050f//��Ƶ�����ʷֽ� 5/100
#define BUFFER_OUTPUT_AUDIO_LOSTRATE_MAXMUM     0.200f//��Ƶ���������� 2/10

#define BUFFER_OUTPUT_VIDEO_LOSTRATE_MINMUM     0.001f//��Ƶ��������  1/1000
#define BUFFER_OUTPUT_VIDEO_LOSTRATE_MIDDLE     0.050f//��Ƶ�����ֽ�  3/100
#define BUFFER_OUTPUT_VIDEO_LOSTRATE_MAXMUM     0.200f//��Ƶ�����ֽ�  2/10
 
#define BUFFER_OUTPUT_LOST_COMPENSATION_MIN     280 //��������������ʱ������
#define BUFFER_OUTPUT_LOST_COMPENSATION_MAX     800 //��������������ʱ������

#define BUFFER_PERSEC_AUDIO_NUMBER          23.4375f/*17*/    //��Ƶÿ��������ݰ����� ������ο�  //=========50
#define BUFFER_PERSEC_VIDEO_NUMBER			22    //��Ƶÿ��������ݰ����� ������ο�
#define BUFFER_INPUT_AUDIO_LIMIT			3000  //�ɼ�������Ƶ���ݻ��������
#define BUFFER_INPUT_VIDEO_LIMIT			3000  //�ɼ�������Ƶ���ݻ��������
#define BUFFER_INPUT_AUDIO_TIME_OUT			3     //��Ƶ���ݳ�ʱ
#define BUFFER_INPUT_VIDEO_TIME_OUT         3	  //��Ƶ���ݳ�ʱ
#define BUFFER_PERSEC_VIDEO_FRAMES          10    //��Ƶÿ��֡��
#define BUFFER_PERSEC_VIDEO_SHAKE_MIN	    1     //��Ƶ����֡ ��С����
#define BUFFER_PERSEC_VIDEO_SHAKE_MAX       5	  //��Ƶ����֡ ��󶶶�
#define BUFFER_PERSEC_VIDEO_SHAKE_LIMIT     1000  //��Ƶ����֡ ����
#define BUFFER_PERSEC_AUDIO_SEND_INTER		(1000.0f/BUFFER_PERSEC_AUDIO_NUMBER)//42.6668f/*(1000/BUFFER_PERSEC_AUDIO_NUMBER)*/    //�������ݰ����ʱ��  //=================50
#define BUFFER_PERSEC_AUDIO_SHAKE_LIMIT     4     //��Ƶ���ݰ�����������Χ
#define BUFFER_PERSEC_AUDIO_SHAKE_CHECK     3000  //3s�Ӽ��һ�ν��������Ƿ��ȶ�

#define BUFFER_OUTPUT_AUDIO_PACKET_MAXLIMIT     BUFFER_PERSEC_AUDIO_NUMBER*30 //�������ݰ� buffer�д�����������
#define BUFFER_OUTPUT_VIDEO_PACKET_MAXLIMIT     BUFFER_PERSEC_VIDEO_NUMBER*30 //��Ƶ���ݰ� buffer�д�����������
 
#define BUFFER_COMPENSATION_NUMBER          1     //���󲹳������͸���
// #define BUFFER_COMPEN_REQUE_INTERVAL_MIN    200   //���󲹳����ݰ���Сʱ����
// #define BUFFER_COMPEN_REQUE_INTERVAL_MAX    500   //���󲹳����ݰ����ʱ����
#define BUFFER_COMPEN_REQUE_TIMES           3     //���󲹳�������
#define BUFFER_VIDEO_PREVIEW_TIME           5*1000 //��Ƶ��ʼ����ǰ5s�������ٶȲ��ţ��ӿ���ʾͼ��Ȼ���ٻ���2s��ͬ��������
#define BUFFER_MEDIA_EXPIRE_TIME			5*60*1000  //����ʹ��ʧЧʱ��
#define BUFFER_MEDIA_CHECK_TIME				5*60*1000  //������ʱ��

//��Ƶ���ݰ�����ṹ
struct StructAudioBufferPack
{
	UInt32	m_iSequence;
	UInt32  m_iFrameSeq;
	Packet* m_pPack;
	DWORD  m_time;
public:
	StructAudioBufferPack()
	{
		m_pPack = NULL;
		m_iSequence = 0;
		m_time=0;
		m_iFrameSeq = 0;
	}
	~StructAudioBufferPack(){}
};

//��Ƶ���ݰ�����ṹ
struct StructVideoBufferPack
{
	UInt32	m_iSequence;//���ݰ����
	UInt32  m_iFrameSeq;//֡���
	UInt32  m_iPieceCount;
	Packet* m_pPack;
	DWORD	m_time;
public:
	StructVideoBufferPack()
	{
		m_pPack = NULL;
		m_iSequence = 0;
		m_time=0;
		m_iFrameSeq = 0;
		m_iPieceCount=0;
	}
	~StructVideoBufferPack(){}
};

//����ÿ֡��Ӧ�����к�
struct StructVideoFrameSeqToSeq
{
	UInt32 m_minSequence;
	UInt32 m_maxSequence;
};

//���油�����ݰ�
struct StructAudioRequestInfo 
{
	UInt32 m_iSequence; //���������
	DWORD  m_lastTime;  //�ϴβ���ʱ��
	UInt32 m_iReqNum;	//�Ѿ���������
public:
	StructAudioRequestInfo()
	{
		m_iSequence = 0;
		m_lastTime = 0;
		m_iReqNum = 0;
	}
	~StructAudioRequestInfo(){}
};

struct StructVideoRequestInfo 
{
	UInt32 m_iSequence; //���������
	DWORD  m_lastTime;  //�ϴβ���ʱ��
	UInt32 m_iReqNum;	//�Ѿ���������
public:
	StructVideoRequestInfo()
	{
		m_iSequence = 0;
		m_lastTime = 0;
		m_iReqNum = 0;
	}
	~StructVideoRequestInfo(){}
};


