// MyGoodsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "..\Room.h"
#include "MyGoodsDlg.h"
#include "SkinUtil.h"


// CMyGoodsDlg �Ի���

IMPLEMENT_DYNAMIC(CMyGoodsDlg, CDialog)

CMyGoodsDlg::CMyGoodsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyGoodsDlg::IDD, pParent)
{
	m_pSkinEngine = NULL;
	::GetSkinEngine(&m_pSkinEngine);
}

CMyGoodsDlg::~CMyGoodsDlg()
{
}

void CMyGoodsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MYGOODS, m_MyGoodsListCtrl);
}


BEGIN_MESSAGE_MAP(CMyGoodsDlg, CDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CMyGoodsDlg ��Ϣ�������

int CMyGoodsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ASSERT(m_pSkinEngine != NULL);
	if (NULL != m_pSkinEngine)
	{
		HRESULT hr = m_pSkinEngine->LoadSkin(GetSafeHwnd(),L"MyGoodsDlg");
		ASSERT(hr == S_OK && __LINE__);
	}

	return 0;
}

BOOL CMyGoodsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_MyGoodsListCtrl.InitGiftListCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
