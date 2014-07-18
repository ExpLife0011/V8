#pragma once

#include "Resource.h"
#include "Skin_i.h"
#include "afxcmn.h"
#include "usermanager\UserManager.h"
#include "RoomBusiness.h"
#include "gift\PropsListCtrl.h"
#include "gift\GiftComboBox.h"
#include "iectrl\OutputHtmlEditImpl.h"
#include "loudspeaker\SpeakerOutputLogic.h"
#include "gift\GiftTipDlg.h"
#include "gift\MyGoodsListCtrl.h"
#include "flash\flashWnd.h"
#include "screeneffect\ScreenEffectManager.h"
#include "..\CommonLibrary\include\ui\GifButton.h"

// CRoomRightDlg �Ի���

class CRoomParentDlg ;
class CPresentDetailDlg ;
class CRoomRightDlg : public CDialog
{
	DECLARE_DYNAMIC(CRoomRightDlg)

public:
	CRoomRightDlg(CRoomParentDlg* pParentDlg, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRoomRightDlg();

public:
	//�û����
	void OnAddUser(IUserItem * pUserItem);
	void OnDeleteUser(IUserItem * pUserItem);

	//�����̳����
	void OnUpdateMoney( uint32 unMoney , BOOL bFirstInit = FALSE )	;										//����Ǯ��
	bool GetSendToUIN(uint32 & unUIN);											//��ȡ�����û�UIN
	void ReloadGiftData();

	//�������
	void CleanSpeakerOutput();

	//ҵ���߼�
	void SetRoomBusiness(RoomBusiness * pRoomBusiness);

// �Ի�������
	enum { IDD = IDD_ROOM_RIGHT_DLG };
	void SetSendObj( CString strName , uint32 unUIN ) ;
	void SetSpeakerOutputGotoEndAble( BOOL bAble ) ;
	void InsertSpeakerText(CString& strText ) ;
	void OnClickNameLink( CString& strName , uint32 unUUID ) ;
	void OnPaodaoSendToChange( CString& strSelText ) ;
	int GetSenToComboInfo(vector<SenToComboInfo>& vSenToComboInfoList ) ;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);
	//afx_msg LRESULT OnClickGifButton( WPARAM wParam ,LPARAM lParam ) ;
	afx_msg LRESULT OnClickMsgBoxGoToRegister(WPARAM wParam, LPARAM lParam);

	//�����̳����
	void InitGiftListCtrl();													//��ʼ�������б�
	void ShowGiftListCtrlByTab(int nTab);										//����Tab ID��ʾ��Ӧ������ҳ
	//void OnClickBtnGiftListDown();                 								//������¼�ͷ�������б�����
	//void OnClickBtnGiftListUp();                   								//������ϼ�ͷ�������б�չ��
	void OnClickTabGift(int nTab);                         						//��������б�tab
	//void SetAboutGiftVisible(BOOL visible);        								//�����б�չ��������ʱ����һЩ�ؼ��ɼ��벻�ɼ�
	void OnClickPresentDetail();                   								//�����������
	void OnClickStamp();														//�������ӡ�¿�
	void OnClickChangeVoice();													//�������������ѡ���
	void OnClickFlyingText();													//����������������
	void OnClickBtnPayVIP();                                                    //�����ֵ
	void OnClickBtnGift();														//�������
	void OnClickBtnGame();														//�����Ϸ

	//����ϵͳ
	void OnClickBtnMyGoods();													//�������

	//�������
	void OnClickSpeaker();                         								//�������
	void OnClickWishSong();														//����������

	void PlayCoinEffect(uint32 totalMoney, uint32 addMoney);                    //���żӱ�Ч��,addMoney����0ʱ�мӱ�Ч������Ч����<=0��ֵ
	//��ֵ��ť
	//void DrawGifButton();
	//void MoveGifButton(BOOL bShow);

	void InitCoinFlashWnd();

	void OnClickBtnBaiTuService(); //�����ϵ�ͷ�

	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnClickUserList(WPARAM wParam, LPARAM lParam);				//����û��б�
	afx_msg LRESULT OnClickGiftList(WPARAM wParam, LPARAM lParam);				//��������б�
	afx_msg LRESULT OnShowGiftTip(WPARAM wParam, LPARAM lParam);				//��ʾ������Ϣ��Ƭ
	afx_msg LRESULT OnClickMyGoodsList(WPARAM wParam, LPARAM lParam);			//���������Ʒ

private:
	CComPtr<ISkinEngine> m_pSkinEngine;

	RoomBusiness * m_pRoomBusiness;												//����ҵ���߼�
	CRoomParentDlg * m_pParentDlg;												//����������
	
	//�����̳�
	std::map<std::wstring, CGiftListCtrl*> m_mapGiftListCtrl;					//�����б�ؼ�
	CGiftComboBox m_GiftCountCombo;												//���������ؼ�
	CComboBox m_GiftSendToCombo;												//�������Ͷ���
	CPresentDetailDlg * m_pPresentDetailDlg;									//������������
	CGiftTipDlg * m_pGiftTipDlg;												//������Ϣ��Ƭ

	//����
	CMyGoodsListCtrl m_MyGoodsListCtrl;											//�����ؼ�

	//����չ��
	COutputHtmlEditImpl* m_pSpeakerHtml;										//��������ؼ�
	CSpeakerOutputLogic m_SpeakerLogic;											//��������߼�

	int m_nGiftTypeCurSel;                                                      //��ǰ��������

	int m_nPayImageIndex;                                                       //��ֵ��ť����֡
	CFlashWnd * m_pCoinFlashWnd;                                                //179��flash
	uint32 m_unLastMoney ;

	//common::ui::GifButton *m_pGifBtnPayMoney;
public:
	UserManager * GetUserManager();												//��ȡ�û�����
	IUserItem * GetSelfUserItem();												//��ȡ�Լ���Ϣ
	afx_msg void OnCbnSelchangeComboRoomGiveto();
	void ShowCoinFlashWnd();

	void GetGiftItemRect(CRect &rcGiftItem);
	//void MoveThePayMoneyBtn(BOOL bShow);
};
