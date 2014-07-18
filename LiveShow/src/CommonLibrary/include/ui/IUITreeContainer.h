#pragma once

#include "../Common.h"
#include "IUIListTreeNode.h"

namespace common { namespace ui
{

class COMMON_INTERFACE CUITreeNodeCheckVisitor :
    public IUITreeNodeVisitor
{
public:
    CUITreeNodeCheckVisitor(bool bCheck = true) {
        m_bCheck = (bCheck != false);
    };
protected:
    virtual void Visit(IUITreeNode* pNode) {
        pNode->SetChecked(m_bCheck);
    };
protected:
    bool m_bCheck;
};

class COMMON_INTERFACE IUITreeContainer :
    public IUIListTreeNode
{
    friend class IUITreeNode;

public:
    /**
    @fn IUITreeContainer(void)
    @brief ���캯��
    */
    IUITreeContainer(void);

    /**
    @fn ~IUITreeContainer(void)
    @brief ��������
    */
    virtual ~IUITreeContainer(void);

    //////////////////////////////////////////////////////////////////////////
    //IUITreeNode
    //////////////////////////////////////////////////////////////////////////
    /** 
    @addtogroup IUITreeNode
    @brief IUITreeNode
    */ 
    //@{
    virtual void Draw(CDC* pDC, const RECT& rcBound);
    virtual void SetRect(const RECT& rect);
    virtual void CalcSize(tagSIZE& size);
    virtual void OnMouseMove(POINT pt, UINT uFlag);
    virtual void OnLButtonDown(POINT pt, UINT uFlag);
    virtual void OnLButtonUp(POINT pt, UINT uFlag);
    virtual void OnLButtonDblClk(POINT pt, UINT uFlag);
    virtual void OnRButtonDown(POINT pt, UINT uFlag);
    virtual void OnRButtonUp(POINT pt, UINT uFlag);
    virtual void OnRButtonDblClk(POINT pt, UINT uFlag);
    virtual void OnMouseEnter(POINT pt, UINT uFlag);
    virtual void OnMouseHover(POINT pt, UINT uFlag);
    virtual void OnMouseLeave(POINT pt, UINT uFlag);
    //@}

protected:
    /**
    @fn void Add(IUITreeNode* pNode)
    @brief ����½ڵ�
    */
    virtual void Add(IUITreeNode* pNode);

    /**
    @fn void Remove(IUITreeNode* pNode)
    @brief �Ƴ��ڵ�
    */
    virtual void Remove(IUITreeNode* pNode);

public:
    /**
    @fn bool Select(IUITreeNode* pNode)
    @brief ѡ��ڵ�
    @param [in] pNode Ҫѡ��Ľڵ�
    @return �Ƿ�ѡ��ɹ�
    */
    virtual bool Select(IUITreeNode* pNode);

    /**
    @fn std::vector<IUITreeNode*> GetSelected()
    @brief ���ѡ��Ľڵ�
    */
    virtual std::vector<IUITreeNode*> GetSelected();

    /**
    @fn bool Expand(IUITreeNode* pNode)
    @brief չ���ڵ�
    @param [in] pNode Ҫչ���Ľڵ�
    @return �Ƿ�չ���ɹ�
    */
    virtual bool Expand(IUITreeNode* pNode);

    /**
    @fn bool Redraw(IUITreeNode* pNode = NULL)
    @brief �ػ�ڵ�
    @param [in] pNode Ҫ�ػ�Ľڵ㣬NULLȫ���ػ�
    @return �Ƿ��ػ�ɹ�
    */
    virtual bool Redraw(IUITreeNode* pNode = NULL);

    /**
    @fn bool EnsureVisible(IUITreeNode* pNode)
    @brief ʹ�ڵ�ɼ�
    @param [in] pNode Ҫ�ɼ��Ľڵ�
    @return �Ƿ�ɹ�
    */
    virtual bool EnsureVisible(IUITreeNode* pNode);

    /**
    @fn bool ShowTip(IUITreeNode* pNode, LPCTSTR lpzText, LPCTSTR lpzTitle)
    @brief ��ʽtip
    @param [in] pNode Ҫ��ʾtip�Ľڵ�
    @param [in] lpzText Ҫ��ʾ��tip����
    @param [in] lpzTitle Ҫ��ʾtip�ı���
    @return �Ƿ�ɹ�
    */
    virtual bool ShowTip(IUITreeNode* pNode, LPCTSTR lpzText, LPCTSTR lpzTitle);

    /**
    @fn void HideTip()
    @brief ����tip
    */
	virtual void HideTip();

    /**
    @fn HWND GetHWND()
    @brief ��ô��ھ��
    @return ���ش��ھ��
    */
    virtual HWND GetHWND() = 0;

    /**
    @fn void GetOffset(POINT& offset)
    @brief ��ô��ڿͻ�����Ը��ڵ��ƫ��
    @param [out] offset ƫ��
    */
    virtual void GetOffset(POINT& offset) = 0;

    /** 
    @addtogroup GDI��Դ
    @brief GDI��Դ
    */ 
    //@{
    virtual COLORREF GetColor(int iIndex = 0);
    virtual HFONT GetFont(int iIndex = 0);
    virtual HICON GetIcon(int iIndex = 0);
    virtual HCURSOR GetCursor(int iIndex = 0);
    virtual HPEN GetPen(int iIndex = 0);
    virtual HBRUSH GetBrush(int iIndex = 0);
    virtual HBITMAP GetBitmap(int iIndex = 0);
    //@}

    /**
    @fn LRESULT SendMessage(UINT uMsg, IUITreeNode* pSender, WPARAM wParam, LPARAM lParam)
    @brief ��Ϣ���ͣ������¼�֪ͨ
    @param [in] uMsg ��Ϣֵ
    @param [in] pSender ��Ϣ������
    @param [in] wParam ����1
    @param [in] lParam ����2
    */
    virtual LRESULT SendMessage(UINT uMsg, IUITreeNode* pSender, WPARAM wParam = 0, LPARAM lParam = 0);

    /**
    @fn IUITreeNode* GetCapture()
    @brief �����겶��
    @return ��ò������Ľڵ�
    */
    virtual IUITreeNode* GetCapture();

    /**
    @fn IUITreeNode* SetCapture(IUITreeNode* pNode)
    @brief ������겶��
    @param [in] pNode Ҫ����Ľڵ�
    @return �ɵĲ���ڵ�
    */
    virtual IUITreeNode* SetCapture(IUITreeNode* pNode);

    /**
    @fn bool ReleaseCapture()
    @brief �ͷ���겶��
    @return �Ƿ��ͷ�
    */
    virtual bool ReleaseCapture();

protected:
    IUITreeNode* m_pCapture;
    IUITreeNode* m_pSelected;
    IUITreeNode* m_pMouseIn;
};

} } //namespace common::ui
