#pragma once
#include "CommonPacket.h"
#include "BufferDefine.h"
#include "Mutex.h"
#include <map>
using namespace std;


class CBufferInputVideoEngine
{
public:
	CBufferInputVideoEngine();
	~CBufferInputVideoEngine();
	
	void	Initialize();
	void	UnInitialize();

	void	AddPacket(Packet* pDataPacket,UInt32 iSequence);//�����Ƶ���ݰ�
	void	KeepBalance();//ά��ָ��ʱ�䳤�Ȼ�������
	bool	GetPacket(Packet* &pDataPacket,UInt32 iSequence);//��ȡ���ݰ�  ������������
	void	ClearPackets();//�˳��������ݰ�
	bool	GetEngineUsed();//��ȡ�����Ƿ���ʹ��
	void	EchoVideoInputInfo();//��Ƶ��Ϣ
private:
	void	AddSequence(UInt32 iSequence);//������ݰ����
	void	AddFrameSeq(UInt32 iFrameSeq);//��ӵ�֡���
	UInt32	GetPackCount();//��ȡ���ݰ�����
	bool	GetFrameSeq(Packet* pDataPacket,UInt32& iFrameSeq);//��ȡ֡Sequence
	bool	ParsePack(const UInt8* pBuf, UInt32 iLen,UInt32& iFrameSeq);//�����ڲ����ݰ���ȡ֡Sequence
	void	ParseAllPack(Packet* pPacket,UInt32& iFrameSeq,bool& bSucc);//һ�����ݰ��ڰ���������һ֡ͼ�����ݽ���
	void	ParsePiecePack(Packet* pPacket,UInt32& iFrameSeq,bool& bSucc);//һ�����ݰ�ֻ��һ֡ͼ���һƬ���ݽ���
	void	RemoveFrame(UInt32 iFrameSeq);//�Ƴ�һ֡����
	void	IncFrameSeq(UInt32& iFrameSeq);//֡���ƶ�һ֡
	void	RemoveTimeOut();//��ʱ�Ƴ�
private:
	UInt32	m_minSequence;//��ǰ��Ƶ���ݰ���С���
	UInt32	m_maxSequence;//��ǰ��Ƶ���ݰ������
	UInt32	m_minFrameSeq;//��ǰ��С��Ƶ֡���
	UInt32	m_maxFrameSeq;//��ǰ�����Ƶ֡���
	DWORD	m_minFrameInterval;//��С֡ʱ���
	DWORD	m_maxFrameInterval;//���֡ʱ���
	UInt32	m_keepFrameNum;//����������֡��Ŀ
	Mutex	m_mutex;
	map<UInt32,StructVideoBufferPack> m_videoBufferMap;
	map<UInt32,StructVideoFrameSeqToSeq> m_frameToSeqMap;

};