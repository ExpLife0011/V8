#pragma once
#include "Common.h"

//���ʿ��ƻ���
class IBufferBaseRate
{
public:
	IBufferBaseRate():m_bOnMic(false){}

	//���õ�ǰ�����Ƿ�������
	virtual void SetMicStatus(bool bEnable)
	{ m_bOnMic = bEnable;}
	
	//��ȡ�Ƿ�������״̬
	virtual bool GetMicStatus(){ return m_bOnMic; }

	//��ȡ��ǰ���ʼ������ʱ���� ���ݲ�ͬBUFFER�����ʵ�����
	virtual DWORD GetRateTimeInterval(
		UInt32 iBufMinInterval,		//��������С����ʱ�� - ���� ��С
		UInt32 iBufMaxInterval,		//��������󻺳�ʱ�� - ���� ���
		UInt32 iBufMinInterval1,	//��������С����ʱ�� - ���� ��С
		UInt32 iBufMaxInterval1,	//��������󻺳�ʱ�� - ���� ���
		UInt32 iBufSize,			//��ǰ��������С
		UInt32 iLastRecvRate,       //�ϴμ���ļ��ʱ��
		DWORD& dwLastRecvTime       //�ϴμ����հ����ʵ�ʱ��
		) = 0;

	//�������󲹳����´������ʱ����
	virtual DWORD CalcRequestCompenInterval(
		UInt32 iBufferSize,			//�������ܴ�С
		UInt32 iBufferDataSize,		//��ǰ���������ݸ���
		float  fRecvRate			//�յ����ݰ�������
		) = 0;

	//����Buffer��С �������綪���� ����̬����BUFFER��С  ����Խ��BUFFERԽС ����Խ��BUFFERԽ��Ϊ�����ṩ��Գ����ʱ��
	virtual UInt32 CalcBufferSize(
		UInt32 iBufMinInterval,		//��������С����ʱ�� - ���� ��С
		UInt32 iBufMaxInterval,		//��������󻺳�ʱ�� - ���� ���
		UInt32 iBufMinInterval1,	//��������С����ʱ�� - ���� ��С
		UInt32 iBufMaxInterval1,	//��������󻺳�ʱ�� - ���� ���
		UInt32 iAverageRate,		//ƽ������ ÿ����յ������ݰ�����
		float  fLostRate,			//��ǰ������
		DWORD& dwLastTime,          //��һ�μ��㻺����ʱ��
		UInt32 iCurBufSize,         //��ǰ��������С
		UInt32 iRefenceBufSize,     //����buf��С����������Ƶͬ��
		DWORD  dwRefRecvTime        //�������һ�ν�������ʱ��
		) =0;

	//���㲥�����ݰ�֮���ʱ����  ���ݰ��ļ��ʱ��
	virtual DWORD CalcSendRate(
		UInt32 iBufSize,			//��������С
		UInt32 iBufDataSize,        //��ǰ�����������ݴ�С
		UInt32 iBufFrameSize,       //��ǰ֡��ʵ�ʷ�Χ
		float  fRecvRate,			//�������ݵ�����
		UInt32 iLastRate			//�ϵķ�������
		)=0;
protected:
	bool m_bOnMic; //�Ƿ������� Ĭ�ϲ������� TRUE:������  FALSE:��������
};