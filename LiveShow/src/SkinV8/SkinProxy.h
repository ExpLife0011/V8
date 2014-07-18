#pragma once

#include "SkinBase.h"

// CSkinProxy

class CSkinProxy : public CSkinBase
{
	DECLARE_DYNCREATE(CSkinProxy)

public:
	CSkinProxy();
	virtual ~CSkinProxy();

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CSkinProxy)
	DECLARE_SKIN_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

protected:
	enum
	{
		SKINBASE_DISPIDS(CSkinProxy),

		SKIN_DISPID(CSkinProxy, SetClient),
        SKIN_DISPID(CSkinProxy, GetClient),
	};

public:
	//////////////////////////////////////////////////////////////////////////
	//���Ե�Get�麯��
	//////////////////////////////////////////////////////////////////////////
	////Ƥ��Ԫ�ص�����
	//virtual BSTR GetName();
	//Ƥ�����ı�
	virtual BSTR GetText();
	//�����
	virtual BSTR GetCursor();
	//����Ƥ��Ԫ�ص�λ��
	virtual LONG GetLeft();
	virtual LONG GetTop();
	virtual LONG GetWidth();
	virtual LONG GetHeight();
    virtual BOOL GetSizeDelay();
	//�ɼ���
	virtual BOOL GetVisible();
	//������
	virtual BOOL GetDisabled();
	//Tab Stop
	virtual BOOL GetTabStop();
	//Group
	virtual BOOL GetGroup();
	//��������
	virtual BOOL GetBackground();
	//͸��
	virtual BOOL GetTransparent();
	//��ɫ�任
	virtual BOOL GetColorTransform();
    //alphaͨ��
    virtual BOOL GetAlpha();
	//�ϱ߽ǰ뾶
	virtual LONG GetUpCornerRadius();
	//�±߽ǰ뾶
	virtual LONG GetDownCornerRadius();
	//���߿�
	virtual LONG GetBorderLineWidth();
	//������ɫ
	virtual LONG GetBorderLineColor();
	//͸��ɫ
	virtual LONG GetTransparentColor();

protected:
	//////////////////////////////////////////////////////////////////////////
	//���Ե�Set�麯��
	//////////////////////////////////////////////////////////////////////////
	////Ƥ��Ԫ�ص�����
	//virtual void SetName(LPCTSTR newVal);
	//�ı�
	virtual void SetText(LPCTSTR newVal);
	//�����
	virtual void SetCursor(LPCTSTR newVal);
	//����Ƥ��Ԫ�ص�λ��
	virtual void SetLeft(LONG newVal);
	virtual void SetTop(LONG newVal);
	virtual void SetWidth(LONG newVal);
	virtual void SetHeight(LONG newVal);
    virtual void SetSizeDelay(BOOL newVal);
	//�ɼ���
	virtual void SetVisible(BOOL newVal);
	//������
	virtual void SetDisabled(BOOL newVal);
	//Tab Stop
	virtual void SetTabStop(BOOL newVal);
	//Group
	virtual void SetGroup(BOOL newVal);
	//��������
	virtual void SetBackground(BOOL newVal);
	//͸��
	virtual void SetTransparent(BOOL newVal);
	//��ɫ�任
	virtual void SetColorTransform(BOOL newVal);
    //alphaͨ��
    virtual void SetAlpha(BOOL newVal);
	//�ϱ߽ǰ뾶
	virtual void SetUpCornerRadius(LONG newVal);
	//�±߽ǰ뾶
	virtual void SetDownCornerRadius(LONG newVal);
	//���߿�
	virtual void SetBorderLineWidth(LONG newVal);
	//������ɫ
	virtual void SetBorderLineColor(LONG newVal);
	//͸��ɫ
	virtual void SetTransparentColor(LONG newVal);

    //Size Delay
    BOOL GetSizeDelayFlag();
    virtual void SetSizeDelayFlag(BOOL bTrue);
    virtual BOOL ApplyDelayedSize(BOOL bRepaint = TRUE);

public:
	//������
	virtual CSkinBase* GetSkinParent();
	//Owner����
	virtual CSkinBase* GetSkinOwner();
	//��һ����
	virtual CSkinBase* GetSkinNext();
	//��һ����
	virtual CSkinBase* GetSkinPrev();
	//��õ�һ����Ԫ�أ�bForwardΪ����
	virtual CSkinBase* GetFirstSubSkin(UINT uFilterBits = 0, UINT uFilterValues = 0, BOOL bForward = TRUE);
	//�����һ�����ֵ�Ԫ�أ�bForwardΪ����
	virtual CSkinBase* GetNextSkin(UINT uFilterBits = 0, UINT uFilterValues = 0, BOOL bForward = TRUE);
	//���Թ���
	virtual BOOL IsFiltered(UINT uFilterBits, UINT uFilterValues);

public:
	//�������
	BOOL RemoveClient();

protected:

	BOOL UpdateClientProperty(CSkinBase* pClient);

	//////////////////////////////////////////////////////////////////////////
	//Dispatch Method
	//////////////////////////////////////////////////////////////////////////
	VARIANT_BOOL SetClient(LONG newVal);
    IUnknown* GetClient(void);

#ifdef V8_JS_ENGINE_SUPPORT
    //v8ʵ��
    v8::Handle<v8::Value> V8SetClient(const v8::Arguments& args);
    v8::Handle<v8::Value> V8GetClient(const v8::Arguments& args);
    virtual v8::Handle<v8::Value> V8InternalCallMethod(const CString& funcName, const v8::Arguments& args);
#endif //V8_JS_ENGINE_SUPPORT

protected:
	CSkinBase* m_pSkinClient;
};


