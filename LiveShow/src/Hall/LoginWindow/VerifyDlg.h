
#pragma once
#include "LoginVerifyHander.h"
#include "resource.h"
#include "Skin_i.h"

#define VERIFY_TEXT_DEFAULT _T("��Ǹ���������������Ϊ����\n�����˺Ű�ȫ����������֤��")  //�����γ���Ϊ��֤�˺Ű�ȫ����������֤��
#define VERIFY_TEXT_EXPIRED _T("        ��֤���ѹ���")
#define VERIFY_TEXT_EMPTY _T("          ��������֤��")
#define VERIFY_TEXT_ERROR _T("          ��֤����������")
#define VERIFY_TEXT_VERIFYING _T("������֤...")

// CVerifyDlg �Ի���

class  CVerifyDlg : public CDialog
{
	DECLARE_DYNAMIC(CVerifyDlg)

public:
	CVerifyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVerifyDlg();

// �Ի�������
	enum { IDD = IDD_VERIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	LRESULT OnSkinMessage(WPARAM wParam, LPARAM lParam);

private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	CLoginVerifyHander m_pVerifyHander;

public:
	void GetVerifyCode();	//�����ȡ��֤��ͼƬ
	void OnGetVerifyCodeRep(Event const& evt);          //�����ȡ��֤��ͼƬ������Ӧ����
	void OnCodeError(CString errorText);					//��֤�����

	void OnClickRefreshCode();			//���������֤��
	void OnClickOk();					//�û�ȷ��
	void OnClickClose();
	void OnClickCancel();

	void NotifySkinCode(CString strCodePath);				//֪ͨƤ����֤��
	void NotifySkinText(CString strText);
	void NotifySkinColor(LONG color);
	
	void OnCodeSuccess();	
	void OnOK();
	void OnCancel();	

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();

	uint32  m_LastVerfiyTime;
};

