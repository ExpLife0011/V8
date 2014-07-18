#include "stdafx.h"
#include "Setting.h"
#include "Packets/AVPacketMacros.h"
#include "Packets/VideoPacket.h"
#include "BufferOutputVideoEngine.h"
#include "UdpChannel.h"
#include "RelayCompenPacket.h"

map<UInt64,CBufferOutputVideoEngine*> CBufferOutputVideoEngine::m_mapVideoOutput; //��Ƶ����ʵ��
Mutex CBufferOutputVideoEngine::m_static_mutex;//�����߳� �����߳� m_mapVideoOutput

CBufferOutputVideoEngine::CBufferOutputVideoEngine(UInt32 iRoomId,UInt32 iFromUin)
:m_iRoomId(iRoomId),
m_iFromUin(iFromUin),
m_pInPlace(NULL),
m_pRate(NULL),
m_lastRecvTime(GetTickCount()),
m_iMinFrameId(0),
m_iMaxFrameId(0),
m_iPlayFrameId(0),
m_iMinSequenceId(0),
m_iMaxSequenceId(0),
m_iCheckSeqId(0),
m_iCheckFrameId(0),
m_iTotalPacketNum(0),
m_iLostPacketNum(0),
m_fLostRate(0.0f),
m_dwLastLostTime(GetTickCount()),
m_dwFirstStartTime(0),
m_dwSecondStartTime(0),
m_dwLostStartTime(0),
m_iFirstStartNum(0),
m_dwLastRecvRateTime(0),
m_iLastRecvRateInter(BUFFER_OUTPUT_RATECALC_MIN_INTERVAL),
m_iBufferSize(BUFFER_OUTPUT_ONMIC_VIDEO_MAX_LIMIT),
m_iFirstStartFrameSeq(0),
m_iFirstCurFrameSeq(0),
m_iSecondStartFrameSeq(0),
m_iSecondCurFrameSeq(0),
m_iFirstStartFrameNum(0),
m_iSecondStartFrameNum(0),
m_iAudioBufferSize(BUFFER_OUTPUT_ONMIC_AUDIO_MAX_LIMIT),
m_bStartPlay(true),
m_dwLastCalcBufSizeTime(0),
m_dwLastRecvAudioTime(0),
m_fRecvRate(0.0f),
m_fRecvFrameRate(0.0f),
m_dwLastPlayRateTime(0),
m_dwSendRate(1000/BUFFER_PERSEC_VIDEO_FRAMES),
m_dwLastPlayTime(0),
m_dwStartPlayTime(0),
m_iStartPlayCount(0),
m_iWillPlayFrameId(0),
m_iSecondStartNum(0),
m_dwStartCalcAudioParam(0),
m_bFilled(false)
{
	try
	{
		BufferTrace("CBufferOutputVideoEngine::CBufferOutputVideoEngine() begin\n");
		MutexLocker m_locker(&m_static_mutex);//�����߳� �����߳� m_mapVideoOutput
		m_mapVideoOutput.insert(make_pair(MakeSession(m_iRoomId,m_iFromUin),this));
	}
	catch (...)
	{
		ErrTrace("CBufferOutputVideoEngine::CBufferOutputVideoEngine() begin Error..........\n");
	}
}

CBufferOutputVideoEngine::~CBufferOutputVideoEngine()
{
		BufferTrace("CBufferOutputVideoEngine::~CBufferOutputVideoEngine() begin\n");
		MutexLocker m_locker(&m_static_mutex);//�����߳� �����߳� m_mapVideoOutput
		map<UInt64,CBufferOutputVideoEngine*>::iterator iter = m_mapVideoOutput.find(MakeSession(m_iRoomId,m_iFromUin));
		if (iter!=m_mapVideoOutput.end()){
			m_mapVideoOutput.erase(iter);
		}
		m_pInPlace = NULL;
		m_pRate = NULL;
		ClearPackets();
}

void CBufferOutputVideoEngine::Initialize(ITransInPlace* pInPlace,IBufferBaseRate* pRate)
{
		m_pInPlace = pInPlace;
		m_pRate = pRate;
		AssertVS(m_pInPlace,0,"CBufferOutputVideoEngine::Initialize m_pInPlace=NULL");
		AssertVS(m_pRate,0,"CBufferOutputVideoEngine::Initialize m_pRate=NULL");
}

void CBufferOutputVideoEngine::UnInitialize()
{
		BufferTrace("CBufferOutputVideoEngine::UnInitialize() \n");
		MutexLocker m_locker(&m_static_mutex);//�����߳� �����߳� m_mapVideoOutput
		map<UInt64,CBufferOutputVideoEngine*>::iterator iter = m_mapVideoOutput.find(MakeSession(m_iRoomId,m_iFromUin));
		if (iter!=m_mapVideoOutput.end()){
			m_mapVideoOutput.erase(iter);
		}
		m_pInPlace = NULL;
		m_pRate = NULL;
		ClearPackets();
}

void CBufferOutputVideoEngine::ClearPackets()
{
		BufferTrace("CBufferOutputVideoEngine::ClearPackets() begin\n");
		MutexLocker locker(&m_mutex);//m_mapOutputVideoBuf buffer�����߳� m_mapFrameToSeq
		map<UInt32,StructVideoBufferPack>::iterator iter = m_mapOutputVideoBuf.begin();
		while (iter!=m_mapOutputVideoBuf.end()){
			BufferTrace("CBufferOutputVideoEngine::ClearPackets() while\n");
			iter->second.m_pPack->RemoveReference();
			iter = m_mapOutputVideoBuf.erase(iter);
		}
}

void CBufferOutputVideoEngine::AddPacket(Packet* pData,UInt32 iSequence)
{
		//BufferTrace("CBufferOutputVideoEngine::AddPacket() begin %d\n",GetTickCount());
		// 	static UInt32 s_iCount = 0;
		// 	if (++s_iCount%80 == 0){//ģ�ⶪ��
		// 		pData->RemoveReference();
		// 		return;
		// 	}
		UInt32 iFrameSeq = 0;
		UInt32 iPieceCount = 0;
		if (!GetFrameSeq(pData,iFrameSeq,iPieceCount)){
			pData->RemoveReference();
			AssertVS(0,m_iFromUin,"CBufferOutputVideoEngine::AddPacket ��Ƶ���ݰ�����ʧ��...");
			return;
		}

		MutexLocker m_locker(&m_mutex);//m_mapOutputVideoBuf buffer�����߳� m_mapFrameToSeq
		map<UInt32,StructVideoBufferPack>::iterator iter;
		if ((iter=m_mapOutputVideoBuf.find(iSequence))!=m_mapOutputVideoBuf.end() || 
			!IsNormalPacket(iFrameSeq,iSequence) || 
			m_mapOutputVideoBuf.size() > BUFFER_OUTPUT_VIDEO_PACKET_MAXLIMIT){
				LostTrace("CBufferOutputVideoEngine �յ���Ч���ݰ�..............%s........���ݰ����峬��=%s,iSequence=%d,time=%d [minSequenceId:%d] [maxSequenceId:%d] [iMinFrameId:%d] [iMaxFrameId:%d]\n",
					m_mapOutputVideoBuf.find(iSequence)!=m_mapOutputVideoBuf.end()?"����":"������",m_mapOutputVideoBuf.size()>BUFFER_OUTPUT_VIDEO_PACKET_MAXLIMIT?"TRUE":"FALSE",iSequence,GetTickCount(),m_iMinSequenceId,m_iMaxSequenceId,m_iMinFrameId,m_iMaxFrameId);
			pData->RemoveReference();
		}else{
			m_lastRecvTime = GetTickCount();

			StructVideoBufferPack svbp;
			svbp.m_iSequence = iSequence;
			svbp.m_pPack = pData;
			svbp.m_iPieceCount = iPieceCount;
			svbp.m_iFrameSeq = iFrameSeq;
			svbp.m_time = GetTickCount();
			m_mapOutputVideoBuf[iSequence] = svbp;

			AddFrameSeq(iFrameSeq);
			AddSequenceId(iSequence);
			UpdateTime(GetTickCount(),iFrameSeq);

			Assert(pData->GetReference()==1);

			map<UInt32,StructVideoFrameSeqToSeq>::iterator iter;
			if ((iter=m_mapFrameToSeq.find(iFrameSeq))!=m_mapFrameToSeq.end()){
				if (iSequence>iter->second.m_maxSequence){
					iter->second.m_maxSequence = iSequence;
				}
			}else{
				StructVideoFrameSeqToSeq struSeq;
				struSeq.m_minSequence = iSequence;
				struSeq.m_maxSequence = iSequence;
				m_mapFrameToSeq[iFrameSeq] = struSeq;
			}
		}
}

void CBufferOutputVideoEngine::AddSequenceId(UInt32 iSequenceId)
{
		//BufferTrace("CBufferOutputVideoEngine::AddSequenceId() %d\n",GetTickCount());
		DWORD dwTime = GetTickCount();
		{
			if (dwTime - m_dwLastLostTime> BUFFER_OUTPUT_BUFFER_SHAKE_LOSTRATE){
				m_dwLastLostTime=GetTickCount();
				if (m_iLostPacketNum+m_iTotalPacketNum!=0)
					m_fLostRate = (float)m_iLostPacketNum /(m_iLostPacketNum+m_iTotalPacketNum);
				//BufferTrace("CBufferOutputVideoEngine::AddSequenceId ���㶪���� -------  m_fLostRate=%f\n",m_fLostRate);
			}

			if (iSequenceId!=m_iMaxSequenceId+1 && m_iMaxSequenceId!=0)
				m_iLostPacketNum  += (iSequenceId - m_iMaxSequenceId-1<10?iSequenceId - m_iMaxSequenceId-1:1) ;
			m_iTotalPacketNum++;
		}

		if (0 == m_iMinSequenceId){
			m_iMinSequenceId = iSequenceId;
		}
		if (iSequenceId>m_iMaxSequenceId){
			m_iMaxSequenceId = iSequenceId;
		}
		else if (!m_bFilled && iSequenceId<m_iMinSequenceId && m_iMinSequenceId-iSequenceId<40)//��ֹ��ʼ��ʱ�������
		{
			m_iMinSequenceId = iSequenceId;
		}
}

void CBufferOutputVideoEngine::AddFrameSeq(UInt32 iFrameId)
{
		//BufferTrace("CBufferOutputVideoEngine::AddFrameSeq() begin %d\n",GetTickCount());
		if (0 == m_iMinFrameId){
			m_iMinFrameId = iFrameId;
		}
		if (iFrameId>m_iMaxFrameId){
			m_iMaxFrameId = iFrameId;
		}
		else if (!m_bFilled && iFrameId<m_iMinFrameId && m_iMinFrameId-iFrameId<40) //��ֹ��ʼ��ʱ�������
		{
			m_iMinFrameId = iFrameId;
		}
}

void CBufferOutputVideoEngine::Play()
{
		//��Ƶ���
		if (!m_bFilled && m_mapOutputVideoBuf.size() < (1.0f*BUFFER_PERSEC_VIDEO_NUMBER*1300)/1000){ //����1.3s������
			return ;
		}

		if (!m_bFilled) {
			m_dwLastPlayTime = GetTickCount();
			m_iStartPlayCount = 0;
			m_bFilled = true;
		}

		//BufferTrace("CBufferOutputVideoEngine::Play().....\n");
		if (m_iMinSequenceId == 0) return;
		if (m_bStartPlay && m_iMinSequenceId>0){
			if (m_dwStartPlayTime==0){
				m_dwStartPlayTime = GetTickCount();
			}
			if (GetTickCount()-m_dwStartPlayTime>BUFFER_VIDEO_PREVIEW_TIME){
				m_bStartPlay = false;
			}
		}
		//���㻺������С
		if (m_pRate){
			if (CanCalcAudioParam()){
				if (m_pInPlace){
					m_iAudioBufferSize = m_pInPlace->GetBufferSize(m_iFromUin,bfAudio);
					m_dwLastRecvAudioTime = m_pInPlace->GetRecvTime(m_iFromUin,bfAudio);
				}else{
					m_dwLastRecvAudioTime = 0;
					m_iAudioBufferSize = BUFFER_OUTPUT_ONMIC_AUDIO_MAX_LIMIT;

					AssertVS(0,m_iFromUin,"CBufferOutputVideoEngine::Play m_pInPlace=NULL");
				}
			}
			m_iBufferSize = m_pRate->CalcBufferSize(
				BUFFER_OUTPUT_ONMIC_VIDEO_MIN_LIMIT, //��������С����ʱ�� - ���� ��С
				BUFFER_OUTPUT_ONMIC_VIDEO_MAX_LIMIT, //��������󻺳�ʱ�� - ���� ���
				BUFFER_OUTPUT_UNMIC_VIDEO_MIN_LIMIT, //��������С����ʱ�� - ���� ��С
				BUFFER_OUTPUT_UNMIC_VIDEO_MAX_LIMIT, //��������󻺳�ʱ�� - ���� ���
				BUFFER_PERSEC_AUDIO_NUMBER,			 //ƽ������
				m_fLostRate,						 //��ǰ������
				m_dwLastCalcBufSizeTime,			 //��һ�μ��㻺����ʱ��
				m_iBufferSize,
				m_iAudioBufferSize,
				m_dwLastRecvAudioTime
				);

			//BufferTrace("���㻺������С m_iBufferSize=%d, lostrate=%f, m_dwLastCalcBufSizeTime=%d,m_iAudioBufferSize=%d,m_dwLastRecvAudioTime=%d\n",
			//	m_iBufferSize,m_fLostRate,m_dwLastCalcBufSizeTime,m_iAudioBufferSize,m_dwLastRecvAudioTime);
		}else{
			AssertVS(0,m_iFromUin,"CBufferOutputVideoEngine::Play m_pRate=NULL");
		}
		
		//���������Ƶ����
		m_fRecvRate = CalcRecevRate();
		m_fRecvFrameRate = CalcRecevFrameRate();
		if (IsCanCalcPlayRate()){
			if (m_pRate){ //���㷢������֡������
				if (m_bStartPlay){
					m_dwSendRate = 1000 / BUFFER_PERSEC_VIDEO_FRAMES;
				}else{
					m_dwSendRate = m_pRate->CalcSendRate(
						m_iBufferSize, //��������С
						(UInt32)m_mapOutputVideoBuf.size(), //�������е�ǰ���ݰ�����
						m_iMaxFrameId - m_iMinFrameId+1,
						m_fRecvRate, //�հ�����
						m_dwSendRate //�ϴμ���ķ�������ʱ������С
						);
				}

				//ErrTrace("CBufferOutputVideoEngine::Play() m_mapOutputVideoBuf.size()=%d,frames=%d,m_fRecvRate=%f,m_fRecvFrameRate=%f,m_dwSendRate=%d\n",m_mapOutputVideoBuf.size(),m_iMaxFrameId - m_iMinFrameId+1,m_fRecvRate,m_fRecvFrameRate,m_dwSendRate);
			}else{
				AssertVS(0,m_iFromUin,"CBufferOutputVideoEngine m_pRate=NULL");
			}
		}
		
		if(m_dwSendRate==0){
			Assert(0);
		}

		//�������� ��֡����
		unsigned int iLoop = 0;
		while (m_dwLastPlayTime < GetTickCount() && m_dwSendRate>0 && iLoop++ <10){
// 			BufferTrace("CBufferOutputVideoEngine::Play() while1 m_mapOutputVideoBuf.size()=%d,m_mapFrameToSeq.size()=%d,m_fRecvRate=%f,m_fRecvFrameRate=%f,m_dwSendRate=%d time=%d�������� %d\n",m_mapOutputVideoBuf.size(),m_mapFrameToSeq.size(),m_fRecvRate,m_fRecvFrameRate,m_dwSendRate,GetTickCount());
 			(m_dwLastPlayTime==0)?(m_dwLastPlayTime=GetTickCount()+m_dwSendRate):(m_dwLastPlayTime += m_dwSendRate);
			m_iStartPlayCount++;
			PlayFrames();
			SwitchToThread();
		}
		RemoveExpireFrame();
		CheckPacket();
		
		if (m_mapOutputVideoBuf.size()==0 && GetTickCount()-m_lastRecvTime>=2000){ //2sû���յ����ݣ�����״̬
			ResetStatus();
		}

		if(GetTickCount()-m_lastRecvTime>=10000){ //10sû���յ����ݣ���buf��������
			ResetStatus();
		}
}

void CBufferOutputVideoEngine::ResetStatus()
{
		BufferTrace("CBufferOutputVideoEngine::ResetStatus() \n");
		MutexLocker locker(&m_mutex); //m_mapOutputVideoBuf buffer�����߳� m_mapFrameToSeq
		m_bFilled = false;
 		//m_lastRecvTime = GetTickCount();
// 		if (m_iMinSequenceId>m_iMaxSequenceId){
// 			m_iCheckSeqId = 0;
// 			m_iMinFrameId = 0;
// 			m_iMaxFrameId = 0;
// 			m_iMinSequenceId = 0;
// 			m_iMaxSequenceId = 0;
// 			m_iPlayFrameId = 0;
// 			m_bStartPlay = true;
// 			m_dwStartPlayTime = 0;
// 		}
		{
			ClearPackets();
			m_mapFrameToSeq.clear();
			m_mapOutputVideoReqInf.clear();
			m_iCheckSeqId = 0;
			m_iMinFrameId = 0;
			m_iMaxFrameId = 0;
			m_iMinSequenceId = 0;
			m_iMaxSequenceId = 0;
			m_iPlayFrameId = 0;
			m_bStartPlay = true;
			m_dwStartPlayTime = 0;
		}
		m_iCheckFrameId = 0;
		m_iTotalPacketNum = 0;
		m_iLostPacketNum = 0;
		m_fLostRate = 0;
		m_dwLastLostTime = GetTickCount();
		m_dwFirstStartTime = 0;
		m_dwSecondStartTime = 0;
		m_dwLostStartTime = 0;
		m_iFirstStartNum = 0;
		m_dwLastRecvRateTime = 0;
		m_iLastRecvRateInter = BUFFER_OUTPUT_RATECALC_MIN_INTERVAL;
		m_iBufferSize = BUFFER_OUTPUT_ONMIC_VIDEO_MAX_LIMIT;
		m_iFirstStartFrameSeq = 0;
		m_iFirstCurFrameSeq = 0;
		m_iSecondStartFrameSeq = 0;
		m_iSecondCurFrameSeq = 0;
		m_iFirstStartFrameNum = 0;
		m_iSecondStartFrameNum = 0;
		m_iAudioBufferSize = BUFFER_OUTPUT_ONMIC_AUDIO_MAX_LIMIT;
		m_dwLastCalcBufSizeTime = 0;
		m_dwLastRecvAudioTime = 0;
		m_fRecvRate = 0.0f;
		m_fRecvFrameRate = 0.0f;
		m_dwLastPlayRateTime=0;
		m_dwSendRate = 1000/BUFFER_PERSEC_VIDEO_FRAMES;
		m_dwLastPlayTime = 0; 
		m_iStartPlayCount = 0;
		m_iWillPlayFrameId = 0;
		m_iSecondStartNum = 0;
		m_dwStartCalcAudioParam = 0;
}

bool CBufferOutputVideoEngine::CanCalcAudioParam()
{
		DWORD dwCurrTime = GetTickCount();
		if (dwCurrTime-m_dwStartCalcAudioParam>BUFFER_OUTPUT_BUFFER_CALC_AUDIO_PARAM){
			m_dwStartCalcAudioParam = dwCurrTime;
			return true;
		}
		return false;
}

void CBufferOutputVideoEngine::RemoveExpireFrame()
{
		//BufferTrace("CBufferOutputVideoEngine::RemoveExpireFrame()\n");
		MutexLocker locker(&m_mutex); //m_mapOutputVideoBuf buffer�����߳� m_mapFrameToSeq
		if (m_iPlayFrameId!=0 && m_iMinFrameId!=0){
			map<UInt32,StructVideoFrameSeqToSeq>::iterator iter;
			while (m_iMinFrameId<m_iPlayFrameId){
				iter = m_mapFrameToSeq.find(m_iMinFrameId);
				if (iter!=m_mapFrameToSeq.end()){
					m_mapFrameToSeq.erase(iter);
				}
				m_iMinFrameId++;
			}
		}
}

void CBufferOutputVideoEngine::CheckPacket()
{
		//BufferTrace("CBufferOutputVideoEngine::CheckPacket()\n");
		//MutexLocker locker(&m_mutex);
		if (m_iCheckSeqId < m_iMinSequenceId) 
			m_iCheckSeqId = m_iMinSequenceId;

		if (m_iCheckSeqId>m_iMaxSequenceId) 
			return;

// 		if (m_bStartPlay) //��ʼ�����󲹳���
// 			return;
		
		unsigned int iMaxSeq = m_iMaxSequenceId-m_iMinSequenceId>BUFFER_PERSEC_VIDEO_NUMBER?m_iMaxSequenceId-5:m_iMaxSequenceId;
		for (UInt32 i = m_iCheckSeqId; i<=iMaxSeq; ){
			if (m_mapOutputVideoBuf.find(i)==m_mapOutputVideoBuf.end()){
				RequestCompenPacket(i,FALSE); //���󲹳�ָ�������Ƶ���ݰ�

				StructVideoRequestInfo sari;
				sari.m_iReqNum = 1;
				sari.m_iSequence = i;
				sari.m_lastTime = GetTickCount();
				m_mapOutputVideoReqInf[i] = sari;
				LostTrace("[RoomId:%12ld] [FromUin:%12ld] [Video-SequenceId:%12ld] [time:%12ld] [-----Request-----] [minSequenceId:%d] [maxSequenceId:%d] [LostPacket:%d] [TotalPacket:%d] [LostRate:%f] %s\n",m_iRoomId,m_iFromUin,i,GetTickCount(),m_iMinSequenceId,m_iMaxSequenceId,m_iLostPacketNum,m_iTotalPacketNum,(float)m_iLostPacketNum/(m_iLostPacketNum+m_iTotalPacketNum),"���󲹳����ݰ�");
			}
			m_iCheckSeqId = ++i;
			SwitchToThread();
		}
		
		DWORD dwInteval = 0;//���󲹳����ݰ�ʱ����
		if (m_pRate){
			dwInteval = m_pRate->CalcRequestCompenInterval(
				m_iBufferSize,(UInt32)m_mapOutputVideoBuf.size(),
				m_fRecvRate);
		}else{
			AssertVS(0,0,"m_pRate->CalcRequestCompenInterval  m_pRate=NULL");
		}
		map<UInt32,StructVideoRequestInfo>::iterator iter=m_mapOutputVideoReqInf.begin();
		while (iter!=m_mapOutputVideoReqInf.end()){//�Ƴ���Ч �� ����ָ����������
			if ((GetTickCount() - iter->second.m_lastTime > dwInteval) && 
				(iter->second.m_iReqNum++>=BUFFER_COMPEN_REQUE_TIMES || iter->first<m_iMinSequenceId)){
				if (m_mapOutputVideoBuf.find(iter->first)==m_mapOutputVideoBuf.end()){
					LostTrace("[RoomId:%12ld] [FromUin:%12ld] [Video-SequenceId:%12ld] [time:%12ld] [-----Delete-----] [request Num:%d] [minSequenceId:%d] [maxSequenceId:%d] [LostPacket:%d] [TotalPacket:%d] [LostRate:%f] %s\n",m_iRoomId,m_iFromUin,iter->first,GetTickCount(),iter->second.m_iReqNum,m_iMinSequenceId,m_iMaxSequenceId,m_iLostPacketNum,m_iTotalPacketNum,(float)m_iLostPacketNum/(m_iLostPacketNum+m_iTotalPacketNum),"�Ƴ���Ч���ݰ�");
				}
				iter = m_mapOutputVideoReqInf.erase(iter);
				SwitchToThread();
				continue;
			}
			//�����ɹ�
			if (m_mapOutputVideoBuf.find(iter->first)!=m_mapOutputVideoBuf.end()){
				LostTrace("[RoomId:%12ld] [FromUin:%12ld] [Video-SequenceId:%12ld] [time:%12ld] [-----Success-----] [request Num:%d] [minSequenceId:%d] [maxSequenceId:%d] [LostPacket:%d] [TotalPacket:%d] [LostRate:%f] %s\n",m_iRoomId,m_iFromUin,iter->first,GetTickCount(),iter->second.m_iReqNum,m_iMinSequenceId,m_iMaxSequenceId,m_iLostPacketNum,m_iTotalPacketNum,(float)m_iLostPacketNum/(m_iLostPacketNum+m_iTotalPacketNum),"���ݰ��Ѿ������ɹ�");
				iter = m_mapOutputVideoReqInf.erase(iter);
				SwitchToThread();
				continue;
			}
			//�������󲹳�
			if (GetTickCount() - iter->second.m_lastTime > dwInteval){
				iter->second.m_lastTime = GetTickCount();
				RequestCompenPacket(iter->first,FALSE);
				SwitchToThread();
				LostTrace("[RoomId:%12ld] [FromUin:%12ld] [Video-SequenceId:%12ld] [time:%12ld] [-----Re Request-----] [request Num:%d] [minSequenceId:%d] [maxSequenceId:%d] [LostPacket:%d] [TotalPacket:%d] [LostRate:%f] %s\n",m_iRoomId,m_iFromUin,iter->first,GetTickCount(),iter->second.m_iReqNum,m_iMinSequenceId,m_iMaxSequenceId,m_iLostPacketNum,m_iTotalPacketNum,(float)m_iLostPacketNum/(m_iLostPacketNum+m_iTotalPacketNum),"���󲹳����ݰ�");
			}
			iter++;
		}
}

void CBufferOutputVideoEngine::RequestCompenPacket(UInt32 iSequenceId,bool bA)
{
		//BufferTrace("CBufferOutputVideoEngine::RequestCompenPacket() begin %d\n",GetTickCount());
		Packet* pPacket = RelayCompenPacket::makePacket(-1,m_iRoomId,m_iFromUin,iSequenceId,bA);
		for (int i=0;i<BUFFER_COMPENSATION_NUMBER;i++)
		{
			pPacket->AddReference();
			UdpChannel::RequestCompenPacket(m_iRoomId,m_iFromUin,pPacket);
		}
}

bool CBufferOutputVideoEngine::GetFrameSeq(Packet* pDataPacket,UInt32& iFrameSeq,UInt32& iPieceCount)
{
		return ParsePack(pDataPacket->getPacketContent(),pDataPacket->getPacketLen(),iFrameSeq,iPieceCount);
}

bool CBufferOutputVideoEngine::ParsePack(const UInt8* pBuf, UInt32 iLen,UInt32& iFrameSeq,UInt32& iPieceCount)
{
		//BufferTrace("CBufferOutputVideoEngine::ParsePack() begin %d\n",GetTickCount());
		Packet tempPacket(-1);
		tempPacket.setContentPtr(const_cast<UInt8*>(pBuf), iLen);

		bool bSucc = false;iPieceCount = 1;
		UInt16  sPacketType = ntohs(*(UInt16*)(&pBuf[2]));
		switch (sPacketType)
		{
		case VIDEO_PACKET_TYPE:
			ParseAllPack(&tempPacket,iFrameSeq,bSucc);
			break;
		case VIDEO_PIECE_PACKET_TYPE:
			ParsePiecePack(&tempPacket,iFrameSeq,iPieceCount,bSucc);
			break;
		default:
			Assert(0);
			break;
		}

		tempPacket.setContentPtr(NULL, 0);
		return bSucc;
}

void CBufferOutputVideoEngine::ParseAllPack(Packet* pPacket,UInt32& iFrameSeq,bool& bSucc)
{
		//BufferTrace("CBufferOutputVideoEngine::ParseAllPack() begin %d\n",GetTickCount());
		VideoPacket videoPacket;
		if (!videoPacket.parserPacket(pPacket)){
			AssertVS(0,m_iFromUin,"CBufferOutputVideoEngine::ParseAllPack ����ʧ��");
			bSucc = false;
			return;
		}

		iFrameSeq = videoPacket.getSeqNum();
		bSucc = true;
		return;
}

void CBufferOutputVideoEngine::ParsePiecePack(Packet* pPacket,UInt32& iFrameSeq,UInt32& iPieceCount,bool& bSucc)
{
		//BufferTrace("CBufferOutputVideoEngine::ParsePiecePack() begin %d\n",GetTickCount());
		VideoPiecePacket PiecePacket;
		if (!PiecePacket.parserPacket(pPacket)){
			AssertVS(0,m_iFromUin,"CBufferOutputVideoEngine::ParsePiecePack ����ʧ��");
			bSucc = false;
			return;
		}

		iFrameSeq = PiecePacket.getSeqNum();
		iPieceCount = PiecePacket.getPieceSum();
		bSucc = true;
		return;
}

bool CBufferOutputVideoEngine::IsNormalPacket(UInt32 iFrameId,UInt32 iSequenceId)
{
		//BufferTrace("CBufferOutputVideoEngine::IsNormalPacket() begin %d\n",GetTickCount());
		if (!m_bFilled && iSequenceId<m_iMinSequenceId && m_iMinSequenceId-iSequenceId<40){
			return true;
		}
		if (iFrameId < m_iMinFrameId-1 && m_iMinFrameId!=0){
			return false;
		}
		if (iSequenceId < m_iMinSequenceId && m_iMinSequenceId!=0 ){
			return false;
		}
		return true;
}

void CBufferOutputVideoEngine::UpdateTime(DWORD dwCurTime,UInt32 iFrameId)//�����հ�����
{
		//BufferTrace("CBufferOutputVideoEngine::UpdateTime() begin\n");
		if (m_pRate)
		{
			//��ȡ �������ʵ�λʱ����
			m_iLastRecvRateInter = m_pRate->GetRateTimeInterval(
				BUFFER_OUTPUT_ONMIC_AUDIO_MIN_LIMIT, //��������С����ʱ�� - ���� ��С
				BUFFER_OUTPUT_ONMIC_AUDIO_MAX_LIMIT, //��������󻺳�ʱ�� - ���� ���
				BUFFER_OUTPUT_UNMIC_AUDIO_MIN_LIMIT, //��������С����ʱ�� - ���� ��С
				BUFFER_OUTPUT_UNMIC_AUDIO_MAX_LIMIT, //��������󻺳�ʱ�� - ���� ���
				m_iBufferSize,
				m_iLastRecvRateInter,
				m_dwLastRecvRateTime
				);

			if (m_iLastRecvRateInter==0){
				Assert(0);
			}

			//BufferTrace("CBufferOutputVideoEngine ����������� ʱ����..m_iLastRecvRateInter=%d\n",m_iLastRecvRateInter);
			DWORD dwCurTimeMinus = GetTickCount();
			if (dwCurTimeMinus - m_dwFirstStartTime > m_iLastRecvRateInter && dwCurTimeMinus - m_dwSecondStartTime > (m_iLastRecvRateInter/2)){
				AssertVS(m_iLastRecvRateInter!=0,m_iFromUin,"CBufferOutputVideoEngine m_iLastRecvRateInter=0");
				m_dwFirstStartTime = dwCurTimeMinus;
				m_iFirstStartNum = 0;
				m_iFirstStartFrameSeq = iFrameId;//��һ��ʼ֡���
				m_iFirstCurFrameSeq = iFrameId;//��һ��ǰ֡���
				m_iFirstStartFrameNum = 1;
			}

			if (dwCurTimeMinus - m_dwFirstStartTime > (m_iLastRecvRateInter / 2) && 
				dwCurTimeMinus - m_dwSecondStartTime > m_iLastRecvRateInter){
				m_dwSecondStartTime = dwCurTimeMinus;
				m_iSecondStartNum = 0;
				m_iSecondStartFrameSeq = iFrameId;//�ڶ���ʼ֡���
				m_iSecondCurFrameSeq = iFrameId;//�ڶ���ǰ֡���
				m_iSecondStartFrameNum = 1;
			}

			if (m_iFirstCurFrameSeq < iFrameId){
				m_iFirstStartFrameNum++;
				m_iFirstCurFrameSeq = iFrameId;
			}
			if (m_iSecondCurFrameSeq < iFrameId){
				m_iSecondStartFrameNum++;
				m_iSecondCurFrameSeq = iFrameId;
			}

			m_iFirstStartNum++;
			m_iSecondStartNum++;

// 			BufferTrace("CBufferOutputVideoEngine::UpdateTime m_iLastRecvRateInter=%d,m_dwFirstStartTime=%d,m_iFirstStartNum=%d,m_dwSecondStartTime=%d,m_iSecondStartNum=%d\n",
// 				m_iLastRecvRateInter,m_dwFirstStartTime,m_iFirstStartNum,m_dwSecondStartTime,m_iSecondStartNum);
		}else{
			AssertVS(0,0,"CBufferOutputVideoEngine::UpdateTime m_pRate=NULL");
		}
}

float CBufferOutputVideoEngine::CalcRecevRate()
{
		//BufferTrace("CBufferOutputVideoEngine::CalcRecevRate() begin %d\n",GetTickCount());
		DWORD dwCurTimeMinus = GetTickCount();
		if (dwCurTimeMinus-m_dwFirstStartTime<BUFFER_OUTPUT_RATECALC_MIN_INTERVAL/2 && 
			dwCurTimeMinus-m_dwSecondStartTime<BUFFER_OUTPUT_RATECALC_MIN_INTERVAL/2){
			return 0.0f;
		}
		if (dwCurTimeMinus - m_dwFirstStartTime > dwCurTimeMinus - m_dwSecondStartTime){
			return (float)m_iFirstStartNum * 1000 / (dwCurTimeMinus - m_dwFirstStartTime+1);
		}else{
			return (float)m_iSecondStartNum * 1000 / (dwCurTimeMinus - m_dwSecondStartTime+1);
		}
}

float CBufferOutputVideoEngine::CalcRecevFrameRate()
{
		//BufferTrace("CBufferOutputVideoEngine::CalcRecevFrameRate() begin %d\n",GetTickCount());
		DWORD dwCurTimeMinus = GetTickCount();
		if (dwCurTimeMinus-m_dwFirstStartTime<BUFFER_OUTPUT_RATECALC_MIN_INTERVAL/2 && 
			dwCurTimeMinus-m_dwSecondStartTime<BUFFER_OUTPUT_RATECALC_MIN_INTERVAL/2){
			return 0.0f;
		}
		if (dwCurTimeMinus - m_dwFirstStartTime > dwCurTimeMinus - m_dwSecondStartTime){
			return (float)m_iFirstStartFrameNum * 1000 / (dwCurTimeMinus - m_dwFirstStartTime+1);
		}else{
			return (float)m_iSecondStartFrameNum * 1000 / (dwCurTimeMinus - m_dwSecondStartTime+1);
		}
}

bool CBufferOutputVideoEngine::IsCanCalcPlayRate()
{
		//BufferTrace("CBufferOutputVideoEngine::IsCanCalcPlayRate() begin %d\n",GetTickCount());
		DWORD dwTime = GetTickCount();
		UInt32 iDataCount = (UInt32)m_mapOutputVideoBuf.size();
		if (iDataCount * 1000 /BUFFER_PERSEC_VIDEO_NUMBER <  m_iBufferSize - 120 
			|| iDataCount * 1000 /BUFFER_PERSEC_VIDEO_NUMBER > m_iBufferSize + 120){
			m_dwLastPlayRateTime = dwTime;
			return true;
		}
		if (dwTime - m_dwLastPlayRateTime > BUFFER_OUTPUT_PLAYRATE_CAL_INTERVAS){
			m_dwLastPlayRateTime = dwTime;
			return true;
		}else{
			return false;
		}
}

void CBufferOutputVideoEngine::PlayPackets()
{
		//BufferTrace("CBufferOutputVideoEngine::PlayPackets() \n");
		Packet* pPacket = NULL;
		while (m_iMinSequenceId<=m_iMaxSequenceId && m_iMaxSequenceId>0)
		{
			pPacket = GetPlayPacket(m_iMinSequenceId++);
			if (m_iWillPlayFrameId!=0){
				if (pPacket){
					try{
						UdpChannel::PlayVideoPacket(m_iRoomId,m_iFromUin,pPacket);
						Assert(pPacket->GetReference()==1);
					}catch (...){
						AssertVS(0,0,"CBufferOutputVideoEngine::PlayPackets()�쳣");
					}
					pPacket->RemoveReference();
					SwitchToThread();
					if (m_iWillPlayFrameId>m_iPlayFrameId) break;
				}else{
					break; //��ǰ֡�Ѿ�����
				}
			}
			SwitchToThread();
		}
}

void CBufferOutputVideoEngine::PlayFrames()
{
		//BufferTrace("CBufferOutputAudioEngine	m_iMinFrameId=%d,m_iMaxFrameId=%d,m_iPlayFrameId=%d,m_iMinSequenceId=%d,m_iMaxSequenceId=%d,m_iCheckSeqId=%d\n",m_iMinFrameId,m_iMaxFrameId,m_iPlayFrameId,m_iMinSequenceId,m_iMaxSequenceId,m_iCheckSeqId);
		DWORD dwStart = GetTickCount();
		if(m_iPlayFrameId<m_iMinFrameId){
			m_iPlayFrameId = m_iMinFrameId;
		}
		if (m_iPlayFrameId>m_iMaxFrameId){
			return;
		}
		PlayPackets();
		m_iPlayFrameId++;
		//BufferTrace("CBufferOutputVideoEngine m_iMinFrameId=%d,m_iMaxFrameId=%d,m_iPlayFrameId=%d,m_iMinSequenceId=%d,m_iMaxSequenceId=%d,m_iCheckSeqId=%d,time=%d\n",m_iMinFrameId,m_iMaxFrameId,m_iPlayFrameId,m_iMinSequenceId,m_iMaxSequenceId,m_iCheckSeqId,GetTickCount()-dwStart);
}

Packet* CBufferOutputVideoEngine::GetPlayPacket(UInt32 iSequenceId)//��ȡ��ǰ���ŵ����ݰ�
{
		//BufferTrace("CBufferOutputVideoEngine::GetPlayPacket() begin %d\n",GetTickCount());
		MutexLocker locker(&m_mutex);//m_mapOutputVideoBuf buffer�����߳� m_mapFrameToSeq
		m_iWillPlayFrameId = 0;
		map<UInt32,StructVideoBufferPack>::iterator iter=m_mapOutputVideoBuf.find(iSequenceId);
		if (iter!=m_mapOutputVideoBuf.end()){
			Packet* pPacket = iter->second.m_pPack;
			m_iWillPlayFrameId = iter->second.m_iFrameSeq;
			m_mapOutputVideoBuf.erase(iter);
			return pPacket;
		}else{
			LostTrace("[RoomId:%12ld] [FromUin:%12ld] [Video-SequenceId:%12ld] [time:%12ld] [-----Play Lost-----] [minSequenceId:%d] [maxSequenceId:%d] [LostPacket:%d] [TotalPacket:%d] [LostRate:%f] %s\n",m_iRoomId,m_iFromUin,iSequenceId,GetTickCount(),m_iMinSequenceId,m_iMaxSequenceId,m_iLostPacketNum,m_iTotalPacketNum,(float)m_iLostPacketNum/(m_iLostPacketNum+m_iTotalPacketNum),"��Ƶ���ݰ���ʧ");
			return NULL;
		}
}

bool	CBufferOutputVideoEngine::IsCanRemove()
{
		return (GetTickCount() - m_lastRecvTime> BUFFER_MEDIA_EXPIRE_TIME)?true:false;
}