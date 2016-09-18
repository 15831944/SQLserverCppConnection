#ifndef __POCODBIO_H_
#define __POCODBIO_H_
#include <string>
#include <vector>
using namespace std;
#include "include\DefineFile.h"
#include "include\DatabaseIO.h"

//com �ӿ� ·��������ڳ���·��
#ifdef _DEBUG
#define __DLL_PATH "./DatabaseDLLD.dll"
#else
#define __DLL_PATH "./DatabaseDLL.dll"
#endif

#define MS_SQL_SERVER_ODBC_DRIVER L"SQL Server"
#define MS_SQL_SERVER_SERVER L"192.168.1.133"
#define MS_SQL_SERVER_DB L"OATransTool"
#define MS_SQL_SERVER_UID L"st"
#define MS_SQL_SERVER_PWD L"123456" 

class S
{
public:
	vector<string> m_menberData;
	int m_menberCount;
	S(){};
	~S(){};
};

// �����Ǵ� PocoDBIO.dll ������
class PocoDBIO {
public:
	PocoDBIO(void);
	PocoDBIO(string DBName);
	PocoDBIO(string DBName, string server, string uId, string pwd);
	~PocoDBIO(void);
	int GetCount(string &SQL);//��ȡ����
	//int GetColumn(string &SQL);//��ȡ����
 	void GetOneData(const string &SQL, string &result);
 	void GetData(const string &SQL, vector<S> &result);
 	bool GetExist(const string &SQL);//ִ��ָ����sql��䡣���ظ�����Ƿ��ܲ�ѯ�������
 	int GetColumnCount(string &Tablename);//��ȡ������
 	
 	int GetTableCount(string &tableName);//��ȡ������
 	void GetFields(string &tableName, string &columName, vector<string> &result);
 	void GetFields(string &tableName, int &columNum, vector<string> &result);

private:
	bool Init();//�����캯�����õĳ�ʼ������
	void Relese();//�ͷ�
	string m_connectString;
	CSQLServerIO m_DataBaseSql;//
	std::wstring StringToWString(const std::string& s);//string תwstring
};

#endif