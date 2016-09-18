#ifndef __IDATABASE_IO_H_
#define __IDATABASE_IO_H_


// ���ݿ�����
typedef enum enumDATABASE_TYPE : UINT
{
	SQLSERVER	= 0,	// SQL Server ���ݿ�
	ORACLE		= 1,	// Oracle ���ݿ�
	ACCESS		= 2,	// ACCESS ���ݿ�
	MYSQL		= 3,	// MySQL  ���ݿ�
	EXCEL		= 4,    // Excel  ���ݿ�
	//	FOXPRO		= 5,    // FoxPro ���ݿ�
}DATABASE_TYPE;

//DECLARE_INTERFACE_(IDataBaseModule, IUnknown)
class IDataBaseModule
{
public:
	virtual ~IDataBaseModule(){};
	STDMETHOD_(long, OnInit)(std::wstring ServerName ,std::wstring DatabaseName ,DATABASE_TYPE enumData_type = DATABASE_TYPE::SQLSERVER ,std::wstring UserName = L"" ,std::wstring UserPassword = L"",std::wstring strConnectionStringOut = L"" ,void /*IDataBase*/ * pIDataBase = NULL) PURE;
	STDMETHOD_(long, MyExecute)(TCHAR * SQL) PURE;
	STDMETHOD_(long, MyExecute)(CString & SQL) PURE;

	STDMETHOD_(long,  MyQuarty)(TCHAR * SQL , _RecordsetPtr & m_RecordSetPtr) PURE;
	STDMETHOD_(long,  MyQuarty)(CString & , _RecordsetPtr & m_RecordSetPtr) PURE;

	STDMETHOD_(long,  GetCount)(TCHAR * SQL) PURE;
	STDMETHOD_(long,  GetCount)(CString & SQL) PURE;
	STDMETHOD_(long,  GetCount)(_RecordsetPtr & record) PURE;

	STDMETHOD_(long,  GetTableCount)(TCHAR * TableName) PURE;
	STDMETHOD_(long,  GetTableCount)(CString & TableName) PURE;

	STDMETHOD_(long,  GetExist)(TCHAR * SQL) PURE;
	STDMETHOD_(long,  GetExist)(CString & SQL) PURE;
	STDMETHOD_(long,  GetExist)(_RecordsetPtr & record) PURE;

	STDMETHOD_(long,  GetTableData)(TCHAR * TableName , _RecordsetPtr & record) PURE;
	STDMETHOD_(long,  GetTableData)(CString & TableName , _RecordsetPtr & record) PURE;

	STDMETHOD_(long,  GetColumnCount)(TCHAR * TableName) PURE;
	STDMETHOD_(long,  GetColumnCount)(_RecordsetPtr & record) PURE;
	STDMETHOD_(long,  GetColumnCount)(CString & Tablename) PURE;

	STDMETHOD_(long,  GetColumnName)(TCHAR * TableName , int & ColumnNum ,TCHAR * ColumnName) PURE;
	STDMETHOD_(long,  GetColumnName)(CString & Tablename ,int & ColumnNum ,CString &  ColumnName) PURE;
	STDMETHOD_(long,  GetColumnName)(_RecordsetPtr & m_record , int & ColumnNum ,TCHAR * ColumnName) PURE;
	STDMETHOD_(long,  GetColumnName)(_RecordsetPtr & m_record , int & ColumnNum ,CString & ColumnName) PURE;

	STDMETHOD_(long,  GetColumnNameList)(TCHAR * TableName ,map<int,string> & ColumnName) PURE;
	STDMETHOD_(long,  GetColumnNameList)(CString & Tablename ,map<int,CString> ColumnName) PURE;
	STDMETHOD_(long,  GetColumnNameList)(_RecordsetPtr & m_record , map<int,string> & ColumnName) PURE;
	STDMETHOD_(long,  GetColumnNameList)(_RecordsetPtr & m_record ,map<int,CString> ColumnName) PURE;

	STDMETHOD_(void,  CloseConnect)()PURE;
	STDMETHOD_(void,  SetConnectionState)(BOOL bState) PURE;
	STDMETHOD_(BOOL,  GetConnectionState)() PURE;
	STDMETHOD_(_RecordsetPtr & , GetRecordSet)() PURE;
	STDMETHOD_(_ConnectionPtr &,  GetConnectionPtr)() PURE;

	STDMETHOD_(long,  SetServerInfo)(TCHAR * ServerName ,TCHAR * DatabaseName) PURE;
	STDMETHOD_(long,  SetServerInfo)(CString &  ServerName ,CString &  DatabaseName) PURE;
	STDMETHOD_(long,  SetServerInfo)(TCHAR * ServerName ,TCHAR * DatabaseName ,TCHAR * UserName ,TCHAR * UserPassword) PURE;
	STDMETHOD_(long,  SetServerInfo)(CString &  ServerName ,CString &  DatabaseName ,CString &  UserName ,CString &  UserPassword) PURE;

	STDMETHOD_(long,  CreateConnect)() PURE;

	STDMETHOD_(std::wstring, GetServerName)() const PURE;
	STDMETHOD_(std::wstring, GetServerUsr)() const PURE;
	STDMETHOD_(std::wstring, GetServerPsd)() const PURE;
	STDMETHOD_(std::wstring, GetDatabaseName)() const PURE;
	STDMETHOD_(std::wstring, GetConnectionStr)() const PURE;

};
// 
// // �����ӿ���Ҫ��IID
// // {91DFCEFA-6B46-468f-BCE4-E85322ECA0CF}
// DEFINE_GUID(IID_DATABASEMODULE, 
// 			0x91dfcefa, 0x6b46, 0x468f, 0xbc, 0xe4, 0xe8, 0x53, 0x22, 0xec, 0xa0, 0xcf);
// 
// 
// // �����ӿ���Ҫ��GUID
// // {CCBD9AF6-AB5D-4d70-B2BD-CC868CC21E57}
// DEFINE_GUID(CLSID_DATABASEMODULE, 
// 			0xccbd9af6, 0xab5d, 0x4d70, 0xb2, 0xbd, 0xcc, 0x86, 0x8c, 0xc2, 0x1e, 0x57);
// 
// //���ڴ������ݿ���ں���
// //ע�⣺�˺�����ʹ��ע�������������������Ҫ�ɹ�����Ҫ��ע��dll
// //�벻Ҫ���������ʹ������Release�����ͷ�com�ӿ�
// bool CreatIDataBaseSql(IDataBaseModule * & lpiDataBaseSql)
// {
// 	if (FAILED(lcCreateInstance(CLSID_DATABASEMODULE, IID_DATABASEMODULE, (void **)&lpiDataBaseSql, NULL)))
// 		return false;
// 	else
// 		return true;
// }
// 
// //���ڴ������ݿ���ں���
// //ע�⣺�˺���ͨ��dll·������������
// //�벻Ҫ���������ʹ������Release�����ͷ�com�ӿ�
// bool CreatIDataBaseSql(LPCSTR lpszDll,IDataBaseModule * & lpiDataBaseSql)
// {
// 	if (FAILED(lcCreateInstanceEx(lpszDll,CLSID_DATABASEMODULE, IID_DATABASEMODULE, (void **)&lpiDataBaseSql, NULL)))
// 		return false;
// 	else
// 		return true;
// }
// 
// bool ReleaseIDataBaseSql(IDataBaseModule * & lpiDataBaseSql)
// {
// 	SAFE_RELEASE(lpiDataBaseSql);
// 
// 	return true;
// }

#endif