// SkinItemAnimate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SkinItemAnimate.h"


// CSkinItemAnimate

IMPLEMENT_DYNCREATE(CSkinItemAnimate, CXmlCmdTarget)
CSkinItemAnimate::CSkinItemAnimate()
{
	EnableAutomation();
	
	// Ϊ��ʹӦ�ó����� OLE �Զ��������ڻ״̬ʱ����
	//	���У����캯������ AfxOleLockApp��
	
	AfxOleLockApp();
}

CSkinItemAnimate::~CSkinItemAnimate()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	
	AfxOleUnlockApp();
}


void CSkinItemAnimate::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CXmlCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CSkinItemAnimate, CXmlCmdTarget)
END_MESSAGE_MAP()


BEGIN_SKIN_DISPATCH_MAP(CSkinItemAnimate, CXmlCmdTarget)
END_SKIN_DISPATCH_MAP(CSkinItemAnimate)

// ע��: ������� IID_ISkinItemAnimate ֧��
//��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//���Ƚӿڵ� GUID ƥ�䡣

// {AC2B91D0-1017-4810-8878-A960F473460F}
static const IID IID_ISkinItemAnimate =
{ 0xAC2B91D0, 0x1017, 0x4810, { 0x88, 0x78, 0xA9, 0x60, 0xF4, 0x73, 0x46, 0xF } };

BEGIN_INTERFACE_MAP(CSkinItemAnimate, CXmlCmdTarget)
	INTERFACE_PART(CSkinItemAnimate, IID_ISkinItemAnimate, Dispatch)
END_INTERFACE_MAP()

// {6ABDF86F-1A1F-4EBC-95BF-15BF4192BAF0}
IMPLEMENT_OLECREATE_FLAGS(CSkinItemAnimate, "Skin.SkinItemAnimate", afxRegApartmentThreading, 0x6abdf86f, 0x1a1f, 0x4ebc, 0x95, 0xbf, 0x15, 0xbf, 0x41, 0x92, 0xba, 0xf0)


// CSkinItemAnimate ��Ϣ�������
