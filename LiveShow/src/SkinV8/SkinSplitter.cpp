// SkinSplitter.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SkinBase.h"
#include "SkinSplitter.h"


// CSkinSplitter

IMPLEMENT_DYNCREATE(CSkinSplitter, CSkinBase)
CSkinSplitter::CSkinSplitter()
{
	EnableAutomation();
	
	// Ϊ��ʹӦ�ó����� OLE �Զ��������ڻ״̬ʱ����
	//	���У����캯������ AfxOleLockApp��
	
	AfxOleLockApp();
}

CSkinSplitter::~CSkinSplitter()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	
	AfxOleUnlockApp();
}


void CSkinSplitter::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CSkinBase::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CSkinSplitter, CSkinBase)
END_MESSAGE_MAP()


BEGIN_SKIN_DISPATCH_MAP(CSkinSplitter, CSkinBase)
	SKINBASE_DISP_PROPERTIES(CSkinSplitter)
END_SKIN_DISPATCH_MAP(CSkinSplitter)

// ע��: ������� IID_ISkinSplitter ֧��
//��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//���Ƚӿڵ� GUID ƥ�䡣

// {5480A98C-0A88-4696-A102-4964DB31D777}
static const IID IID_ISkinSplitter =
{ 0x5480A98C, 0xA88, 0x4696, { 0xA1, 0x2, 0x49, 0x64, 0xDB, 0x31, 0xD7, 0x77 } };

BEGIN_INTERFACE_MAP(CSkinSplitter, CSkinBase)
	INTERFACE_PART(CSkinSplitter, IID_ISkinSplitter, Dispatch)
END_INTERFACE_MAP()

// {8BDFDABC-DA04-429C-8309-213A29D9A2F8}
IMPLEMENT_OLECREATE_FLAGS(CSkinSplitter, "Skin.SkinSplitter", afxRegApartmentThreading, 0x8bdfdabc, 0xda04, 0x429c, 0x83, 0x9, 0x21, 0x3a, 0x29, 0xd9, 0xa2, 0xf8)


// CSkinSplitter ��Ϣ�������
