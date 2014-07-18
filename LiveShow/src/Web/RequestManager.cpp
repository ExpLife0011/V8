#include "stdafx.h"
#include "RequestManager.h"
#include "process.h"
#include "utility/stringhelper.h"
#include "../../include/log.h"
#include "HttpClient.h"
#include "WebModule.h"

#define MAX_RETRY_TIMES	3//������Դ���

using namespace webinterface;
using namespace common::utility;

CRequestManager::CRequestManager()
{
	m_pHttpClient = NULL;
	m_ResponseParser.SetReuqestManager(this);
	m_nReqSeq = 100;			//	��Ŵ�100��ʼ
}

CRequestManager::~CRequestManager()
{
	if(m_pHttpClient)
	{
		delete m_pHttpClient;
		m_pHttpClient = NULL;
	}
}

void 
CRequestManager::Init()
{
	m_pHttpClient->SetNoProxy();
}

void 
CRequestManager::Clear()
{
	if( m_pHttpClient)
		m_pHttpClient->CleanAll();
}

int 
CRequestManager::GetRetCodeByStatus( int nStatusCode)
{
	switch( nStatusCode)
	{
		case 200: 	return WEB_RET_SUCCESS;
		case 401:	return WEB_RET_COMMON_NO_AUTH;
		case 403:	return WEB_RET_COMMON_NO_PERMIT;
		case 404:	return WEB_RET_COMMON_NO_URL;
		case 405:	return WEB_RET_COMMON_METHOD_NOT_SUPPORT;
		case 500: 	return WEB_RET_COMMON_SERVER_INTERNAL_ERROR;
		case 407:	return WEB_RET_COMMON_PROXY_NEED_AUTH;
		case 501:	return WEB_RET_COMMON_SERVER_NOT_IMPL;
		case 503:	return WEB_RET_COMMON_SERVER_NOT_AVAIL;
		default:	return WEB_RET_COMMON_ERROR_INTERNAL;
	}
}

uint32 
CRequestManager::PushUrl(EventValue nEventValue, int64 nParam0, wstring strUrl, POST_PARAMS* pArgument, 
						 RequestType eReqType, wstring wstrWritedFileName,  UINT nTimeout,BOOL bAllowRepeated,BOOL bResumable)
{
	POST_PARAMS* pPostArgument= NULL;
	if( pArgument != NULL)
	{
		pPostArgument = new POST_PARAMS(*pArgument);
	}

	HTTPCONTEXT* pCxt = new HTTPCONTEXT( stringhelper::UnicodeToAscii(strUrl));
	pCxt->nEventValue = nEventValue;
	pCxt->uParam0 = nParam0;
	pCxt->strURL = stringhelper::UnicodeToAscii( strUrl);
	pCxt->eReqType = eReqType;
	pCxt->wstrWritedFileName = wstrWritedFileName;
	pCxt->pArgument = pPostArgument;
	pCxt->nTimeout	=	 nTimeout/MAX_RETRY_TIMES;
	pCxt->bAllowRepeated = bAllowRepeated;
	pCxt->bResumable = bResumable;
	pCxt->nReqSeq = ++m_nReqSeq;

	m_vRequestQueue.push_back( pCxt);

	return pCxt->nReqSeq;
}

uint32		
CRequestManager::PushUrl(  HTTPCONTEXT* pContext)
{
	HTTPCONTEXT* pCxt = new HTTPCONTEXT(*pContext);
	pCxt->nReqSeq = ++m_nReqSeq;
	m_vRequestQueue.push_back( pCxt);

	return pCxt->nReqSeq;
}

uint8 
CRequestManager::PopUrl( HTTPCONTEXT*& pContext )
{
	std::vector<HTTPCONTEXT*>::iterator itr = m_vRequestQueue.begin();
	if( itr == m_vRequestQueue.end())
		return 0;

	pContext = *itr;
	m_vRequestQueue.erase( itr);
	return 1;
}

/**
* Function		��������URL�Ƿ��Ѿ������������
*/	
BOOL		
CRequestManager::IsExistUrl( string strUrl)
{
	for( size_t i = 0; i<m_vRequestQueue.size(); i++)
	{
		HTTPCONTEXT* pCxt = m_vRequestQueue[i];
		if( pCxt)
		{
			if( pCxt->strURL ==  strUrl)
				return TRUE;
		}
	}

	return FALSE;
}

void 
CRequestManager::ReqUrl( HTTPCONTEXT* pContext)
{
	if( pContext == NULL)
	{
		assert(0);
		return;
	}

	if( pContext->strURL != "")
	{
		// �������ظ���URL
		if( pContext->bAllowRepeated == FALSE)
		{
			if( IsExistUrl( pContext->strURL) == TRUE)
			{
				LOG_ERROR(L"%s �Ѿ����ڣ����Ҳ������ظ������������URL", stringhelper::AsciiToUnicode(pContext->strURL.c_str()));
				return;
			}
		}

		// δ���ߵ�����²Ž�������
		if( pContext->pArgument == NULL)
			m_pHttpClient->ReqURL( pContext);
		else
			m_pHttpClient->ReqPostUrl( pContext);
	}
}

void	
CRequestManager::ReReqUrl( string strUrl, HTTPCONTEXT* pContext, POST_PARAMS* pArgument)
{
	if( strUrl == "" || pContext == NULL)
		return;

	m_pHttpClient->ClearSeqIdMap( pContext->nReqSeq);

	if(pArgument == NULL)
		m_pHttpClient->ReReqURL( pContext);
	else
		m_pHttpClient->ReReqPostUrl( pContext);
}

void		
CRequestManager::CancelTask( uint32 nSeqNo)
{
	if( m_pHttpClient)
		m_pHttpClient->CancelTask( nSeqNo);
}


// �ú�������Ҫ���þ��Ǵ�HTTPClient�ķ��ض����в��ϵ�ȡ���Ѿ��������
// ����������Ƿ��صı������ݣ������ǲ���ʧ�ܵĽ��
// �����ķ���ֵ���������£�
//	-1		û��ȡ����Ч����Ӧ
//	0		��ʾ���ڽ�������������˷��ص�HTTPCONTEXT���ᱻɾ��
//	WEB_RET_SUCCESS	�����������
//	����>0		����������Ĵ���

HTTPCONTEXT
CRequestManager::ProcessResp()
{
	HTTPCONTEXT httpContext = m_pHttpClient->RetriveResp();
	
	if( httpContext.uOpPolicy == INVALID_RESP)
		return httpContext;

	string strUrl = httpContext.strURL;
	if( strUrl == "")	
	{
		httpContext.uOpPolicy = INVALID_RESP;
		return httpContext;
	}

	/** ��ǰ�������з�����ʧ�ܣ�û�н��յ�����������Ӧ*/
	/** ����д����󵥶�����*/
	if( httpContext.uResult == HTTP_FAILED )
	{
		if( httpContext.nErrorCode != ERR_TASK_WRITE_FILE_ERROR)
		{
			httpContext.nFailedTime++;

			// ����ܵĳ��Դ���С�����Σ���ʱ���ٴη��͸�����
			if( httpContext.nFailedTime < MAX_RETRY_TIMES)
			{
				ReReqUrl( strUrl, &httpContext, httpContext.pArgument);
				httpContext.uOpPolicy = REPEATED_REQ;
				return httpContext;
			}
			
			httpContext.uOpPolicy =  WEB_RET_NET_ERROR_TIMEOUT;
			return httpContext;
		}

		LOG_ERROR(L"\n\n");
		LOG_ERROR(L"=================== %s FATAL ERROR BEGIN==================", __FUNCTIONW__);
		LOG_ERROR(L"����д�����");
		LOG_ERROR(L"==========================FATAL ERROR END  ====================================\n\n");
		
		// д���̴�����Ҫ���ԣ�ֱ�ӷ���
		httpContext.uOpPolicy =  WEB_RET_COMMON_WRITE_FILE_ERROR;
		return httpContext;
	}

	/** 
	 * ���յ����������صı��ģ���ʱ��ⷵ�صı��ĵ�StatusCode��
	 * ֻ��200��״̬�������ȷ��
	 */
	if( httpContext.nHttpCode != 200 && httpContext.nErrorCode != 0)
	{
		LOG_ERROR(L"���������ص�״̬����� %d", httpContext.nHttpCode);
		httpContext.uOpPolicy =  GetRetCodeByStatus( httpContext.nHttpCode);
		return httpContext;
	}

	/** 
	 * �ɹ����յ�����������Ӧ���ģ��Ըñ��Ľ��н���������Ƿ���ȷ�������ݽ������
	 * ���з���
	 */
	int nEltsNum = 0;
	m_ResponseParser.SetUin( httpContext.uParam0);
	m_ResponseParser.ParseResponse( &httpContext);

	httpContext.uOpPolicy =  SUCCESS_RESP;
	return httpContext;
}

bool CRequestManager::QueryDownloadProcess( uint32 nSeqNo, uint32* uPercent, 
											  uint32* uTotalLength, uint32* uFinishedLength, uint32* uSpeed, int32* uRemainedTime)
{
	HTTPCONTEXT* pHttpContext = m_pHttpClient->GetContext( nSeqNo);
	if( pHttpContext == NULL)
		return false;

	if( uTotalLength)
		*uTotalLength = pHttpContext->nContentLength;

	if( uFinishedLength)
		*uFinishedLength = pHttpContext->nFinishedLength;

	if( uPercent)
	{
		if(0 == pHttpContext->nContentLength)
		{
			*uPercent = 0;
		}
		else
		{
			//*uPercent = (int)(pHttpContext->nFinishedLength*100/pHttpContext->nContentLength);   �˷����������ʱ�� ��ֵ̫������
			*uPercent = (int)(pHttpContext->nFinishedLength*1.0/pHttpContext->nContentLength*100);
		}
	}

	if( uSpeed)
		*uSpeed = pHttpContext->nSpeed;
	else
		pHttpContext->nSpeed = 0;

	if( uRemainedTime)
		*uRemainedTime = pHttpContext->nRemainedTime;
	else
		*uRemainedTime = -1;


	return true;
}