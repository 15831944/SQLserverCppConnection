/********************************************************************
	����ʱ�䣺	2014/10/08  11:55:38 
	�ļ�����    	MyRegistry.h
	���ߣ�		лС��
	
	���ܣ�		1.��Ҫʵ��DllRegisterServer������ע���ע��ʹ��
				2.
				
	˵����	    1. 
				2. 
*********************************************************************/
#ifndef __MYREGISTRY_H_
#define __MYREGISTRY_H_

HRESULT RegisterServer(const CLSID& clsid,         // Class ID
	const TCHAR *szFileName,     // DLL module handle
	const TCHAR* szProgID,       //   IDs
	const TCHAR* szDescription,  // Description String
	const TCHAR* szVerIndProgID); // optional

HRESULT UnregisterServer(const CLSID& clsid,      // Class ID
	const TCHAR* szProgID,       //   IDs
	const TCHAR* szVerIndProgID); // Programmatic
#endif