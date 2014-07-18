// XmlCmdTarget.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XmlCmdTarget.h"

#include "Types.h"

#include <set>
#include <map>

using namespace std;

#ifdef V8_JS_ENGINE_SUPPORT
using namespace v8;
#endif //V8_JS_ENGINE_SUPPORT

// CXmlCmdTarget

IMPLEMENT_DYNCREATE(CXmlCmdTarget, CCmdTarget)
CXmlCmdTarget::CXmlCmdTarget()
:
m_bInitialized(FALSE)
{
	EnableAutomation();
}

CXmlCmdTarget::~CXmlCmdTarget()
{
#ifdef V8_JS_ENGINE_SUPPORT
    m_v8Object.Dispose();
#endif //V8_JS_ENGINE_SUPPORT
}

void CXmlCmdTarget::Initialize()
{
	ASSERT(m_bInitialized == FALSE);
	if (m_bInitialized)
		return;

	LONG size = 0;
	LONG lMinDispid = -1;
	LONG lMaxDispid = -1;
	const SKIN_DISPATCH_INFO* pDispInfo = GetSkinDispatchInfo();
	if (pDispInfo->GetDispatchMapSize(size, lMinDispid, lMaxDispid)) {
		LONG bitsetSize = lMaxDispid - lMinDispid;
		ASSERT(bitsetSize > 0);
		m_bitsetModified.resize(bitsetSize, false);
	}

	m_bInitialized = TRUE;
}

void CXmlCmdTarget::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CXmlCmdTarget, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_SKIN_DISPATCH_MAP_XMLCMDTARGET(CXmlCmdTarget, CCmdTarget)
END_SKIN_DISPATCH_MAP(CXmlCmdTarget)

BEGIN_SKIN_DEFAULT_VALUE_MAP(CXmlCmdTarget, CCmdTarget)
END_SKIN_DEFAULT_VALUE_MAP(CXmlCmdTarget)

// ע��: ������� IID_IXmlCmdTarget ֧��
//��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//���Ƚӿڵ� GUID ƥ�䡣

// {E0238822-17BB-43E9-91A1-F77B69B42C98}
static const IID IID_IXmlCmdTarget =
{ 0xE0238822, 0x17BB, 0x43E9, { 0x91, 0xA1, 0xF7, 0x7B, 0x69, 0xB4, 0x2C, 0x98 } };

BEGIN_INTERFACE_MAP(CXmlCmdTarget, CCmdTarget)
	INTERFACE_PART(CXmlCmdTarget, IID_IXmlCmdTarget, Dispatch)
#ifdef MS_JS_ENGINE_SUPPORT
    INTERFACE_PART(CXmlCmdTarget, IID_IActiveScriptSite, ActiveScriptSite)
    INTERFACE_PART(CXmlCmdTarget, IID_IActiveScriptSiteWindow, ActiveScriptSiteWindow)
#endif //MS_JS_ENGINE_SUPPORT
END_INTERFACE_MAP()


#ifdef MS_JS_ENGINE_SUPPORT

STDMETHODIMP CXmlCmdTarget::XActiveScriptSite::GetLCID(LCID *plcid)
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSite);

    return pThis->GetLCID(plcid);
}

STDMETHODIMP_(ULONG) CXmlCmdTarget::XActiveScriptSite::AddRef()
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSite);

    return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CXmlCmdTarget::XActiveScriptSite::Release()
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSite);

    return pThis->ExternalRelease();
}

STDMETHODIMP  CXmlCmdTarget::XActiveScriptSite::QueryInterface(REFIID iid, LPVOID* ppvObj)
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSite);

    return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CXmlCmdTarget::XActiveScriptSite::GetItemInfo(LPCOLESTR pstrName, DWORD dwReturnMask, IUnknown **ppiunkItem, ITypeInfo **ppti)
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSite);

    return pThis->GetItemInfo(pstrName, dwReturnMask, ppiunkItem, ppti);
}

STDMETHODIMP CXmlCmdTarget::XActiveScriptSite::GetDocVersionString(BSTR *pszVersion)
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSite);

    return pThis->GetDocVersionString(pszVersion);
}

STDMETHODIMP CXmlCmdTarget::XActiveScriptSite::OnScriptTerminate(const VARIANT *pvarResult, const EXCEPINFO *pexcepinfo)
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSite);

    return pThis->OnScriptTerminate(pvarResult,pexcepinfo);
}

STDMETHODIMP CXmlCmdTarget::XActiveScriptSite::OnStateChange(SCRIPTSTATE ssScriptState)
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSite);

    return pThis->OnStateChange(ssScriptState);
}

STDMETHODIMP CXmlCmdTarget::XActiveScriptSite::OnScriptError(IActiveScriptError *pscripterror)
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSite);

    return pThis->OnScriptError(pscripterror);
}

STDMETHODIMP CXmlCmdTarget::XActiveScriptSite::OnEnterScript()
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSite);

    return pThis->OnEnterScript();
}

STDMETHODIMP CXmlCmdTarget::XActiveScriptSite::OnLeaveScript()
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSite);

    return pThis->OnLeaveScript();
}

STDMETHODIMP_(ULONG) CXmlCmdTarget::XActiveScriptSiteWindow::AddRef()
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSiteWindow);

    return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CXmlCmdTarget::XActiveScriptSiteWindow::Release()
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSiteWindow);

    return pThis->ExternalRelease();
}

STDMETHODIMP  CXmlCmdTarget::XActiveScriptSiteWindow::QueryInterface(REFIID iid, LPVOID* ppvObj)
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSiteWindow);

    return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CXmlCmdTarget::XActiveScriptSiteWindow::EnableModeless(BOOL bEnable)
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSiteWindow);

    return pThis->EnableModeless(bEnable);
}

STDMETHODIMP CXmlCmdTarget::XActiveScriptSiteWindow::GetWindow(HWND* pHwnd)
{
    METHOD_PROLOGUE(CXmlCmdTarget, ActiveScriptSiteWindow);

    return pThis->GetWindow(pHwnd);
}

HRESULT CXmlCmdTarget::GetLCID(LCID *plcid)
{
    if(plcid == NULL)
        return(E_POINTER);

    *plcid = GetUserDefaultLCID();
    return S_OK;
}

HRESULT CXmlCmdTarget::GetItemInfo(LPCOLESTR pstrName, DWORD dwReturnMask, IUnknown **ppiunkItem, ITypeInfo **ppti)
{
    if( (dwReturnMask&SCRIPTINFO_IUNKNOWN) && ppiunkItem == NULL)
        return E_POINTER;

    if( (dwReturnMask&SCRIPTINFO_ITYPEINFO) && ppti == NULL)
        return E_POINTER;

    return S_OK;
}

HRESULT CXmlCmdTarget::GetDocVersionString(BSTR *pszVersion)
{
    return E_NOTIMPL;
}

HRESULT CXmlCmdTarget::OnScriptTerminate(const VARIANT *pvarResult, const EXCEPINFO *pexcepinfo)
{
    return S_OK;
}

HRESULT CXmlCmdTarget::OnStateChange(SCRIPTSTATE ssScriptState)
{
    return S_OK;
}

HRESULT CXmlCmdTarget::OnScriptError(IActiveScriptError *pscripterror)
{
    return S_OK;
}

HRESULT CXmlCmdTarget::OnEnterScript(void)
{
    return S_OK;
}

HRESULT CXmlCmdTarget::OnLeaveScript(void)
{
    return S_OK;
}

HRESULT CXmlCmdTarget::GetWindow(HWND *phwnd)
{
    *phwnd = NULL;
    return S_OK;
}

HRESULT CXmlCmdTarget::EnableModeless(BOOL fEnable)
{
    CWinApp* pApp = AfxGetApp();
    if (pApp != NULL){
        pApp->EnableModeless(fEnable);
        return S_OK;
    }
    return S_FALSE;
}

BOOL CXmlCmdTarget::AddNameItemToSrcipt(CComPtr<IActiveScript> pScript)
{
    if (pScript == NULL)
        return FALSE;

    return TRUE;
}

#endif //MS_JS_ENGINE_SUPPORT

#ifdef V8_JS_ENGINE_SUPPORT

BOOL CXmlCmdTarget::AddObjectToSrcipt(Handle<Object> object)
{
    HandleScope handleScope;

    return TRUE;
}

#endif //V8_JS_ENGINE_SUPPORT


// CXmlCmdTarget ��Ϣ�������
HRESULT CXmlCmdTarget::GetInterface(IUnknown** ppiunk)
{
	GUID guid = IID_IUnknown;
	return ExternalQueryInterface(&guid, (void**)ppiunk);
}

//////////////////////////////////////////////////////////////////////////
//Dispatch Map ��Ϣ��ѯ
//////////////////////////////////////////////////////////////////////////
BOOL CXmlCmdTarget::GetDispIds(std::list<LONG>& listIds, BOOL bDispProp)
{
	const SKIN_DISPATCH_INFO* pInfo = GetSkinDispatchInfo();
	if (pInfo == NULL)
		return FALSE;

	return pInfo->GetAllDispId(listIds, bDispProp);
}

BOOL CXmlCmdTarget::GetDispName(LONG dispId, CString& strName)
{
	const SKIN_DISPATCH_INFO* pInfo = GetSkinDispatchInfo();
	if (pInfo == NULL)
		return FALSE;

	return pInfo->GetDispNameByDispId(dispId, strName);
}

BOOL CXmlCmdTarget::GetDispType(LONG dispId, VARENUM& enumType)
{
	const SKIN_DISPATCH_INFO* pInfo = GetSkinDispatchInfo();
	if (pInfo == NULL)
		return FALSE;

	const AFX_DISPMAP_ENTRY* pEntry = pInfo->GetDispEntryByDispId(dispId);
	if (pEntry == NULL)
		return FALSE;

	*((LONG*)&enumType) = pEntry->vt;
	return TRUE;
}

const AFX_DISPMAP_ENTRY* CXmlCmdTarget::GetDispEntry(BSTR bstrPropName)
{
	ASSERT(m_bInitialized);
	if (! m_bInitialized)
		return NULL;

    const SKIN_DISPATCH_INFO* pInfo = GetSkinDispatchInfo();
    ASSERT(pInfo != NULL);
    if (pInfo == NULL)
        return NULL;

    const CString strPropName = bstrPropName;
    const AFX_DISPMAP_ENTRY* pEntry = pInfo->GetDispEntryByDispNameOrAlias(strPropName);
#ifdef _DEBUG
    ASSERT(pEntry != NULL);
    if (pEntry == NULL) {
        CString strError;
        strError.Format(_T("Unknown Dispatch Name : %s \n"), strPropName);
        OutputDebugString(strError);
    }
#endif
    return pEntry;

	////���Dispatch��
	//const AFX_DISPMAP* pDispMap = GetDispatchMap();
	//if (pDispMap == NULL)
	//	return NULL;
	//const AFX_DISPMAP_ENTRY* pDispMapEntry = pDispMap->lpEntries;
	//if (pDispMapEntry == NULL)
	//	return NULL;

	////��DispatchMap�в�������
	//for (; pDispMapEntry->lpszName != VTS_NONE; pDispMapEntry++) {

	//	//�Ƚ����֣������ִ�Сд
    //    if (strPropName.CompareNoCase(pDispMapEntry->lpszName) != 0)
    //        continue;

	//	return pDispMapEntry;
	//}

	//return NULL;
}

const AFX_DISPMAP_ENTRY* CXmlCmdTarget::GetDispEntry(LONG propId)
{
	ASSERT(m_bInitialized);
	if (! m_bInitialized)
		return NULL;

    const SKIN_DISPATCH_INFO* pInfo = GetSkinDispatchInfo();
    ASSERT(pInfo != NULL);
    if (pInfo == NULL)
        return NULL;

    const AFX_DISPMAP_ENTRY* pEntry = pInfo->GetDispEntryByDispId(propId);
#ifdef _DEBUG
    ASSERT(pEntry != NULL);
    if (pEntry == NULL) {
        CString strError;
        strError.Format(_T("Unknown Dispatch ID : %d \n"), propId);
        OutputDebugString(strError);
    }
#endif
    return pEntry;

	////���Dispatch��
	//const AFX_DISPMAP* pDispMap = GetDispatchMap();
	//if (pDispMap == NULL)
	//	return NULL;
	//const AFX_DISPMAP_ENTRY* pDispMapEntry = pDispMap->lpEntries;
	//if (pDispMapEntry == NULL)
	//	return NULL;

	////��DispatchMap�в���
	//for (; pDispMapEntry->lpszName != VTS_NONE; pDispMapEntry++) {

	//	//�Ƚ�Id
	//	if (pDispMapEntry->lDispID != propId)
	//		continue;

	//	return pDispMapEntry;
	//}

	//return NULL;
}

HRESULT CXmlCmdTarget::GetProperty(BSTR bstrPropName, VARIANT* pVarPropValue)
{
	if (IsBadWritePtr(pVarPropValue, sizeof(VARIANT)) != 0)
		return E_POINTER;

	//���Dispatch���
	const AFX_DISPMAP_ENTRY* pDispMapEntry = GetDispEntry(bstrPropName);
	if (pDispMapEntry == NULL ||
		pDispMapEntry->lpszParams != NULL)	//��������
		return S_FALSE;

	//ΪCallMemberFunc����׼������
	DISPPARAMS dispParam;
	dispParam.rgvarg = NULL;
	dispParam.cArgs = 0;
	dispParam.cNamedArgs = 0;
	DISPID nameArgs = DISPID_VALUE;
	dispParam.rgdispidNamedArgs = &nameArgs;
	UINT puArgErr = (UINT)(-1);

	//��շ���ֵ
	::VariantClear(pVarPropValue);

	//����CallMemberFunc�������в������ã��������쳣
	HRESULT sc = S_OK;
	TRY {
		sc = CCmdTarget::CallMemberFunc(pDispMapEntry, DISPATCH_PROPERTYGET, 
			pVarPropValue, &dispParam, &puArgErr);
	} CATCH (COleException, e) {
		sc = e->m_sc;
	} AND_CATCH_ALL(e) {
		EXCEPINFO excepInfo;
		// fill exception with translation of MFC exception
		COleDispatchException::Process(&excepInfo, e);
		sc = DISP_E_EXCEPTION;
	}
	END_CATCH_ALL

	return sc;
}

HRESULT CXmlCmdTarget::GetProperty(LONG propId, VARIANT* pVarPropValue)
{
	if (IsBadWritePtr(pVarPropValue, sizeof(VARIANT)) != 0)
		return E_POINTER;

	//���Dispatch���
	const AFX_DISPMAP_ENTRY* pDispMapEntry = GetDispEntry(propId);
	if (pDispMapEntry == NULL ||
		pDispMapEntry->lpszParams != NULL)	//��������
		return S_FALSE;

	//ΪCallMemberFunc����׼������
	DISPPARAMS dispParam;
	dispParam.rgvarg = NULL;
	dispParam.cArgs = 0;
	dispParam.cNamedArgs = 0;
	DISPID nameArgs = DISPID_VALUE;
	dispParam.rgdispidNamedArgs = &nameArgs;
	UINT puArgErr = (UINT)(-1);

	//��շ���ֵ
	::VariantClear(pVarPropValue);

	//����CallMemberFunc�������в������ã��������쳣
	HRESULT sc = S_OK;
	TRY {
		sc = CCmdTarget::CallMemberFunc(pDispMapEntry, DISPATCH_PROPERTYGET, 
			pVarPropValue, &dispParam, &puArgErr);
	} CATCH (COleException, e) {
		sc = e->m_sc;
	} AND_CATCH_ALL(e) {
		EXCEPINFO excepInfo;
		// fill exception with translation of MFC exception
		COleDispatchException::Process(&excepInfo, e);
		sc = DISP_E_EXCEPTION;
	}
	END_CATCH_ALL

	return sc;
}

HRESULT CXmlCmdTarget::SetProperty(BSTR bstrPropName, VARIANT varPropValue)
{
	//���Dispatch���
	const AFX_DISPMAP_ENTRY* pDispMapEntry = GetDispEntry(bstrPropName);
	if (pDispMapEntry == NULL ||
		pDispMapEntry->lpszParams != NULL)	//��������
		return S_FALSE;

	//���Ͳ�һ��ʱ���Խ�������ת��
	CComVariant var(varPropValue);
	if (varPropValue.vt != pDispMapEntry->vt) {
		if (varPropValue.vt == VT_BSTR && 
			pDispMapEntry->vt != VT_BSTR){
				FormatBstrVariantToDecimal(var);
		}
		if (var.ChangeType(pDispMapEntry->vt) != S_OK){
			return E_INVALIDARG;
		}
	}

	//ΪCallMemberFunc����׼������
	DISPPARAMS dispParam;
	dispParam.rgvarg = &var;
	dispParam.cArgs = 1;
	dispParam.cNamedArgs = 1;
	DISPID nameArgs = DISPID_PROPERTYPUT;
	dispParam.rgdispidNamedArgs = &nameArgs;
	UINT puArgErr = (UINT)(-1);

	//����CallMemberFunc�������в������ã��������쳣
	HRESULT sc = S_OK;
	TRY {
		sc = CCmdTarget::CallMemberFunc(pDispMapEntry, DISPATCH_PROPERTYPUT, 
			NULL, &dispParam, &puArgErr);
	} CATCH (COleException, e) {
		sc = e->m_sc;
	} AND_CATCH_ALL(e) {
		EXCEPINFO excepInfo;
		// fill exception with translation of MFC exception
		COleDispatchException::Process(&excepInfo, e);
		sc = DISP_E_EXCEPTION;
	}
	END_CATCH_ALL

	return sc;
}

HRESULT CXmlCmdTarget::SetProperty(LONG propId, VARIANT varPropValue)
{
	//���Dispatch���
	const AFX_DISPMAP_ENTRY* pDispMapEntry = GetDispEntry(propId);
	if (pDispMapEntry == NULL ||
		pDispMapEntry->lpszParams != NULL)	//��������
		return S_FALSE;

	//���Ͳ�һ��ʱ���Խ�������ת��
	CComVariant var(varPropValue);
	if (varPropValue.vt != pDispMapEntry->vt) {
		if (varPropValue.vt == VT_BSTR && 
			pDispMapEntry->vt != VT_BSTR){
				FormatBstrVariantToDecimal(var);
		}
		if (var.ChangeType(pDispMapEntry->vt) != S_OK){
			return E_INVALIDARG;
		}
	}

	//ΪCallMemberFunc����׼������
	DISPPARAMS dispParam;
	dispParam.rgvarg = &var;
	dispParam.cArgs = 1;
	dispParam.cNamedArgs = 1;
	DISPID nameArgs = DISPID_PROPERTYPUT;
	dispParam.rgdispidNamedArgs = &nameArgs;
	UINT puArgErr = (UINT)(-1);

	//����CallMemberFunc�������в������ã��������쳣
	HRESULT sc = S_OK;
	TRY {
		sc = CCmdTarget::CallMemberFunc(pDispMapEntry, DISPATCH_PROPERTYPUT, 
			NULL, &dispParam, &puArgErr);
	} CATCH (COleException, e) {
		sc = e->m_sc;
	} AND_CATCH_ALL(e) {
		EXCEPINFO excepInfo;
		// fill exception with translation of MFC exception
		COleDispatchException::Process(&excepInfo, e);
		sc = DISP_E_EXCEPTION;
	}
	END_CATCH_ALL

	return sc;
}

HRESULT CXmlCmdTarget::CallMethod(BSTR bstrFuncName, VARIANT* pVarResult, DISPPARAMS* pDispParams)
{
	//���Dispatch���
	const AFX_DISPMAP_ENTRY* pDispMapEntry = GetDispEntry(bstrFuncName);
	if (pDispMapEntry == NULL)
		return S_FALSE;

	//������
	UINT puArgErr = (UINT)(-1);

	//����CallMemberFunc�������в������ã��������쳣
	HRESULT sc = S_OK;
	TRY {
		sc = CCmdTarget::CallMemberFunc(pDispMapEntry, DISPATCH_METHOD, 
			pVarResult, pDispParams, &puArgErr);
	} CATCH (COleException, e) {
		sc = e->m_sc;
	} AND_CATCH_ALL(e) {
		EXCEPINFO excepInfo;
		// fill exception with translation of MFC exception
		COleDispatchException::Process(&excepInfo, e);
		sc = DISP_E_EXCEPTION;
	}
	END_CATCH_ALL

	return sc;
}

HRESULT CXmlCmdTarget::CallMethod(LONG propId, VARIANT* pVarResult, DISPPARAMS* pDispParams)
{
	//���Dispatch���
	const AFX_DISPMAP_ENTRY* pDispMapEntry = GetDispEntry(propId);
	if (pDispMapEntry == NULL)
		return S_FALSE;

	//������
	UINT puArgErr = (UINT)(-1);

	//����CallMemberFunc�������в������ã��������쳣
	HRESULT sc = S_OK;
	TRY {
		sc = CCmdTarget::CallMemberFunc(pDispMapEntry, DISPATCH_METHOD, 
			pVarResult, pDispParams, &puArgErr);
	} CATCH (COleException, e) {
		sc = e->m_sc;
	} AND_CATCH_ALL(e) {
		EXCEPINFO excepInfo;
		// fill exception with translation of MFC exception
		COleDispatchException::Process(&excepInfo, e);
		sc = DISP_E_EXCEPTION;
	}
	END_CATCH_ALL

	return sc;
}

#ifdef V8_JS_ENGINE_SUPPORT

Handle<Value> CXmlCmdTarget::V8GetProperty(Local<String> property, const AccessorInfo& info)
{
    HandleScope handleScope;

    //���������
    CString strPropName = ValueToCString(property);
    CComBSTR bstrPropName(strPropName);

    //��ö���ָ��
    CXmlCmdTarget* pXmlCmd = UnwrapXmlCmdTarget(info.This());

    //�������ֵ
    CComVariant var;
    pXmlCmd->GetProperty(bstrPropName, &var);

    return handleScope.Close(VariantToValue(var));
}

void CXmlCmdTarget::V8SetProperty(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    HandleScope handleScope;

    //���������
    CString strPropName = ValueToCString(property);
    CComBSTR bstrPropName(strPropName);

    //��ö���ָ��
    CXmlCmdTarget* pXmlCmd = UnwrapXmlCmdTarget(info.This());

    //ת������ֵ
    CComVariant var = ValueToVariant(value);

    //��������
    pXmlCmd->SetProperty(bstrPropName, var);
}

Handle<Value> CXmlCmdTarget::V8InternalCallMethod(const CString& funcName, const Arguments& args)
{
    HandleScope handleScope;

    return handleScope.Close(v8::Undefined());
}

Handle<Value> CXmlCmdTarget::V8CallMethod(const Arguments& args)
{
    HandleScope handleScope;

    //��ú�����
    Handle<Function> callee = args.Callee();
    CString strName = ValueToCString(callee->GetName());
    CComBSTR bstrName(strName);

    //��ö���ָ��
    CXmlCmdTarget* pXmlCmd = UnwrapXmlCmdTarget(args.This());

    return handleScope.Close(pXmlCmd->V8InternalCallMethod(strName, args));
}

Handle<Value> CXmlCmdTarget::WrapXmlCmdTarget(CXmlCmdTarget* target)
{
    HandleScope handleScope;

    if (target == NULL)
        return handleScope.Close(v8::Null());

    const SKIN_DISPATCH_INFO* pSkinDispInfo = target->GetSkinDispatchInfo();

    Handle<FunctionTemplate> funcTempl = pSkinDispInfo->GetClassTemplate();

    Handle<Function> func = funcTempl->GetFunction();
    Handle<Object> object = func->NewInstance();

    object->SetInternalField(0, External::New(target));

    return handleScope.Close(object);
}

CXmlCmdTarget* CXmlCmdTarget::UnwrapXmlCmdTarget(Handle<Value> object)
{
    HandleScope handleScope;

    if (object->IsNull())
        return NULL;

    ASSERT(object->IsObject());
    Handle<Object> obj = Handle<Object>::Cast(object);

    Handle<External> field = Handle<External>::Cast(obj->GetInternalField(0));
    void* target = field->Value();

    return static_cast<CXmlCmdTarget*>(target);
}

Handle<Value> CXmlCmdTarget::GetV8Object()
{
    HandleScope scope;

    if (m_v8Object.IsEmpty()) {
        Handle<Value> object = CXmlCmdTarget::WrapXmlCmdTarget(this);
        m_v8Object = Persistent<Value>::New(object);
    }

    Handle<Value> object = m_v8Object;
    return scope.Close(object);
}

#endif //V8_JS_ENGINE_SUPPORT

BOOL CXmlCmdTarget::LoadPropertyFromXml(IXMLDOMNodePtr ptrNode)
{
	IXMLDOMNodePtr pNode = NULL;
	IXMLDOMNamedNodeMapPtr pNamedNodeMap = NULL;
	DOMNodeType nodeType = NODE_INVALID;

	long len = 0;
	BOOL allSuc = TRUE;
	ptrNode->get_attributes(&pNamedNodeMap);
	pNamedNodeMap->get_length(&len);
	for (int i=0; i<len; i++){
		pNamedNodeMap->get_item(i, &pNode);
		pNode->get_nodeType(&nodeType);
		if (nodeType != NODE_ATTRIBUTE)
			continue;

		CComBSTR bstrName;
		CComVariant varValue;
		pNode->get_nodeName(&bstrName);
		pNode->get_nodeValue(&varValue);
		if (varValue.vt != VT_BSTR)
			continue;

		//��������
		HRESULT hr = SetProperty(bstrName, varValue);
		if (hr == S_OK)
			continue;

		if (FAILED(hr))
			allSuc = FALSE;

		//���������Ϣ
		CString strName(bstrName);
		CString strValue(varValue.bstrVal);
		USES_CONVERSION;
		TRACE(("����XML���Է�������������: %s, ����ֵ: %s\n"), T2A(strName), T2A(strValue));
	}

	return allSuc;
}

BOOL CXmlCmdTarget::SetModified(LONG dispid, BOOL bTrue)
{
	ASSERT(m_bInitialized);
	if (! m_bInitialized)
		return FALSE;

	m_bitsetModified.set(dispid, bTrue ? (true) : (false));
	return TRUE;
}

BOOL CXmlCmdTarget::GetModified(LONG dispid, BOOL& bTrue)
{
	ASSERT(m_bInitialized);
	if (! m_bInitialized)
		return FALSE;

	bTrue = m_bitsetModified.test(dispid);
	return TRUE;
}

BOOL CXmlCmdTarget::ClearModified()
{
	ASSERT(m_bInitialized);
	if (! m_bInitialized)
		return FALSE;

	//���Լ��������0
	m_bitsetModified ^= m_bitsetModified;
	return TRUE;
}
