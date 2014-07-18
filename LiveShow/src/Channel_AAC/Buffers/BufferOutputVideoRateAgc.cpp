#include "stdafx.h"
#include <math.h>
#include "BufferDefine.h"
#include "BufferOutputVideoRateAgc.h"


//��ȡ��ǰ���ʼ������ʱ���� ���ݲ�ͬBUFFER�����ʵ�����
DWORD CBufferOutputVideoRateAgc::GetRateTimeInterval(
								  UInt32 iBufMinInterval,		//��������С����ʱ�� - ���� ��С
								  UInt32 iBufMaxInterval,		//��������󻺳�ʱ�� - ���� ���
								  UInt32 iBufMinInterval1,		//��������С����ʱ�� - ���� ��С
								  UInt32 iBufMaxInterval1,		//��������󻺳�ʱ�� - ���� ���
								  UInt32 iBufSize,				//��ǰ��������С
								  UInt32 iLastRecvRate,			//�ϴμ���ļ��ʱ��
								  DWORD& dwLastRecvTime			//�ϴμ����հ����ʵ�ʱ��
								  )
{
		if (0 == dwLastRecvTime){
			dwLastRecvTime = GetTickCount();
			return BUFFER_OUTPUT_RATECALC_MIN_INTERVAL;
		}
		if (GetTickCount() - dwLastRecvTime < BUFFER_OUTPUT_BUFFER_RECVRATE_SHAKE)
		{
			return iLastRecvRate;
		}
		else
		{
			dwLastRecvTime = GetTickCount();
		}

		//��������С��Χ
		unsigned int iBufMinInter = iBufMinInterval;
		unsigned int iBufMaxInter = iBufMaxInterval;
		bool bOnMic = GetMicStatus();
		if (!bOnMic) //��������
		{
			iBufMinInter = iBufMinInterval1;
			iBufMaxInter = iBufMaxInterval1;	
		}

		unsigned int iondisf =  iBufMaxInter - iBufMinInter;
		if (iBufSize<iBufMinInter || iBufSize>iBufMaxInter || iondisf==0)
		{
			//Assert(0);
			return iLastRecvRate;
		}

		unsigned int iDelayTime = (float)(iBufSize- iBufMinInter) * (BUFFER_OUTPUT_RATECALC_MAX_INTERVAL -	\
			BUFFER_OUTPUT_RATECALC_MIN_INTERVAL) / iondisf +BUFFER_OUTPUT_RATECALC_MIN_INTERVAL;
		iDelayTime = iDelayTime - iDelayTime%10;

		return iDelayTime;
}

//�������󲹳����´������ʱ����
DWORD CBufferOutputVideoRateAgc::CalcRequestCompenInterval(
	UInt32 iBufferSize,			//�������ܴ�С
	UInt32 iBufferDataSize,		//��ǰ���������ݸ���
	float  fRecvRate			//�յ����ݰ�������
	)
{
		DWORD dwInter = BUFFER_OUTPUT_LOST_COMPENSATION_MIN;
		if (iBufferSize < BUFFER_OUTPUT_LOST_COMPENSATION_MIN * 3){
			return dwInter;
		}

		float fBufferDataSize = iBufferDataSize * 1000 / BUFFER_PERSEC_VIDEO_NUMBER;
		if (fBufferDataSize < BUFFER_OUTPUT_LOST_COMPENSATION_MIN * 3){
			return dwInter;
		}

		float flimit = fBufferDataSize>iBufferSize?iBufferSize:fBufferDataSize;
		dwInter = (flimit - BUFFER_OUTPUT_LOST_COMPENSATION_MIN * 3) / 3 + 
			BUFFER_OUTPUT_LOST_COMPENSATION_MIN;
		dwInter = dwInter > BUFFER_OUTPUT_LOST_COMPENSATION_MAX?BUFFER_OUTPUT_LOST_COMPENSATION_MAX:dwInter;
		dwInter = dwInter - dwInter%10;
		return dwInter;
}

//����Buffer��С �������綪���� ����̬����BUFFER��С  ����Խ��BUFFERԽС ����Խ��BUFFERԽ��Ϊ�����ṩ��Գ����ʱ��
UInt32 CBufferOutputVideoRateAgc::CalcBufferSize(
							  UInt32 iBufMinInterval,		//��������С����ʱ�� - ���� ��С
							  UInt32 iBufMaxInterval,		//��������󻺳�ʱ�� - ���� ���
							  UInt32 iBufMinInterval1,		//��������С����ʱ�� - ���� ��С
							  UInt32 iBufMaxInterval1,		//��������󻺳�ʱ�� - ���� ���
							  UInt32 iAverageRate,			//ƽ������ ÿ����յ������ݰ�����
							  float  fLostRate,				//��ǰ������
							  DWORD& dwLastTime,			//��һ�μ��㻺����ʱ��
							  UInt32 iCurBufSize,			//��ǰ��������С
							  UInt32 iRefenceBufSize,		//����buf��С����������Ƶͬ��
							  DWORD  dwRefRecvTime			//�������һ�ν�������ʱ��
							  )
{
		if (GetTickCount() - dwLastTime < BUFFER_OUTPUT_BUFFER_SHAKE_INTERVAL){
			return iCurBufSize;
		}else{
			dwLastTime = GetTickCount();
		}
		//��ʼ����
		unsigned int iBufferSizeTemp = iCurBufSize;
		unsigned int iBufMinInter = iBufMinInterval;
		unsigned int iBufMaxInter = iBufMaxInterval;
		unsigned int iBufMidInter = iBufMinInterval + (iBufMaxInterval - iBufMinInterval) / 2;
		bool bOnMic = GetMicStatus();
		if (!bOnMic){
			iBufMinInter = iBufMinInterval1;
			iBufMaxInter = iBufMaxInterval1;	
			iBufMidInter = iBufMaxInterval;
		}
		float fx = 0.0f;
		unsigned int iondisf =  iBufMidInter - iBufMinInter;
		unsigned int iondisb =  iBufMaxInter - iBufMidInter;
		float flostf = BUFFER_OUTPUT_VIDEO_LOSTRATE_MIDDLE - BUFFER_OUTPUT_VIDEO_LOSTRATE_MINMUM;
		float flostb = BUFFER_OUTPUT_VIDEO_LOSTRATE_MAXMUM - BUFFER_OUTPUT_VIDEO_LOSTRATE_MIDDLE;
		if (iondisf>0 && iondisb>0){
			//���ն����ʼ��㻺������С
			if ( 0.0f == fLostRate){
				iBufferSizeTemp = iBufMinInterval1;
			}else 
			if (fLostRate<BUFFER_OUTPUT_VIDEO_LOSTRATE_MINMUM){
				iBufferSizeTemp = iBufMinInterval1;
			}else 
			if (fLostRate >=BUFFER_OUTPUT_VIDEO_LOSTRATE_MINMUM && 
				fLostRate < BUFFER_OUTPUT_VIDEO_LOSTRATE_MIDDLE){ // �������� 1/1000 ~ 5/100֮��ļ���
					fx = fLostRate/flostf>1.0f?1.0f:fLostRate/flostf;
					iBufferSizeTemp = (float)iondisf * sqrtf( 1 - (1-fx)*(1-fx))+iBufMinInter;//buf�Ͷ����ʵĹ�ϵ y=sqrtf(1-(1-x)*(1-x)),xΪ�����ʣ�yΪ��������
			}else 
			if (fLostRate>=BUFFER_OUTPUT_VIDEO_LOSTRATE_MIDDLE && 
				fLostRate < BUFFER_OUTPUT_VIDEO_LOSTRATE_MAXMUM){// �������� 5/100 ~ 3/10֮��ļ���
					fx = fLostRate/flostf>1.0f?1.0f:fLostRate/flostf;
					iBufferSizeTemp = (float)iondisb * sqrtf(1 - (1-fx)*(1-fx))+ iBufMidInter;
			}else 
			if (fLostRate >= BUFFER_OUTPUT_VIDEO_LOSTRATE_MAXMUM){
				iBufferSizeTemp = iBufMaxInter;
			}
			iBufferSizeTemp = iBufferSizeTemp - iBufferSizeTemp%10 + (iBufferSizeTemp%10>0?10:0);//��10Ϊ��λ
			//�뵱ǰ��������С��ϵ
			if (iBufferSizeTemp < iCurBufSize-100){
				UInt32 iDeta = (iCurBufSize - iBufferSizeTemp) / 4;
				iDeta = iDeta < 100 ? 100:iDeta;
				iBufferSizeTemp = iCurBufSize-iDeta;
			}else 
			if (iBufferSizeTemp > iCurBufSize+100){
				UInt32 iDeta = (iBufferSizeTemp - iCurBufSize) / 4;
				iDeta = iDeta < 100 ? 100:iDeta;
				iBufferSizeTemp = iCurBufSize+iDeta;
			}
			//�������仯��Χ
			if (iBufferSizeTemp <iBufMinInter){
				iBufferSizeTemp = iBufMinInter;
			}else 
			if (iBufferSizeTemp>iBufMaxInter){
				iBufferSizeTemp = iBufMaxInter;
			}
		}
		//�Ƚϲ���buf��С
		if (GetTickCount() - dwRefRecvTime<500){
			if (iRefenceBufSize>1000){
				iBufferSizeTemp = iRefenceBufSize;
				iBufferSizeTemp += -854; //500ms ��Ƶ����Ƶ����  ��Ƶ�����ӳ�500ms,��Ƶ˫��Ԥ���ӳٽ�500ms �໥������
			}
		}
		
		return iBufferSizeTemp;
}

//���㲥�����ݰ�֮���ʱ����  ���ݰ��ļ��ʱ��
DWORD CBufferOutputVideoRateAgc::CalcSendRate(
							UInt32 iBufSize,			//��������С   ---ʱ���  ��ǰ������ʱ���С
							UInt32 iBufDataSize,        //��ǰ�����������ݸ��� ---���ݰ�����
							UInt32 iBufFrameSize,       //��ǰ֡��ʵ�ʷ�Χ --���ݰ�֡��Χ
							float  fRecvRate,			//�������ݵ����� ---�հ�����
							UInt32 iLastRate			//�ϵķ������� --�ϴμ���õ��ķ�������
							)
{
		//��ǰ�������е�֡���Ƿ���ָ���ķ�Χ��
		UInt32 iShake = BUFFER_PERSEC_VIDEO_SHAKE_MIN;
		float fNormalFrameSize = (float)iBufSize * BUFFER_PERSEC_VIDEO_FRAMES / 1000;  //�����������֡��
		UInt32 iBufferDataTime = iBufFrameSize*100;  //iBufDataSize * 1000 / BUFFER_PERSEC_VIDEO_NUMBER;
		UInt32 iSendFrameRate = 1000 / BUFFER_PERSEC_VIDEO_FRAMES;

		//����֡�Ķ�����Χ�ڣ�֡�ʱ��ֲ���
		if(iBufFrameSize <=fNormalFrameSize+iShake && iBufFrameSize>=fNormalFrameSize){
			return  iSendFrameRate;
		}

		//������������Χ��С
		iShake = ceil((float)iBufSize*5 / BUFFER_PERSEC_VIDEO_SHAKE_LIMIT);
		iShake = iShake > BUFFER_PERSEC_VIDEO_SHAKE_MAX*2?BUFFER_PERSEC_VIDEO_SHAKE_MAX*2:iShake;

		if (iBufferDataTime <= iBufSize / 4)
		{
			iSendFrameRate += 50;
		}
		else if (iBufferDataTime>iBufSize / 4 && iBufferDataTime<=iBufSize / 2)
		{
			iSendFrameRate += 50;
		}
		else if (iBufferDataTime>iBufSize / 2 && iBufferDataTime<=iBufSize*3/ 4)
		{
			iSendFrameRate += 30;
		}
		else if (iBufferDataTime>iBufSize*3/ 4 && iBufferDataTime<=iBufSize-50)
		{
			iSendFrameRate +=5;
		}
		else if (iBufferDataTime>iBufSize-100 && iBufferDataTime<=iBufSize+100)
		{
			iSendFrameRate +=0;
		}
		else if (iBufferDataTime>iBufSize+100 && iBufferDataTime<=iBufSize*5/4)
		{
			iSendFrameRate -=5;
		}
		else if (iBufferDataTime>iBufSize*5/4 && iBufferDataTime<=iBufSize*6/4)
		{
			iSendFrameRate -=10;
		}
		else if (iBufferDataTime>iBufSize*6/4 && iBufferDataTime<=iBufSize*7/4)
		{
			iSendFrameRate -=30;
		}
		else if (iBufferDataTime>iBufSize*7/4 && iBufferDataTime<=iBufSize*8/4)
		{
			iSendFrameRate -=40;
		}
		else
		{
			iSendFrameRate -=50;
		}

		if (iSendFrameRate - iLastRate > iShake && iSendFrameRate > iLastRate)
		{
			iSendFrameRate = iLastRate+iShake;
		}
		if (iLastRate - iSendFrameRate < iShake && iSendFrameRate < iLastRate)
		{
			iSendFrameRate = iLastRate-iShake;
		}

		return iSendFrameRate;
}