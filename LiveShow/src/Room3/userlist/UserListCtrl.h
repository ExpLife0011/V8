#pragma once
#include "skinlistctrl.h"
//#include "iuseritem.h"
#include "..\usermanager/UserItem.h"

#define COLUMN_COUT	6

enum ENM_UserListColumn
{
	COLUNM_VIP_LEVEL	= 0,
	COLUNM_MIC_STATUS	= 1,
	COLUNM_USER_LEVEL	= 2,
	COLUNM_USER_PIC		= 3,
	COLUNM_USER_NAME	= 4,
	COLUNM_USER_ID		= 5,
};

class CUserListCtrl : public CSkinListCtrl
{
public:
	CUserListCtrl(void);
	virtual ~CUserListCtrl(void);

	//��ʼ���û��б�
	virtual bool InitUserListCtrl(std::wstring strRoomName, bool bShowRoomName = false);

	//���뵥���û�
	virtual bool InsertUserItem(IUserItem * pUserItem);
	//���������û�
	virtual bool InsertUserItem(std::vector<IUserItem*> vecUserItem);
	//�����û�
	virtual bool UpdateUserItem(IUserItem * pUserItem);
	//ɾ���û�
	virtual bool DeleteUserItem(IUserItem * pUserItem);
	//�����û�
	virtual int FindUserItem(IUserItem * pUserItem);
	//�ƶ���nItem�����У���ѡ��״̬
	virtual void MoveTo(int nItem);
	//�ƶ���pUserItem�����У���ѡ��״̬
	virtual void MoveToUserItem(IUserItem * pUserItem);
	//�����б�ʵ������
	virtual bool UpdateUserList();

protected:
	//����pUserItem��ȡÿһ������ʾ����
	std::wstring GetDisplayText(IUserItem * pUserItem, uint32 unColumn);
	//����ص�����
	static int CALLBACK SortFun(LPARAM lParam1, LPARAM lParam2, LPARAM lParamList);
	
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);

	bool m_bTimerRunning;
	void UpdateColumnWidth(bool doRightNow = false);

	std::wstring m_strRoomName;
	bool m_bShowRoomName;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
