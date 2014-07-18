#include "VideoRateControl.h"
#include "AvDefine.h"
#ifndef Video_Device_CapDx_h
#define Video_Device_CapDx_h
#include "RC.h"
#ifndef SELF_CONTROL_VIDEO
#define MAX_VIDEO_FRAME_RATE  12
#else
#define MAX_VIDEO_FRAME_RATE  30
#endif


#include <atlbase.h>
#include <qedit.h>
#include <control.h>
#include <map>
#include "Mutex.h"

enum
{
	kResult_Success  = 0,
	kResult_NoCamer  = 1,
	kResult_NoExist  = 2,
	kResult_IsUsing  = 3,
	kResult_Failed   = 4
};

class CCapGrabberCB;
class CVideoDeviceCapDx 
{
public:
	CVideoDeviceCapDx();
	virtual ~CVideoDeviceCapDx();

	bool             Init(int iwidth, int iheight, UInt32 &iResult, int iDeviceID);
	void             Destroy();
	bool             GetData(unsigned char *pv,int len);
	static HRESULT   GetCapDevice(UINT no, IBaseFilter** ppCap,UINT& num);
	static std::wstring GetCapDeviceGuid(UINT no);
	Enum_Camera_Status	   m_enumCamerStatus;
protected:
	int              PutData(char *pv,int len);

	HWND                                              m_hDeviceCapWnd;//��׽���ھ��
	
	CComPtr<IGraphBuilder>                            m_pGraph;      //filter�������  

    CComPtr< ISampleGrabber>                          m_pGrabber;    //��������

	CComQIPtr< IMediaControl, &IID_IMediaControl>     m_pControl;    //������

	CComPtr<ICaptureGraphBuilder2>                    m_pCGB2; 
	
	IAMStreamConfig *                                 m_pVSC;         //���Ʋɼ��ĸ�ʽ 

	int                    m_nDeviceID;
	bool                   m_bInit;
	int                    m_nHeight;
	int                    m_nWidth;
	unsigned char*         mpBuffer;
	bool                   mbGotData;
	volatile DWORD         m_dwGraphTime;   //�ϴβɼ�����ʱ��
	volatile DWORD         m_dwLastReset;   //�ϴ�����ʱ��
	volatile bool          m_bReset;

	Mutex                  m_Mutex;
protected:

	friend class CCapGrabberCB;
	static std::map<int,CCapGrabberCB*> m_grabberMap;
	typedef std::pair<int, CCapGrabberCB* > m_grabberPair;

	HRESULT           InitGraph(UInt32 &iResult);//��ʼ���ɼ���������
	void              DestroyGraph();//���ٲɼ���������
	bool			  ResetGraph();
};

extern std::map<unsigned int,std::wstring> g_mapVideoInputIdGuid;  //id<----->guid
extern std::map<std::wstring,std::wstring> g_mapVideoInputGuidName;//guid<----->friendname
extern std::map<unsigned int,unsigned int> g_mapVideoInputIdStatus;//id<----->status
extern unsigned int g_maxVideoInputId;//��ǰ����DeviceId
extern Mutex g_inputVideoMutex;
extern bool g_bIsDeviceInit;

#endif // Video_Device_CapDx_h
