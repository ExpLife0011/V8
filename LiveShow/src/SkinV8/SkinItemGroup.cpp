// SkinItemGroup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SkinItem.h"
#include "SkinItemGroup.h"


// CSkinItemGroup

IMPLEMENT_DYNCREATE(CSkinItemGroup, CSkinItem)
CSkinItemGroup::CSkinItemGroup()
{
	EnableAutomation();
	
	// Ϊ��ʹӦ�ó����� OLE �Զ��������ڻ״̬ʱ����
	//	���У����캯������ AfxOleLockApp��
	
	AfxOleLockApp();
}

CSkinItemGroup::~CSkinItemGroup()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	
	AfxOleUnlockApp();
}


void CSkinItemGroup::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CSkinItem::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CSkinItemGroup, CSkinItem)
END_MESSAGE_MAP()


BEGIN_SKIN_DISPATCH_MAP(CSkinItemGroup, CSkinItem)
END_SKIN_DISPATCH_MAP(CSkinItemGroup)

// ע��: ������� IID_ISkinItemGroup ֧��
//��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//���Ƚӿڵ� GUID ƥ�䡣

// {540DEB4D-8322-4C53-983D-4942AA7B237A}
static const IID IID_ISkinItemGroup =
{ 0x540DEB4D, 0x8322, 0x4C53, { 0x98, 0x3D, 0x49, 0x42, 0xAA, 0x7B, 0x23, 0x7A } };

BEGIN_INTERFACE_MAP(CSkinItemGroup, CSkinItem)
	INTERFACE_PART(CSkinItemGroup, IID_ISkinItemGroup, Dispatch)
END_INTERFACE_MAP()

// {623BD64E-9E96-4DB7-A6DD-126390DD47EF}
IMPLEMENT_OLECREATE_FLAGS(CSkinItemGroup, "Skin.SkinItemGroup", afxRegApartmentThreading, 0x623bd64e, 0x9e96, 0x4db7, 0xa6, 0xdd, 0x12, 0x63, 0x90, 0xdd, 0x47, 0xef)


// CSkinItemGroup ��Ϣ�������
