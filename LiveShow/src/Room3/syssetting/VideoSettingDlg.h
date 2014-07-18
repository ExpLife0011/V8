#pragma once
#include "..\resource.h"
#include "Skin_i.h"
#include "RoomDefine.h"
// CAudioDlg �Ի���

#define DEVICE_NAME_LEN 128

class CVideoSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CVideoSettingDlg)

public:

	CVideoSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVideoSettingDlg();

	// �Ի�������
	enum { IDD = IDD_ATROOM_AUDIO_DLG };
	
	void StartVideo(int iDevice);  //����ָ����Ƶ
	void CloseVideo();  //�ر���Ƶ
	void ShowVideoAdjust();  //��ʾ�ѿ�����Ƶ�����ԶԻ���
	
protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnShowWindow(BOOL bShow,UINT nStatus);	

	void OnVedioChanged();
	void OnDestroy();
	BOOL PreTranslateMessage(MSG* pMsg);	
	void SendSetVideo();   //����������Ƶ����
	void SendStartVideo(); //���Ϳ�����Ƶ����
	void SendCloseVideo(); //���͹ر���Ƶ����

	DECLARE_MESSAGE_MAP()

private:

	CComPtr<ISkinEngine> m_pSkinEngine;
	int m_iDevice; //����ͷ�豸���� ��Ƶ�豸	
};