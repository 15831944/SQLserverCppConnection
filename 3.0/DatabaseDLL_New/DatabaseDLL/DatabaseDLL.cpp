// DatabaseDLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "DatabaseDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//dll export
#include "../src/include/MyRegistry.h"
#include "../src/include/MyObjectFactory.h"
#include "../src/include/IDatabaseIO.h"

HMODULE g_hModule = NULL;
//ULONG    g_LockNumber;
// EXTERN_C const CLSID IID_DATABASEMODULE;
// EXTERN_C const CLSID CLSID_DATABASEMODULE;


STDAPI DllGetClassObject(const CLSID& clsid, const IID& iid, void **ppv)
{
	TRACE(L"DllGetClassObject...");
	if (clsid == CLSID_DATABASEMODULE) {

		CObjectFactory *pFactory = new CObjectFactory;

		if (pFactory == NULL) {
			return E_OUTOFMEMORY;
		}

		HRESULT result = pFactory->QueryInterface(iid, ppv);

		return result;
	}
	else
	{
		return CLASS_E_CLASSNOTAVAILABLE;
	}
}

STDAPI DllCanUnloadNow(void)
{
	if (g_LockNumber == 0)
		return S_OK;
	else
		return S_FALSE;
}

STDAPI DllRegisterServer()
{
	TCHAR szFileName[MAX_PATH];
	::GetModuleFileName((HMODULE)g_hModule, szFileName, sizeof(szFileName));
	TRACE(szFileName);
	return RegisterServer(CLSID_DATABASEMODULE, szFileName, "dataBaseCom.Object", "dataBase Componet", NULL);
}


STDAPI DllUnregisterServer()
{
	//return AMovieDllRegisterServer2(FALSE);
	return UnregisterServer(CLSID_DATABASEMODULE, "dataBaseCom.Object", NULL);

}

BOOL MyDllMain(HMODULE hModule)
{
	if (!g_hModule)
		g_hModule = hModule;

	return TRUE;
}
//------------------------------------end



// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO:  ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����:  MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO:  �ڴ˴�ΪӦ�ó������Ϊ��д���롣
			MyDllMain(hModule);
		}
	}
	else
	{
		// TODO:  ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����:  GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
