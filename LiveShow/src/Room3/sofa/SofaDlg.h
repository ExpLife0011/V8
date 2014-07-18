#pragma once
#include "..\Resource.h"
#include "Skin_i.h"
#include "flash.h"


// CSofaDlg �Ի���

class CSofaDlg : public CDialog
{
	DECLARE_DYNAMIC(CSofaDlg)

public:
	CSofaDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSofaDlg();

	void InitSofaList(uint32 unSelf179ID, bool bGuest, CString strInitInfo);
	void UpdateSofa(uint8 unIndex, CString strSofaInfo);				//����ɳ���û�����
	void UpdateSofaInfo(CString strSofaInfo);			//ɳ���û���Ϣ����
	void UpdateSize(int cx);
	void ClearSofaList();
	void HideSendPanel();
	bool IsInited();

// �Ի�������
	enum { IDD = IDD_SOFA_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	CFlash m_flash;
	DECLARE_EVENTSINK_MAP()
	void FlashCallFlash(LPCTSTR request);
	void FSCommandFlash(LPCTSTR command, LPCTSTR args);
	virtual BOOL OnInitDialog();
	void CallFunction(CString func, std::vector<CString> vecParams);

	CComPtr<ISkinEngine> m_pSkinEngine;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnClickFlash(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFlashKillFocus(WPARAM wParam, LPARAM lParam);

protected:
	void ParseParams(CString strParam, CString& strFunc, std::vector<CString>& vecParam);

private:
	bool m_bVersionLow;
	bool m_bInited;
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
