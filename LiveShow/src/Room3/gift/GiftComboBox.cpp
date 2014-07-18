#include "StdAfx.h"
#include "GiftComboBox.h"

CGiftComboBox::CGiftComboBox(void)
{
}

CGiftComboBox::~CGiftComboBox(void)
{
}
BEGIN_MESSAGE_MAP(CGiftComboBox, CComboBox)
	ON_CONTROL_REFLECT_EX(CBN_SELCHANGE, &CGiftComboBox::OnCbnSelchange)
	ON_CONTROL_REFLECT(CBN_DROPDOWN, &CGiftComboBox::OnCbnDropdown)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, &CGiftComboBox::OnCbnCloseup)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CGiftComboBox::OnCbnSelchange()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nSel = GetCurSel();
	CString sCount;
	GetLBText(nSel,sCount);
	sCount = sCount.Left(sCount.Find(L"("));
	nSel = AddString(sCount);
	SetCurSel(nSel);

	return TRUE;
}

void CGiftComboBox::OnCbnDropdown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ResetContent();
	InsertString(0,L"18(Ҫ��)");
	InsertString(1,L"38(����)");
	InsertString(2,L"99(����)");
	InsertString(3,L"520(�Ұ���)");
	InsertString(4,L"666(������˳)");
	InsertString(5,L"888(��ϲ����)");
	InsertString(6,L"1314(һ��һ��)");
	InsertString(7,L"3344(��������)");
	InsertString(8,L"9999(�쳤�ؾ�)");
}

void CGiftComboBox::InitGiftCombo()
{
	SetDroppedWidth(74);
	InsertString(0,L"1");
	SetCurSel(0);
	//((CEdit*)GetDlgItem(1001))->SetWindowText(L"1");
}

void CGiftComboBox::OnCbnCloseup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nSel = GetCurSel();
	if (nSel == CB_ERR)
	{
		InsertString(0,L"1");
		SetCurSel(0);
	}
}

void CGiftComboBox::GetEditText( CString & strText )
{
	CEdit * pEdit = (CEdit*)(GetWindow(GW_CHILD));
	if (pEdit)
	{
		pEdit->GetWindowText(strText);
	}
}
HBRUSH CGiftComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	pDC->SetBkMode(TRANSPARENT);
	if (nCtlColor == CTLCOLOR_LISTBOX)
	{
		if (m_listbox.GetSafeHwnd() == NULL)
		{
			m_listbox.SubclassWindow(pWnd->GetSafeHwnd());
		}
	}
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (m_edit.GetSafeHwnd() == NULL)
		{
			m_edit.SubclassWindow(pWnd->GetSafeHwnd());
		}
	}
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	//pDC->SetTextColor(RGB(0, 0, 255));
	//hbr = ::CreateSolidBrush(RGB(255, 0, 0));

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CGiftComboBox::PreSubclassWindow()
{
	//CWnd * pWnd = GetWindow(GW_CHILD);
	//ModifyStyle(pWnd->GetSafeHwnd(), 0, ES_NUMBER, 0);

	CComboBox::PreSubclassWindow();
}
