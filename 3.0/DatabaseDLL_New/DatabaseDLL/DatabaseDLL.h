// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DATABASEDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DATABASEDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DATABASEDLL_EXPORTS
#define DATABASEDLL_API __declspec(dllexport)
#else
#define DATABASEDLL_API __declspec(dllimport)
#endif

// �����Ǵ� DatabaseDLL.dll ������
// class DATABASEDLL_API CDatabaseDLL {
// public:
// 	CDatabaseDLL(void);
// 	// TODO:  �ڴ�������ķ�����
// };

extern DATABASEDLL_API int nDatabaseDLL;

DATABASEDLL_API int fnDatabaseDLL(void);
