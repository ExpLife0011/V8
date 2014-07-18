#include "stdafx.h"
#include "Event.h"
#include "AsyncCom.h"
#include "Thread.h"
#include "ThreadsManager.h"
#include "IOThread.h"
#include "MyAssert.h"

using namespace std;

HWND						 AsyncCom::s_hMsgWindow		= NULL;		//��Ϣ���ڵľ��;
SInt32						 AsyncCom::s_iWndAtom		= 0;		//���� WndClass Name �����ظ� 


//////////////////////////////////////////////////////////////////////////
//
void AsyncCom::initialize()
{
	s_iWndAtom = (unsigned)time( NULL );
}

//////////////////////////////////////////////////////////////////////////
//
void AsyncCom::destroy()
{
	::DestroyWindow(s_hMsgWindow);
	char szClassName[32] = {0};
	sprintf_s( szClassName, 32, "%s%d", "AsyncComWindow", s_iWndAtom );
	UnregisterClass( szClassName, NULL );//(LPCTSTR)s_theWndAtom, NULL );//"AsyncComWindow", NULL );
}

//////////////////////////////////////////////////////////////////////////
//
//����һ��Socket�ϵ��¼���
//���룺Socket���ļ���������
//�����ASYNCCOM_SUCESSED ��ʾ����ɹ�;
//	    ASYNCCOM_FAILED ��ʾ����ʧ��;
//#ifdef WIN32
Bool   AsyncCom::requestEvent(SInt32 iFd, SInt32 iUniqueID, UInt32 iEventMask)
{
	 Bool bRet(1);
	 Assert(iEventMask!=0);
	 SInt32		iRet	=	0;
	 SInt32		iIndex  =   0;

	//�����Socket�ϵ������¼�;
	 SInt32	iEvent	=	0;
	 SInt32	iMsg	=   0;
	 if(iEventMask&0x0000ffff)
	 {
		if(iEventMask&kSocketReadableEvent)
		{
			iEvent |= FD_READ;
		}
		iEvent	|= FD_CLOSE;
		iIndex  = iUniqueID%  ThreadsManager::s_pIOThread->m_iTotalSocketEventNum;
		ThreadsManager::s_pIOThread->m_pSocketIOEvents[iIndex].m_iUniqueID=iUniqueID;
		//ÿһ��socket���ò�ͬ����Ϣ��־
		iMsg    = WM_USER+1+iIndex;
	 }
	
	 iRet = ::WSAAsyncSelect(iFd, s_hMsgWindow, iMsg, iEvent);
	 Assert(iRet==0);
	 if (iRet!=0)
	 {
		 bRet = 0;
	 }
	 return bRet;
}

//////////////////////////////////////////////////////////////////////////
//
void   AsyncCom::clearEventRequest(SInt32 iFd)
{
	//�����Socket�ϵ������¼�����
	::WSAAsyncSelect(iFd, s_hMsgWindow, 0, 0);
}

//////////////////////////////////////////////////////////////////////////
//
SInt32 AsyncCom::waitEvents(std::vector<LPEvent>& vCurComEvents)
{
	SInt32		iRet	=	0;
	if (s_hMsgWindow == NULL)
	{
		//����̨���ھ��Ϊ�գ��򴴽�һ����̨�������Ĵ��ڣ�
		char szClassName[32] = {0};
		sprintf_s( szClassName, 32, "%s%d", "AsyncComWindow", s_iWndAtom );

		WNDCLASSEX theWndClass;
		theWndClass.cbSize = sizeof(theWndClass);
		theWndClass.style = 0;
		theWndClass.lpfnWndProc = &select_wndproc;
		theWndClass.cbClsExtra = 0;
		theWndClass.cbWndExtra = 0;
		theWndClass.hInstance = NULL;
		theWndClass.hIcon = NULL;
		theWndClass.hCursor = NULL;
		theWndClass.hbrBackground = NULL;
		theWndClass.lpszMenuName = NULL;
		theWndClass.lpszClassName = szClassName;
		theWndClass.hIconSm = NULL;
		ATOM theWndAtom = ::RegisterClassEx(&theWndClass);

		Assert(theWndAtom != NULL);

		if (theWndAtom == NULL)
		{
			::exit(-1);
		}

		s_hMsgWindow = ::CreateWindow( szClassName, szClassName, WS_POPUP, 0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL,
									  NULL, NULL, NULL);
		
		Assert(s_hMsgWindow != NULL);
		if (s_hMsgWindow == NULL)
		{
			::exit(-1);
		}
	}

	//�ڸô�������ȴ�Socket�¼��ĵ���ú�������ֱ����Socket�¼���Ϣ���
	MSG theMessage;
	UInt32 theErr = ::GetMessage(&theMessage, s_hMsgWindow, 0, 0);
	
	if (theErr > 0)
	{
		UInt32	iSelectErr			=  0;
		UInt32	iEvent				=  0;
		SInt32	iFd			        =  -1;
		SInt32	iCookie             =  0;
		LPEvent	pEvent				=  NULL;
		SInt32  iIndex              =  0;
		
		iSelectErr					= WSAGETSELECTERROR(theMessage.lParam);	
		iEvent						= WSAGETSELECTEVENT(theMessage.lParam);
		iFd							= (SInt32)theMessage.wParam;
		iCookie						= theMessage.message;
		
		if((iCookie>WM_USER)&&(iCookie<(SInt32)(ThreadsManager::s_pIOThread->m_iTotalSocketEventNum+WM_USER+1)))
		{
			iIndex = iCookie-WM_USER-1;
			if(iIndex<0)
			{
				Assert(0);
				return EINTR;
			}
			pEvent = &(ThreadsManager::s_pIOThread->m_pSocketIOEvents[iIndex]);
			Assert(pEvent!=NULL);
			pEvent->m_iEventType = kSocketNetworkEvent;

			if(iSelectErr !=0)
			{
				AssertV(0, iFd);  
				pEvent->m_iEventType   |=	kSocketClosedEvent;
			}
			else
			{
				if (iEvent & FD_READ)
				{
					pEvent->m_iEventType |= kSocketReadableEvent;
				}
				if (iEvent & FD_CLOSE)
				{
					pEvent->m_iEventType |= kSocketClosedEvent;
				}
			}
		}		
		else
		{
			return EINTR;
		}
		//�����Sokcet�ϵ�Event����;
		::WSAAsyncSelect(iFd, s_hMsgWindow, 0, 0);
		vCurComEvents.push_back(pEvent);
		return	0;
	}
	else
	{
		//////////////////////////////////////////////////////////////////////////
		//�������д���;
		return EINTR;
	}
	return iRet;
}

LRESULT CALLBACK select_wndproc(HWND inWindow, UINT inMsg, WPARAM inParam, LPARAM inOtherParam)
{
		if(inMsg == WM_NCCREATE)
		{
			return TRUE;
		}
		return 0;
}
