#pragma once
#include "RC.h"
#include "BufferInPlace.h"
#include "BufferBaseRate.h"
#include "CommonPacket.h"
#include "BufferDefine.h"
#include <map>

using namespace std;
class CBufferOutputVideoTask;
class CBufferOutputVideoEngine:public RCObject
{
friend class CBufferOutputVideoTask;
public:
	CBufferOutputVideoEngine(UInt32 iRoomId,UInt32 iFromUin);
	~CBufferOutputVideoEngine();

	void	Initialize(ITransInPlace* pInPlace,IBufferBaseRate* pRate);
	void	UnInitialize();
	void	AddPacket(Packet* pData,UInt32 iSequence);
	void	ClearPackets();
	bool	IsCanRemove();
	void	Play();
protected:
	bool	GetFrameSeq(Packet* pDataPacket,UInt32& iFrameSeq,UInt32& iPieceCount);//��ȡ֡Sequence
	bool	ParsePack(const UInt8* pBuf, UInt32 iLen,UInt32& iFrameSeq,UInt32& iPieceCount);//�����ڲ����ݰ���ȡ֡Sequence
	void	ParseAllPack(Packet* pPacket,UInt32& iFrameSeq,bool& bSucc);//һ�����ݰ��ڰ���������һ֡ͼ�����ݽ���
	void	ParsePiecePack(Packet* pPacket,UInt32& iFrameSeq,UInt32& iPieceCount,bool& bSucc);//һ�����ݰ�ֻ��һ֡ͼ���һƬ���ݽ���
	bool	IsNormalPacket(UInt32 iFrameId,UInt32 iSequenceId); //�յ��������Ƿ�Ϊ������Ч�����ж�
	void	AddFrameSeq(UInt32 iFrameId);//���֡���
	void	AddSequenceId(UInt32 iSequenceId);//��Ӷ������
	void	UpdateTime(DWORD dwCurTime,UInt32 iFrameId);//�����հ�����
	float	CalcRecevRate(); //�����հ�����
	float	CalcRecevFrameRate();//������֡����
	bool	IsCanCalcPlayRate(); //��ǰ�Ƿ���Լ��㲥��������
	void    PlayFrames();//����֡
	void    PlayPackets();//���Ű�
	Packet* GetPlayPacket(UInt32 iSequenceId);//��ȡ��ǰ���ŵ����ݰ�
	void    RemoveExpireFrame();//�Ƴ���Ч��֡
	void    CheckPacket();//����У�顢����
	bool    CanCalcAudioParam();//���Լ�����Ƶ����
	void    ResetStatus();//����״̬
	void    RequestCompenPacket(UInt32 iSequenceId,bool bA);
protected:
	static map<UInt64,CBufferOutputVideoEngine*> m_mapVideoOutput; //��Ƶ����ʵ��
	static Mutex m_static_mutex; //�����߳� �����߳� m_mapVideoOutput

	Mutex   m_mutex; //m_mapOutputVideoBuf buffer�����߳� m_mapFrameToSeq
	map<UInt32,StructVideoBufferPack> m_mapOutputVideoBuf;//��Ƶ�������ݰ�
	typedef pair<UInt32,StructVideoBufferPack> pair_outputVB;
	map<UInt32,StructVideoFrameSeqToSeq> m_mapFrameToSeq; //iframeId -- isequenceId
	typedef pair<UInt32,StructVideoFrameSeqToSeq> pair_outputFB;
	map<UInt32,StructVideoRequestInfo> m_mapOutputVideoReqInf;//�����������Ϣ
	typedef pair<UInt32,StructVideoRequestInfo> pair_outputRI;
private:
	ITransInPlace* m_pInPlace;
	IBufferBaseRate* m_pRate;

	UInt32		m_iFromUin;				//��������Ƶ�û�UIN
	UInt32		m_iRoomId;				//����ID
	UInt32		m_iMinFrameId;			//��С֡ID
	UInt32		m_iMaxFrameId;			//���֡ID
	UInt32		m_iPlayFrameId;			//��ǰ���ŵ�֡ID
	UInt32      m_iWillPlayFrameId;     //�������ŵ�֡ID
	UInt32		m_iMinSequenceId;		//��С���ID
	UInt32		m_iMaxSequenceId;		//������ID
	UInt32		m_iCheckSeqId;			//��ǰ�������ID
	UInt32		m_iCheckFrameId;		//��ǰ����֡���ID
	UInt32		m_iTotalPacketNum;		//��ʱ��ʼ�ܹ��յ������ݰ��ܺ�
	UInt32		m_iLostPacketNum;       //��ʱ��ʼ�ܹ���ʧ�����ݰ��ܺ�
	float		m_fLostRate;            //��һ�μ�ʱ������
	DWORD		m_dwLastLostTime;		//��һ�μ��㶪����ʱ��
	DWORD		m_lastRecvTime;         //�ϴν������ݰ�ʱ��

	DWORD		m_dwFirstStartTime;	    //��һ�μ�ʱ
	DWORD		m_dwSecondStartTime;    //�ڶ��μ�ʱ
	DWORD		m_dwLostStartTime;      //���㶪����ʼʱ��
	UInt32		m_iFirstStartNum;       //��һ�μ�ʱ��ʼ�������յ������ݰ�
	UInt32		m_iSecondStartNum;      //�ڶ��μ�ʱ��ʼ�������յ������ݰ�
	DWORD		m_dwLastRecvRateTime;   //��һ�μ���������ݰ����ʵĿ�ʼʱ��
	UInt32		m_iLastRecvRateInter;   //��һ�μ���ĵļ��ʱ��
	UInt32		m_iBufferSize;          //��������С
	UInt32      m_iAudioBufferSize;     //��Ƶ��������С  ms
	DWORD       m_dwLastRecvAudioTime;  //���һ�ν�����Ƶ����ʱ��
	DWORD       m_dwStartCalcAudioParam;//��ʼ��ȡ��Ƶ�����С���������������ʼʱ��
	bool        m_bStartPlay;           //�Ƿ��״β���
	DWORD		m_dwLastCalcBufSizeTime; //�ϴμ��㻺������Сʱ����

	UInt32		m_iFirstStartFrameSeq;    //��һ��ʱ��ʼ֡���
	UInt32		m_iFirstCurFrameSeq;	  //��һ��ʱ��ǰ֡���
	UInt32		m_iSecondStartFrameSeq;   //�ڶ���ʱ��ʼ֡���
	UInt32		m_iSecondCurFrameSeq;     //�ڶ���ʱ��ǰ֡���
	UInt32		m_iFirstStartFrameNum;    //��һ��ʱ֡��Ŀ
	UInt32		m_iSecondStartFrameNum;   //�ڶ���ʱ֡��Ŀ

	float		m_fRecvRate;			  //��ǰ�հ���
	float		m_fRecvFrameRate;         //��ǰ����֡����
	DWORD		m_dwLastPlayRateTime;     //�ϴα����������ʱ�� 
	DWORD		m_dwSendRate;			  //�������ݵ����� ���ݰ�֮��ʱ����
	DWORD		m_dwLastPlayTime;		  //��һ�β���ý�����ݰ�ʱ�� ����ÿ����һ�����ݰ����ʱ��
	DWORD		m_dwStartPlayTime;        //��ʼ��ʱ����ý��ʱ��
	UInt32		m_iStartPlayCount;        //��ʼ����ý�����
	bool		m_bFilled;				  //�Ƿ񻺳��㹻������
};
