#pragma once
#include "Common.h"
#include "RC.h"
#include "BufferInPlace.h"
#include "BufferBaseRate.h"
#include "BufferDefine.h"
#include <map>

using namespace std;

class CBufferOutputAudioTask;
class CBufferOutputAudioEngine:public RCObject
{
friend class CBufferOutputAudioTask;
friend class CBufferOutputEngine;
public:
	CBufferOutputAudioEngine(UInt32 iRoomId,UInt32 iFromUin);
	~CBufferOutputAudioEngine();

	void Initialize(ITransInPlace* pInPlace,IBufferBaseRate* pRate);
	void UnInitialize();

	void AddPacket(Packet* pData,UInt32 iSequence);
	void ClearPackets();
	bool IsCanRemove();
	void Play();
protected:
	void AddFrameSeq(UInt32 iFrameId); //���֡��� ���浱ǰBUFFER����� ��С����֡
	void AddSequenceId(UInt32 iSequenceId); //��Ӷ������ ���浱ǰBUFFER�� ��� ��С���к�
	void UpdateTime(DWORD dwCurTime);//�����հ�����
	void PlayPackets();//�������ݰ�
	void CheckPacket(); //������������һ�����ݰ����� 
	void RequestCompenPacket(UInt32 iSequenceId,bool bA); //���󲹳����ݰ�
	void RefreshStatus();//���µ�ǰ��Ƶ���峤��״̬
	void ResetStatus();//���û�����״̬
	bool IsNormalPacket(UInt32 iFrameId,UInt32 iSequenceId); //�յ��������Ƿ�Ϊ������Ч�����ж�
	bool IsCanCalcRecvRate();//�Ƿ���Լ����հ�����
	float CalcRecevRate();//�����հ�����
	Packet* GetPlayPacket(UInt32 iSequenceId);//��ȡ��ǰ���ŵ����ݰ�
	double CanCalcPlayRate();//���㲥������
	
	map<UInt32,StructAudioBufferPack> m_mapOutputAudioBuf;//��Ƶ�������ݰ�
	typedef pair<UInt32,StructAudioBufferPack> pair_outputAB;
	map<UInt32,StructAudioRequestInfo> m_mapOutputAudioReqInf;//�����������Ϣ
	typedef pair<UInt32,StructAudioRequestInfo> pair_outputRI;

	static map<UInt64,CBufferOutputAudioEngine*> m_mapAudioOutput; //��Ƶ����ʵ��
	static Mutex m_static_mutex;//�����߳� �����߳� m_mapAudioOutput
private:
	ITransInPlace* m_pInPlace;
	IBufferBaseRate* m_pRate;

	Mutex	m_mutex;				 //�����߳� �����߳� m_mapOutputAudioBuf
	float	m_fLostRate;             //��һ�μ�ʱ������
	DWORD	m_dwLastLostTime;		 //��һ�μ��㶪����ʱ��
	DWORD   m_lastRecvTime;			 //���һ�ν�������ʱ��
	UInt32	m_iTotalPacketNum;		 //��ʱ��ʼ�ܹ��յ������ݰ��ܺ�
	UInt32	m_iLostPacketNum;        //��ʱ��ʼ�ܹ���ʧ�����ݰ��ܺ�
	
	DWORD	m_dwLastRecvRateTime;    //��һ�μ���������ݰ����ʵĿ�ʼʱ��
	DWORD	m_dwFirstStartTime;		 //��һ�μ�ʱ
	DWORD	m_dwSecondStartTime;     //�ڶ��μ�ʱ
	UInt32	m_iBufferSize;           //��������С
	UInt32	m_iFirstStartNum;        //��һ�μ�ʱ��ʼ�������յ������ݰ�
	UInt32	m_iSecondStartNum;       //�ڶ��μ�ʱ��ʼ�������յ������ݰ�
	UInt32  m_iLastRecvRateInter;	 //��һ�μ���ĵļ��ʱ��

	UInt32	m_iFromUin;				//��������Ƶ�û�UIN
	UInt32	m_iRoomId;				//����ID
	UInt32	m_iMinFrameId;			//��С֡ID
	UInt32	m_iMaxFrameId;			//���֡ID
	UInt32	m_iMinSequenceId;		//��С���ID
	UInt32	m_iMaxSequenceId;		//������ID
	UInt32	m_iCheckSeqId;			//��ǰ�������ID
	bool    m_bFilled;              //�Ƿ񻺳��㹻������
	float   m_fRecvRate;			//�հ�����
	DWORD   m_dwLastCalcRecvRate;   //�ϴμ����հ�����ʱ��
	DWORD   m_fLastPlayTime;        //�ϴβ������ݰ���ʱ��
	UInt32  m_iStartPlayCount;      //��ʼ��ʱ�𲥷ŵ����ݰ���
	double  m_fSendRate;			//ÿ�η������ݰ����ʱ��
	bool    m_bAjustSendRate;       //�Ƿ�ʼ������������

	bool    m_bShakeKeepRate;       //������Ᵽ��һ��ʱ����ȶ�����
	DWORD   m_dwShakeCheckStart;

};
