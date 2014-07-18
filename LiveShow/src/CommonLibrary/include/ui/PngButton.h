#pragma once
#include "afxwin.h"
#include "51ktvtype.h"
#include "../Common.h"
#include "ImageEx.h"

namespace common 
{
	namespace ui
	{
		#define  WM_ONCLICK_PNGBUTTON         WM_USER + 770
        #define WM_ONMOUSERHOVER_PNGBUTTON    WM_USER + 771
		#define WM_ONMOUSERLEAVE_PNGBUTTON    WM_USER + 772

		class COMMON_INTERFACE PngButton :
			public CWnd
		{
		public:
			PngButton(void);
			~PngButton(void);
			DECLARE_MESSAGE_MAP()
		protected:
			virtual BOOL PreTranslateMessage(MSG* pMsg);
			
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);
			afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam); 
			afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam); 
			afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
			afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
			afx_msg void OnClose();

			void DrawBtn();
			common::ui::ImageEx* GetDrawImage();
		public:
			BOOL CreateEx(CWnd* pBottomWnd, CWnd* pParentWnd);
			
			void SetBtnHandCursor(BOOL bHand);
			void SetBtnDisabled(BOOL bDis);
			void SetBtnChecked(BOOL bChecked);
			
			void SetNormalImg(CString & strNormalImg);
			void SetHoverImg(CString & strHoverImg);
			void SetDownImg(CString & strDownImg);
			void SetDisabledImg(CString & strDisabledImg);
			void SetContent(CString strContent, CString strFont, COLORREF color, int fontSize);

			void ShowBtnTask(CRect& rc);

			BOOL GetBtnChecked(){ return m_bChecked; }
		private:
			CWnd* m_pParentWnd;
			BOOL m_bHandCursor;
			BOOL m_bNormal;
			BOOL m_bHover;
			BOOL m_bDown;
			BOOL m_bOver;	//���λ�ڿؼ�֮��ʱ��ֵΪTRUE����֮ΪFALSE
			BOOL m_bDisabled;
			BOOL m_bChecked;
			CString m_strContent;//�ַ�����
			CString m_strConFont;//����
			COLORREF m_colCon;//��ɫ
			int m_fontSize;//�����С

			common::ui::ImageEx* m_imgNoamrl;
			common::ui::ImageEx* m_imgHover;
			common::ui::ImageEx* m_imgDown;
			common::ui::ImageEx* m_imgDisabled;

			CRect m_rcWnd;

			//���ڴ���͸��
			BLENDFUNCTION m_blend ;			
		};
        

	}
}