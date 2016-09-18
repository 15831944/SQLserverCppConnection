#pragma once
#include "DefineFile.h"

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__,__LINE__)
#endif

#define __NUMBER_TO_STR(x) #x
// ��������Ԥ���������ת��Ϊ�ַ��������磺�� 4354 ת��Ϊ "4354"
#define NUMBER_TO_STR(x)			__NUMBER_TO_STR(x)
// �ڱ�����Ϣ������ļ����еĶ�λ��־������ͨ��˫������Ϣ��λ��Դ����
#define FILE_LINE_TEXT __FILE__  "(" NUMBER_TO_STR(__LINE__) ") : "

//----------------------just for simplicity , But not recommended
#define DO_EXCUTE_FUN1(_SELECTOR)\
	if (SQL.IsEmpty())\
	return SQL_SENTENCE_ERROR;\
	int err=(this->_SELECTOR)(SQL.GetBuffer());\
	SQL.ReleaseBuffer();\
	return err;

#define DO_EXCUTE_FUN2(_SELECTOR , _PARAM2)\
	if (SQL.IsEmpty())\
	return SQL_SENTENCE_ERROR;\
	int err=(this->_SELECTOR)(SQL.GetBuffer(),_PARAM2);\
	SQL.ReleaseBuffer();\
	return err;

#define COM_ERROR_MESSAGE_OUT\
	TCHAR buf[1024];\
	wsprintf( buf, _T("%s\r\n Code = %08lx\r\n Cnode meaning = %d\r\n Source = %s\r\n Description = %s\r\n"), \
	_T("SQL ERROR=") ,e.Error(), e.ErrorMessage(), (LPCSTR)((_bstr_t)e.Source()), (LPCSTR)((_bstr_t)e.Description()));\
	::MessageBox(NULL, buf,_T("atabase Message"), MB_OK);

#define  GET_CSTRING(CHAR_NAME)\
	if (m_pIDataBase)\
	{\
		return m_pIDataBase->CHAR_NAME; \
	}\
	else\
		return L""; 

//--------------------------------------end

////////////////////////////////////////////////////////
class CriticalSection//�ٽ���
{
public:
	CriticalSection(){InitializeCriticalSection(&m_CritiSect);};//��ʼ���ٽ���
	~CriticalSection(){DeleteCriticalSection(&m_CritiSect);};//ɾ���ٽ���
	void Enter(){EnterCriticalSection(&m_CritiSect);};//�����ٽ���
	void Leave(){LeaveCriticalSection(&m_CritiSect);};//�뿪�ٽ���
private:
	CRITICAL_SECTION m_CritiSect;//�����ٽ�������
};

class Lock//�Զ�����
{
public:
	explicit Lock(std::tr1::shared_ptr<CriticalSection> & PCritSect)//��������ʽת��
	{
		if (PCritSect)
		{
			m_pCritical=PCritSect;
			m_pCritical->Enter();
		}
	}
	~Lock(){ if (m_pCritical)m_pCritical->Leave();}
private:
	std::tr1::shared_ptr<CriticalSection> m_pCritical;//�Զ����ٽ���
};
///////////////////////////////////////////////////////////////

//----------------------------------------DATABASE TYPE
/*----Connection interface for different databases---------------*/

interface IDataBase 
{
	std::wstring m_strConnectionStringOut;//�ⲿ���������ַ���
	std::wstring m_strDataSource;//sql server ip address  : ���ݿ�������ַ��
	std::wstring m_strInitialCatalog;//Database name(���ݿ�����)
	std::wstring m_strUserID;//���ݿ������û���
	std::wstring m_strPassword;//���ݿ��û�����

	std::wstring  m_strConnectionString;//���ɵ������ַ������ɴ�ŵ�

	explicit IDataBase(std::wstring ServerName ,std::wstring DatabaseName ,std::wstring UserName ,std::wstring UserPassword,std::wstring strConnectionStringOut)
	{
		m_strDataSource = ServerName;
		m_strInitialCatalog = DatabaseName;
		m_strUserID = UserName;
		m_strPassword = UserPassword;
		m_strConnectionStringOut = strConnectionStringOut;
	}
	 
public:
	// ���ܣ��������ݿ���Ϣ ����ʼ��ConnectionPtr
	long  SetServerInfo(std::wstring ServerName ,std::wstring DatabaseName ,std::wstring UserName ,std::wstring UserPassword,std::wstring strConnectionStringOut);

	 //�ӿڶ���
	 //�Զ������ݿ�����
	 virtual long CreateConnect(_ConnectionPtr & _connectPtr) = 0; 
	 //���� :�������ݿ������ַ���
	 virtual void SetConnectionString()=0;
};

// ���� SQL Server ���ݿ�
class CSQlServer : public IDataBase
{
public:
	explicit CSQlServer(std::wstring ServerName ,std::wstring DatabaseName ,std::wstring UserName =  L"",std::wstring UserPassword = L"",std::wstring strConnectionStringOut = L"" ):IDataBase(ServerName,DatabaseName,UserName,UserPassword,strConnectionStringOut){}

	void SetConnectionString(){

		if (m_strConnectionStringOut.empty())
		{
			//�ڴ�����Լ�����������
			if (m_strUserID.empty() && m_strPassword.empty())
				m_strConnectionString = L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=" +m_strInitialCatalog+ 
				L";Data Source=" + m_strDataSource;
			else
				m_strConnectionString = L"Provider=SQLOLEDB.1; Server=" + m_strDataSource + 
				L"; Database=" + m_strInitialCatalog + 
				L"; UID=" + m_strUserID + 
				L"; PWD=" + m_strPassword + 
				L"; OLE DB Services=-1; Driver={SQL Server}";
		}
		else
			m_strConnectionString = m_strConnectionStringOut;

	}

	long CreateConnect(_ConnectionPtr & _connectPtr);

};

// ���� MySQL ���ݿ�
class CMySQl : public IDataBase
{
public:
	explicit CMySQl(std::wstring ServerName ,std::wstring DatabaseName ,std::wstring UserName = L"" ,std::wstring UserPassword = L"",std::wstring strConnectionStringOut = L"" ):IDataBase(ServerName,DatabaseName,UserName,UserPassword,strConnectionStringOut){}

	void SetConnectionString(){

		if (m_strConnectionStringOut.empty())
		{
			//�ڴ�����Լ�����������
			m_strConnectionString = L"DSN=sqloledb; Server=" + m_strDataSource + 
				L"; Database=" + m_strInitialCatalog + 
				L"; UID=" + m_strUserID + 
				L"; PWD=" + m_strPassword;
		}
		else
			m_strConnectionString = m_strConnectionStringOut;
	}

	long CreateConnect(_ConnectionPtr & _connectPtr);

};

// ���� ACCESS ���ݿ�
class CACCESS : public IDataBase
{
public:
	explicit CACCESS(std::wstring ServerName ,std::wstring DatabaseName ,std::wstring UserName = L"" ,std::wstring UserPassword = L"",std::wstring strConnectionStringOut = L"" ):IDataBase(ServerName,DatabaseName,UserName,UserPassword,strConnectionStringOut){}

	void SetConnectionString(){

		if (m_strConnectionStringOut.empty())
		{
			//�ڴ�����Լ�����������
			// 		if (m_strPassword.empty())
			// 			m_strConnectionString = L"Provider=" +m_strConnectionStringOut+
			// 				L";Data Source=" + m_strInitialCatalog;
			// 		else
			m_strConnectionString = L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + m_strInitialCatalog + 
				L";Persist Security Info=False;Jet OLEDB:Database Password=" + m_strPassword;
		}
		else
			m_strConnectionString = m_strConnectionStringOut;
	}

	long CreateConnect(_ConnectionPtr & _connectPtr);

};

class CEXCEL : public IDataBase
{
public:
	explicit CEXCEL(std::wstring ServerName ,std::wstring DatabaseName ,std::wstring UserName = L"" ,std::wstring UserPassword = L"",std::wstring strConnectionStringOut = L"" ):IDataBase(ServerName,DatabaseName,UserName,UserPassword,strConnectionStringOut){}

	void SetConnectionString(){
		if (m_strConnectionStringOut.empty())
		{
			//�ڴ�����Լ�����������
			m_strConnectionString = L"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + m_strInitialCatalog +   
				L";Extended Properties=\"Excel 8.0;HDR=Yes;IMEX=0\""; 
		}
		else
			m_strConnectionString = m_strConnectionStringOut;
	}

	long CreateConnect(_ConnectionPtr & _connectPtr);
};

// ���� Oracle ���ݿ�
class COracle : public IDataBase
{
public:
	explicit COracle(std::wstring ServerName ,std::wstring DatabaseName ,std::wstring UserName = L"" ,std::wstring UserPassword = L"",std::wstring strConnectionStringOut = L"" /*"MSDAORA.1    OraOLEDB.Oracle.1      {Microsoft ODBC for Oracle}"*/ ):IDataBase(ServerName,DatabaseName,UserName,UserPassword,strConnectionStringOut){}

	void SetConnectionString(){

		if (m_strConnectionStringOut.empty())
		{
			//�ڴ�����Լ�����������
			// 		m_strConnectionString = L"Provider=" + m_strConnectionStringOut+
			// 			L";User  Id=" + m_strUserID +
			// 			L";Password=" + m_strPassword +
			// 			L";Data Source=" + m_strInitialCatalog+
			// 			L";Persist Security Info=False";

			// 		m_strConnectionString = L"Provider=" + m_strConnectionStringOut + 
			// 			L";Password=" + m_strPassword +
			// 			L";Persist Security Info=True" +
			// 			L";User ID=" + m_strUserID +
			// 			L";Data Source=\"(DESCRIPTION =(ADDRESS_LIST =(ADDRESS = (PROTOCOL = TCP)(HOST = " + m_strDataSource +
			// 			L")(PORT = 1521)) )(CONNECT_DATA = (SID = "+ m_strInitialCatalog +
			// 			L")))\"";

			m_strConnectionString = L"Driver={Microsoft ODBC for Oracle};Server=(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST="+m_strDataSource+
				L")(PORT=1521))(CONNECT_DATA=(SID="+ m_strInitialCatalog +
				L")));Uid="+m_strUserID+
				L";Pwd="+m_strPassword+
				L";";
		}
		else
			m_strConnectionString = m_strConnectionStringOut;
	}

	long CreateConnect(_ConnectionPtr & _connectPtr);
	/*
	1����װoracle 
	2����sysdba��ʽ����orcl���ݿ�
	3���½���ռ䣬�½��û���sys�ϣ�������DBA��CONNECT ��Ȩ��
	4�����ʵ������ռ�δ������
		CREATE USER xxj IDENTIFIED BY xxj 
		GRANT DBA ,CONNECT TO xxj;
	*/
};
//--------------------------------------end

/*  ���ݿ⻹δ���ԣ�������
class CFoxPro : public IDataBase
{
public:
	explicit CFoxPro(std::wstring ServerName ,std::wstring DatabaseName ,std::wstring UserName = L"" ,std::wstring UserPassword = L"",std::wstring strConnectionStringOut = L"" ):IDataBase(ServerName,DatabaseName,UserName,UserPassword,strConnectionStringOut){}
	void SetConnectionString(){
		if (m_strConnectionStringOut.empty())
		{
			//�ڴ�����Լ�����������
			m_strConnectionString = L"Provider=MSDASQL.1;Driver=Microsoft Visual Foxpro Driver;SourceDB="+ m_strInitialCatalog +
				L"SourceType=DBF;";
		}
		else
			m_strConnectionString = m_strConnectionStringOut;
	}

	long CreateConnect(_ConnectionPtr & _connectPtr);
};
*/

