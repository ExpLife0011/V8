
#include "..\..\include\ui\VDCComboBox.h"


CVDCComboBox::CVDCComboBox(void)
{
	m_bReadOnly = FALSE;
	m_hBrush = CreateSolidBrush(RGB(255, 255, 255));
}

CVDCComboBox::~CVDCComboBox(void)
{
	if (m_hBrush != NULL)
	{
		DeleteObject(m_hBrush);
		m_hBrush = NULL;
	}
}
BEGIN_MESSAGE_MAP(CVDCComboBox, CComboBox)
	ON_WM_CTLCOLOR()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

HBRUSH CVDCComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	//����ֻ�����ԣ�ִֻ��һ��
	if (!m_bReadOnly)
	{
		CEdit* pEdit = (CEdit*)this->GetWindow(GW_CHILD);
		if ((pEdit != NULL) && (pEdit->GetSafeHwnd() != NULL))
		{
			pEdit->SetReadOnly(TRUE);
			m_bReadOnly = TRUE;
		}
	}

	//���ñ���ɫ
	if (m_hBrush)
	{
		pDC->SetBkColor(RGB(255, 255, 255));
		return m_hBrush;
	}
	
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void CVDCComboBox::OnSetFocus(CWnd* pOldWnd)
{
	CComboBox::OnSetFocus(pOldWnd);

	// TODO: �ڴ˴������Ϣ����������
	//��һ�ε�����ʱ�����й����֣��ڴ�����
	CEdit* pEdit = (CEdit*)this->GetWindow(GW_CHILD);
	if ( (pEdit != NULL) && (pEdit->GetSafeHwnd() != NULL) )
	{
		pEdit->HideCaret();
	}
}

BOOL CVDCComboBox::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	HWND hWnd = ::GetFocus();
	CEdit* pEdit = (CEdit*)this->GetWindow(GW_CHILD);
	if ( (pEdit != NULL) && (pEdit->GetSafeHwnd() != NULL) )
	{
		if (pEdit->GetSafeHwnd() == hWnd)
		{
			pEdit->HideCaret();
		}
	}
	
	return CComboBox::PreTranslateMessage(pMsg);
}
