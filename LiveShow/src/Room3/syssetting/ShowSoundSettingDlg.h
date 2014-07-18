#pragma once

#include "..\Resource.h"
#include "Skin_i.h"
#include "AudioVideoSetting.h"
#include "SysSettingDlg.h"
// CShowHarassmentDlg �Ի���

class CShowAudioTestDlg;
class CShowSoundSettingDlg : public CDialog
{
	DECLARE_DYNAMIC(CShowSoundSettingDlg)

public:
	CShowSoundSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowSoundSettingDlg();

// �Ի�������
	enum { IDD = IDD_ATROOM_SHOW_SOUND_SETTING_DLG };  //��Ƶ���öԻ���

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);	

	virtual BOOL OnInitDialog();
	virtual void OnShowWindow(BOOL bShow,UINT nStatus);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedCheck();

	void Init();
	void OnClickBtnAudioTest();
	void OnClickBtnMoreAudioSetting();  //������Ƶ���ð�Ť��Ӧ����
	void OnClickBtnGotoFreshRoom();  //
	void Confirm();  //ȷ�ϱ���
	

	DECLARE_MESSAGE_MAP()
public:
	void SetApplyEffect(BOOL bEffect);//���õ��Ӧ�õ�Ч��

private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	CShowAudioTestDlg *m_pAudioTest;
	EnMixerControlMode m_enmMode;
	
};
