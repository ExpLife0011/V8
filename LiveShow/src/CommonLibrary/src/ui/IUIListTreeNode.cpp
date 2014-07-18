#include "StdAfx.h"
#include "../../include/ui/IUIListTreeNode.h"

namespace common { namespace ui
{

IUIListTreeNode::IUIListTreeNode(IUITreeContainer* pContainer)
:
IUITreeNode(pContainer),
m_lTitleHeight(0)
{
}

IUIListTreeNode::~IUIListTreeNode(void)
{
}

LONG IUIListTreeNode::GetTitleHeight()
{
    return m_lTitleHeight;
}

void IUIListTreeNode::SetTitleHeight(LONG height)
{
    m_lTitleHeight = height;
}

void IUIListTreeNode::SetRect(const RECT& rect)
{
    for (int i=0; i<GetChildNum(); i++) {
        IUITreeNode* pNode = GetChild(i);
        CRect nodeRect = pNode->GetRect();
        nodeRect.right = rect.right;
        pNode->SetRect(nodeRect);
    }

    __super::SetRect(rect);
}

void IUIListTreeNode::OnChildNotify(IUITreeNode* pChild, UINT uCode, LPTNN lpTNN)
{
    __super::OnChildNotify(pChild, uCode, lpTNN);

    if (uCode == TNN_POSCHANGED) {
        int pos = GetChildPos(pChild);
        ASSERT(pos >= 0);
        if (pos < 0)
            return;

        CRect rcOld = lpTNN->rc;

        //�ض�λpChanged���ֵܽڵ�
        CRect changeRect = pChild->GetRect();
        LONG deltaHeight = changeRect.bottom - rcOld.bottom;
        int count = GetChildNum();
        for (int i=pos+1; i<count; i++) {
            IUITreeNode* pNode = GetChild(i);
            CRect rect = pNode->GetRect();
            rect.OffsetRect(0, deltaHeight);
            pNode->SetRect(rect);
            changeRect.bottom = rect.bottom;
        }

        //���¸��±��ڵ�
        CRect oldRect = GetRect();
        CRect newRect = oldRect;
        newRect.bottom += deltaHeight;
        SetRect(newRect);

        //�򸸽ڵ㴫��λ�øı�
        IUITreeNode* pParent = GetParent();
        if (pParent != NULL && oldRect.Height() != newRect.Height()) {
            TNN tnn = {oldRect, (0, 0)};
            pParent->OnChildNotify(this, TNN_POSCHANGED, &tnn);
        }
    }
}

//�����ӽڵ�
bool IUIListTreeNode::AddListChild(IUITreeNode* pChild, int iPos, const tagSIZE& szChild, LONG xOffset)
{
    ASSERT(GetChildPos(pChild) < 0);
    if (GetChildPos(pChild) >= 0)
        return false;

    //����ԭ������
    CRect oldRect = GetRect();

    //�����ӽڵ㣬�������ݣ������
    AddChild(pChild, iPos);

    //�����ӽڵ��λ�ã�����������
    int realPos = (iPos == -1) ? (GetChildNum() - 1) : (iPos);
    CSize size = szChild;
    CRect nodeRect(xOffset, 0, size.cx, size.cy);
    if (realPos == 0) {
        nodeRect.OffsetRect(0, m_lTitleHeight);
    } else {
        IUITreeNode* pPrevNode = GetChild(realPos - 1);
        CRect prevRect = pPrevNode->GetRect();
        nodeRect.OffsetRect(0, prevRect.bottom);
    }
    pChild->SetRect(nodeRect);

    //���²����ӽڵ������ֵܽڵ�λ��
    for (int i=realPos+1; i<GetChildNum(); i++) {
        IUITreeNode* pNext = GetChild(i);
        CRect rcTemp = pNext->GetRect();
        rcTemp.OffsetRect(0, nodeRect.Height());
        pNext->SetRect(rcTemp);
    }

    //���±��ڵ��λ��
    CRect newRect = oldRect;
    newRect.bottom += nodeRect.Height();
    if (! IsExpanded())
        newRect.bottom = newRect.top + m_lTitleHeight;
    SetRect(newRect);

    //֪ͨ���ڵ�
    IUITreeNode* pParent = GetParent();
    if (pParent != NULL && oldRect.Height() != newRect.Height()) {
        TNN tnn = {oldRect, (0, 0)};
        pParent->OnChildNotify(this, TNN_POSCHANGED, &tnn);
    }

    return true;
}

//�����ӽڵ�
bool IUIListTreeNode::UpdateListChild(IUITreeNode* pChild, const tagSIZE& szChlid, LONG xOffset)
{
    int iPos = GetChildPos(pChild);
    if (iPos < 0)
        return false;

    //����ԭ������
    CRect oldRect = GetRect();
    CRect nodeOldRect = pChild->GetRect();

    //�ӽڵ��λ�ã�����������
    int realPos = iPos;
    CSize size = szChlid;
    CRect nodeRect(xOffset, 0, size.cx, size.cy);
    if (realPos == 0) {
        nodeRect.OffsetRect(0, m_lTitleHeight);
    } else {
        IUITreeNode* pPrevNode = GetChild(realPos - 1);
        CRect prevRect = pPrevNode->GetRect();
        nodeRect.OffsetRect(0, prevRect.bottom);
    }
    pChild->SetRect(nodeRect);

    //���²����ӽڵ������ֵܽڵ�λ��
    for (int i=realPos+1; i<GetChildNum(); i++) {
        IUITreeNode* pNext = GetChild(i);
        CRect rcTemp = pNext->GetRect();
        rcTemp.OffsetRect(0, nodeRect.Height() - nodeOldRect.Height());
        pNext->SetRect(rcTemp);
    }

    //���±��ڵ��λ��
    CRect newRect = oldRect;
    newRect.bottom += nodeRect.Height() - nodeOldRect.Height();
    if (! IsExpanded())
        newRect.bottom = newRect.top + m_lTitleHeight;
    SetRect(newRect);

    //֪ͨ���ڵ�
    IUITreeNode* pParent = GetParent();
    if (pParent != NULL && oldRect.Height() != newRect.Height()) {
        TNN tnn = {oldRect, (0, 0)};
        pParent->OnChildNotify(this, TNN_POSCHANGED, &tnn);
    }

    return true;
}

//ɾ���ӽڵ�
bool IUIListTreeNode::RemoveListChild(IUITreeNode* pChild)
{
    int pos = GetChildPos(pChild);
    if (pos < 0)
        return false;

    CRect oldRect = GetRect();

    CRect changeRect = pChild->GetRect();
    LONG deltaHeight = -changeRect.Height();
    RemoveChild(pChild);

    //�ض�λpChanged���ֵܽڵ�
    int count = GetChildNum();
    for (int i=pos; i<count; i++) {
        IUITreeNode* pChild = GetChild(i);
        CRect rect = pChild->GetRect();
        rect.OffsetRect(0, deltaHeight);
        pChild->SetRect(rect);
    }

    //���¸��±��ڵ�
    CRect newRect = oldRect;
    newRect.bottom += deltaHeight;
    if (! IsExpanded())
        newRect.bottom = newRect.top + m_lTitleHeight;
    SetRect(newRect);

    //�򸸽ڵ㴫����Ϣ
    IUITreeNode* pParent = GetParent();
    if (pParent != NULL && oldRect.Height() != newRect.Height()) {
        TNN tnn = {oldRect, (0, 0)};
        pParent->OnChildNotify(this, TNN_POSCHANGED, &tnn);
    }

    return true;
}

} } //namespace common::ui
