// CommonLibrary.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include <afxdllx.h>
#include "include\Net\NetLayer.h"
#include "include/utility/expat++/expat_error.h"

#ifdef _MANAGED
#error ���Ķ� CommonLibrary.cpp �е�˵����ʹ�� /clr ���б���
// ���Ҫ��������Ŀ����� /clr������ִ�����в���:
//	1. �Ƴ������� afxdllx.h �İ���
//	2. ��û��ʹ�� /clr ���ѽ���Ԥ����ͷ��
//	   ��Ŀ���һ�� .cpp �ļ������к��������ı�:
//			#include <afxwin.h>
//			#include <afxdllx.h>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static AFX_EXTENSION_MODULE CommonLibraryDLL = { NULL, NULL };

#ifdef _MANAGED
#pragma managed(push, off)
#endif

extern netlayer::ConnectionLayer* m_ConnectionLayer;

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// ���ʹ�� lpReserved���뽫���Ƴ�
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("CommonLibrary.DLL ���ڳ�ʼ��!\n");
		
		// ��չ DLL һ���Գ�ʼ��
		if (!AfxInitExtensionModule(CommonLibraryDLL, hInstance))
			return 0;

		// ���� DLL ���뵽��Դ����
		// ע��: �������չ DLL ��
		//  MFC ���� DLL (�� ActiveX �ؼ�)��ʽ���ӵ���
		//  �������� MFC Ӧ�ó������ӵ�������Ҫ
		//  �����д� DllMain ���Ƴ������������һ��
		//  �Ӵ���չ DLL �����ĵ����ĺ����С�ʹ�ô���չ DLL ��
		//  ���� DLL Ȼ��Ӧ��ʽ
		//  ���øú����Գ�ʼ������չ DLL������
		//  CDynLinkLibrary ���󲻻ḽ�ӵ�
		//  ���� DLL ����Դ���������������ص�
		//  ���⡣

		new CDynLinkLibrary(CommonLibraryDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("CommonLibrary.DLL ������ֹ!\n");

		if( common::utility::last_error_key != TLS_OUT_OF_INDEXES)
			TlsFree( common::utility::last_error_key);

		// �ڵ�����������֮ǰ��ֹ�ÿ�
		AfxTermExtensionModule(CommonLibraryDLL);
	}

	return 1;   // ȷ��
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

