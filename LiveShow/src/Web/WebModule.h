// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� WEBSERVICE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// WEBSERVICE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#include "51ktv.h"
#include "webdefine.h"
#include "RequestManager.h"
#include <map>
#include "HttpClient.h"
#include "ResponseParser.h"
#include "imodulemanager.h"
#include "coredefine.h"
#include "imodule.h"
#include "log.h"

using namespace std;
using namespace webinterface;

extern "C" 
{
	__declspec( dllexport ) IModule *  GetModule();
	__declspec( dllexport ) void  ReleaseModule();
}

inline uint32	CALLSERVICE(ModuleId moduleId, param wparam, param lparam);
void			PUSH_MESSAGE( EventValue event_value, param param0, param param1,param param2);
void			PUSH_EVENT( Event& event_);
core::CurInfo	GetCurInfo();


struct IModuleManager;
class  WebModule : public IModule
{
public:
	WebModule(void);
	~WebModule(void);

	virtual void	Load(IModuleManager *);
	virtual void	Unload();
	virtual void	ProcessEvent(Event const &);
	virtual void	ProcessMessage(Message const & );
	virtual void	PushEvent_( Event* event_);
	virtual void	PaybackExtraInfo(uint32  ,void *  );
	virtual int32	Invoke(param const ,param lparam);

	
	wstring	GetLogPath(uin nUin);

	/**
	 * outImagePath  �Ǵ����ͼƬ�ı���·�������·�������ڣ�����Զ�����	
	 */
	bool	ProcessImage( wstring inImagePath, wstring& outImagePath);

private:
	//=================================================================
	//            �ڲ�������
	//=================================================================
	
	static uint32 ProcessReqGetUpdateConfigXml( WebModule* pModule, Event* pEvent);
	static uint32 ProcessGetFilterWords( WebModule* pModule, Event* pEvent);	
	static uint32 ProcessReqUploadHeadImage(WebModule* pModule,  Event*	pEvent);
	static uint32 ProcessReqDownloadHeadImage(WebModule* pModule,  Event*	pEvent);
	static uint32 ProcessReqGetFileReq( WebModule* pModule, Event*	pEvent);
	static uint32 ProcessReqQueryDownloadProcess( WebModule* pModule, Event* pEvent);	
	static uint32 ProcessReqGetHttp( WebModule* pModule, Event* pEvent);	
	static uint32 ProcessCancelHttpTask( WebModule* pModule, Event* pEvent);		
	static uint32 ProcessGetLoginIdentifyCode( WebModule* pModule, Event* pEvent);
	/** 
	 * ��Ϣ������
	 */
	void	OnMessagePreLoginResp( Message const& _message);
	void	OnMessageOffline( );

	// ��ȡ�ض������URL��Ҫ�ӳٷ��͵�ʱ��
	void	ProcessGetResponse();
	void	ProcessSendUrl( );
	bool	ProcessHeadImage( wstring wstrImagePath, wstring& wstrOutputPath);


public:	
	IModuleManager*		m_pModuleManager;
	CRequestManager*	m_pRequestManager;				// ��HTTP����Ĺ����������̨��Web��������������

	map<int32, Event*>	m_mapRequestEvent;				// ��¼�û������Event
	
	bool				m_bLogout;						// �Ƿ��Ѿ����������߲���

	std::map<uint32, uint32>	m_mapSeqNo2ModuleId;	//	�������к���ģ��ID�Ķ�Ӧ��ϵ

	// ������ָ��
	typedef uint32 (*CallHandler)( WebModule* pParser, Event* pEvent );

	typedef struct _HanderTable
	{
		EventValue		m_nEventValue;		//	��Ӧ���¼�ֵ
		CallHandler		m_hHandler;			//	������

	} HandlerTableEntry;
	static HandlerTableEntry m_tableDriven[];
};

namespace webinterface
{
	extern WebModule*	g_WebModule;
	EXTERN_LOG();
}