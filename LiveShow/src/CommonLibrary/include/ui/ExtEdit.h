#pragma once

//=================================================================
//            �ļ��ж��峣�õ���չEdit

#include "Common.h"
#include "afxwin.h"
#include "ColorEdit.h"


class CLimitTextEdit;
class CAutoEndEdit;
class CShowHintEdit;

//=================================================================
// CLimitTextEdit
// ���������Edit�ֽ���Ŀ
 

class COMMON_INTERFACE CLimitTextEdit : 
	public CColorEdit
{
	DECLARE_DYNAMIC(CLimitTextEdit)

public:
	CLimitTextEdit();
	virtual ~CLimitTextEdit();

	/**
	@fn SetLimit( UINT nLimitNum)
	@brief ��ʾ�༭����������ֽ���Ŀ
	@param	[in] nLimitNum	���Ƶ��ֽ���Ŀ
	**/
	void	SetLimit( UINT nLimitNum);

	/**
	@fn GetLimit()
	@brief ��ȡ�༭��������������ֽڵ������Ŀ
	@return	�༭��������������ֽڵ������Ŀ
	**/
	const UINT	GetLimit() { return m_nLimitInBytes;}


protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnPaste(WPARAM w, LPARAM l);

	int		GetLengthInAnsi();
	int		GetSelLengthInAnsi();
	int		ReplaceSel(const wchar_t* szTextNew);
	void	NotifyInputExceed(int nLimitNow, int nInputLenYouWant);

private:

	UINT	m_nLimitInBytes;
};

//=================================================================
//  CShowHintEdit
//	��Edit��һ�λ�ȡ�����ʱ���Զ���λ�����ֵ�ĩβ

class COMMON_INTERFACE CAutoEndEdit : 
	public CLimitTextEdit
{
	DECLARE_DYNAMIC(CAutoEndEdit)

public:
	CAutoEndEdit();
	virtual ~CAutoEndEdit();

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

private:
	bool	m_bFirstClick;
};


//=================================================================
//  CShowHintEdit
//	����༭����û���κε��ı�������ʧȥ����󣬽��ڱ༭����
//  ��ʾһ����ʾ�ı�������ȡ����󣬸��ı������

class COMMON_INTERFACE CShowHintEdit : 
	public CLimitTextEdit
{
	DECLARE_DYNAMIC(CShowHintEdit)

public:
	CShowHintEdit();
	virtual ~CShowHintEdit();

	/**
	@fn SetHintText( CString strHintText)
	@brief ����ʧȥ�����ʱ�����ʾ����
	@param	[in] strHintText	��ʾ�ı�
	**/
	void	SetHintText( CString strHintText) { m_strHintText = strHintText;}

	/**
	@fn GetHintText
	@brief ��ȡʧȥ�����ʱ�����ʾ����
	@param	[in] strHintText	��ʾ�ı�
	**/
	CString	GetHintText(){return m_strHintText;}

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnSetFocus( CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);

	CString	m_strHintText;
};