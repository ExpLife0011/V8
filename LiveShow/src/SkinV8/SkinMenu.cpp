// MenuEx.cpp: implementation of the CSkinMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SkinMenu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC( CSkinMenu, CMenu )
CSkinMenu::CSkinMenu():m_szImage(16,15)
{
	m_nTotalWidth = -1;
	m_colMenu = RGB(250,250,250);
	m_colText = RGB(7,30,129);
	m_colTextSelected =RGB(0,0,0);

	m_bHasImageLeft =FALSE;
	m_nSeparator = 7;	//sparator��Ĭ�ϸ߶�
}

CSkinMenu::~CSkinMenu()
{
	m_ImageList.DeleteImageList();

	if(m_bHasImageLeft)
		m_bmpImageLeft.DeleteObject();

	//�ͷ����е��Ӳ˵�
	int i = 0;
	for(i = 0; i < m_SubMenuArr.GetSize(); i++)
	{
		CSkinMenu *pSubMenu = m_SubMenuArr.GetAt(i);
		delete pSubMenu;
	}
	
	//�ͷ����еĲ˵���
	for(i = 0; i < m_MenuItemArr.GetSize(); i++)
	{
		MENUITEM *pMenuItem = m_MenuItemArr.GetAt(i);
		delete pMenuItem;
	}
	
	//���ٲ˵�
	DestroyMenu();
}
/////////////////////////////////////////////////
//���˵���Ϊ������ʱ���ƻ�ɫ���ı�
void CSkinMenu::GrayString(CDC *pDC, const CString &str, const CRect rect)
{
	CRect	rt(rect);
	//int nMode =pDC->SetBkMode(TRANSPARENT);

	rt.left +=1;
	rt.top +=1;
		
	pDC->SetTextColor(RGB(255,255,255));
	pDC->DrawText(str,&rt,DT_EXPANDTABS|DT_VCENTER|DT_SINGLELINE);

	rt.left -=1;
	rt.top -=1;
	pDC->SetTextColor(RGB(127,127,127));
	pDC->DrawText(str,&rt,DT_EXPANDTABS|DT_VCENTER|DT_SINGLELINE);

	//pDC->SetBkMode(nMode);
}
/////////////////////////////////////////////////
//���Ʋ˵���λͼ
void CSkinMenu::DrawMenuItemImage(CDC *pDC, CRect &rect, BOOL bSelected, BOOL bChecked,
								BOOL bGrayed, BOOL bHasImage,LPMENUITEM lpItem)
{
	CRect	rt(rect.left ,rect.top ,rect.left + m_szImage.cx + 4,
									rect.top + m_szImage.cy + 4);

	if(bChecked)
	{	
		if(bGrayed)
		{	
			//�˵�������
			GrayString(pDC,"��",rt);
		}
		else
		{
			if(bSelected)
			{
				//�˵�ѡ��
				//�����ѡ�н������һ���������
				//pDC->Draw3dRect(&rt,RGB(255,255,255),RGB(127,127,127));
			}

			rt.InflateRect(-2,-2);
			
			//����"��"
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(m_colText);
			pDC->DrawText("��",&rt,DT_EXPANDTABS|DT_VCENTER|DT_SINGLELINE);
		}
		
		rect.left +=m_szImage.cx + 4 +2 ;
		
		return ;
	}
	

	if(bHasImage)
	{
		CPoint pt(rt.left+2 , rt.top+2 );
		if(bSelected)
		{
			//pt.x = rt.left + 1;
			pt.y = rt.top + 1;
		}
		UINT	uStyle =ILD_TRANSPARENT;	//CImageList::Draw()����λͼ�ķ��
		if(bGrayed)
		{
			uStyle |=ILD_BLEND50;	//�˵�����������λͼ�ϰ�
		}
		else
		{
			if(bSelected)
			{
				//�����ѡ�н������һ���������
				//pDC->Draw3dRect(&rt,RGB(255,255,255),RGB(127,127,127));
			}
		}
//		pDC->FillSolidRect(rect.left + 2,rect.top + 2,m_szImage.cx,m_szImage.cy,0);
		lpItem->pImageList->Draw(pDC,lpItem->uIndex,pt,uStyle);	//�ڲ˵����л���λͼ

		//�����ɻ��ƾ��εĴ�С
		//4��λͼ��Ӿ��α�λͼ��4
		//2���˵��ı���λͼ��Ӿ��εļ��Ϊ2
		//rect.left  +=m_szImage.cx + 4 + 2;
	}
}
/////////////////////////////////////////////////
//���Ʋ˵����ı�
//������rect:������ε�CRect
//		rtText:�˵��ı���CRect
void CSkinMenu::TextMenu(CDC *pDC, CRect rect,CRect rcText,BOOL bSelected, BOOL bGrayed, LPMENUITEM lpItem)
{
	//ѡ��״̬�Ĳ˵���Ҫ�Ȼ����������
	
	if(bSelected)
	{
		CRect rcItem = rect;
		CPen BorderPen,*pOldPen;
		BorderPen.CreatePen(PS_SOLID,1,RGB(134,165,196));
		CBrush BKBrush,*pOldBrush;
		BKBrush.CreateSolidBrush(RGB(207,231,255));
		pOldPen = pDC->SelectObject(&BorderPen);
		pOldBrush = pDC->SelectObject(&BKBrush);
		
		pDC->Rectangle(&rcItem);
		
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);
	}

	if(bGrayed)
	{
		//GrayString(pDC,lpItem->strText,rtText);
		CPoint pt(rcText.left,rcText.top);
		CSize si(rcText.Width(),rcText.Height());
		pDC->DrawState(pt, si, lpItem->strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		//pDC->DrawText(lpItem->strText,rtText,DT_LEFT | DT_EXPANDTABS | DT_VCENTER | DT_GRAY);
	}
	else
	{
		rcText.top += 3;
		pDC->DrawText(lpItem->strText,rcText,DT_LEFT | DT_EXPANDTABS | DT_VCENTER);
	}
}

void CSkinMenu::DrawImageLeft(CDC *pDC, CRect &rect,LPMENUITEM lpItem)
{
	if(!m_bHasImageLeft || lpItem->uPositionImageLeft == -1)
		return ;
	
	CDC  memDC;
	if(!memDC.CreateCompatibleDC(pDC)) return;
	CBitmap	*oldBmp =(CBitmap *) memDC.SelectObject(&m_bmpImageLeft);

	int cy;	//�趨�ò˵���Ӧ���Ļ���

	//cy = m_szImageLeft.cy - rect.Height() * lpItem->uPositionImageLeft;
	cy = 0;
	pDC->BitBlt(rect.left ,rect.top ,m_szImageLeft.cx ,rect.Height(),&memDC,0,cy,SRCCOPY);

	memDC.SelectObject(oldBmp);
	memDC.DeleteDC();

	rect.left +=m_szImageLeft.cx+1;
}

void CSkinMenu::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC	dc;
	LPMENUITEM lpItem;
	CRect rect(lpDIS->rcItem);
	dc.Attach(lpDIS->hDC);
	lpItem =(LPMENUITEM)lpDIS->itemData;

	//��ѡ�еĻ�,ʹ�ñ�ѡ�е��ı���ɫ
	if(lpDIS->itemState & ODS_SELECTED)
		dc.SetTextColor(m_colTextSelected);
	else
		dc.SetTextColor(m_colText);

	//�趨����ɫ
	CBrush brush(m_colMenu);
	dc.FillRect(&rect, &brush);

	CRect rcLeft = rect;
	rcLeft.right = rcLeft.left + m_szImage.cx + 5;

	CRect rcText = rect;
	rcText.left += (m_szImage.cx + 10);
	
	dc.FillSolidRect(&rcLeft, RGB(140,210,255));
	
	//�趨��ʾģʽ
	dc.SetBkMode(TRANSPARENT);
		
	if(lpItem->uID==0)//�ָ���
	{
		rcText.top =rcText.Height()/2+rcText.top ;
		rcText.bottom =rcText.top +2;
		rcText.right -=2;
		dc.Draw3dRect(rcText,RGB(170,194,218),RGB(255,255,255));
	}
	else
	{
		BOOL	bSelected =lpDIS->itemState & ODS_SELECTED;
		BOOL	bChecked  =lpDIS->itemState & ODS_CHECKED;
		BOOL	bGrayed	  =lpDIS->itemState & ODS_GRAYED;
		BOOL	bHasImage =(lpItem->uIndex != -1);
		
		//���Ʋ˵��ı�
		TextMenu(&dc,rect,rcText,bSelected,bGrayed,lpItem);
		
		//���Ʋ˵�λͼ
		DrawMenuItemImage(&dc,rect,bSelected,bChecked,bGrayed,bHasImage,lpItem);
	}
	dc.SetBkMode(OPAQUE);
	dc.Detach();
}

//////////////////////////////////////////////////////////
//�ɹ�������λͼ�������˵����õ�λͼ�б�m_ImageList
int CSkinMenu::GetImageFromToolBar(UINT uToolBar, CToolBar *pToolBar,COLORREF	crMask/*������λͼ������*/,UINT uBitmap)
{
	if(!pToolBar)
		return 0;

	CBitmap	bmp;
	int nWidth,nHeight;
	BITMAP	bmpInfo;

	bmp.LoadBitmap(uToolBar);
	bmp.GetBitmap(&bmpInfo);
	//�õ�λͼ�ĸ߶�
	nHeight =bmpInfo.bmHeight;

	int nCount=0;
	int	ret =pToolBar->GetToolBarCtrl().GetButtonCount();

	//�õ���������λͼ�ĸ���nCount
	for(int i=0;i<ret;i++)
	{
		UINT uID = pToolBar->GetItemID(i);
		for(int j = 0; j < m_MenuItemArr.GetSize(); j++)
		{
			MENUITEM *pMenuItem = m_MenuItemArr.GetAt(j);
			if(pMenuItem->uID == uID)
			{
				pMenuItem->uIndex = i;
			}
		}


		if(uID != ID_SEPARATOR)
			nCount ++;
	}

/*
	for(int j = 0; j < m_MenuItemArr.GetSize(); j++)
	{
		MENUITEM *pMenuItem = m_MenuItemArr.GetAt(j);
		pMenuItem->uIndex = 2;
	}
*/

	//�����λͼ�Ŀ��
	nWidth =bmpInfo.bmWidth/nCount;

	bmp.DeleteObject();

	TRACE("Menu Bitmap--width:%d\theight:%d\n",nWidth,nHeight);
	
	//����λͼ�б�
	if(uBitmap)
	{
		m_ImageList.Create(uBitmap,nWidth,nHeight,crMask);
	}
	else
	{
		BOOL bRet = m_ImageList.Create(uToolBar,nWidth,5,crMask);
	}
	m_szImage.cx =nWidth;
	m_szImage.cy =nHeight;

	return nCount;
}

void CSkinMenu::MeasureItem(LPMEASUREITEMSTRUCT  lpMIS)
{
	MENUITEM *lpItem =(LPMENUITEM)lpMIS->itemData;

	if(lpItem->uID==0)//�ָ���
	{
		lpMIS->itemHeight =m_nSeparator;
	}
	else
	{
		CDC *pDC =AfxGetMainWnd()->GetDC();		

		if(m_nTotalWidth <= 0)
		{
			CString	strText=lpItem->strText;
			CSize  size;
			size=pDC->GetTextExtent(lpItem->strText);

			lpMIS->itemWidth = size.cx + m_szImage.cx;
			
			if(lpItem->uPositionImageLeft >= 0)
			{
				lpMIS->itemWidth += 30;
			}
			
			if(lpItem->uID == -1)
			{
				lpMIS->itemWidth += 15;
			}
		}
		else
		{
			lpMIS->itemWidth = m_nTotalWidth - 2 - m_szImage.cx;
		}
		
		lpMIS->itemHeight = m_szImage.cy+4;
		
		AfxGetMainWnd()->ReleaseDC(pDC);
	}
}

void CSkinMenu::SetImageLeft(UINT idBmpLeft,BOOL bIsPopupMenu)
{
	if(m_bHasImageLeft)
		m_bmpImageLeft.DeleteObject();
	m_bmpImageLeft.LoadBitmap(idBmpLeft);
	m_bHasImageLeft = TRUE;
	BITMAP	bmpInfo;
	m_bmpImageLeft.GetBitmap(&bmpInfo);
	m_szImageLeft.cx =bmpInfo.bmWidth;
	m_szImageLeft.cy =bmpInfo.bmHeight;
	for(int i=0; i < m_MenuItemArr.GetSize(); i++)
	{
		MENUITEM *pMenuItem = m_MenuItemArr.GetAt(i);
		pMenuItem->uPositionImageLeft = 1;
	}
}

void CSkinMenu::SetTextColor(COLORREF crColor)
{
	m_colText =crColor;
	for(int i = 0; i < m_SubMenuArr.GetSize(); i++)
	{
		CSkinMenu *pSubMenu = m_SubMenuArr.GetAt(i);
		pSubMenu->SetTextColor(crColor);
	}
}

void CSkinMenu::SetBackColor(COLORREF crColor)
{
	m_colMenu =crColor;
	for(int i = 0; i < m_SubMenuArr.GetSize(); i++)
	{
		CSkinMenu *pSubMenu = m_SubMenuArr.GetAt(i);
		pSubMenu->SetBackColor(crColor);
	}
}

void CSkinMenu::SetHighLightColor(COLORREF crColor)
{
	m_colTextSelected =crColor;
	for(int i = 0; i < m_SubMenuArr.GetSize(); i++)
	{
		CSkinMenu *pSubMenu = m_SubMenuArr.GetAt(i);
		pSubMenu->SetHighLightColor(crColor);
	}
}

void CSkinMenu::LoadToolBar(UINT uToolBar, UINT uFace)
{
	CToolBar m_wndToolBar;
	if (!m_wndToolBar.CreateEx(AfxGetMainWnd(), TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE |
		CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(uToolBar))
	{
		return;
	}
	GetImageFromToolBar(uToolBar,&m_wndToolBar,RGB(192,192,192),0);	
}
BOOL CSkinMenu::RemoveMenuEx(UINT nPosition, UINT nFlags)
{
	UINT uItemID = 0;
	if(nFlags & MF_BYPOSITION)
	{
		uItemID = GetMenuItemID((int)nPosition);
	}
	else
	{
		uItemID = nPosition;
	}
	if((int) uItemID >= 0)			//��ͨ�˵����ָ���
	{
		for(int i = 0; i < m_MenuItemArr.GetSize(); i++)
		{
			MENUITEM *pMenuItem = m_MenuItemArr.GetAt(i);
			if(pMenuItem->uID == uItemID)
			{
				m_MenuItemArr.RemoveAt(i);
				break;
			}
		}
	}
	else                           //�Ӳ˵�
	{
	}
	return CMenu::RemoveMenu(nPosition,nFlags);
}

void CSkinMenu::SetWidth(int nWidth)
{
	m_nTotalWidth = nWidth;
}

void CSkinMenu::SetHeight(int nHeight)
{

}

BOOL CSkinMenu::AppendMenuEx(UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem)
{
	MENUITEM *pMenuItem = new MENUITEM;
	pMenuItem->strText = lpszNewItem;
	pMenuItem->uID = nIDNewItem;
	pMenuItem->uIndex = -1;
	pMenuItem->uPositionImageLeft = -1;
/*
	UINT uNewFlags = 0;
	if(nFlags & MF_CHECKED) uNewFlags |= MF_CHECKED;
	if(nFlags & MF_UNCHECKED) uNewFlags |= MF_UNCHECKED;
	if(nFlags & MF_SEPARATOR) uNewFlags |= MF_SEPARATOR;
	uNewFlags |= MF_OWNERDRAW;*/

	nFlags &= ~MF_STRING;
	nFlags |= MF_OWNERDRAW;

	m_MenuItemArr.Add(pMenuItem);
	return CMenu::AppendMenu(nFlags,nIDNewItem,(LPCTSTR)pMenuItem);
}

BOOL CSkinMenu::LoadMenu(UINT uMenu)
{
	//���¶���˵�,����Ϊpopup�˵�,�����Ի�(�ɿ�ܵ���MesureItem() �� DrawItem()
	HMENU hMenu = ::CreateMenu();
	this->Attach(hMenu);

	CMenu Menu;		//��ʱ�˵�
	UINT uID;
	Menu.LoadMenu(uMenu);
	for(int i = 0; i < (int)Menu.GetMenuItemCount(); i++)
	{
		uID = Menu.GetMenuItemID(i);
		if(uID == 0)			//�ָ���
		{
			::AppendMenu(hMenu,MF_SEPARATOR,0,NULL);
		}
		else if((int)uID == -1)		//�����˵�(���Ӳ˵�)
		{
			CMenu *pSubMenu = Menu.GetSubMenu(i);
			
			//�����Ӳ˵�	
			HMENU hSubMenu = ::CreatePopupMenu();
			CString strPopup;
			Menu.GetMenuString(i,strPopup,MF_BYPOSITION);
			::InsertMenu(hMenu,i,MF_BYPOSITION | MF_POPUP | MF_STRING,(UINT)hSubMenu,strPopup);						
			
			//���Ӳ˵��ݹ����ChangeMenuStyle(),���Ӳ˵���ΪMF_OWNERDRAW���
			ChangeMenuStyle(pSubMenu,hSubMenu);
		}
		else					//�����Ĳ˵���
		{
			CString strText;
			Menu.GetMenuString(uID,strText,MF_BYCOMMAND);
			AppendMenu(MF_STRING,uID,strText);
		}
	}
	Menu.DestroyMenu();			//������ʱ�˵�
	return TRUE;
}

void CSkinMenu::ChangeMenuStyle(CMenu *pMenu,HMENU hNewMenu)
{	
	//����ΪCSkinMenu(����ΪCSkinMenu������Զ��ػ�
	//ԭ����(CMenu��װ�Ľ��?)

	CSkinMenu *pNewMenu;
	pNewMenu = new CSkinMenu;
	pNewMenu->Attach(hNewMenu);
	m_SubMenuArr.Add(pNewMenu);


	UINT uID;
	int nItemCount = pMenu->GetMenuItemCount();
	for(int i = 0; i < nItemCount; i++)
	{
		uID = pMenu->GetMenuItemID(i);
		if(uID == 0)			//�ָ���
		{
			::AppendMenu(hNewMenu,MF_SEPARATOR,0,NULL);
			CString strText;
			MENUITEM *pMenuItem = new MENUITEM;
			pMenuItem->uID = 0;
			pMenuItem->uIndex = -1;
			pMenuItem->uPositionImageLeft = -1;
			pMenuItem->pImageList = &m_ImageList;
			m_MenuItemArr.Add(pMenuItem);
			
			::ModifyMenu(hNewMenu,i,MF_BYPOSITION | MF_OWNERDRAW,-1,(LPCTSTR)pMenuItem);		
		}
		else if(uID == -1)		//�����˵�(���Ӳ˵�)
		{
			CMenu *pSubMenu = pMenu->GetSubMenu(i);
			HMENU hPopMenu = ::CreatePopupMenu();
			CString strPopup;
			pMenu->GetMenuString(i,strPopup,MF_BYPOSITION);
			::InsertMenu(hNewMenu,i,MF_BYPOSITION | MF_POPUP,(UINT)hPopMenu,strPopup);

			MENUITEM *pMenuItem = new MENUITEM;
			pMenuItem->uID = -1;
			pMenuItem->strText = strPopup;
			pMenuItem->uIndex = -1;
			pMenuItem->uPositionImageLeft = -1;
			pMenuItem->pImageList = &m_ImageList;
			m_MenuItemArr.Add(pMenuItem);
			::ModifyMenu(hNewMenu,i,MF_BYPOSITION | MF_OWNERDRAW,-1,(LPCTSTR)pMenuItem);
			
			//pNewMenu->ModifyMenuEx(i,MF_BYPOSITION,-1,strPopup);

			
			ChangeMenuStyle(pSubMenu,hPopMenu);
			
		}
		else					//�����Ĳ˵���
		{
			CString strText;
			pMenu->GetMenuString(uID,strText,MF_BYCOMMAND);
			MENUITEM *pMenuItem = new MENUITEM;
			pMenuItem->uID = pMenu->GetMenuItemID(i);
			pMenu->GetMenuString(pMenuItem->uID,pMenuItem->strText,MF_BYCOMMAND);
			pMenuItem->uIndex = -1;
			pMenuItem->uPositionImageLeft = -1;
			pMenuItem->pImageList = &m_ImageList;
			//::AppendMenu(hNewMenu,MF_STRING,uID,(LPCTSTR)pMenuItem->strText);
			m_MenuItemArr.Add(pMenuItem);

			UINT uState = pMenu->GetMenuState(i,MF_BYPOSITION);
			::AppendMenu(hNewMenu,MF_OWNERDRAW | MF_BYCOMMAND | uState,uID,(LPCTSTR)pMenuItem);

			//pNewMenu->AppendMenuEx(MF_STRING,uID,strText);
		}
	}
}

BOOL CSkinMenu::ModifyMenuEx(UINT nPosition, UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem)
{
	UINT uItemID = 0;
	if(nFlags & MF_BYPOSITION)
	{
		uItemID = GetMenuItemID((int)nPosition);
	}
	else
	{
		uItemID = nPosition;
	}
	//��ͨ�˵���͵���ʽ�˵�
	MENUITEM *pMenuItem = NULL;
	int i = 0;
	for(i = 0; i < m_MenuItemArr.GetSize(); i++)
	{
		pMenuItem = m_MenuItemArr.GetAt(i);
		if(pMenuItem->uID == uItemID)
		{
			pMenuItem->strText = lpszNewItem;
			if((int)nIDNewItem != 0)
				pMenuItem->uID = nIDNewItem;
			break;
		}
	}
	//û�ҵ���Ӧ�Ĳ˵���
	if(i >= m_MenuItemArr.GetSize())
	{
		MENUITEM *pMenuItem = new MENUITEM;
		pMenuItem->strText = lpszNewItem;
		pMenuItem->uID = nIDNewItem;
		pMenuItem->pImageList = &m_ImageList;
		m_MenuItemArr.Add(pMenuItem);
	}
	
/*
	UINT uNewFlags = 0;
	if(nFlags & MF_CHECKED) uNewFlags |= MF_CHECKED;
	if(nFlags & MF_UNCHECKED) uNewFlags |= MF_UNCHECKED;
	if(nFlags & MF_BYPOSITION) uNewFlags |= MF_BYPOSITION;
	if(nFlags & MF_BYCOMMAND) uNewFlags |= MF_BYCOMMAND;
	uNewFlags |= MF_OWNERDRAW;*/

	nFlags &= ~MF_STRING;
	nFlags |= MF_OWNERDRAW;
	
	return CMenu::ModifyMenu(nPosition,nFlags,nIDNewItem,(LPCTSTR)pMenuItem);
}

void CSkinMenu::CalculateLeftImagePos(CMenu *pPopupMenu)
{
	int MenuItemCount = pPopupMenu->GetMenuItemCount();

	for(int i = MenuItemCount - 1 ; i >= 0; i--)
	{
		int nID = pPopupMenu->GetMenuItemID(i);
		CString strText;
		pPopupMenu->GetMenuString(i,strText,MF_BYPOSITION);
		for(int j = 0; j < m_MenuItemArr.GetSize(); j++)
		{
			MENUITEM *pMenuItem = m_MenuItemArr.GetAt(j);
			if((int)pMenuItem->uID == nID)
			{
				pMenuItem->uPositionImageLeft = MenuItemCount - 1 - i;
			}
		}
	}
}
