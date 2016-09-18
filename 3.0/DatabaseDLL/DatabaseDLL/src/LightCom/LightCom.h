#ifndef _LIGHTCOM_H
#define _LIGHTCOM_H
//////////////////////////////////////////////////////////////////////////
//
//	LightCom.h
//
//	��װ������ COM ���
//
//-------------------------------------------------------------
//	2006-11-3
//	Ver 1.1
//	Typhone ����޸�
//-------------------------------------------------------------
//
//////////////////////////////////////////////////////////////////////////

#include <AFXTEMPL.H>
#include <olectl.h>

DECLARE_INTERFACE_(IPureUnknown, IUnknown)
{
	
};

//-------------------------------------------------------------
//	���� IUnknown
#define LC_DECLARE_UNKNOWN	\
protected:\
	ULONG		m_cRef;\
	IUnknown	*m_pOuterUnknown;\
public:\
	STDMETHOD_(ULONG, AddRef)();\
	STDMETHOD_(ULONG, Release)();\
	STDMETHOD(QueryInterface)(REFIID riid, void **ppv);\
protected:\
	virtual BOOL OnInitialize();\
	virtual void OnFinalRelease();
//-------------------------------------------------------------

//-------------------------------------------------------------
//	��ʼ�� IUnknown
#define LC_INIT_UNKNOWN	\
	m_cRef = 0;\
	m_pOuterUnknown = NULL;
//-------------------------------------------------------------

//-------------------------------------------------------------
//	���� IUnknown
#define LC_DECLARE_UNKNOWN_(classname)	\
protected:\
	ULONG		m_cRef;\
	IUnknown	*m_pOuterUnknown;\
public:\
	classname##Exp() {LC_INIT_UNKNOWN};\
	classname##Exp(IUnknown *pUnknown) {LC_INIT_UNKNOWN; m_pOuterUnknown = pUnknown;};\
public:\
	STDMETHOD_(ULONG, AddRef)();\
	STDMETHOD_(ULONG, Release)();\
	STDMETHOD(QueryInterface)(REFIID riid, void **ppv);\
public:\
	HRESULT Initialize() {return OnInitialize();};\
	void FinalRelease() {OnFinalRelease();};\
protected:\
	virtual HRESULT OnInitialize();\
	virtual void OnFinalRelease();
//-------------------------------------------------------------

//-------------------------------------------------------------
//	���������
#define LC_BEGIN_INIT(classname)	\
	HRESULT classname##Exp::OnInitialize()	\
	{

#define LC_END_INIT	\
	}

#define LC_BEGIN_RELEASE(classname)	\
	void classname##Exp::OnFinalRelease()\
	{
	
#define LC_END_RELEASE	\
	}

//-------------------------------------------------------------

//-------------------------------------------------------------
//	���������
#define LC_BEGIN_DECLARE_CLASS(classname)	\
class classname##Exp : public IPureUnknown

#define LC_DO_INHERITED(classname)	\
, public classname

#define LC_END_DECLARE_CLASS(classname)	\
{\
	LC_DECLARE_UNKNOWN_(classname)\
};

#define LC_DECLARE_CLASS(classname)\
	LC_BEGIN_DECLARE_CLASS(classname)\
	LC_DO_INHERITED(classname)\
	LC_END_DECLARE_CLASS(classname)
//-------------------------------------------------------------

//-------------------------------------------------------------
//	ʵ�� AddRef �� Release
#define LC_IMPL_REF(classname)	\
STDMETHODIMP_(ULONG) classname##Exp::AddRef()\
{\
	if (m_pOuterUnknown)\
	{\
		return m_pOuterUnknown->AddRef();\
	}\
	return (++m_cRef);\
}\
STDMETHODIMP_(ULONG) classname##Exp::Release()\
{\
	if (m_pOuterUnknown)\
	{\
		return m_pOuterUnknown->Release();\
	}\
	m_cRef--;\
	if (!m_cRef)\
	{\
		FinalRelease();\
		delete this;\
		return 0;\
	}\
	return m_cRef;\
}
//-------------------------------------------------------------

//-------------------------------------------------------------
//	��ʼ QueryInterface
#define LC_BEGIN_QUERYINTERFACE(classname)	\
	STDMETHODIMP classname##Exp::QueryInterface(REFIID riid, void **ppv)\
{\
	if (!ppv)\
	{\
		return E_INVALIDARG;\
	}
//-------------------------------------------------------------

//-------------------------------------------------------------
//	���� QueryInterface
#define LC_END_QUERYINTERFACE	\
	if (m_pOuterUnknown)\
	{\
		return m_pOuterUnknown->QueryInterface(riid, ppv);\
	}\
	return E_NOINTERFACE;\
}
//-------------------------------------------------------------

//-------------------------------------------------------------
//	���� QueryInterface
#define LC_END_QUERYINTERFACE_(inheritedclass, iid, interfacename)	\
	if (!FAILED(inheritedclass::QueryInterface(iid, interfacename)))\
	{\
		if (m_pOuterUnknown)\
		{\
			return m_pOuterUnknown->QueryInterface(riid, ppv);\
		}\
	}\
	return E_NOINTERFACE;\
}
//-------------------------------------------------------------

//-------------------------------------------------------------
//	ִ�� QueryInterface
#define LC_DO_QUERYINTERFACE(iid, interfacename)	\
	if (IsEqualGUID(riid, iid))\
	{\
		*ppv = static_cast<interfacename *>(this);\
		(static_cast<IPureUnknown *>(*ppv))->AddRef();\
		return S_OK;\
	}
//-------------------------------------------------------------

//-------------------------------------------------------------
//	ʵ������ӿ���
#define LC_BEGIN_IMPL_CLASS_NOINIT(classname)\
	LC_IMPL_REF(classname)\
	LC_BEGIN_QUERYINTERFACE(classname)

#define LC_BEGIN_IMPL_CLASS(classname)\
	HRESULT classname##Exp::OnInitialize() {return S_OK;}\
	void classname##Exp::OnFinalRelease() {};\
	LC_IMPL_REF(classname)\
	LC_BEGIN_QUERYINTERFACE(classname)

#define LC_DO_IMPL_CLASS(iid, interfacename)		LC_DO_QUERYINTERFACE(iid, interfacename)

#define LC_END_IMPL_CLASS\
	LC_END_QUERYINTERFACE

#define LC_IMPL_CLASS(classname, iid, interfacename)\
	LC_BEGIN_IMPL_CLASS(classname)\
	LC_DO_IMPL_CLASS(iid, interfacename)\
	LC_END_IMPL_CLASS
//-------------------------------------------------------------

//-------------------------------------------------------------
#define LC_DECLARE_EXP	\
extern CArray <LC_MODULE_INFO, LC_MODULE_INFO>	g_xxaLightComExpClassInfo;\
HRESULT __stdcall LightComCreate(REFCLSID rclsid, REFIID riid, void **lplpv, IUnknown *pUnknown);\
HRESULT __stdcall DllRegisterServer();\
HRESULT __stdcall DllUnregisterServer();
//-------------------------------------------------------------

//-------------------------------------------------------------
//	�Զ�ʵ���������������
#define LC_BEGIN_CREATE \
	HRESULT __stdcall LightComCreate(REFCLSID rclsid, REFIID riid, void **lplpv, IUnknown *pUnknown)\
	{\
		HRESULT hr = E_NOINTERFACE;

#define LC_DO_CREATE(classname, clsid)\
		classname##Exp *pObj##classname##Exp = NULL;\
		if (IsEqualGUID(rclsid, clsid))\
		{\
			pObj##classname##Exp = new classname##Exp(pUnknown);\
			if (pObj##classname##Exp)\
			{\
				if (!FAILED(hr = pObj##classname##Exp->Initialize()))\
				{\
					if (FAILED(hr = static_cast<IPureUnknown *>(pObj##classname##Exp)->QueryInterface(riid, lplpv)))\
					{\
						static_cast<IPureUnknown *>(pObj##classname##Exp)->Release();\
					}\
				}\
				else\
				{\
					delete pObj##classname##Exp;\
				}\
			}\
			else\
			{\
				hr = E_OUTOFMEMORY;\
			}\
		}

#define LC_END_CREATE\
		return hr;\
	}

#define LC_BEGIN_EXP	\
	CArray <LC_MODULE_INFO, LC_MODULE_INFO>	g_xxaLightComExpClassInfo;\
	void lcFillInfo()\
	{

#define LC_DO_EXP(classname, clsid, author, version, script)	\
	LC_MODULE_INFO info##classname##Exp;	\
	info##classname##Exp.dwSize = sizeof(LC_MODULE_INFO);\
	info##classname##Exp.ClassId = clsid;\
	strcpy(info##classname##Exp.szName, #classname"Exp");\
	info##classname##Exp.dwVersion = version;\
	strcpy(info##classname##Exp.szDescript, script);\
	strcpy(info##classname##Exp.szAuthor, author);\
	char sz##classname[MAX_PATH];\
	ZeroMemory(sz##classname, MAX_PATH);\
	GetModuleFileName(theApp.m_hInstance, sz##classname, MAX_PATH);\
	CString str##classname = sz##classname;\
	strncpy(info##classname##Exp.szPath, (LPSTR)(LPCSTR)str##classname, 200);\
	int nIndex##classname = str##classname.ReverseFind('\\');\
	if (nIndex##classname >= 0)\
	{\
		str##classname = str##classname.Right(str##classname.GetLength() - nIndex##classname - 1);\
	}\
	strncpy(info##classname##Exp.szFile, (LPSTR)(LPCSTR)str##classname, 200);\
	g_xxaLightComExpClassInfo.Add(info##classname##Exp);

#define LC_END_EXP	\
	}\
HRESULT __stdcall DllRegisterServer()\
{\
	HRESULT hr = E_FAIL;\
	lcFillInfo();\
	for (int i = 0; i < g_xxaLightComExpClassInfo.GetSize(); i++)\
	{\
		LC_MODULE_INFO info = g_xxaLightComExpClassInfo.GetAt(i);\
		if (FAILED(hr = LC_SelfReg(info)))\
		{\
			CString strErr;\
			strErr.Format("ע���� [ %s ] ʧ��!", info.szName);\
			AfxMessageBox(strErr);\
		}\
	}\
	return hr;\
}\
HRESULT __stdcall DllUnregisterServer()\
{\
	HRESULT hr = S_OK;\
	lcFillInfo();\
	for (int i = 0; i < g_xxaLightComExpClassInfo.GetSize(); i++)\
	{\
		LC_MODULE_INFO info = g_xxaLightComExpClassInfo.GetAt(i);\
		LC_UnReg(info.ClassId);\
	}\
	return hr;\
}
    
//-------------------------------------------------------------

#define PROC_RETURNINTERFACE(ptr, ppv)	\
{\
	if (ptr)\
	{\
		if (ppv)\
		{\
			*ppv = ptr;\
			(*ppv)->AddRef();\
		}\
		return S_OK;\
	}\
	return E_NOTIMPL;\
}

//-------------------------------------------------------------
//	��ݲ����궨��
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)	{ if ( p ) { p->Release(); p = NULL; } }
#endif
#define RELEASE(p)		SAFE_RELEASE(p)
#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if ( p ) { delete p; p = NULL; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if ( p ) { delete []p; p = NULL; } }
#endif
#define ZeroVar(p)		ZeroMemory( &p, sizeof( p ) )
#define CpyVar(dst, src)	memcpy( &dst, &src, sizeof( src ) )
#define ADDREF(p)	{ if (p) { p->AddRef(); } }
//-------------------------------------------------------------

//-------------------------------------------------------------
//	�����Ϣ			
#define INFO_TEXT_LEN	200
typedef struct tagLC_MODULE_INFO
{
	DWORD	dwSize;
	char	szName[INFO_TEXT_LEN];
	GUID	ClassId;
	DWORD	dwVersion;
	char	szDescript[INFO_TEXT_LEN];
	char	szPath[INFO_TEXT_LEN];
	char	szFile[INFO_TEXT_LEN];
	char	szAuthor[INFO_TEXT_LEN];
}LC_MODULE_INFO, *PLC_MODULE_INFO;
//-------------------------------------------------------------

//-------------------------------------------------------------
//	�����Ϣע���ؼ���
#define SZ_KEY_LIGHTCOM	"LightCom"
#define SZ_KEY_CLASS		"Class"

#define SZ_VALUE_NAME		"ModuleName"
#define SZ_VALUE_CLSID		"ClassId"
#define SZ_VALUE_VER		"Version"
#define SZ_VALUE_DESCRIPT	"Descript"
#define SZ_VALUE_PATH		"ModulePath"
#define SZ_VALUE_FILE		"ModuleFile"
#define SZ_VALUE_AUTHOR		"ModuleAuthor"
//-------------------------------------------------------------

//-------------------------------------------------------------
//	�������
extern HRESULT __stdcall LightComCreate(REFCLSID rclsid, REFIID riid, void **ppv, IUnknown *pUnknown);
//	��ע��
extern HRESULT __stdcall LC_SelfReg(LC_MODULE_INFO &info);
//	������
extern HRESULT __stdcall LC_FindClass(REFCLSID rclsid, PLC_MODULE_INFO pInfo, DWORD *pdwSize);							
//	ж��
extern void	__stdcall LC_UnReg(REFCLSID rclsid);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	�������������
#define LIGHTCOMCREATE_PROCNAME	"LightComCreate"
//	ע�ᶯ̬���ӿ⺯����
#define LIGHTCOMREG_PROCNAME	"DllRegisterServer"
//	��ע�ᶯ̬���ӿ⺯����
#define LIGHTCOMUNREG_PROCNAME	"DllUnregisterServer"
//-------------------------------------------------------------

//-------------------------------------------------------------
//	��������
typedef HRESULT (__stdcall *LIGHTCOMCREATEPROC)(REFCLSID rclsid, REFIID riid, void **ppv, IUnknown *pUnknown);
typedef HRESULT (__stdcall *LIGHTCOMREGPROC)();
typedef HRESULT (__stdcall *LIGHTCOMUNREGPROC)();
//-------------------------------------------------------------

//-------------------------------------------------------------
//	�����б�
//		�Զ����������� COM ���
typedef struct tagLIGHTCOMMODULE
{
	char		szPath[MAX_PATH];
	HMODULE		hModule;
}LIGHTCOMMODULE, *PLIGHTCOMMODULE;

typedef CArray<LIGHTCOMMODULE, LIGHTCOMMODULE>	CLightComModuleArray;

class CObjList  
{
private:
	CLightComModuleArray m_aObjList;
private:
	void ClearAll();
	BOOL FindPath(REFCLSID rclsid, CString &str);
	HMODULE AutoLoadModule(LPCSTR lpsz, BOOL *pbLoadNewModule);
	BOOL RemoveModule(HMODULE hModule);
public: 
	CObjList();
	virtual ~CObjList();
public:
	HRESULT CreateObjEx(LPCSTR lpszDllFile, REFCLSID rclsid, REFIID riid, void **ppv, IUnknown *pUnknown);
	HRESULT CreateObj(REFCLSID rclsid, REFIID riid, void **ppv, IUnknown *pUnknown);
	HRESULT CreateObjInternal(HINSTANCE hInstance, REFCLSID rclsid, REFIID riid, void **ppv, IUnknown *pUnknown);
	HRESULT RegComponent(LPCSTR lpsz);
	HRESULT UnRegComponent(REFCLSID rclsid);
	//  DengBin-[2014/2/26 14:47]
	void	ObjFreeLibrary(HINSTANCE hInstance);
};
//-------------------------------------------------------------

//-------------------------------------------------------------
//	�������ʵ��
HRESULT __stdcall lcCreateInstance(REFCLSID rclsid, REFIID riid, void **ppv, IUnknown *pUnknown);
HRESULT __stdcall lcCreateInstanceEx(LPCSTR lpszDll, REFCLSID rclsid, REFIID riid, void **ppv, IUnknown *pUnknown);
HRESULT __stdcall lcCreateInstanceInternal(HINSTANCE hInstance, REFCLSID rclsid, REFIID riid, void **ppv, IUnknown *pUnknown);
HINSTANCE __stdcall lcGetLastInstance();
//  DengBin-[2014/2/26 14:47]
void __stdcall lcFreeInstanceLibrary(HINSTANCE hInstance);
//	ע�����
HRESULT __stdcall RegComponent(LPCSTR lpsz);
//	��ע�����
HRESULT __stdcall UnRegComponent(REFCLSID rclsid);
//-------------------------------------------------------------

//-------------------------------------------------------------
//	��ע��������ʵ��
#define LCCREATEINSTANCE_BYREG(rclsid, riid, ppv, pUnknown)	lcCreateInstance(rclsid, riid, ppv, pUnknown)
//	���ļ��������ʵ��
#define LCCREATEINSTANCE_BYFILE(lpszDll, rclsid, riid, ppv, pUnknown)	lcCreateInstanceEx(lpszDll, rclsid, riid, ppv, pUnknown)
//-------------------------------------------------------------

//-------------------------------------------------------------
//	���ݺ��־�Զ��жϴ�ע�������ļ��������
#ifndef _LIGHTCOMCREATE_BY_FILENAME
#define LCCREATEINSTANCE(lpszDll, rclsid, riid, ppv, pUnknown)	LCCREATEINSTANCE_BYREG(rclsid, riid, ppv, pUnknown)
#else
#define LCCREATEINSTANCE(lpszDll, rclsid, riid, ppv, pUnknown)	LCCREATEINSTANCE_BYFILE(lpszDll, rclsid, riid, ppv, pUnknown)
#endif
//-------------------------------------------------------------

//-------------------------------------------------------------
//	�Զ���ʼ���ӿ�
#define INIT_INTERFACE(lpi)		{lpi = NULL;}
#define FINAL_INTERFACE(lpi)	{SAFE_RELEASE(lpi);}
#define AUTO_INTERFACE(lpi)		{if (xxbInitInterface_auto) INIT_INTERFACE(lpi) else FINAL_INTERFACE(lpi)}
//-------------------------------------------------------------

//-------------------------------------------------------------
//	�Զ���ʼ��
#define _INIT(member, value)	member = value;
//-------------------------------------------------------------

//-------------------------------------------------------------
//	��ʼ�������ͷŽӿڱ�־
#define START_INITINTERFACE		BOOL xxbInitInterface_auto = TRUE;
#define START_DESTROYINTERFACE	BOOL xxbInitInterface_auto = FALSE;
//���ں� DEAL_INTERFACE �м�����Ҫ�Զ���ʼ�����ͷŵĽӿ�
//���ڹ��캯�������������е���(���Զ���ʼ��ǰ�ȵ��� START_INITINTERFACE, ���Զ�����ǰ�ȵ��� START_DESTROYINTERFACE)
//-------------------------------------------------------------

//-------------------------------------------------------------
//	���� Debug ���־�Զ����춯̬���ӿ�·��
#ifdef _DEBUG
#define _XX_DEBUG_ID	"D"
#else
#define _XX_DEBUG_ID	""
#endif
#define MAKE_MODULE_PATH(str, strFolder, strPureFileName)	str.Format("%s\\%s%s.dll", strFolder, strPureFileName, _XX_DEBUG_ID);
#define MAKE_MODULE_PATH_(str, strFolder, strPureFileName, strExt)	str.Format("%s\\%s%s.%s", strFolder, strPureFileName, _XX_DEBUG_ID, strExt);
//-------------------------------------------------------------

#endif