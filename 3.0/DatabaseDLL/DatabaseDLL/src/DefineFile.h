#pragma once
#include <map>
#include <string>
using namespace std;

//���ļ����ڷ���ֵ����

#define CONNECTION_ON	TRUE
#define CONNECTION_OFF	FALSE

#define CREATE_CONNECT_SUCCESS	0
#define CREATE_CONNECT_FAIL		1

#define EXECUTE_SUCCESS	-1
#define EXECUTE_FAIL	-2

#define SEARCH_SUCCESS	-1
#define SEARCH_FAIL		-2

#define DATA_EXIST	0
#define DATA_NULL	1

#define GET_COLUMN_SUM_FAIL	-1
#define COLUMN_NAME_ERROR	-2

#define GET_COLUMN_NAME_SUCESS	-1
#define GET_COLUMN_NAME_FAIL	-2

#define RECORDSETPTR_ERROR	-6
#define TABLE_NAME_ERROR	-3
#define DATABASE_INFO_ERROR	-4
#define SQL_SENTENCE_ERROR	-5

#define MAX_SERVER_NAME_LENTH				16
#define MAX_DATABASE_NAME_LENTH				16
#define MAX_DATABASE_USER_NAME_LENTH		16
#define MAX_DATABASE_USER_PASSWORD_LENTH	16
