#pragma once

#include "XmlCmdTarget.h"
#include "SkinBaseDefine.h"

#ifdef V8_JS_ENGINE_SUPPORT
#include "V8ContextFunction.h"
#endif //V8_JS_ENGINE_SUPPORT

#include <list>
#include <map>

class CImageTransformParam;
class CSkinEngine;
class CSkinItem;
class CImageBase;
class CSkinProxy;
class CSkinBase : public CXmlCmdTarget
{
	friend class CSkinEngine;
	friend class CSkinProxy;
	DECLARE_DYNCREATE(CSkinBase)
protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_SKIN_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
	DECLARE_SKINBASE_PROPERTIES()

    //////////////////////////////////////////////////////////////////////////
    //Script֧��
    //////////////////////////////////////////////////////////////////////////
#ifdef V8_JS_ENGINE_SUPPORT

    //V8֧��
    BOOL AddObjectToSrcipt(v8::Handle<v8::Object> object);

#endif //V8_JS_ENGINE_SUPPORT

#ifdef MS_JS_ENGINE_SUPPORT

protected:
	HRESULT GetItemInfo(LPCOLESTR pstrName, DWORD dwReturnMask, IUnknown **ppiunkItem, ITypeInfo **ppti);
	HRESULT OnScriptError(IActiveScriptError *pscripterror);

protected:
	HRESULT GetWindow(HWND *phwnd);

	//��ű���¶���ֿռ�
public:
    BOOL AddNameItemToSrcipt(CComPtr<IActiveScript> pScript);

#endif //MS_JS_ENGINE_SUPPORT

public:
    //��ʼ�����ļ�·��
    BOOL SetConfigFileName(LPCTSTR strConfigFileName);
    CString GetXmlFileName() const;
    CString GetScriptFileName() const;

    //XML����
    BOOL CreateSubSkinFromXml(IXMLDOMElementPtr ptrDocumentRoot, BOOL bPreLoad = TRUE);
    BOOL LoadSubSkinPropFromXml(IXMLDOMElementPtr ptrDocumentRoot);
    BOOL PreLoadXml(LPCTSTR lpzPreLoad);
    static BOOL GetXmlRoot(const char* pzXml, BOOL bUnicode, IXMLDOMElement** ppXmlRoot);
    BOOL CreateFromXml();
    BOOL LoadPropFromXml();
    BOOL ParseXmlHelper(IXMLDOMElementPtr ptrDocumentRoot);
    BOOL LoadXML(const char* pzXml, BOOL bUnicode = TRUE);
    BOOL ParseXml();

    CString						   m_strConfigName;

protected:
	enum
	{
		SKINBASE_DISPIDS(CSkinBase),
	};

	//////////////////////////////////////////////////////////////////////////
	//�������������
	//////////////////////////////////////////////////////////////////////////
public:
    //���캯��
	CSkinBase();
    //��������
	virtual ~CSkinBase();
protected:
    //��ʼ����������SkinEngine���ã���Ҫ���ڼ���Ĭ������
    virtual void Initialize();
    //�ͷ�Ƥ��Ԫ��
	virtual DWORD ReleaseSkin();
    //�������ñ��ͷ�ʱ����
	virtual void OnFinalRelease();

	//////////////////////////////////////////////////////////////////////////
	//���Ƥ�������ļ���Ŀ¼�������ļ�������
	//////////////////////////////////////////////////////////////////////////
public:
	//���Ƥ��·��
	CString GetSkinPath() const;

	//////////////////////////////////////////////////////////////////////////
	//�������ں�������ΪCSkinProxy�Ĵ���ģʽ�����ֺ�����Ҫ��Ϊ�麯��
	//////////////////////////////////////////////////////////////////////////
public:
	//������
	virtual CSkinProxy* GetSkinProxy();
	//������
	virtual CSkinBase* GetSkinParent();
	//������
	void SetSkinParent(CSkinBase* pSkinParent);
	//Owner����
	virtual CSkinBase* GetSkinOwner();
	//��һ����
	virtual CSkinBase* GetSkinNext();
	//��һ����
	virtual CSkinBase* GetSkinPrev();
	//���ȴ���
	CSkinBase* GetSkinAncestor();
private:
	//Owner����
	void SetSkinOwner(CSkinBase* pSkinOwner);
	//��һ����
	void SetSkinNext(CSkinBase* pSkinNext);
	//��һ����
	void SetSkinPrev(CSkinBase* pSkinPrev);

protected:
    CSkinBase* CreateSkinChild(LPCTSTR lpzClassName, LPCTSTR lpzChildName);

	//////////////////////////////////////////////////////////////////////////
	//���������ʺ�������ΪCSkinProxy�Ĵ���ģʽ�����ֺ�����Ҫ��Ϊ�麯��
	//////////////////////////////////////////////////////////////////////////
public:
	//��õ�һ����Ԫ�أ�bForwardΪ����
	virtual CSkinBase* GetFirstSubSkin(UINT uFilterBits = 0, UINT uFilterValues = 0, BOOL bForward = TRUE);
	//�����һ�����ֵ�Ԫ�أ�bForwardΪ����
	virtual CSkinBase* GetNextSkin(UINT uFilterBits = 0, UINT uFilterValues = 0, BOOL bForward = TRUE);
	//����Skin����bForwardΪ����
	static BOOL WalkSubSkinTree(CSkinBase* pRoot, CSkinBase*& pFind,
		UINT uFilterBits = 0, UINT uFilterValues = 0,
		UINT uNodeFileterBits = 0, UINT uNodeFilterValues = 0,
		BOOL bForward = TRUE);
	static BOOL WalkSkinTree(CSkinBase* pStart, CSkinBase*& pFind,
		UINT uFilterBits = 0, UINT uFilterValues = 0,
		UINT uNodeFileterBits = 0, UINT uNodeFilterValues = 0,
		BOOL bForward = TRUE);
	//�����һ��ͨ��Tab�����ս����Ƥ������bForwardΪ����
	CSkinBase* GetNextTabStopSkinInSkinTree(BOOL bForward = TRUE);

public:
	//���Ƥ�������������Ĵ��ھ��������ô��ھ�������֮�������ƫ�ƣ���ƫ�ư�����Ը����ڵ�ƫ��
	//�����SkinItem������ΪSkinItem�ľ��
	HWND GetSkinHwnd(LPPOINT lpOffset = NULL);

	//�����Ƥ�������Ĵ��ڵ�����ƫ��
	BOOL GetSkinHwndOffset(LPPOINT lpOffset);

	//���Ƥ�����������Ĵ��ھ��������Ƥ������
	CSkinItem* GetSkinHwndItem(LPPOINT lpOffset = NULL);

	//Ƥ��������Ƥ������
	CSkinEngine* GetEngine() const;

	//���ͼ��任����
	const CImageTransformParam* GetImageParam() const;

	//���Ƥ������
	virtual CString GetSkinName();

    //���Ƥ������
    virtual CString GetSkinClassName();

    //���Ƥ��Ԥ��������
    virtual CString GetSkinPreLoad();

	//���Ƥ��������
	virtual CString GetClassName();

	//���Ƥ������
	virtual CString GetSkinText();

    //Size Delay
    virtual BOOL GetSizeDelayFlag();
    virtual void SetSizeDelayFlag(BOOL bTrue);
    virtual BOOL ApplyDelayedSize(BOOL bRepaint = TRUE);
    void SetSubSkinSizeDelayFlag(BOOL bTrue);
    void ApplySubSkinDelayedSize(BOOL bRepaint = TRUE);

	//����ת��
	//skin����ת��Ļ����
	virtual BOOL SkinToScreen(LONG& x, LONG& y);
	virtual BOOL SkinToScreen(POINT& point);
	virtual BOOL SkinToScreen(RECT& rect);
	//��Ļ����תskin����
	virtual BOOL ScreenToSkin(LONG& x, LONG& y);
	virtual BOOL ScreenToSkin(POINT& point);
	virtual BOOL ScreenToSkin(RECT& rect);
	//skin����ת����������
	virtual BOOL SkinToSkinParent(LONG& x, LONG& y);
	virtual BOOL SkinToSkinParent(POINT& point);
	virtual BOOL SkinToSkinParent(RECT& rect);
	//����������skin����
	virtual BOOL SkinParentToSkin(LONG& x, LONG& y);
	virtual BOOL SkinParentToSkin(POINT& point);
	virtual BOOL SkinParentToSkin(RECT& rect);
	//skin����תskin�����Ĵ�������
	virtual BOOL SkinToSkinHwnd(LONG& x, LONG& y);
	virtual BOOL SkinToSkinHwnd(POINT& point);
	virtual BOOL SkinToSkinHwnd(RECT& rect);
	//skin�����Ĵ�������תskin����
	virtual BOOL SkinHwndToSkin(LONG& x, LONG& y);
	virtual BOOL SkinHwndToSkin(POINT& point);
	virtual BOOL SkinHwndToSkin(RECT& rect);

	//���Ƥ������
	virtual CRect GetSkinRect();	//����Ը����ڵ�ƫ��
	virtual CRect GetSkinAbsRect();	//������Ը����ڵ�ƫ��

	//�жϵ��Ƿ���Ƥ��������
	virtual BOOL IsPointInSkinRect(POINT pt);
	virtual BOOL IsPointInSkinRect(LONG x, LONG y);

	//���Ƥ������Ŀ��������Ƿ�����Ч���
	//ע�⣺�������������ص���Ƥ�������һ��������ʹ�ú����ͷ�
	virtual HRGN GetSkinRgn();	//����Ը����ڵ�ƫ��
	virtual HRGN GetSkinAbsRgn();	//������Ը����ڵ�ƫ��

	//�жϵ��Ƿ���Ƥ��������
	virtual BOOL IsPointInSkinRgn(POINT pt);
	virtual BOOL IsPointInSkinRgn(LONG x, LONG y);

	//Ƥ�����
	virtual HCURSOR GetSkinCursor(LPPOINT lpPoint);

	//��ñ任���͸��ɫ
	virtual LONG GetTransformedTransparentColor();

	//////////////////////////////////////////////////////////////////////////
	//Helper
	//////////////////////////////////////////////////////////////////////////
	BOOL SetImageHelper(CImageBase*& pImage, CString& strImage, LPCTSTR newVal, BOOL bSetSize = FALSE);
	HICON GetIconHelper(LPCTSTR iconFileName, LONG iconSize = -1);
	HCURSOR GetCursorHelper(LPCTSTR curFileName);
    BOOL DrawImageAlphaSideHelper(CImageBase* pImage, HDC hDC, LPCRECT lpDrawRect, LPRECT lpClipRect = NULL, BOOL bAlpha = FALSE, BOOL bSideStretch = TRUE, LONG sideWidth = 0, LONG sideHeight = 0);
    BOOL DrawImageAlphaHelper(CImageBase* pImage, HDC hDC, LPCRECT lpDrawRect, LPRECT lpClipRect = NULL, BOOL bAlpha = FALSE);
    BOOL DrawImageHelper(CImageBase* pImage, HDC hDC, LPCRECT lpDrawRect, LPRECT lpClipRect = NULL);
	DWORD GetComctl32Version();
    BOOL LoadSkinClassHelper(LPCTSTR lpzClassName, LPCTSTR lpzSkinClassName);

public:
	//////////////////////////////////////////////////////////////////////////
	//���Ե�Get�麯��
	//////////////////////////////////////////////////////////////////////////
	//Ƥ��Ԫ�ص�����
	virtual BSTR GetName();
    //����
    virtual BSTR GetSkinClass();
    //����
    virtual BSTR GetPreLoad();
	//Ƥ�����ı�
	virtual BSTR GetText();
	//�����
	virtual BSTR GetCursor();
    virtual BSTR GetSysCursor();
	//����Ƥ��Ԫ�ص�λ��
	virtual LONG GetLeft();
	virtual LONG GetTop();
	virtual LONG GetWidth();
	virtual LONG GetHeight();
    //SizeDelay
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
	//���������Ϣ
	virtual BOOL GetMouseEvent();
	//͸��
	virtual BOOL GetTransparent();
	//��ɫ�任
	virtual BOOL GetColorTransform();
	//��ɫ�任
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
    //
    virtual BOOL GetScriptHandleEvent();

protected:
	//////////////////////////////////////////////////////////////////////////
	//���Ե�Set�麯��
	//////////////////////////////////////////////////////////////////////////
	//Ƥ��Ԫ�ص�����
	virtual void SetName(LPCTSTR newVal);
    //����
    virtual void SetSkinClass(LPCTSTR newVal);
    //����
    virtual void SetPreLoad(LPCTSTR newVal);
	//�ı�
	virtual void SetText(LPCTSTR newVal);
	//�����
	virtual void SetCursor(LPCTSTR newVal);
	virtual void SetSysCursor(LPCTSTR newVal);
	//����Ƥ��Ԫ�ص�λ��
	virtual void SetLeft(LONG newVal);
	virtual void SetTop(LONG newVal);
	virtual void SetWidth(LONG newVal);
	virtual void SetHeight(LONG newVal);
    //SizeDelay
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
    //���������Ϣ
    virtual void SetMouseEvent(BOOL newVal);
	//͸��
	virtual void SetTransparent(BOOL newVal);
	//��ɫ�任
	virtual void SetColorTransform(BOOL newVal);
	//��ɫ�任
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
    //
    virtual void SetScriptHandleEvent(BOOL newVal);

    //////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////
protected:
    CXmlCmdTarget* InternalCreateLayout(LPCTSTR lpzLayoutClass, LPCTSTR lpzLayoutName);
    CXmlCmdTarget* InternalGetLayout(LPCTSTR lpzLayoutName);
    BOOL InternalDestroyLayout(LPCTSTR lpzLayoutName);

	//////////////////////////////////////////////////////////////////////////
	//Dispatch Method
	//////////////////////////////////////////////////////////////////////////
protected:
	//Debug
	void DebugBreak(void);
	//Parent and Child
	IUnknown* GetParent(void);
	IUnknown* GetChild(LPCTSTR strChildName);
    IUnknown* CreateChild(LPCTSTR lpzXmlName, LPCTSTR lpzChildName);
	//Event
	VARIANT_BOOL AttachEvent(LPCTSTR strFuncName, IDispatch* pFuncDisp);
	VARIANT_BOOL DetachEvent(LPCTSTR strFuncName);
	//Timer
	UINT_PTR SetTimer(UINT nIDEvent, UINT nEclapse);
	VARIANT_BOOL KillTimer(UINT nIDEvent);
	//
	IUnknown* GetActive(void);
	IUnknown* SetActive(void);
	IUnknown* GetFocus(void);
	IUnknown* SetFocus(void);
	IUnknown* GetCapture(void);
	IUnknown* SetCapture(void);
	VARIANT_BOOL ReleaseCapture(void);
    //Layout
    IUnknown* CreateLayout(LPCTSTR lpzLayoutClass, LPCTSTR lpzLayoutName);
    IUnknown* GetLayout(LPCTSTR lpzLayoutName);
    VARIANT_BOOL DestroyLayout(LPCTSTR lpzLayoutName);

	//Internal AttachEvent and DetachEvent
protected:
	virtual BOOL InternalAttachEvent(LPCTSTR strFuncName, IDispatch* pFuncDisp);
	virtual BOOL InternalDetachEvent(LPCTSTR strFuncName);

#ifdef V8_JS_ENGINE_SUPPORT

    //v8ʵ��
protected:
    //Debug
    v8::Handle<v8::Value> V8DebugBreak(const v8::Arguments& args);
    //Parent and Child
    v8::Handle<v8::Value> V8GetParent(const v8::Arguments& args);
    v8::Handle<v8::Value> V8GetChild(const v8::Arguments& args);
    v8::Handle<v8::Value> V8CreateChild(const v8::Arguments& args);
    //Event
    v8::Handle<v8::Value> V8AttachEvent(const v8::Arguments& args);
    v8::Handle<v8::Value> V8DetachEvent(const v8::Arguments& args);
    //Timer
    v8::Handle<v8::Value> V8SetTimer(const v8::Arguments& args);
    v8::Handle<v8::Value> V8KillTimer(const v8::Arguments& args);
    //
    v8::Handle<v8::Value> V8GetActive(const v8::Arguments& args);
    v8::Handle<v8::Value> V8SetActive(const v8::Arguments& args);
    v8::Handle<v8::Value> V8GetFocus(const v8::Arguments& args);
    v8::Handle<v8::Value> V8SetFocus(const v8::Arguments& args);
    v8::Handle<v8::Value> V8GetCapture(const v8::Arguments& args);
    v8::Handle<v8::Value> V8SetCapture(const v8::Arguments& args);
    v8::Handle<v8::Value> V8ReleaseCapture(const v8::Arguments& args);
    //Layout
    v8::Handle<v8::Value> V8CreateLayout(const v8::Arguments& args);
    v8::Handle<v8::Value> V8GetLayout(const v8::Arguments& args);
    v8::Handle<v8::Value> V8DestroyLayout(const v8::Arguments& args);

protected:
    virtual v8::Handle<v8::Value> V8InternalCallMethod(const CString& funcName, const v8::Arguments& args);

#endif //V8_JS_ENGINE_SUPPORT

public:
	//////////////////////////////////////////////////////////////////////////
	//Message Handler
	//////////////////////////////////////////////////////////////////////////
	//for CSkinBase
	virtual BOOL OnSetText();
	virtual BOOL OnMouseMove(LONG x, LONG y, UINT flag);
	virtual BOOL OnLButtonDown(LONG x, LONG y, UINT flag);
	virtual BOOL OnLButtonUp(LONG x, LONG y, UINT flag);
	virtual BOOL OnLButtonDblClk(LONG x, LONG y, UINT flag);
	virtual BOOL OnRButtonDown(LONG x, LONG y, UINT flag);
	virtual BOOL OnRButtonUp(LONG x, LONG y, UINT flag);
	virtual BOOL OnRButtonDblClk(LONG x, LONG y, UINT flag);
	virtual BOOL OnMButtonDown(LONG x, LONG y, UINT flag);
	virtual BOOL OnMButtonUp(LONG x, LONG y, UINT flag);
	virtual BOOL OnMButtonDblClk(LONG x, LONG y, UINT flag);
	virtual BOOL OnMouseWheel(LONG x, LONG y, UINT flag);
	virtual BOOL OnMouseHover(LONG x, LONG y, UINT flag);
	virtual BOOL OnMouseEnter();
	virtual BOOL OnMouseLeave();
	virtual BOOL OnShowWindow(BOOL bShow);
	virtual BOOL OnMove(LONG x, LONG y);
    virtual BOOL OnEnterSizeMove(BOOL bSize);
    virtual BOOL OnExitSizeMove(BOOL bSize);
	virtual BOOL OnFrameSize(LONG x, LONG y, UINT flag);
	virtual BOOL OnSize(LONG x, LONG y, UINT flag);
	virtual BOOL OnEnable(BOOL bEnable);
	virtual BOOL OnSetFocus(CSkinBase* pOldFocus);
	virtual BOOL OnKillFocus(CSkinBase* pNewFocus);
	virtual BOOL OnActivate(CSkinBase* pOther, UINT flag);
	virtual BOOL OnCaptureChanged(CSkinBase* pNewCapture);
	virtual BOOL OnKeyDown(UINT VKCode, UINT flag);
	virtual BOOL OnKeyUp(UINT VKCode, UINT flag);
	virtual BOOL OnChar(UINT VKCode, UINT flag);
	virtual BOOL OnTimer(UINT nIDEvent);
	virtual BOOL OnClick(LONG iTab = 0);
	virtual BOOL OnSkinNotify(UINT nCode, VARIANT param);
	virtual BOOL OnInitDialog(CSkinBase* pFocus);
    virtual BOOL OnSetState(UINT uState);
    virtual BOOL OnSetCheck(UINT uCheck);
    virtual BOOL OnUpdateHwnd();

#ifdef MS_JS_ENGINE_SUPPORT

	//////////////////////////////////////////////////////////////////////////
	//Fire Script Event
	//////////////////////////////////////////////////////////////////////////
	//for CSkinBase
	BOOL Fire_OnSetText();
	BOOL Fire_OnMouseMove(LONG x, LONG y, UINT flag);
	BOOL Fire_OnLButtonDown(LONG x, LONG y, UINT flag);
	BOOL Fire_OnLButtonUp(LONG x, LONG y, UINT flag);
	BOOL Fire_OnLButtonDblClk(LONG x, LONG y, UINT flag);
	BOOL Fire_OnRButtonDown(LONG x, LONG y, UINT flag);
	BOOL Fire_OnRButtonUp(LONG x, LONG y, UINT flag);
	BOOL Fire_OnRButtonDblClk(LONG x, LONG y, UINT flag);
	BOOL Fire_OnMButtonDown(LONG x, LONG y, UINT flag);
	BOOL Fire_OnMButtonUp(LONG x, LONG y, UINT flag);
	BOOL Fire_OnMButtonDblClk(LONG x, LONG y, UINT flag);
	BOOL Fire_OnMouseWheel(LONG x, LONG y, UINT flag);
	BOOL Fire_OnMouseHover(LONG x, LONG y, UINT flag);
	BOOL Fire_OnMouseEnter();
	BOOL Fire_OnMouseLeave();
	BOOL Fire_OnShowWindow(BOOL bShow);
	BOOL Fire_OnMove(LONG x, LONG y);
    BOOL Fire_OnEnterSizeMove(BOOL bSize);
    BOOL Fire_OnExitSizeMove(BOOL bSize);
	BOOL Fire_OnFrameSize(LONG x, LONG y, UINT flag);
	BOOL Fire_OnSize(LONG x, LONG y, UINT flag);
	BOOL Fire_OnEnable(BOOL bEnable);
	BOOL Fire_OnSetFocus(CSkinBase* pOldFocus);
	BOOL Fire_OnKillFocus(CSkinBase* pNewFocus);
	BOOL Fire_OnActivate(CSkinBase* pOther, UINT flag);
	BOOL Fire_OnCaptureChanged(CSkinBase* pNewCapture);
	BOOL Fire_OnKeyDown(UINT VKCode, UINT flag);
	BOOL Fire_OnKeyUp(UINT VKCode, UINT flag);
	BOOL Fire_OnChar(UINT VKCode, UINT flag);
	BOOL Fire_OnTimer(UINT nIDEvent);
	BOOL Fire_OnClick(LONG iTab);
	BOOL Fire_OnSkinNotify(UINT nCode, VARIANT param);
	BOOL Fire_OnInitDialog(CSkinBase* pFocus);
    BOOL Fire_OnSetState(UINT uState);
    BOOL Fire_OnSetCheck(UINT uCheck);
    BOOL Fire_OnUpdateHwnd();

#endif //MS_JS_ENGINE_SUPPORT

	//////////////////////////////////////////////////////////////////////////
	//Script������
	//////////////////////////////////////////////////////////////////////////
protected:
    //Dispatchʵ��
	std::map<CString, IDispatchPtr> m_mapDispatch;
	IDispatchPtr GetFunction(LPCTSTR strDispName);
	BOOL SetFunction(LPCTSTR strDispName, IDispatchPtr ptrDisp);

#ifdef V8_JS_ENGINE_SUPPORT

public:
    //V8ʵ��
    BOOL V8Fire_OnSetText();
    BOOL V8Fire_OnMouseMove(LONG x, LONG y, UINT flag);
    BOOL V8Fire_OnLButtonDown(LONG x, LONG y, UINT flag);
    BOOL V8Fire_OnLButtonUp(LONG x, LONG y, UINT flag);
    BOOL V8Fire_OnLButtonDblClk(LONG x, LONG y, UINT flag);
    BOOL V8Fire_OnRButtonDown(LONG x, LONG y, UINT flag);
    BOOL V8Fire_OnRButtonUp(LONG x, LONG y, UINT flag);
    BOOL V8Fire_OnRButtonDblClk(LONG x, LONG y, UINT flag);
    BOOL V8Fire_OnMButtonDown(LONG x, LONG y, UINT flag);
    BOOL V8Fire_OnMButtonUp(LONG x, LONG y, UINT flag);
    BOOL V8Fire_OnMButtonDblClk(LONG x, LONG y, UINT flag);
    BOOL V8Fire_OnMouseWheel(LONG x, LONG y, UINT flag);
    BOOL V8Fire_OnMouseHover(LONG x, LONG y, UINT flag);
    BOOL V8Fire_OnMouseEnter();
    BOOL V8Fire_OnMouseLeave();
    BOOL V8Fire_OnShowWindow(BOOL bShow);
    BOOL V8Fire_OnMove(LONG x, LONG y);
    BOOL V8Fire_OnEnterSizeMove(BOOL bSize);
    BOOL V8Fire_OnExitSizeMove(BOOL bSize);
	BOOL V8Fire_OnFrameSize(LONG x, LONG y, UINT flag);
    BOOL V8Fire_OnSize(LONG x, LONG y, UINT flag);
    BOOL V8Fire_OnEnable(BOOL bEnable);
    BOOL V8Fire_OnSetFocus(CSkinBase* pOldFocus);
    BOOL V8Fire_OnKillFocus(CSkinBase* pNewFocus);
    BOOL V8Fire_OnActivate(CSkinBase* pOther, UINT flag);
    BOOL V8Fire_OnCaptureChanged(CSkinBase* pNewCapture);
    BOOL V8Fire_OnKeyDown(UINT VKCode, UINT flag);
    BOOL V8Fire_OnKeyUp(UINT VKCode, UINT flag);
    BOOL V8Fire_OnChar(UINT VKCode, UINT flag);
    BOOL V8Fire_OnTimer(UINT nIDEvent);
    BOOL V8Fire_OnClick(LONG iTab);
    BOOL V8Fire_OnSkinNotify(UINT nCode, VARIANT param);
    BOOL V8Fire_OnInitDialog(CSkinBase* pFocus);
    BOOL V8Fire_OnSetState(UINT uState);
    BOOL V8Fire_OnSetCheck(UINT uCheck);
    BOOL V8Fire_OnUpdateHwnd();

protected:
    std::map<CString, CV8ContextFunction*> m_mapV8ContextFunction;
    CV8ContextFunction* V8GetFunction(LPCTSTR strDispName);
    BOOL V8SetFunction(LPCTSTR strDispName, v8::Handle<v8::Function> object);
    void V8ClearAllFunction();

    virtual BOOL V8InternalAttachEvent(v8::Handle<v8::String> strFuncName, v8::Handle<v8::Function> pFunc);
    virtual BOOL V8InternalDetachEvent(v8::Handle<v8::String> strFuncName);

#endif //V8_JS_ENGINE_SUPPORT

public:
	//������ˢ��
	virtual void DrawParentBackground(CDC* pDC, LPRECT lpInvalidRect = NULL, CRgn* pInvalidRgn = NULL);
	virtual void DrawBackground(CDC* pDC, LPRECT lpInvalidRect = NULL, CRgn* pInvalidRgn = NULL, BOOL bChildSkin = FALSE);
	virtual void DrawForeground(CDC* pDC, LPRECT lpInvalidRect = NULL, CRgn* pInvalidRgn = NULL);
	virtual void DrawFrame(CDC* pDC, LPRECT lpInvalidRect = NULL, CRgn* pInvalidRgn = NULL);
	virtual void Draw(CDC* pDC, LPRECT lpInvalidRect = NULL, CRgn* pInvalidRgn = NULL);
	virtual BOOL InvalidateRect(LPCRECT pRect = NULL, BOOL bErase = TRUE);

	//�������
	virtual BOOL UpdateSkinRgn(LONG width, LONG height, BOOL bReDraw = FALSE);
	virtual BOOL MoveWindow(LPCRECT lpRect = NULL, BOOL bRepaint = FALSE);

protected:
	CSkinEngine* const	m_pEngine;		//Ƥ��������Ƥ������ָ�룬��������Ƥ������󶨺ͽ��
	CSkinBase*		m_pSkinParent;		//������ָ��
	CSkinBase*		m_pSkinOwner;		//Owner����ָ��
	CSkinBase*		m_pSkinNext;		//��һ�ֵܴ���ָ��
	CSkinBase*		m_pSkinPrev;		//ǰһ�ֵܴ���ָ��
	CSkinProxy*		m_pSkinProxy;		//�������
	CString			m_strName;			//Ƥ��Ԫ�ص����֣���ΪƤ��Ԫ�ص�Ψһ��ID��ֻ������һ��
    CString         m_strSkinClass;     //Ƥ��Ԫ�ص����ͣ�Ϊ���Ե�һ������
    CString         m_strPreLoad;       //Ԥ���ص�����
	CString			m_strText;			//Ƥ��������
	HCURSOR			m_hCursor;			//�����
	HCURSOR			m_hSysCursor;		//ϵͳ���
	CString			m_strCursor;		//����ļ���
	CString			m_strSysCursor;		//ϵͳ����ļ���
	CRect			m_rcSkinRect;		//Ƥ��Ԫ�صľ�����������Ϊ��Ը�Ƥ������
	HRGN			m_hSkinRgn;			//Ƥ��Ԫ�ص�����
	LONG			m_nUpCornerRadius;	//�����ϱ߽�Բ���뾶
	LONG			m_nDownCornerRadius;//�����±߽�Բ���뾶
	LONG			m_nBorderLineWidth;	//�����߿�
	LONG			m_clrBorderLineColor;//������ɫ
	LONG			m_clrTransparentColor;//͸��ɫ
	BOOL			m_bVisible;			//�ɼ�
	BOOL			m_bDisabled;		//����
	BOOL			m_bTabStop;			//Tab Stop
	BOOL			m_bGroup;			//Group
	BOOL			m_bBackground;		//�Ƿ��Ǳ���Ԫ��
	BOOL			m_bMouseEvent;		//�Ƿ���������Ϣ
	BOOL			m_bTransparent;		//�Ƿ���͸���ģ����ɸ����ڻ��Ʊ���
	BOOL			m_bColorTransform;	//�Ƿ���ɫ�任
    BOOL            m_bAlpha;           //��alphaͨ��
    BOOL            m_bSizeDelay;       //�ӳ�Size�ı����Ч
    BOOL            m_bSizeDelayFlag;   //�ӳ�Size��ʶ���ɸ���������
    BOOL            m_bScriptHandleEvent;//�ű�ȫȨ��Ӧ��Ϣ

    //////////////////////////////////////////////////////////////////////////
    //Layout
    //////////////////////////////////////////////////////////////////////////
protected:
    typedef std::vector<std::pair<CString, CXmlCmdTarget*>> LayoutArray;
    LayoutArray m_vecLayouts;

	//////////////////////////////////////////////////////////////////////////
	//Active Focus Capture ״̬
	//////////////////////////////////////////////////////////////////////////
public:
	BOOL GetActiveSkin(CSkinBase** ppSkin = NULL);
	BOOL SetActiveSkin(CSkinBase** ppPrevSkin = NULL);
	BOOL GetFocusSkin(CSkinBase** ppSkin = NULL);
	BOOL SetFocusSkin(CSkinBase** ppPrevSkin = NULL);
	BOOL GetCaptureSkin(CSkinBase** ppSkin = NULL);
	BOOL SetCaptureSkin(CSkinBase** ppPrevSkin = NULL);
	BOOL ReleaseCaptureSkin();

	//////////////////////////////////////////////////////////////////////////
	//Ԫ�����Թ���
	//////////////////////////////////////////////////////////////////////////
public:
	enum SKIN_FILTER
	{
		FILTER_SKINITEM = 0x00000001,
		FILTER_VISIBLE = 0x00000002,
		FILTER_DISABLED = 0x00000004,
		FILTER_TABSTOP = 0x00000008,
		FILTER_GROUP = 0x00000010,
		FILTER_BACKGROUND = 0x00000020,
        FILTER_MOUSEEVENT = 0x00000040,
		FILTER_TRANSPARENT = 0x00000080,
	};

	//�ж��Ƿ������������
	virtual BOOL IsFiltered(UINT uFilterBits, UINT uFilterValues);

	//////////////////////////////////////////////////////////////////////////
	//��Ԫ�����
	//////////////////////////////////////////////////////////////////////////
public:
	//��ӡ�ɾ�����жϡ��滻��Ԫ��
	BOOL AddSubSkin(CSkinBase* pSkin);
	BOOL RemoveSubSkin(CSkinBase* pSkin);
	BOOL IsSubSkin(CSkinBase* pSkin) const;
	BOOL ReplaceSubSkin(CSkinBase* pOldSkin, CSkinBase* pNewSkin);

public:
	//��Ԫ�������뷽���ĵ��ú���
	HRESULT GetSubSkinProp(BSTR bstrSubSkinName, BSTR bstrPropName, VARIANT* pVarValue);
	HRESULT SetSubSkinProp(BSTR bstrSubSkinName, BSTR bstrPropName, VARIANT varValue);
	HRESULT CallSubSkinMethod(BSTR bstrSubSkinName, BSTR bstrFuncName, VARIANT* pVarResult, DISPPARAMS* pDispParams);
	HRESULT GetSubSkinPos(BSTR bstrSubSkinName, LONG* pLeft, LONG* pTop, LONG* pRight, LONG* pBottom);

	//�Ƿ����Ӵ���
	BOOL IsChildOf(CSkinBase* pParent);
	//�Ƿ������ﴰ��
	BOOL IsDescendantOf(CSkinBase* pAncestor);
	//�Ƿ����������ڣ����й�ͬ�����ȴ���
	BOOL IsRelativeOf(CSkinBase* pRelative);

	//�����Ԫ��
	CSkinBase* GetSubSkin(LPCTSTR strSubSkinName);
	CSkinBase* GetSubSkin(BSTR bstrSubSkinName);

	//�����Ԫ�ص������
	HRGN GetAllSubSkinRgn(UINT uFilterBits = (FILTER_SKINITEM | FILTER_VISIBLE),
		UINT uFilterValues = (FILTER_SKINITEM | FILTER_VISIBLE) );

	//��õ����ڵ����������Ե���Ԫ��
	CSkinBase* GetPointInSubSkin(LONG x, LONG y, BOOL bReverse = TRUE, UINT uFilterBits = (FILTER_VISIBLE | FILTER_BACKGROUND | FILTER_MOUSEEVENT),
		UINT uFilterValues = (FILTER_VISIBLE | FILTER_MOUSEEVENT) );
	CSkinBase* GetPointInSubSkin(POINT pt, BOOL bReverse = TRUE, UINT uFilterBits = (FILTER_VISIBLE | FILTER_BACKGROUND | FILTER_MOUSEEVENT),
		UINT uFilterValues = (FILTER_VISIBLE | FILTER_MOUSEEVENT) );

protected:
	std::list<CSkinBase*>	m_listSkinBase;		//������Ԫ��

#ifdef _DEBUG
	//////////////////////////////////////////////////////////////////////////
	//��̬��Ա��SkinBase����
	//////////////////////////////////////////////////////////////////////////
protected:
	static int s_iSkinBaseCount;
#endif
};
