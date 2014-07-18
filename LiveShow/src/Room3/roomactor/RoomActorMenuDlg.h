#pragma once

#include "..\Resource.h"
#include "Skin_i.h"
// CRoomActorMenuDlg �Ի���
#include "..\usermanager\UserManager.h"
#include "..\..\CommonLibrary\include\ui\ImageImpl.h"

#define ROOMACTOR_MOUSE_TIMER_IDEVENT 1
#define ROOMACTOR_MOUSE_TIMER_INTERVALTIME 500
#define ROOMACTOR_GIDUE_TIMER_IDEVENT 2  
#define ROOMACTOR_GIDUE_TIMER_INTERVALTIME 60*1000

struct ActorInfo
{
	uint32 m_ActorUin;       //����uin
	uint32 m_VipLevel;       //���
	uint8 m_RichLevel;       //�����ȼ�
	bool m_IsLine;           //�Ƿ�����	(���Ƿ��ڷ���)
	bool m_IsMan;            //�Ƿ�Ϊ��
	std::wstring m_ActorRoleName;  //�����ǳ�	
	common::ui::CImageImpl* m_HeadImage;     //ԭɫͷ��
	common::ui::CImageImpl* m_HeadImageGray; //��ɫͷ��


	ActorInfo()
	{
		m_ActorUin = 0;
		m_VipLevel = 0;
		m_RichLevel = 0;
		m_IsLine = 0;	
		m_IsMan = 0;
		m_HeadImage = NULL;
		m_HeadImageGray = NULL;

	}
};

class CRoomActor;
class CRoomParentDlg ;
class CRoomActorMenuDlg : public CDialog
{
	DECLARE_DYNAMIC(CRoomActorMenuDlg)

public:
	CRoomActorMenuDlg( CRoomParentDlg* pParentDlg ,CRoomActor* pRoomActor,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRoomActorMenuDlg();

// �Ի�������
	enum { IDD = IDD_ROOMACTOR_MENU_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog() ;
	void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
public:
	void Show(ActorInfo *pActor);
	void Hide();
	void SetActorInfo(ActorInfo *pActor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam) ;
	void OnClickbtnActorInfo() ;  //������Ϣ
	void OnClickbtnSelTalk() ;  //ѡ���������
	void OnClickbtnSelSendGifts(); //ѡ���������
	void OnClickbtnSeePrivateVideo();//�ۿ�˽����Ƶ
	void OnClickbtnOneToOneVideo();//һ��һ��Ƶ

private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	CRoomParentDlg* m_pParentDlg ;
	CRoomActor* m_RoomActor;
	ActorInfo* m_pActor;
};
