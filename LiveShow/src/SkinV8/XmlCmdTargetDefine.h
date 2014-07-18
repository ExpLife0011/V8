#pragma once

#include "CmdTargetPtr.h"

#include <set>
#include <map>
#include <list>

//////////////////////////////////////////////////////////////////////////
//Dispatch Map ��Ϣ
//////////////////////////////////////////////////////////////////////////
//Skin��Dispatch Map��Ϣ
//�����˾�̬ȫ�ֱ����Ĺ��캯������ʼ������ṹ
struct SKIN_DISPATCH_INFO
{
public:
	explicit SKIN_DISPATCH_INFO(LPCTSTR pzClassName, const AFX_DISPMAP_ENTRY* pDispatchEntry, const SKIN_DISPATCH_INFO* pBaseDispInfo);
    ~SKIN_DISPATCH_INFO();

    //�������
    LPCTSTR GetClassName() const;

    //���SKIN_DISPATCH_INFO������һ��
    static const SKIN_DISPATCH_INFO* GetSkinDispatchInfoHeader();

    //���SKIN_DISPATCH_INFO������һ��
    const SKIN_DISPATCH_INFO* GetNextSkinDispatchInfo() const;

    //��û����SKIN_DISPATCH_INFO
    const SKIN_DISPATCH_INFO* GetBaseSkinDispatchInfo() const;

	//���DispatchMap Size �����Ϣ
	BOOL GetDispatchMapSize(LONG& size, LONG& minId, LONG& maxId) const;

	//���Disp ���ֻ�����Ƿ����ظ�����
	BOOL CheckRedefinedDispNameOrAlias(std::set<CString>* pSetOfRedefined = NULL) const;

	//���Disp ID�Ƿ����ظ����壬��ͬһ��Disp ID����ͬ�����Ի򷽷�ʹ�ã���������
	BOOL CheckRedefinedDispID(std::set<int>* pSetOfRedefined = NULL) const;

	//�Ƿ���ͬһDispatchInfo
	BOOL IsSameAs(const SKIN_DISPATCH_INFO& other) const;

	//�Ƿ�������
	BOOL IsDispProperty(LONG dispId) const;
	BOOL IsDispProperty(LPCTSTR dispNameOrAlias) const;

	//�Ƿ��Ƿ���
	BOOL IsDispMethod(LONG dispId) const;
	BOOL IsDispMethod(LPCTSTR dispNameOrAlias) const;

	//�ж��Ƿ�������
	BOOL IsDispName(LPCTSTR pzDispName) const;

	//�ж��Ƿ������ֻ����
	BOOL IsDispNameOrAlias(LPCTSTR pzDispNameOrAlias) const;

	//���DispEntry
    const AFX_DISPMAP_ENTRY* GetDispEntry() const;
	const AFX_DISPMAP_ENTRY* GetDispEntryByDispId(LONG dispId) const;
	const AFX_DISPMAP_ENTRY* GetDispEntryByDispNameOrAlias(LPCTSTR pzDispNameOrAlias) const;

	//�������
	BOOL GetDispNameByDispId(LONG dispId, CString& strName) const;
	BOOL GetDispNameByDispNameOrAlias(LPCTSTR pzDispNameOrAlias, CString& strName) const;

	//���Id
	BOOL GetDispIdByDispNameOrAlias(LPCTSTR pzDispNameOrAlias, LONG& dispId) const;

	//��ñ���
	BOOL GetDispAliasByDispId(LONG dispId, std::list<CString>& listOfAlias) const;
	BOOL GetDispAliasByDispNameOrAlias(LPCTSTR pzDispNameOrAlias, std::list<CString>& listOfAlias) const;

	//���Id�б����ظ�
	BOOL GetAllDispId(std::list<LONG>& listOfIds, BOOL bAllProp = TRUE) const;

	//��������б�
	BOOL GetAllDispName(std::list<CString>& listOfNames, BOOL bAllProp = TRUE) const;

#ifdef V8_JS_ENGINE_SUPPORT
    v8::Handle<v8::FunctionTemplate> GetClassTemplate() const;
public:
    v8::Persistent<v8::FunctionTemplate> m_functionTemplate;
#endif //V8_JS_ENGINE_SUPPORT

protected:
	BOOL InitializeSkinDispatchInfo();

protected:
	//ȫ������ͷ
	static SKIN_DISPATCH_INFO* s_pSkinDispatchInfoListHeader;
protected:
	const AFX_DISPMAP_ENTRY* const m_pDispEntry;
	const SKIN_DISPATCH_INFO* const m_pNextSkinDispatchInfo;
    const SKIN_DISPATCH_INFO* const m_pBaseSkinDispatchInfo;
	LPCTSTR m_pzClassName;
	LONG m_lMinDispid;
	LONG m_lMaxDispid;
	LONG m_lDispSize;
	std::map<LONG, const AFX_DISPMAP_ENTRY*> m_mapIDToEntry;	//��IDӳ�䵽DispEntry��ע�ⲻ�Ǳ�������������Dispatch Map�е�һ�˳��ֵ�
	std::map<CString, LONG> m_mapNameOrAliasToID;		//������(�����)ӳ�䵽ID
	std::map<CString, std::list<CString>> m_mapNameAlias;	//���ֵı�����
};

//����SkinDispatchMap
#define DECLARE_SKIN_DISPATCH_MAP() \
	DECLARE_DISPATCH_MAP() \
private: \
	static const SKIN_DISPATCH_INFO _skinDispatchInfo; \
    static const SKIN_DISPATCH_INFO* GetBaseSkinDispatchInfo(); \
protected: \
    static const SKIN_DISPATCH_INFO* GetThisSkinDispatchInfo(); \
	virtual const SKIN_DISPATCH_INFO* GetSkinDispatchInfo() const; \

#define SKIN_DISPID(theClass, propName)  theClass##Dispid##propName

#define SKIN_DISPID_WITH_COMMA(theClass, propName)  theClass##Dispid##propName, 

//��ʼSkinDispatchMap
#define BEGIN_SKIN_DISPATCH_MAP_XMLCMDTARGET(theClass, baseClass) \
    const SKIN_DISPATCH_INFO* theClass::GetBaseSkinDispatchInfo() \
    { return NULL; } \
    const SKIN_DISPATCH_INFO* theClass::GetThisSkinDispatchInfo() \
    { return &theClass::_skinDispatchInfo; } \
    const SKIN_DISPATCH_INFO* theClass::GetSkinDispatchInfo() const \
    { return &theClass::_skinDispatchInfo; } \
    BEGIN_DISPATCH_MAP(theClass, baseClass) \

#define BEGIN_SKIN_DISPATCH_MAP(theClass, baseClass) \
    const SKIN_DISPATCH_INFO* theClass::GetBaseSkinDispatchInfo() \
    { return baseClass::GetThisSkinDispatchInfo(); } \
    const SKIN_DISPATCH_INFO* theClass::GetThisSkinDispatchInfo() \
    { return &theClass::_skinDispatchInfo; } \
	const SKIN_DISPATCH_INFO* theClass::GetSkinDispatchInfo() const \
	{ return &theClass::_skinDispatchInfo; } \
	BEGIN_DISPATCH_MAP(theClass, baseClass) \

//����һ������
#define SKIN_DISP_PROPERTY(theClass, propName, propType)	\
	DISP_PROPERTY_EX_ID(theClass, #propName, SKIN_DISPID(theClass, propName), Get##propName, Set##propName, propType)

//����һ������
#define SKIN_DISP_FUNCTION(theClass, funcName, retType, params)	\
	DISP_FUNCTION_ID(theClass, #funcName, SKIN_DISPID(theClass, funcName), funcName, retType, params)

//����һ�����Եı���
//ע�⣺�����Ķ�������ڶ�Ӧ���Զ���ĺ���
#define SKIN_DISP_PROPERTY_ALIAS(theClass, propAlias, propName, propType)	\
	DISP_PROPERTY_EX_ID(theClass, #propAlias, SKIN_DISPID(theClass, propName), Get##propName, Set##propName, propType)

//����һ�������ı���
//ע�⣺�����Ķ�������ڶ�Ӧ�����Ķ������
#define SKIN_DISP_FUNCTION_ALIAS(theClass, funcAlias, funcName, retType, params)	\
	DISP_FUNCTION_ID(theClass, #funcAlias, SKIN_DISPID(theClass, funcName), funcName, retType, params)

//����SkinDispatchMap
//ע�⣺�˴��ٶ���ȫ�ֱ���theClass::_dispatchEntries�ĳ�ʼ��˳����theClass::_skinDispatchInfo֮ǰ
#define END_SKIN_DISPATCH_MAP(theClass) \
	END_DISPATCH_MAP() \
    const SKIN_DISPATCH_INFO theClass::_skinDispatchInfo(_T(#theClass), theClass::_dispatchEntries, theClass::GetBaseSkinDispatchInfo()); \


//����
#define SKIN_DISP_PROPERTY_BOOL(theClass, propName)  SKIN_DISP_PROPERTY(theClass, propName, VT_BOOL)
#define SKIN_DISP_PROPERTY_BSTR(theClass, propName)  SKIN_DISP_PROPERTY(theClass, propName, VT_BSTR)
#define SKIN_DISP_PROPERTY_LONG(theClass, propName)  SKIN_DISP_PROPERTY(theClass, propName, VT_I4)


//////////////////////////////////////////////////////////////////////////
//Ĭ��ֵ��Ĭ��ֵ���ַ�����ʾ���ִ�����Ҫ��_T
//�����ں����Ĭ��ֵ������ǰ���Ĭ��ֵ
//////////////////////////////////////////////////////////////////////////
//Ĭ��ֵ�ԵĽṹ
struct SKIN_DEFAULT_VALUE_PAIR
{
	BOOL m_bEnd;
	LONG m_lDispid;
	LPCTSTR m_pzDefaultValue;
};

//Ĭ��ֵ��Ϣ
struct SKIN_DEFAULT_VALUE_INFO
{
	explicit SKIN_DEFAULT_VALUE_INFO(const SKIN_DEFAULT_VALUE_PAIR* pDefaultValuePair)
		:m_pDefaultValuePair(pDefaultValuePair)
	{

	}
protected:
	const SKIN_DEFAULT_VALUE_PAIR* const m_pDefaultValuePair;
};

//����Ĭ��ֵ��
#define DECLARE_SKIN_DEFAULT_VALUE_MAP() \
private: \
	static const SKIN_DEFAULT_VALUE_INFO _skinDefaultValueInfo; \
	static const SKIN_DEFAULT_VALUE_PAIR _skinDefaultValuePair[]; \
protected: \
	virtual const SKIN_DEFAULT_VALUE_INFO* GetSkinDefaultValueInfo() const; \

//��ʼĬ��ֵ��
#define BEGIN_SKIN_DEFAULT_VALUE_MAP(theClass, baseClass) \
	const SKIN_DEFAULT_VALUE_INFO* theClass::GetSkinDefaultValueInfo() const \
	{return &theClass::_skinDefaultValueInfo;}; \
	const SKIN_DEFAULT_VALUE_PAIR theClass::_skinDefaultValuePair[] = { \

//����һ��Ĭ��ֵ���dispName����Ͷ����Dispid��nameһ��
#define SKIN_DEFALUT_VALUE(theClass, dispName, dispValue) \
	{FALSE, SKIN_DISPID(theClass, dispName), _T(dispValue)}, \

//����Ĭ��ֵ��
//ע�⣺�˴��ٶ���ȫ�ֱ���theClass::_skinDefaultValuePair�ĳ�ʼ��˳����theClass::_skinDefaultValueInfo֮ǰ
#define END_SKIN_DEFAULT_VALUE_MAP(theClass) \
	{TRUE, 0, NULL} }; \
	const SKIN_DEFAULT_VALUE_INFO theClass::_skinDefaultValueInfo(_skinDefaultValuePair); \

