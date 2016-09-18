/********************************************************************
	����ʱ�䣺	2014/10/08  11:42:49 
	�ļ�����    	MyObjectFactory.h
	���ߣ�		лС��
	
	���ܣ�		1.����com�����ഴ��
				2.
				
	˵����	    1. �����ǵ���CoCreateInstance��������com�����ʱ��com��׼������DllGetClassObject��ȡ�����������ɹ�������������Ա����CreateInstance������������Ҫ��com����
				2. 
*********************************************************************/
#ifndef __MYOBJECTFACTORY_H_
#define __MYOBJECTFACTORY_H_
#include <Unknwn.h>

extern ULONG    g_LockNumber;
class CObjectFactory :public IClassFactory
{
protected:
	int m_nRef;
public:
	CObjectFactory(void);
public:
	~CObjectFactory(void);
public:
	HRESULT __stdcall QueryInterface(REFIID riid, void **ppvObject);
	ULONG   __stdcall AddRef(void);
	ULONG   __stdcall Release(void);
public:
	HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObject);
	HRESULT STDMETHODCALLTYPE LockServer(BOOL fLock);
};

#endif