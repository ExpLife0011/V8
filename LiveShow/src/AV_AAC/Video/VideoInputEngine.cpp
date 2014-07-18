#include "StdAfx.h"
#include "VideoInputEngine.h"
#include "TimersManager.h"
#include "AVEngine.h"
#include "VideoRateControl.h"
#include "Global.h"
#include "VideoOutputEngine.h"
#include "./crc/Crc32.h"

#define    FIVE_FRAME_EVERY_SECOND                  200
#define    EIGHT_FRAME_EVERY_SECOND                 125
#define    TEN_FRAME_EVERY_SECOND					100
#define    TWELVE_FRAME_EVERY_SECOND                 83




Mutex VideoInputEngine::m_Mutex;//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
std::map<UInt32, RCPtr<VideoInputEngine> > VideoInputEngine::m_VInputEngineMap;
std::map<UInt32, RCPtr<VideoInputEngine> > VideoInputEngine::m_VideoInputEngineRoomMap;
UInt32 VideoInputEngine::m_iCaptureTimerID = 0;
bool VideoInputEngine::m_bViewFFTME = TRUE;
VideoInputEngine::VideoInputEngine(void)
					:m_iDeviceID(0),
					m_iQuality(3),
					m_iWidth(320),
					m_iHeight(240),
#ifdef SELF_TWELVE_FRAME									  //���ò�������
					m_lTimePeriod(TWELVE_FRAME_EVERY_SECOND), //Ĭ��12֡ÿ��
#endif
#ifdef SELF_TEN_FRAME
					m_lTimePeriod(TEN_FRAME_EVERY_SECOND), //Ĭ��ÿ��10֡  ����Ч��
#endif
#ifdef SELF_EIGHT_FRAME
					m_lTimePeriod(EIGHT_FRAME_EVERY_SECOND), //Ĭ�� ÿ��8֡
#endif
#ifdef SELF_FIVE_FRAME
					m_lTimePeriod(FIVE_FRAME_EVERY_SECOND), //Ĭ�� ÿ��5֡	
#endif

					m_bStart(false),
					m_pVideoEncoder(NULL),
					m_pVideoCapture(NULL),
					m_pVideoDecoder(NULL),
					m_pVideoData(NULL),
					m_bIsInit(false),
					m_bInitKey(false),
					m_bShowRealVideo(false),
					m_iDecoderWidth(640),
					m_iDecoderHeight(480),
					m_iVideoMode(-1),
					m_enumCamerStatus(kVideo_Success),
					m_enType(VIDEO_PRIV_MIC),
					m_bNet(false)
{
	Trace("VideoOutputEngine::VideoInputEngine() ��ʼ�� time = %I64d \n",GetTickCount());
}

VideoInputEngine::~VideoInputEngine(void)
{
	SAFE_DELETE(m_pVideoEncoder);
	SAFE_DELETE(m_pVideoCapture);
	SAFE_DELETEA(m_pVideoData);
	SAFE_DELETE(m_pVideoDecoder);
	m_pVideoEncoder = NULL;
	m_pVideoCapture = NULL;
	m_pVideoData=NULL;
	m_pVideoDecoder = NULL;
	Trace("VideoOutputEngine::~VideoInputEngine() ���� time = %I64d \n",GetTickCount());
}

void  VideoInputEngine::Init(UInt32 iWidth, UInt32 iHeight, UInt32 iQuality, SInt32 iDeviceID,UInt32 iVideoMode/* = (UInt32)ROOM_VIDEO_CRF_MODE*/)
{
	Trace("VideoOutputEngine::Init() time = %I64d \n",GetTickCount());
	m_iQuality = iQuality;
	m_iWidth   = iWidth;
	m_iHeight  = iHeight;
	m_iDeviceID = iDeviceID;
	m_iVideoMode = iVideoMode;

	if (320==m_iWidth) //320*240
	{
#ifdef SELF_TWELVE_FRAME 
		m_lTimePeriod = TWELVE_FRAME_EVERY_SECOND; //Ĭ��12֡ÿ��
#endif
#ifdef SELF_TEN_FRAME
		m_lTimePeriod = TEN_FRAME_EVERY_SECOND; //Ĭ��ÿ��10֡  ����Ч��
#endif
#ifdef SELF_EIGHT_FRAME
		m_lTimePeriod = EIGHT_FRAME_EVERY_SECOND; //Ĭ�� ÿ��8֡
#endif
#ifdef SELF_FIVE_FRAME
		m_lTimePeriod = FIVE_FRAME_EVERY_SECOND; //Ĭ�� ÿ��5֡	
#endif
	}
	else
	{
		m_lTimePeriod = EIGHT_FRAME_EVERY_SECOND; //8֡
	}

	SAFE_DELETEA(m_pVideoData);
	m_pVideoData = new UInt8[m_iWidth*m_iHeight*3];

	m_bIsInit = true;
}

void VideoInputEngine::InitDecoder(UInt32 iWidth/*=640*/, UInt32 iHeight/*=480*/)
{
	Trace("VideoOutputEngine::InitDecoder() time = %I64d \n",GetTickCount());
	m_iDecoderWidth = iWidth;
	m_iDecoderHeight = iHeight;
}

RCPtr<VideoInputEngine>	VideoInputEngine::Create(SInt32 iDeviceID)
{
	Trace("VideoOutputEngine::Create() iDeviceID=%d time = %I64d \n",iDeviceID,GetTickCount());
	MutexLocker locker(&m_Mutex); //timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	std::map<UInt32, RCPtr<VideoInputEngine> >::iterator iter;
	if (m_VInputEngineMap.find(iDeviceID)!=m_VInputEngineMap.end())
	{
		iter = m_VInputEngineMap.find(iDeviceID);
		return iter->second;
	}
	else
	{
		RCPtr<VideoInputEngine> pVInput(new VideoInputEngine());
		m_VInputEngineMap.insert(vinput_pair(iDeviceID, pVInput));
		return pVInput;

	}
}

void VideoInputEngine::AppendRoom(SInt32 iDeviceID,SInt32 iRoomId)
{
	Trace("VideoOutputEngine::AppendRoom() iDeviceID=%d time = %I64d \n",iDeviceID,GetTickCount());
	m_VideoInputEngineRoomMap.insert(vinputroom_pair(iRoomId,Create(iDeviceID)));
}

void VideoInputEngine::RemoveAppendRoom(SInt32 iRoomId)
{
	Trace("VideoOutputEngine::RemoveAppendRoom() iRoomId=%d time = %I64d \n",iRoomId,GetTickCount());
	MutexLocker locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	std::map<UInt32, RCPtr<VideoInputEngine> >::iterator iter;
	if ((iter=VideoInputEngine::m_VideoInputEngineRoomMap.find(iRoomId))!=VideoInputEngine::m_VideoInputEngineRoomMap.end())
	{
		if (!VideoInputEngine::IsDeviceUsed(iter->second->GetDeviceID(),iRoomId) && !iter->second->IsExistsUsed())
		{
			VideoInputEngine::RemoveInputEngine(iter->second->GetDeviceID());
		}
	}
	if (m_VideoInputEngineRoomMap.find(iRoomId)!=m_VideoInputEngineRoomMap.end())
	{
		m_VideoInputEngineRoomMap.erase(m_VideoInputEngineRoomMap.find(iRoomId));
	}
}

void VideoInputEngine::RemoveAppendDevice(SInt32 iDeviceId)
{
	Trace("VideoOutputEngine::RemoveAppendDevice() iDeviceId=%d time = %I64d \n",iDeviceId,GetTickCount());
	MutexLocker locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	std::map<UInt32, RCPtr<VideoInputEngine> >::iterator iter;
	for (iter=m_VideoInputEngineRoomMap.begin();iter!=m_VideoInputEngineRoomMap.end();)
	{
		if (iter->second->GetDeviceID() == iDeviceId)
		{
			iter=m_VideoInputEngineRoomMap.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

bool VideoInputEngine::IsDeviceUsed(SInt32 iDeviceId)
{
	Trace("VideoOutputEngine::IsDeviceUsed() iDeviceId=%d time = %I64d \n",iDeviceId,GetTickCount());
	MutexLocker locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	std::map<UInt32, RCPtr<VideoInputEngine> >::iterator iter;
	for (iter=m_VideoInputEngineRoomMap.begin();iter!=m_VideoInputEngineRoomMap.end();iter++)
	{
		if (iter->second->GetDeviceID() == iDeviceId)
		{
			return true;
		}
	}
	return false;
}

RCPtr<VideoInputEngine>	VideoInputEngine::FindAppendRoom(SInt32 iRoomId)
{
	Trace("VideoOutputEngine::FindAppendRoom() iRoomId=%d time = %I64d \n",iRoomId,GetTickCount());
	//MutexLocker locker(&m_Mutex);
	RCPtr<VideoInputEngine> pVInput(NULL);
	std::map<UInt32, RCPtr<VideoInputEngine> >::iterator iter = m_VideoInputEngineRoomMap.find(iRoomId);
	if (iter!=m_VideoInputEngineRoomMap.end())
	{
		return iter->second;
	}
	return pVInput;
}

void VideoInputEngine::RemoveAllAppendRoom()
{
	Trace("VideoOutputEngine::RemoveAllAppendRoom() time = %I64d \n",GetTickCount());
	MutexLocker locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds

	m_VideoInputEngineRoomMap.clear();
}

void  VideoInputEngine::RemoveInputEngine(SInt32 iDeviceID)
{
	Trace("VideoOutputEngine::RemoveInputEngine() iDeviceID=%d time = %I64d \n",iDeviceID,GetTickCount());
	MutexLocker locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	if (m_VInputEngineMap.find(iDeviceID)!=m_VInputEngineMap.end())
	{
		m_VInputEngineMap.find(iDeviceID)->second->StopCapture(true);
	}
	if (m_VInputEngineMap.find(iDeviceID)!=m_VInputEngineMap.end())
	{
		m_VInputEngineMap.erase(m_VInputEngineMap.find(iDeviceID));
	}
	
}

RCPtr<VideoInputEngine>	VideoInputEngine::FindInputEngine(SInt32 iDeviceID)
{
	Trace("VideoOutputEngine::FindInputEngine() iDeviceID=%d time = %I64d \n",iDeviceID,GetTickCount());
	//MutexLocker locker(&m_Mutex);
	RCPtr<VideoInputEngine> pVInput(NULL);
	std::map<UInt32, RCPtr<VideoInputEngine> >::iterator iter;
	if (m_VInputEngineMap.find(iDeviceID)!=m_VInputEngineMap.end())
	{
		iter = m_VInputEngineMap.find(iDeviceID);
		return iter->second;
	}
	return pVInput;
}

void VideoInputEngine::RemoveAllInputEngine()
{
	Trace("VideoOutputEngine::RemoveAllInputEngine() time = %I64d \n",GetTickCount());
	MutexLocker locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	std::map<UInt32, RCPtr<VideoInputEngine> >::iterator iter;
	for (iter=m_VInputEngineMap.begin();iter!=m_VInputEngineMap.end();++iter)
	{
		iter->second->StopCapture(true);
	}
	m_VInputEngineMap.clear();
}

void  VideoInputEngine::Destroy()
{
	Trace("VideoOutputEngine::Destroy() time = %I64d \n",GetTickCount());

	// ֹͣ��Ƶ�ɼ�
	//	StopCapture(true);

	// ������صĴ�����Դ
	{
		MutexLocker locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
		for (UInt32 i=0; i<m_SelfWnds.size(); ++i)
		{
			delete m_SelfWnds[i];
			m_SelfWnds[i] = NULL;
		}
		m_SelfWnds.clear();

		for (UInt32 i=0; i<m_PauseSelfWnds.size(); ++i)
		{
			delete m_PauseSelfWnds[i];
			m_PauseSelfWnds[i] = NULL;
		}
		m_PauseSelfWnds.clear();
	}
}

void VideoInputEngine::SetType(enuVIDEO_TYPE enType)
{
	m_enType = enType;
	if (m_pVideoEncoder)
		m_pVideoEncoder->SetType(m_enType);
}

bool  VideoInputEngine::StartCapture(UInt32 &iResult)
{
	Trace("VideoOutputEngine::StartCapture() time = %I64d \n",GetTickCount());
	MutexLocker locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	Trace("VideoEngine::StartCapture() deviceid = %d \n", m_iDeviceID);

	if (m_bStart)
	{
		return true;
	}

	if (!m_bStart)
	{
		//���´���������
		SAFE_DELETE(m_pVideoEncoder);
// #ifdef  XVID
// 		m_pVideoEncoder = new xvidCodec();
// #endif
// #ifdef  H264
// 		m_pVideoEncoder = new h264Codec();
// #endif
// 
// 		if (!m_pVideoEncoder->Init(0, m_iWidth, m_iHeight, m_iQuality,m_enType,(enuROOM_AV_VIDEO_MODE)m_iVideoMode))
// 		{
// 			Assert(0);
// 		}

		
		SAFE_DELETE(m_pVideoDecoder)
		m_pVideoDecoder = new h264Codec;
		if (!m_pVideoDecoder->Init(1, this->m_iDecoderWidth, this->m_iDecoderHeight, this->m_iQuality,m_enType,(enuROOM_AV_VIDEO_MODE)this->m_iVideoMode))
		{
			Assert(0);
			SAFE_DELETE(m_pVideoCapture);
			return false;
		}
		
		//��ʼ��Ƶ��׽
		SAFE_DELETE(m_pVideoCapture);
		m_pVideoCapture = new CVideoDeviceCapDx();
		m_enumCamerStatus = kVideo_Success;
		if (!m_pVideoCapture->Init(m_iWidth, m_iHeight, iResult, m_iDeviceID))
		{
			switch(iResult)
			{
			case kResult_Success:
				m_enumCamerStatus = kVideo_Success;
				break;
			case kResult_NoCamer:
				m_enumCamerStatus = kVideo_NoCamer;
				break;
			case kResult_NoExist:
				m_enumCamerStatus = kVideo_NoExist;
				break;
			case kResult_IsUsing:
				m_enumCamerStatus = kVideo_IsUsing;
				break;
			case kResult_Failed:
				m_enumCamerStatus = kVideo_Failed;
				break;
			default:
				break;
			}
			Assert(0);
			SAFE_DELETE(m_pVideoCapture);
			return false;
		}
		if (0==m_iCaptureTimerID)
		{
			CaptureTimer* pCapTimer = new CaptureTimer();
			TimersManager* pTimersManager   = TimersManager::getInstance();
			Assert(pTimersManager!=NULL);
			m_iCaptureTimerID= pTimersManager->registerTimerHandler(0, m_lTimePeriod, pCapTimer);
			Assert(m_iCaptureTimerID>0);
		}
		m_bStart =true;
	}

	return true;
}

bool  VideoInputEngine::StopCapture(bool bForce)
{
	Trace("VideoOutputEngine::StopCapture() bForce=%d time = %I64d \n",bForce,GetTickCount());
	MutexLocker  locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	Trace("VideoEngine::StopCapture() [bStart = %d] \n", m_bStart?1:0);
	if (!m_bStart)
	{
		return true;
	}

	if (!bForce)
	{
		if (!m_SelfWnds.empty() || !m_PauseSelfWnds.empty())
		{
			//��ʱ����ֹͣ��Ƶ
			Assert(0);
			return false;
		}
	}

	m_SelfWnds.clear();
	m_PauseSelfWnds.clear();

	Trace("VideoEngine::StopCapture() mid\n");
	if (m_bStart)
	{
		m_bStart = false;
		if (m_iCaptureTimerID!=0 && m_VInputEngineMap.size()==0)
		{
			Trace("VideoInputEngine::StopCapture removeTimerHandler \n");
			Assert(0);
			TimersManager* pTimersManager   = TimersManager::getInstance();
			pTimersManager->removeTimerHandler(m_iCaptureTimerID, false);
			m_iCaptureTimerID = 0;
		}
		SAFE_DELETE(m_pVideoCapture);
		SAFE_DELETE(m_pVideoEncoder);
	}
	Trace("VideoEngine::StopCapture() end\n");
	return true;
}


void  VideoInputEngine::AddLocalHwnd(HWND hLocalWnd,UInt32 iRoomId,bool bFFTWav)
{
	Trace("VideoOutputEngine::AddLocalHwnd() iRoomId=%d time = %I64d \n",iRoomId,GetTickCount());
	MutexLocker locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	for (UInt32 i=0; i<m_SelfWnds.size(); ++i)
	{
		if (m_SelfWnds[i]->GetHwnd()==hLocalWnd)
		{
			//�Ѿ��иþ����ֱ�ӷ���
			return;
		}
	}

	DIBSection* pDibSection = new DIBSection;
	pDibSection->Create(hLocalWnd, m_iWidth, m_iHeight, 3,bFFTWav);
	pDibSection->SetViewFFT(bFFTWav);
	pDibSection->SetRoomId(iRoomId);
	m_SelfWnds.push_back(pDibSection);
}

void VideoInputEngine::ChangeLocalHwnd(HWND hNewLocalWnd,HWND hOldLocalWnd)
{
	Trace("VideoOutputEngine::ChangeLocalHwnd() time = %I64d \n",GetTickCount());
	MutexLocker locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	bool bEncodeVideo = false;
	bool bViewFFT = false;
	unsigned int iRoomId = 0;
	std::vector<DIBSection*>::iterator iter;
	for (iter=m_SelfWnds.begin(); iter!=m_SelfWnds.end(); ++iter)
	{
		DIBSection* pDibSection = *iter;
		if (hOldLocalWnd == pDibSection->GetHwnd())
		{
			bEncodeVideo = pDibSection->IsShowEncodeVideo();
			bViewFFT = pDibSection->IsViewFFT();
			iRoomId = pDibSection-> GetRoomId();
			delete pDibSection;
			m_SelfWnds.erase(iter);
			break;
		}
	}

	//�����ͣ�ı��ش���
	for (iter=m_PauseSelfWnds.begin(); iter!=m_PauseSelfWnds.end(); ++iter)
	{
		DIBSection* pDibSection = *iter;
		if (hOldLocalWnd == pDibSection->GetHwnd())
		{
			bEncodeVideo = pDibSection->IsShowEncodeVideo();
			bViewFFT = pDibSection->IsViewFFT();
			iRoomId = pDibSection-> GetRoomId();
			delete pDibSection;
			m_PauseSelfWnds.erase(iter);
			break;
		}
	}

	for (UInt32 i=0; i<m_SelfWnds.size(); ++i)
	{
		if (m_SelfWnds[i]->GetHwnd()==hNewLocalWnd)
		{
			//�Ѿ��иþ����ֱ�ӷ���
			return;
		}
	}

	DIBSection* pDibSection = new DIBSection;
	if (bEncodeVideo)
	{
		pDibSection->Create(hNewLocalWnd, this->m_iDecoderWidth, this->m_iDecoderHeight, 3,bViewFFT);
	}
	else
	{
		pDibSection->Create(hNewLocalWnd, m_iWidth, m_iHeight, 3,bViewFFT);
	}
	
	pDibSection->SetShowEncodeVide(bEncodeVideo);
	pDibSection->SetRoomId(iRoomId);
	m_SelfWnds.push_back(pDibSection);
}

bool VideoInputEngine::SetVideoDecoder(HWND hLocalWnd,bool bEnable)
{
	Trace("VideoOutputEngine::SetVideoDecoder() time = %I64d \n",GetTickCount());
	MutexLocker  locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	bool bRet = false;
	std::vector<DIBSection*>::iterator iter;
	if (bEnable && !m_bShowRealVideo)
	{
		if (NULL == m_pVideoDecoder)
		{
#ifdef XVID
			m_pVideoDecoder = new xvidCodec;
#endif
#ifdef H264
			m_pVideoDecoder = new h264Codec;
#endif
			m_pVideoDecoder->Init(1, this->m_iDecoderWidth, this->m_iDecoderHeight, this->m_iQuality,m_enType,(enuROOM_AV_VIDEO_MODE)this->m_iVideoMode);
		}
	}
	if (!m_bShowRealVideo)
	{
		m_bShowRealVideo = bEnable;
	}
	for (iter=m_SelfWnds.begin(); iter!=m_SelfWnds.end(); ++iter)
	{
		DIBSection* pDibSection = *iter;
		if (hLocalWnd == pDibSection->GetHwnd())
		{
			if (bEnable)
			{
				pDibSection->Create(pDibSection->GetHwnd(),this->m_iDecoderWidth, this->m_iDecoderHeight,3,pDibSection->IsViewFFT());
			}
			else
			{
				pDibSection->Create(pDibSection->GetHwnd(),this->m_iWidth, this->m_iHeight,3,pDibSection->IsViewFFT());
			}
			pDibSection->SetShowEncodeVide(bEnable);
			bRet = true;
		}
	}
	return bRet;
}

bool VideoInputEngine::IsVideoDecoder(HWND hLocalWnd)
{
	Trace("VideoOutputEngine::IsVideoDecoder() time = %I64d \n",GetTickCount());
	std::vector<DIBSection*>::iterator iter;
	MutexLocker  locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	for (iter=m_SelfWnds.begin(); iter!=m_SelfWnds.end(); ++iter)
	{
		DIBSection* pDibSection = *iter;
		if (hLocalWnd == pDibSection->GetHwnd())
		{
			return pDibSection->IsShowEncodeVideo();
		}
	}
	return false;
}

bool VideoInputEngine::PaintLocal(HWND hWnd)
{
	Trace("VideoOutputEngine::PaintLocal() time = %I64d \n",GetTickCount());
	std::vector<DIBSection*>::iterator iter;
	MutexLocker locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	for (iter=m_SelfWnds.begin(); iter!=m_SelfWnds.end(); ++iter)
	{
		DIBSection* pDibSection = *iter;
		if (hWnd == pDibSection->GetHwnd())
		{
			if (!pDibSection->IsPhotoable()) return false;

			HDC hdc = ::GetWindowDC(pDibSection->GetHwnd());
			pDibSection->Paint(hdc, 0, 0);
			if (g_struct.po && m_bViewFFTME && VideoOutputEngine::m_bViewFFTALL && pDibSection->IsViewFFT() && !g_struct.IsRoomAudioPause(pDibSection->GetRoomId()))
			{
				g_struct.po->Draw(pDibSection->GetHwnd(),hdc);
			}
			::ReleaseDC(pDibSection->GetHwnd(), hdc);
			return true;
		}
	}

// 	//�����ͣ�ı��ش���
// 	for (iter=m_PauseSelfWnds.begin(); iter!=m_PauseSelfWnds.end(); ++iter)
// 	{
// 		DIBSection* pDibSection = *iter;
// 		if (hWnd == pDibSection->GetHwnd())
// 		{
// 			HDC hdc = ::GetWindowDC(pDibSection->GetHwnd());
// 			pDibSection->Paint(hdc, 0, 0);
// 			if (g_struct.po && m_bViewFFTME && VideoOutputEngine::m_bViewFFTALL && pDibSection->IsViewFFT() && !g_struct.IsRoomAudioPause(pDibSection->GetRoomId()))
// 			{
// 				g_struct.po->Draw(pDibSection->GetHwnd(),hdc);
// 			}
// 			::ReleaseDC(pDibSection->GetHwnd(), hdc);
// 			return true;
// 		}
// 	}
	return false;
}

void  VideoInputEngine::DelLocalHwnd(HWND hLocalWnd)
{
	CocTrace("VideoInputEngine::DelLocalHwnd\n");
	std::vector<DIBSection*>::iterator iter;
	MutexLocker locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	for (iter=m_SelfWnds.begin(); iter!=m_SelfWnds.end(); ++iter)
	{
		DIBSection* pDibSection = *iter;
		if (hLocalWnd == pDibSection->GetHwnd())
		{
			delete pDibSection;
			m_SelfWnds.erase(iter);
			CocTrace("VideoInputEngine::DelLocalHwnd 1\n");
			break;
		}
	}

	//�����ͣ�ı��ش���
	for (iter=m_PauseSelfWnds.begin(); iter!=m_PauseSelfWnds.end(); ++iter)
	{
		DIBSection* pDibSection = *iter;
		if (hLocalWnd == pDibSection->GetHwnd())
		{
			delete pDibSection;
			m_PauseSelfWnds.erase(iter);
			CocTrace("VideoInputEngine::DelLocalHwnd 2\n");
			break;
		}
	}
}

void VideoInputEngine::PauseLocalHwnd(HWND hLocalWnd)
{
	Trace("VideoOutputEngine::PauseLocalHwnd() time = %I64d \n",GetTickCount());
	DIBSection* pDibSection = NULL;
	std::vector<DIBSection*>::iterator iter;
	MutexLocker locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	for (iter=m_SelfWnds.begin(); iter!=m_SelfWnds.end(); ++iter)
	{
		if (hLocalWnd == (*iter)->GetHwnd())
		{
			pDibSection = *iter;
			m_SelfWnds.erase(iter);
			break;
		}
	}

	if (pDibSection)
	{
		m_PauseSelfWnds.push_back(pDibSection);
	}
}

void  VideoInputEngine::ContinueLocalHwnd(HWND hLocalWnd)
{
	Trace("VideoOutputEngine::ContinueLocalHwnd() time = %I64d \n",GetTickCount());
	DIBSection* pDibSection = NULL;
	std::vector<DIBSection*>::iterator iter;
	MutexLocker locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds
	for (iter=m_PauseSelfWnds.begin(); iter!=m_PauseSelfWnds.end(); ++iter)
	{
		if (hLocalWnd == (*iter)->GetHwnd())
		{
			pDibSection = *iter;
			m_PauseSelfWnds.erase(iter);
			break;
		}
	}

	if (pDibSection)
	{
		m_SelfWnds.push_back(pDibSection);
	}
}


bool  VideoInputEngine::IsPhotoableLocalHwnd(HWND hLocalWnd)
{
	Trace("VideoOutputEngine::IsPhotoableLocalHwnd() time = %I64d \n",GetTickCount());
	MutexLocker  locker(&m_Mutex);//timer �����߳�  m_VInputEngineMap  m_VideoInputEngineRoomMap m_SelfWnds m_PauseSelfWnds

	for (UInt32 i=0; i<m_SelfWnds.size(); ++i)
	{
		if (m_SelfWnds[i]->GetHwnd()==hLocalWnd && m_SelfWnds[i]->IsPhotoable())
		{
			return true;
		}
	}

	return false;
}


void  VideoInputEngine::CaptureAndEncodeVideo()
{
	//MutexLocker locker(&m_Mutex);  //�������ܻ���������

	if (!m_bStart)
	{
		return;
	}

	if (m_pVideoCapture == NULL || !m_pVideoCapture->GetData(m_pVideoData, m_iWidth*m_iHeight*3))
	{
		return;
	}
	
	Trace("VideoEngine::CaptureAndEncodeVideo(): �ɼ���ͼ������ time = %I64d \n",GetTickCount());
	
	std::vector<HWND> vAllLocalHwnds;
	bool bSendData = false;
	bool bEnCode = false;
	
	//1 �ڱ������еĴ�������ʾ
	if (!m_SelfWnds.empty())
	{
		bSendData = true;
		if (g_struct.po && m_bViewFFTME && VideoOutputEngine::m_bViewFFTALL)
		{
			g_struct.po->Process();
		}
		for (UInt32 i=0; i<m_SelfWnds.size(); ++i)
		{
			vAllLocalHwnds.push_back(m_SelfWnds[i]->GetHwnd());
			if (m_SelfWnds[i]->IsShowEncodeVideo())
			{
				bEnCode = true; 
			}
			if (m_bShowRealVideo  && m_pVideoDecoder && m_SelfWnds[i]->IsShowEncodeVideo())	continue;
			m_SelfWnds[i]->SetImage(m_pVideoData, m_iWidth, m_iHeight, 3);
			HDC hdc = ::GetWindowDC(m_SelfWnds[i]->GetHwnd());
			m_SelfWnds[i]->Paint(hdc, 0, 0);
			if (g_struct.po && m_bViewFFTME && VideoOutputEngine::m_bViewFFTALL && m_SelfWnds[i]->IsViewFFT() && !g_struct.IsRoomAudioPause(m_SelfWnds[i]->GetRoomId()))
			{
				g_struct.po->Draw(m_SelfWnds[i]->GetHwnd(),hdc);
			}
			::ReleaseDC(m_SelfWnds[i]->GetHwnd(), hdc);
		}
	}	
	
// 	//û����Ҫ��ѹ����ʾ�ı��ش���
// 	if (!bEnCode)
// 	{
// 		return;
// 	}
	
	//����Ҫ���紫��
	if (!m_bNet)
	{
		SAFE_DELETE(m_pVideoEncoder);
		return;
	}
	else
	{
		if (!m_pVideoEncoder)
		{
			m_pVideoEncoder = new h264Codec();

			if (!m_pVideoEncoder->Init(0, m_iWidth, m_iHeight, m_iQuality,m_enType,(enuROOM_AV_VIDEO_MODE)m_iVideoMode))
			{
				Assert(0);
			}
		}
	}

	//2 ��������
	int  iEncLen =0;
	int iFinal =0;
	unsigned char cKey = FALSE;  //�Ƿ�Ϊ�ؼ���
	bool bStop = false;
	
	if (m_pVideoEncoder == NULL || !m_pVideoEncoder->EncodeVideoData(m_pVideoData, 
			m_iWidth*m_iHeight*3, m_pVideoEncoder->GetBuffer(), &iEncLen, &cKey,bStop))
	{
		//Assert(0);
		AssertVS(m_pVideoEncoder!=NULL,cKey,"EncodeVideoData...");
		return;
	}
		
	++(m_pVideoEncoder->m_iCurSeqNum);

	if ((cKey & KEY_VALUE) == KEY_VALUE)
	{
		//���õ�ǰ�ؼ�֡�����
		m_pVideoEncoder->m_iCurKeySeqNum = m_pVideoEncoder->m_iCurSeqNum;
		if (m_bShowRealVideo && !m_bInitKey) 
			m_bInitKey = true;
	}
	
	if (m_bShowRealVideo && m_bInitKey && m_pVideoDecoder && !m_SelfWnds.empty())
	{
		h264Codec* pDecoder = m_pVideoDecoder;
		bool bFlag = false;
		if (m_pVideoEncoder->m_iCurSeqNum > pDecoder->m_iCurSeqNum)
		{
			if ((cKey & KEY_VALUE) == KEY_VALUE)
			{
				if (pDecoder->m_iCurKeySeqNum >= m_pVideoEncoder->m_iCurKeySeqNum)
				{
					//�ùؼ�֡�Ѿ�����
					Assert(0);
					Trace("VideoEngine::CaptureAndEncodeVideo(): �ؼ�֡���� time = %I64d \n",GetTickCount());
					return;
				}

				pDecoder->m_iCurKeySeqNum = m_pVideoEncoder->m_iCurKeySeqNum;
				pDecoder->m_iCurSeqNum = m_pVideoEncoder->m_iCurSeqNum;
				if (m_bShowRealVideo && !m_bInitKey)  
					m_bInitKey = true;
			}
			else
			{
				if (m_pVideoEncoder->m_iCurSeqNum!=pDecoder->m_iCurSeqNum+1)
				{
					bFlag = true;
				}
				else
				{
					pDecoder->m_iCurSeqNum = m_pVideoEncoder->m_iCurSeqNum;
				}
			}	

			BAD_MEM_READ(m_pVideoEncoder->GetBuffer(),iEncLen,"VideoEngine::CaptureAndEncodeVideo()")
			BAD_MEM_WRITE(pDecoder->GetBuffer(),208*156*3,"VideoEngine::CaptureAndEncodeVideo()")

			m_dibRectCalc.Initialize();
			for (UInt32 i=0; i<m_SelfWnds.size(); ++i)
			{
				if (m_bShowRealVideo && m_bInitKey && m_pVideoDecoder && m_SelfWnds[i]->IsShowEncodeVideo())
				{
					m_dibRectCalc.AddHWnd(m_SelfWnds[i]->GetHwnd());
				}
			}

			//����ʵ�ʴ�С�Ŵ�ͼƬ
			CRect rcWindow = m_dibRectCalc.GetRectInfo();
			Assert(rcWindow.Width()>=224 && rcWindow.Height()>=168);
			pDecoder->DeChangeInit(rcWindow.Width(),rcWindow.Height());
			
// 			static unsigned int s_keyCount = 0; //�ؼ�֡
// 			static unsigned int s_pCount = 0;//P֡
// 			static unsigned int s_bCount = 0;//B֡
// 			static unsigned int s_oCount = 0;//����֡
// 			static bool waitforkey = false;
// 			static bool bReset = false;
// 			switch(m_pVideoEncoder->GetEncodeType())
// 			{
// 			case X264_TYPE_IDR://�ؼ�֡
// 				{
// 					s_keyCount = 0;
// 					s_pCount = 0;
// 					s_bCount = 0;
// 					waitforkey = false;
// 				}
// 				break;
// 			case X264_TYPE_P:
// 				{
// 					s_pCount = 0;
// 					s_bCount = 0;
// 					s_keyCount++;
// 					if (waitforkey)
// 					{
// 						bReset = true;
// 					}
// 					waitforkey = false;
// 				}
// 				break;
// 			case X264_TYPE_B:
// 				{
// 					s_bCount++;
// 					s_pCount++;
// 					s_keyCount++;
// 					if (waitforkey)
// 					{
// 						ErrTrace("+++++++++++++++++++++++++++����B+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
// 					}
// 
// 				}
// 				break;
// 			default://����
// 				{
// 					s_oCount ++;
// 				}
// 
// 			}
// 
// 			if (s_keyCount>1 && s_pCount==0)
// 			{
// 				waitforkey = true;
// 			}
// 			if (bReset)
// 			{
// 				waitforkey = false;
// 				bReset = false;
// 			}
// 			
// 			if (waitforkey)
// 			{
// 				return;
// 			}
// 			switch(m_pVideoEncoder->GetEncodeType())
// 			{
// 				case X264_TYPE_IDR://�ؼ�֡
// 				{
// 					ErrTrace("��ǰ����type=X264_TYPE_IDR\n");
// 				}
// 				break;
// 				case X264_TYPE_P://p֡
// 				{
// 					ErrTrace("��ǰ����type=X264_TYPE_P\n");
// 				}
// 				break;
// 				case X264_TYPE_B:
// 				{
// 					Trace("��ǰ����type=X264_TYPE_B\n");
// 				}
// 				break;
// 				case X264_TYPE_AUTO:
// 				{
// 					ErrTrace("��ǰ����type=X264_TYPE_AUTO\n");
// 				}
// 				break;
// 				case X264_TYPE_I:
// 				{
// 					ErrTrace("��ǰ����type=X264_TYPE_I\n");
// 				}
// 				break;
// 				case X264_TYPE_BREF:
// 				{
// 					ErrTrace("��ǰ����type=X264_TYPE_BREF\n");
// 				}
// 				break;
// 				case X264_TYPE_KEYFRAME:
// 				{
// 					ErrTrace("��ǰ����type=X264_TYPE_KEYFRAME\n");
// 				}
// 				break;
// 				default:
// 				{
// 					ErrTrace("��ǰ����type=����\n");
// 				}
// 			}
			if (bEnCode)
			{
				int err = 0;
				if(!bFlag && pDecoder->DecodeVideoData(m_pVideoEncoder->GetBuffer(), iEncLen, pDecoder->GetBuffer(), iFinal,err, bFlag))
				{
					// 				if (g_struct.po && m_bViewFFTME && VideoOutputEngine::m_bViewFFTALL)
					// 				{
					// 					g_struct.po->Process();
					// 				}
					//��ʾԶ���û�������ʵ��Ч��ͼ��
					for (UInt32 i=0; i<m_SelfWnds.size(); ++i)
					{
						if (m_bShowRealVideo && m_bInitKey && m_pVideoDecoder && m_SelfWnds[i]->IsShowEncodeVideo())
						{
							m_SelfWnds[i]->SetImage(pDecoder->GetBuffer(), pDecoder->GetWidth(), pDecoder->GetHeight(), 3);
							HDC hdc = ::GetWindowDC(m_SelfWnds[i]->GetHwnd());
							m_SelfWnds[i]->Paint(hdc, 0, 0);
							if (g_struct.po && m_bViewFFTME && VideoOutputEngine::m_bViewFFTALL && m_SelfWnds[i]->IsViewFFT() && !g_struct.IsRoomAudioPause(m_SelfWnds[i]->GetRoomId()))
							{
								g_struct.po->Draw(m_SelfWnds[i]->GetHwnd(),hdc);
							}
							::ReleaseDC(m_SelfWnds[i]->GetHwnd(), hdc);
						}
					}
				}
				else
				{
					Trace("VideoEngine::CaptureAndEncodeVideo(): ����ʧ�� time = %I64d \n",GetTickCount());
				}
			}
		}
	}
	
	if (bStop)
	{
		--(m_pVideoEncoder->m_iCurSeqNum);
		if (m_pVideoDecoder)
		m_pVideoDecoder->m_iCurSeqNum = m_pVideoEncoder->m_iCurSeqNum;
		return;
	}

	if (bSendData)
	{
		//ErrTrace("��ǰҪ����ͼ������[�ؼ�֡=%d, iSeqNum=%d, KeySeqNum=%d, Len = %d]  time = %I64d\n", (cKey & KEY_VALUE)/*((cKey & KEY_VALUE) == KEY_VALUE?1:0)*/, m_pVideoEncoder->m_iCurSeqNum, m_pVideoEncoder->m_iCurKeySeqNum, iEncLen,GetTickCount());
	
#ifndef IGNOR_CRC_CHECK
		static ClsCrc32 s_Crc32;
		*(DWORD*)(m_pVideoEncoder->GetBuffer()+iEncLen) = s_Crc32.Crc(m_pVideoEncoder->GetBuffer(),iEncLen);
		iEncLen = iEncLen+sizeof(DWORD);
#endif
		//......haosl
		g_AVEngine.SendVideoData(m_pVideoEncoder->GetBuffer(), iEncLen, cKey, m_pVideoEncoder->m_iCurSeqNum, m_pVideoEncoder->m_iCurKeySeqNum, vAllLocalHwnds);
	}
}

#include <atlbase.h>
#include <qedit.h>
#include <control.h>
#include <uuids.h>
#include <streams.h>

//ö�����е���Ƶ�豸
void  VideoInputEngine::EnumVideoDevices(std::vector<std::wstring> &vDeviceName)
{
	MutexLocker l(&g_inputVideoMutex);
	HRESULT hr=E_FAIL;

	//	CoInitialize(NULL);

	// create an enumerator
	CComPtr< ICreateDevEnum > pCreateDevEnum;
	hr = pCreateDevEnum.CoCreateInstance( CLSID_SystemDeviceEnum );
	ASSERT(pCreateDevEnum);
	if(  hr!=S_OK || !pCreateDevEnum )
		return;

	// enumerate video capture devices
	CComPtr< IEnumMoniker > pEm;
	hr = pCreateDevEnum->CreateClassEnumerator( CLSID_VideoInputDeviceCategory, &pEm, 0 );
	if(  hr!=S_OK || !pEm )
		return;

	pEm->Reset();

	if (!g_bIsDeviceInit){ 
		g_mapVideoInputIdGuid.clear();
		g_mapVideoInputGuidName.clear();
		g_mapVideoInputIdStatus.clear();
	}else{
		g_mapVideoInputIdStatus.clear();
	}
	while( 1 )
	{
		ULONG ulFetched = 0;
		CComPtr< IMoniker > pM;

		hr = pEm->Next( 1, &pM, &ulFetched );
		if( hr != S_OK )
			break;

		// get the property bag interface from the moniker
		CComPtr< IPropertyBag > pBag;
		hr = pM->BindToStorage( 0, 0, IID_IPropertyBag, (void**) &pBag );
		if( hr != S_OK )
			continue;

		// ask for the english-readable name
		//
		CComVariant var;
		var.vt = VT_BSTR;
		hr = pBag->Read( L"FriendlyName", &var, NULL );
		if( hr != S_OK )
			continue;

		CComVariant varGuid;
		varGuid.vt = VT_BSTR;
		hr = pBag->Read( L"CLSID", &varGuid, NULL );
		if( hr != S_OK )
			continue;

		hr=pBag->Read( L"DevicePath", &varGuid, NULL );

		if (!g_bIsDeviceInit){
			g_mapVideoInputIdGuid.insert(make_pair(g_maxVideoInputId++,std::wstring(varGuid.bstrVal)));
			g_mapVideoInputGuidName.insert(make_pair(std::wstring(varGuid.bstrVal),std::wstring(var.bstrVal)));
			g_mapVideoInputIdStatus.insert(make_pair(g_maxVideoInputId-1,1));
		}else{
			bool bFind = false;
			std::wstring str = varGuid.bstrVal;
			std::map<unsigned int,std::wstring>::iterator iter;
			for (iter=g_mapVideoInputIdGuid.begin();iter!=g_mapVideoInputIdGuid.end();iter++)
			{
				if (str.compare(iter->second)==0){
					g_mapVideoInputIdStatus[iter->first] = 1;
					bFind = true;
					break;
				}
			}
			if (!bFind){
				g_mapVideoInputIdGuid.insert(make_pair(g_maxVideoInputId++,str));
				g_mapVideoInputGuidName.insert(make_pair(str,std::wstring(var.bstrVal)));
				g_mapVideoInputIdStatus[g_maxVideoInputId-1] = 1;
			}
		}
		vDeviceName.push_back(std::wstring(var.bstrVal));
	}
	g_bIsDeviceInit = true;
	//	CoUninitialize();

	return;
}

//unicode=>ansi
std::string UnicodeToAscii(const std::wstring& wide)
{
	int nNeedChars = WideCharToMultiByte( CP_ACP, 0, wide.c_str(), -1, 0, 0, 0, 0 );
	if (nNeedChars>0)//�ٴ��ж�һ��
	{	
		std::vector<char> temp(nNeedChars);
		::WideCharToMultiByte( CP_ACP, 0, wide.c_str(), -1, &temp[0], nNeedChars, 0, 0 );
		return std::string(&temp[0]);
	}

	return std::string();
}

void VideoInputEngine::EnumVideoDeviceInfo(int &iDeviceNum,Service_Video_Info struDeviceInfo[])
{
	MutexLocker l(&g_inputVideoMutex);
	memset(&struDeviceInfo[0],0,sizeof(Service_Video_Info)*MAX_VIDEO_DEVICE_NUM);
	HRESULT hr=E_FAIL;
	iDeviceNum = 0;

	//	CoInitialize(NULL);

	// create an enumerator
	CComPtr< ICreateDevEnum > pCreateDevEnum;
	hr = pCreateDevEnum.CoCreateInstance( CLSID_SystemDeviceEnum );
	ASSERT(pCreateDevEnum);
	if( hr!=S_OK || !pCreateDevEnum)
		return;

	// enumerate video capture devices
	CComPtr< IEnumMoniker > pEm;
	hr = pCreateDevEnum->CreateClassEnumerator( CLSID_VideoInputDeviceCategory, &pEm, 0 );
	if( hr!=S_OK|| !pEm)
		return;

	pEm->Reset();

	if (!g_bIsDeviceInit){ 
		g_mapVideoInputIdGuid.clear();
		g_mapVideoInputGuidName.clear();
		g_mapVideoInputIdStatus.clear();
	}else{
		g_mapVideoInputIdStatus.clear();
	}
	unsigned int icount = 0;
	while( 1 )
	{
		ULONG ulFetched = 0;
		CComPtr< IMoniker > pM;

		hr = pEm->Next( 1, &pM, &ulFetched );
		if( hr != S_OK )
			break;

		// get the property bag interface from the moniker
		CComPtr< IPropertyBag > pBag;
		hr = pM->BindToStorage( 0, 0, IID_IPropertyBag, (void**) &pBag );
		if( hr != S_OK || !pBag)
			continue;

		// ask for the english-readable name
		//
		CComVariant var;
		var.vt = VT_BSTR;
		hr = pBag->Read( L"FriendlyName", &var, NULL );
		if( hr != S_OK )
			continue;

		CComVariant varGuid;
		varGuid.vt = VT_BSTR;
		hr = pBag->Read( L"CLSID", &varGuid, NULL );
		if( hr != S_OK )
			continue;
		hr=pBag->Read( L"DevicePath", &varGuid, NULL );

		if (!g_bIsDeviceInit){
			g_mapVideoInputIdGuid.insert(make_pair(g_maxVideoInputId++,std::wstring(varGuid.bstrVal)));
			g_mapVideoInputGuidName.insert(make_pair(std::wstring(varGuid.bstrVal),std::wstring(var.bstrVal)));
			g_mapVideoInputIdStatus.insert(make_pair(g_maxVideoInputId-1,1));
			ErrTrace("�״γ�ʼ����ȡ����Ƶ�豸 Id=%d,GUID=%s,friendlyname=%s\n",g_maxVideoInputId-1,UnicodeToAscii(std::wstring(varGuid.bstrVal)).c_str(),UnicodeToAscii(std::wstring(var.bstrVal)).c_str());
		}else{
			bool bFind = false;
			std::wstring str = varGuid.bstrVal;
			std::map<unsigned int,std::wstring>::iterator iter;
			for (iter=g_mapVideoInputIdGuid.begin();iter!=g_mapVideoInputIdGuid.end();iter++)
			{
				if (str.compare(iter->second)==0){
					ErrTrace("�����豸GUID Id=%d,GUID=%s,friendlyname=%s\n",iter->first,UnicodeToAscii(std::wstring(varGuid.bstrVal)).c_str(),UnicodeToAscii(std::wstring(var.bstrVal)).c_str());
					g_mapVideoInputIdStatus[iter->first] = 1;
					bFind = true;
					break;
				}
			}
			if (!bFind){
				ErrTrace("�������豸GUID�����ҵ��豸 Id=%d,GUID=%s,friendlyname=%s\n",g_maxVideoInputId-1,UnicodeToAscii(std::wstring(varGuid.bstrVal)).c_str(),UnicodeToAscii(std::wstring(var.bstrVal)).c_str());
				g_mapVideoInputIdGuid.insert(make_pair(g_maxVideoInputId++,str));
				g_mapVideoInputGuidName.insert(make_pair(str,std::wstring(var.bstrVal)));
				g_mapVideoInputIdStatus[g_maxVideoInputId-1] = 1;
			}
		}
	}
	std::map<unsigned int,unsigned int>::iterator iterStatus;
	std::map<std::wstring,std::wstring>::iterator iterGuidName;
	std::map<unsigned int,std::wstring>::iterator iterIdGuid;
	for (unsigned int k = 0;k<g_maxVideoInputId;k++){
		iterStatus = g_mapVideoInputIdStatus.find(k);
		if (iterStatus!=g_mapVideoInputIdStatus.end()){
			if (iterStatus->second==1){
				iterIdGuid = g_mapVideoInputIdGuid.find(k);	
				if (iterIdGuid!=g_mapVideoInputIdGuid.end()){
					iterGuidName = g_mapVideoInputGuidName.find(iterIdGuid->second);
					if (iterGuidName!=g_mapVideoInputGuidName.end()){
						wstring strGuid = iterGuidName->first;
						wstring strName = iterGuidName->second;
						Service_Video_Info svi;
						svi.iDeviceId = k;
						wcsncpy_s(&svi.wsDeviceGUID[0],MAX_VIDEO_DEVICE_GUID_LEN,strGuid.c_str(),min(strGuid.length(),MAX_VIDEO_DEVICE_GUID_LEN-1));
						wcsncpy_s(&svi.wsDeviceName[0],DEVICE_NAME_LEN,strName.c_str(),min(strName.length(),DEVICE_NAME_LEN-1));
						memcpy_s(&struDeviceInfo[icount++],sizeof(Service_Video_Info),&svi,sizeof(Service_Video_Info));
						ErrTrace("�����豸�б� Id=%d,GUID=%s,friendlyname=%s\n",k,UnicodeToAscii(strGuid).c_str(),UnicodeToAscii(strName).c_str());
						iDeviceNum++;
					}else{
						ErrTrace("VideoInputEngine::EnumVideoDeviceInfo GUID-Nameӳ��û�ҵ��豸��~Id=%d\n",k);
					}
				}else{
					ErrTrace("VideoInputEngine::EnumVideoDeviceInfo Id-GUIDӳ��û�ҵ��豸��~Id=%d\n",k);
				}
			}else{
				ErrTrace("VideoInputEngine::EnumVideoDeviceInfo �������豸��~Id=%d\n",k);
			}
		}else{
			ErrTrace("VideoInputEngine::EnumVideoDeviceInfo ȱʧ�豸��~Id=%d\n",k);
		}
	}
	g_bIsDeviceInit = true;
	//	CoUninitialize();

	return;
}

bool VideoInputEngine::IsVideoVirtualDevice(int iDevId)
{
	MutexLocker l(&g_inputVideoMutex);
	std::wstring strGuid = CVideoDeviceCapDx::GetCapDeviceGuid(iDevId);
	HRESULT hr=E_FAIL;

	// create an enumerator
	CComPtr< ICreateDevEnum > pCreateDevEnum;
	hr = pCreateDevEnum.CoCreateInstance( CLSID_SystemDeviceEnum );

	ASSERT(pCreateDevEnum);
	if(  hr!=S_OK || !pCreateDevEnum )
		return false;

	// enumerate video capture devices
	CComPtr< IEnumMoniker > pEm;
	hr = pCreateDevEnum->CreateClassEnumerator( CLSID_VideoInputDeviceCategory, &pEm, 0 );
	if(  hr!=S_OK || !pEm )
		return false;

	pEm->Reset();

	UINT number = 0; 
	while( number++<g_maxVideoInputId )
	{
		ULONG ulFetched = 0;
		CComPtr< IMoniker > pM;

		hr = pEm->Next( 1, &pM, &ulFetched );
		if( hr != S_OK )
			break;

		// get the property bag interface from the moniker
		CComPtr< IPropertyBag > pBag;
		hr = pM->BindToStorage( 0, 0, IID_IPropertyBag, (void**) &pBag );
		if( hr != S_OK )
			continue;

		// ask for the english-readable name
		//
		CComVariant var;
		var.vt = VT_BSTR;
		hr = pBag->Read( L"FriendlyName", &var, NULL );
		if( hr != S_OK )
			continue;

		CComVariant varGuid;
		varGuid.vt = VT_BSTR;
		hr = pBag->Read( L"CLSID", &varGuid, NULL );
		if( hr != S_OK )
			continue;

		hr=pBag->Read( L"DevicePath", &varGuid, NULL );
		wstring strg = varGuid.bstrVal;
		if(!strGuid.empty() && strg.compare(strGuid)!=0){
			continue;
		}
		if( hr != S_OK )
		{
			return true;
		}
		if (var.bstrVal == NULL)
		{
			return true;
		}
		return false;
	}

	return false;
}

bool  VideoInputEngine::ShowVideoAdjustDlg(HWND hParWnd, UInt32 iDeviceID)
{
	// get capture device 
	CComPtr< IBaseFilter > pCap;
	unsigned int iCamCount = 0;
	HRESULT hr = CVideoDeviceCapDx::GetCapDevice(iDeviceID, &pCap,iCamCount);
	if(E_FAIL==hr)
	{
		Assert(0);
		return false;
	}

	if (!pCap)
	{
		Assert(0);
		return false;
	}

	CComPtr< ISpecifyPropertyPages > pSpec;
	hr = pCap->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pSpec);
	if (S_OK != hr)
	{
		Assert(0);
		return false;
	}

	if (!pSpec)
	{
		Assert(0);
		return false;
	}

	CAUUID cauuid = {0};
	hr = pSpec->GetPages(&cauuid);
	if (S_OK != hr)
	{
		Assert(0);
		return false;
	}

	BSTR bstrText = ::SysAllocString(L"��Ƶ����");

	hr = OleCreatePropertyFrame(hParWnd, 30, 30, bstrText, 1, (IUnknown **)&pCap, 
		cauuid.cElems, (GUID *)cauuid.pElems, 0, 0, NULL);

	::SysFreeString(bstrText);
	::CoTaskMemFree(cauuid.pElems);

	return true;
}

bool VideoInputEngine::IsOtherUsed(HWND hWnd)
{
	std::vector<DIBSection*>::iterator iter;
	for (iter=m_SelfWnds.begin(); iter!=m_SelfWnds.end(); ++iter)
	{
		DIBSection* pDibSection = *iter;
		if (hWnd != pDibSection->GetHwnd())
		{
			return true;
		}
	}

	//�����ͣ�ı��ش���
	for (iter=m_PauseSelfWnds.begin(); iter!=m_PauseSelfWnds.end(); ++iter)
	{
		DIBSection* pDibSection = *iter;
		if (hWnd != pDibSection->GetHwnd())
		{
			return true;
		}
	}
	return false;
}

bool VideoInputEngine::IsExistsUsed()
{
	if (m_SelfWnds.size()>0 || m_PauseSelfWnds.size()>0)
	{
		return true;
	}
	return false;
}

bool VideoInputEngine::IsDeviceUsed(SInt32 iDeviceID,SInt32 iRoomId)
{
	bool bRet = false;
	std::map<UInt32,RCPtr<VideoInputEngine>>::iterator iter;
	for(iter=m_VideoInputEngineRoomMap.begin();iter!=m_VideoInputEngineRoomMap.end();++iter)
	{
		if (iRoomId != iter->first)
		{
			if (iter->second->GetDeviceID() == iDeviceID)
			{
				bRet = true;
				break;
			}
		}
	}
	return bRet;
}

Enum_Camera_Status VideoInputEngine::GetCamerStatus()
{
	if (m_pVideoCapture)
	{
		return m_pVideoCapture->m_enumCamerStatus;
	}
	return m_enumCamerStatus;
}
