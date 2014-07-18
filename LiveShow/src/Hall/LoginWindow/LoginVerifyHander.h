#pragma once
#include "logindlg.h"


class CLoginVerifyHander	
{
public:
	CLoginVerifyHander(HWND hwndLogin);
	~CLoginVerifyHander(void);

public:
	void GetVerifyCode();               //�����ȡ��֤��ͼƬ
	CString OnGetVerifyCodeRep(Event const& evt);          //�����ȡ��֤��ͼƬ������Ӧ������������֤��ͼƬ·��

	void RefreshCode();					//ˢ����֤��
	void VerifyCode(CString strVerifyCode);	
	string GetKey();
	CString GetStrVerifyCode();
	
private:	
	string m_strKey;//�����������ͻ��˵�һ��key
	CString m_strVerifyCode;//�û���������ĵ���֤��
	uint32 m_respId;								//��֤��ͼƬ������Id	
	HWND m_loginHwnd;
};
