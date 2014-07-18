#pragma once

#include <vector>
#include <map>
#include "afxcmn.h"
#include "ximage.h"
#include "..\gift/GiftManager.h"

struct stStamp  //���½ṹ
{
	CString stampPath;//·��
	CString stampName;//����
};

struct stStampGroup //������ṹ
{
	CString groupName;//����
	std::vector<stStamp*> groupStamp;//�����µ����и���
};

typedef  std::vector<stStampGroup*>   VecStampGroup;
typedef  std::vector<stStamp*>    VecStamp;
typedef  std::map<int,stStamp*>   MapStamp;

class CStampListCtrl :
	public CListCtrl
{
public:
	CStampListCtrl(void);
	~CStampListCtrl(void);

protected:
    virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

    afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult); 
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);

	void DrawBorder(CDC* pDC,const CRect& rcBorder,COLORREF color,int iWidth);
	void Resize(long cx, long cy, RECT rcOuter, RECT& rcRet);
	void DrawHoverBorder(CDC* pDC,const CRect& rcBorder,COLORREF color,int iWidth);
  
	DECLARE_MESSAGE_MAP()
public:
	void Initialize();
	int  AddImage(int iIndex,CxImage * pImage);
	BOOL SetListData(int iGroup = 0);//Ĭ����ʾ��һ��
	void DeleteAll() ;//�����Ϣ
private:
	CImageList m_imageList;
	std::vector<CxImage*> m_pVectImgs;

	CToolTipCtrl m_OwnToolTipCtrl;
	int m_lastToolTip;
	CRect m_oldHoveRect;
	std::map< int , IGiftItem* > m_mapEmotion ;
   // MapStamp m_mapEmotion;//ÿ��ITEM��Ӧ��Ϣ����ÿ��������Ϣ
	int m_curGroup;//��ǰ��ʾ������
	
};
