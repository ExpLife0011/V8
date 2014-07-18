#pragma once
#include "Resource.h"
#include "Skin_i.h"
#include "RoomParentDlg.h"
#include "userlist\AllUserListCtrl.h"
#include "userlist\ManagerListCtrl.h"
#include "userlist\WaitingUserList.h"
#include "usermanager\UserManager.h"
#include "RoomBusiness.h"
#include "usermanager\UserItem.h"
#include "userlist\SearchDlg.h"
#include "userlist\IconIntroductionDlg.h"

// CRoomBottomLeftDlg �Ի���
class CRoomParentDlg;
class CSelfInfoAndSetDlg;
class CRoomBottomLeftDlg : public CDialog
{
	DECLARE_DYNAMIC(CRoomBottomLeftDlg)

public:
	CRoomBottomLeftDlg(CRoomParentDlg* pParentDlg, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRoomBottomLeftDlg();

// �Ի�������
	enum { IDD = IDD_ROOM_BOTTOMLEFT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnSkinMessage(WPARAM wParam,LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	//�û��б����
	void OnGetUserList(std::map<uint32, IUserItem*> & mapAllUser);
	void OnGetAdminList(std::map<uint32, IUserItem*> & mapAdminUser);
	void OnGetWaitingList(std::map<uint32, IUserItem*> & mapWaitingUser);
	void OnAddUser(IUserItem * pUserItem);
	void OnUpdateUser(IUserItem * pUserItem);
	void OnDeleteUser(IUserItem * pUserItem);
	void OnAddAdminUser(IUserItem * pUserItem);
	void OnDeleteAdminUser(IUserItem * pUserItem);
	void OnAddWaitingUser(IUserItem * pUserItem);
	void OnDeleteWaitingUser(IUserItem * pUserItem);
	void OnUserListCountChange();
	void ShowUserItem(IUserItem * pUserItem);
	void OnGetUserListBegin();
	void OnGetUserListComplete();
	void OnClickBtnWhereIAm();                     								//���������
	void OnClickIconIntroClose();
	void OnClickNameLink( CString& strName , uint32 unUUID ) ;

	void OnClickOrderSong();
	//������Ϣ����ز�������
	void SetBottomUserInfo(IUserItem* pUserItem);
	CSelfInfoAndSetDlg* GetSelfInfoAndSetDlg(){ return m_pSelfInfoAndSetDlg; }

	void OnAddUserIsMgr(IUserItem * pUserItem);
	void OnUpdateUserIsMgr(IUserItem * pUserItem);

	//ҵ���߼�
	void SetRoomBusiness(RoomBusiness * pRoomBusiness);

	void OnCycleTrigger();

public:
	afx_msg LRESULT OnSearchEditChange(WPARAM wParam ,LPARAM lParam);			//�û��б���������Ӧ
	afx_msg LRESULT OnClickUserList(WPARAM wParam, LPARAM lParam);				//����û��б�
	afx_msg LRESULT OnDBClickUserList(WPARAM wParam, LPARAM lParam);			//˫���û��б�
	afx_msg void OnNMRclickRoomUserList(NMHDR *pNMHDR, LRESULT *pResult);		//�Ҽ�����û��б�
	afx_msg void OnNMRclickRoomManagerList(NMHDR *pNMHDR, LRESULT *pResult);	//�Ҽ���������б�
	afx_msg void OnNMRclickRoomMicList(NMHDR *pNMHDR, LRESULT *pResult);		//�Ҽ���������б�
	afx_msg void OnNMRclickRoomSearchList(NMHDR *pNMHDR, LRESULT *pResult);		//�Ҽ���������б�
	afx_msg void OnNMRclickRoomAgentList(NMHDR *pNMHDR, LRESULT *pResult);		//�Ҽ���������б�

protected:
	//�û��б����
	void OnClickTabBtnMgr();					   								//���tab����
	void OnClickTabBtnUser();                      								//���tab�û�
	void OnClickTabBtnMic();                       								//���tab����
	void OnClickTabBtnAgt();													//���tab����
	void OnClickBtnSearch(int checked);            								//�������
	void OnClickBtnIconIntro(int checked);         								//���ͼ�����
	void SearchUserList(std::wstring strKey, ENM_UserListType enmListType);		//�����û��б�
	void UpdateUserListTabInfo();												//�����û��б�Tabҳ����
	int GetUserListCount();														//��������û�����
	int GetManagerListCount();													//��ù����û�����
	int GetMicListCount();														//��������û�����
	int GetGuestCount();														//����ο��û�����

private:
	CComPtr<ISkinEngine> m_pSkinEngine;
	CRoomParentDlg * m_pParentDlg;												//����������
	RoomBusiness * m_pRoomBusiness;												//����ҵ���߼�

	//�û��б�
	CAllUserListCtrl m_UserListCtrl;											//�û��б�ؼ�
	CManagerListCtrl m_ManagerListCtrl;											//�����б�ؼ�
	CWaitingUserList m_MicListCtrl;												//�����б�ؼ�
	CUserListCtrl m_SearchListCtrl;												//�����б�ؼ�
	CUserListCtrl m_AgentListCtrl;												//�����б�ؼ�
	CSearchDlg * m_pSearchDlg;													//�û��б�������
	//CIconIntroductionDlg* m_pIconIntroducDlg;									//ͼ��˵����

public:
	UserManager * GetUserManager();												//��ȡ�û�����
	IUserItem * GetSelfUserItem();												//��ȡ�Լ���Ϣ
	//������Ϣ������
	CSelfInfoAndSetDlg * m_pSelfInfoAndSetDlg; 
};
