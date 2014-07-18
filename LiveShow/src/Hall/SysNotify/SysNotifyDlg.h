#pragma once

#include "Resource.h"
#include "Skin_i.h"
#include <map>
// CSysNotifyDlg �Ի���

struct stSysMsg  //ϵͳ��Ϣ�ṹ�壬�ɸ�����Ҫ�޸�
{
   CString strContent;//����
   CString strHyperLinkLabel;//��������
   CString strHyperLingAddr;//���ӵ�ַ
};

#define SYSNOTIFY_WIDTH 250   //ϵͳ��Ϣ�Ի���Ŀ��
#define SYSNOTIFY_HIGHT 170   //ϵͳ��Ϣ�Ի���ĸ߶�

typedef std::map<int,stSysMsg*> SYSMSGMAP;//keyָ�ڼ�����Ϣ,��0��ʼ��value������Ϣ����
class CSysNotifyDlg : public CDialog
{
	DECLARE_DYNAMIC(CSysNotifyDlg)

public:
	CSysNotifyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysNotifyDlg();

// �Ի�������
	enum { IDD = IDD_SYSTEM_NOTIFY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	HRESULT OnMouseLeave( WPARAM wParam , LPARAM lParam );
	HRESULT OnNcMouseLeave( WPARAM wParam , LPARAM lParam );

	void ShowSysMsg();

	DECLARE_MESSAGE_MAP()

public:
	void SetSysMsg(SYSMSGMAP mapSysMsg ,LPCTSTR pTitle);//����ϵͳ��Ϣ���ݺ�����,���б���
	void ClearSysMes();  //���������Ϣ
	BOOL IfMouseLeave();
    
private:
	CComPtr<ISkinEngine> m_pSkinEngine;

	SYSMSGMAP m_mapSysMsg;
	int m_curPage,m_totalPage;//��ǰҳ����ҳ
	RECT m_rect;  //ϵͳ��Ϣ�Ի�����ʾ��λ��
	BOOL m_bMouseLeave;
};
