#include "stdAfx.h"
#include "TypShell.h"
#include "math.h"
#include "shlwapi.h"

#pragma comment( lib, "shlwapi.lib" )

CString GetFileName( LPCSTR lpszPath )
{
	CString strFileName = lpszPath;
	
	int nPos = 0;
	do{
		nPos = strFileName.Find( "\\", 0 );
		if ( nPos >= 0 )
		{
			strFileName = strFileName.Right( strFileName.GetLength() - nPos - 1 );
		}
	}while( nPos >= 0 );
	//		ȥ�����Ҷ���Ŀո�
	strFileName.TrimLeft();
	strFileName.TrimRight();
	return strFileName;
}

CString GetFolderName( LPCSTR lpszPath )
{
	CString strFileName = lpszPath;
	
	int nPos = -1, nPos1 = -1;
	do{
		nPos1 = nPos;
		nPos = strFileName.Find( "\\", nPos + 1 );
	}while( nPos >= 0 );

	CString strFolder = "";
	if ( nPos1 >= 0 )
	{
		strFolder = strFileName.Left( nPos1 + 1 );
	}
	
	strFolder.TrimLeft();
	strFolder.TrimRight();

	return strFolder;
}

CString GetSafeFolder( LPCSTR lpszPath, BOOL bWithLSeparator/*=TRUE*/ )
{
	CString strPath = lpszPath;

	if ( bWithLSeparator )
	{
		if ( strPath.Find( "\\", strPath.GetLength() - 1 ) < 0 )
		{
			strPath += "\\";
		}
	}
	else
	{
		if ( strPath.Find( "\\", strPath.GetLength() - 1 ) >= 0 )
		{
			strPath = strPath.Left( strPath.GetLength() - 1 );
		}
	}

	strPath.TrimLeft();
	strPath.TrimRight();

	return strPath;
}

CString GetFileExt( LPCSTR lpszFile )
{
	CString strFile = lpszFile;

	int nPos = 0;
	do{
		nPos = strFile.Find( ".", 1 );
		if ( nPos > 0 )
			strFile = strFile.Right( strFile.GetLength() - nPos );
	}while( nPos > 0 );

	strFile.TrimLeft();
	strFile.TrimRight();

	return strFile;
}

CString GetPureName( LPCSTR lpszFile )
{
	CString strFile = GetFileName(lpszFile);
	
	int nPos = 0, nPos1 = 0;
	do{
		nPos1 = nPos;
		nPos = strFile.Find( ".", nPos + 1 );
	}while( nPos >= 0 );

	CString strPureName = strFile.Left(nPos1);

	if (nPos1 == 0)
	{
		strPureName = strFile;
	}

	strPureName.TrimLeft();
	strPureName.TrimRight();

	if (strPureName == "")
	{
		strPureName = lpszFile;
	}

	return strPureName;
}

#define BROWSEFOLDER_TITLE	"��ѡ��·��"
BOOL BrowseFolder( HWND hWnd, CString strCaption, CString &strPath )
{
	_browseinfoA *lpbi = new _browseinfoA;
	char szPathName[256];
	LPITEMIDLIST pID;
	
	lpbi->hwndOwner = hWnd;
	lpbi->pidlRoot = NULL;
	lpbi->pszDisplayName = (LPSTR)szPathName;
	
	if ( strCaption == "" )
		lpbi->lpszTitle = BROWSEFOLDER_TITLE;
	else
		lpbi->lpszTitle = (LPCTSTR)strCaption;
	
	lpbi->ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	lpbi->lpfn = NULL;
	lpbi->lParam = 0;
	lpbi->iImage = 0;
	pID = SHBrowseForFolder(lpbi);
	SHGetPathFromIDList( pID, (LPSTR)szPathName );
	
	delete lpbi;
	
	CString strPathTmp = (CString)szPathName;
	
	if (strPathTmp == "")
		return FALSE;
	else
	{
		strPath = GetSafeFolder( (CString)szPathName );
		return TRUE;
	}
}

CString GetModuleFile( HMODULE hModule )
{
	char sz[MAX_PATH];
	::GetModuleFileName( hModule, sz, MAX_PATH );
	return GetFileName( sz );
}

CString GetModulePath( HMODULE hModule )
{
	char sz[MAX_PATH];
	::GetModuleFileName( hModule, sz, MAX_PATH );
	return sz;
}

CString GetModuleFolder( HMODULE hModule )
{
	char sz[MAX_PATH];
	::GetModuleFileName( hModule, sz, MAX_PATH );
	return GetFolderName( sz );
}

CString ChInt(int Value, UINT uType)
{
	CString str, str2, str3, tmpstr; 
	DWORD i, TmpInt, absValue; 
	BOOL  zeroflag;
	
	absValue =abs(Value);
	if ( absValue >= 100000000 )
		str3 =ChInt(absValue / 100000000, uType)+"��";
	else
		str3 ="";
	
	TmpInt =absValue % 100000000 / 10000;
	if ( absValue>=10000 )
	{
		if ( (str3 != "")&&(TmpInt<1000) )
			str2 ="��"+ChInt(TmpInt, uType)+"��";
		else
			str2 =ChInt(TmpInt, uType)+"��";
	}
	else
	{
		if ( str3!="" )
			str2 = "��";
		else
			str2 = "";
	};
	
	zeroflag =FALSE;
	for (i = 0; i<4; i++)
	{
		if ( uType == 0 )
			switch(i) 
		{
      case 0:
		  tmpstr ="";
		  break;
	  case 1:
		  tmpstr ="ʮ";
		  break;
	  case 2:
		  tmpstr ="��";
		  break;
	  case 3:
		  tmpstr ="ǧ";
		  break;
	  case 4:
		  tmpstr ="��";
		  break;
		}
		else
			switch(i)
		{
	  case 0:
		  tmpstr ="";
		  break;
	  case 1:
		  tmpstr ="ʰ";
		  break;
	  case 2:
		  tmpstr ="��";
		  break;
	  case 3:
		  tmpstr ="Ǫ";
		  break;
	  case 4:
		  tmpstr ="��";
		  break;
		}

		if ( absValue == 0 )
			str = "��";

		if ( absValue >= pow(10.0, (int)i ) )
		{
			TmpInt =absValue % (int)(pow(10.0, (int)i+1)) / (int)(pow(10.0, (int)i));
			if ( ((absValue>=pow(10.0, (int)i+1))&&(zeroflag))||(TmpInt>0) )
			{
				if ( TmpInt>0 )
				{
					str = ChSInt((BYTE)TmpInt, uType)+tmpstr+str;
					zeroflag =TRUE;
				}
				else
				{
					str = "��"+str;
					zeroflag =FALSE;
				};
			};
		};
	};
	if ( Value>=0 )
		return str3+str2+str;
	else
		return "��"+str3+str2+str;
};

CString ChSInt( BYTE nValue, UINT uType)
{
  if (uType == CHI_LIT)
  switch( nValue )
  {
    case 0:
		return "��";
    case 1:
		return "һ";
    case 2:
		return "��";
    case 3: 
		return "��";
    case 4: 
		return "��";
    case 5: 
		return "��";
    case 6: 
		return "��";
    case 7: 
		return "��";
    case 8: 
		return "��";
    case 9: 
		return "��";
    default:
       return "E";
  }
  else
  switch( nValue )
  {
    case 0: 
		return "��";
    case 1: 
		return "Ҽ";
    case 2: 
		return "��";
    case 3: 
		return "��";
    case 4: 
		return "��";
    case 5: 
		return "��";
    case 6: 
		return "½";
    case 7: 
		return "��";
    case 8: 
		return "��";
    case 9: 
		return "��";
    default:
       return "E";
  };
};

CString ShowDigitalInt(DWORD Value, BYTE Digital)
{
  BYTE i;
  CString str;
  str.Format( "%d", Value );

  for ( i = 0; i < Digital; i++ )
    if ( Value < pow( 10.0, i ) )
    {
      if ( ( i == 0 )&&( Value == 0 ) )
        str = "0";
      else
        str = "0" + str;
    }

  return str;
}

CString ShowSystemTime( SYSTEMTIME TimeValue, UINT uType )
{
	CString strYear, strMonth, strDay,
		strHour, strMin, strSec,
		strDayOfWeek, strDate, strTime;

	if ( IsContain( uType, SSTM_CHN ) )
	{
		strYear = ChInt(TimeValue.wYear);
		strMonth = ChInt(TimeValue.wMonth);
		strDay = ChInt(TimeValue.wDay);
		strHour = ChInt(TimeValue.wHour);
		strMin = ChInt(TimeValue.wMinute);
		strSec = ChInt(TimeValue.wSecond);
		if (TimeValue.wDayOfWeek == 0)
		{
			strDayOfWeek = " ������";
		}
		else
		{
			strDayOfWeek = " ����"+ChInt(TimeValue.wDayOfWeek);
		}		
		strDate = strYear+"��"+strMonth+"��"+strDay+"�� ";
		strTime = strHour+"��"+strMin+"��"+strSec+"�� ";
	}
	else
	{
		if ( IsContain( uType, SSTM_SIMPLE ) )
		{
			strYear.Format("%d", TimeValue.wYear);
			strMonth = ShowDigitalInt(TimeValue.wMonth, 2);
			strDay = ShowDigitalInt(TimeValue.wDay, 2);
			strHour = ShowDigitalInt(TimeValue.wHour, 2);
			strMin = ShowDigitalInt(TimeValue.wMinute, 2);
			strSec = ShowDigitalInt(TimeValue.wSecond, 2);
			if (TimeValue.wDayOfWeek == 0)
			{
				strDayOfWeek = " ������";
			}
			else
			{
				strDayOfWeek = " ����"+ChInt(TimeValue.wDayOfWeek);
			}
		
			strDate = strYear+strMonth+strDay+"[";
			strTime = strHour+strMin+strSec+"]";
		}
		else
		{
			strYear.Format("%d", TimeValue.wYear);
			strMonth = ShowDigitalInt(TimeValue.wMonth, 2);
			strDay = ShowDigitalInt(TimeValue.wDay, 2);
			strHour = ShowDigitalInt(TimeValue.wHour, 2);
			strMin = ShowDigitalInt(TimeValue.wMinute, 2);
			strSec = ShowDigitalInt(TimeValue.wSecond, 2);
			if (TimeValue.wDayOfWeek == 0)
			{
				strDayOfWeek = " ������";
			}
			else
			{
				strDayOfWeek = " ����"+ChInt(TimeValue.wDayOfWeek);
			}
		
			strDate = strYear+"-"+strMonth+"-"+strDay+" ";
			strTime = strHour+":"+strMin+":"+strSec;
		}		
	}
	
	CString strResult = "";
	
	if ( IsContain( uType, SSTM_DATE ) )
		strResult +=  strDate;
	if ( IsContain( uType, SSTM_TIME ) )
		strResult += strTime;
	if ( IsContain( uType, SSTM_WEEK ) )
		strResult += strDayOfWeek;
	
	return strResult;

}

BOOL CreateMDir(CString strDir)
{
	char *p;
	int i;
	CString tmpstr;
	if ( PathFileExists(strDir) )
		return TRUE;
	
	p = (LPTSTR)(LPCTSTR)strDir;
	for ( i = 0; i<strDir.GetLength(); i++ )
	{
		tmpstr += *p;
		if ( *p == '\\' )
			if ( !(PathFileExists((LPCSTR)tmpstr)) )
				if ( !(CreateDirectory((LPCSTR)tmpstr, NULL)) )
					return FALSE;
				p += 1;
	}
	
	if ( !(PathFileExists((LPCSTR)tmpstr)) )
		if ( !(CreateDirectory((LPCSTR)tmpstr, NULL)) )
			return FALSE;
		
		if ( !(PathFileExists((LPCSTR)strDir)) )
			return FALSE;
		else
			return TRUE;
}

BOOL DeleteTree(CString strDir)
{
	WIN32_FIND_DATA _wfd;
	HANDLE h;
	CString strFileName;
	BOOL flag;
	flag = FALSE;
	
	CString strSafeDir = GetSafeFolder(strDir);
	//���Ŀ¼��������Ҹ�Ŀ¼�������ļ�
	if ( PathFileExists(strSafeDir) )
	{
		ZeroMemory(&_wfd, sizeof WIN32_FIND_DATA);
		strFileName = strSafeDir+"*.*";
		h = FindFirstFile((LPCSTR)strFileName, &_wfd);
		if ( h != INVALID_HANDLE_VALUE )
			flag = TRUE;
		
		//���Ŀ¼��û���ļ���ɾ����Ŀ¼���˳�
		do {
			if ( (!flag) )
			{
				if ( (GetLastError() == ERROR_NO_MORE_FILES) )
				{
					FindClose(h);
					RemoveDirectory((LPCSTR)strSafeDir);
					return TRUE;
					
				}
				else
				{
					FindClose(h);
					return FALSE;
					
				}
			}
			//����ҵ����ļ����ļ�����ɾ����ʧ���򷵻ش��󣬳ɹ������
			if ( !( IsContain( _wfd.dwFileAttributes, FILE_ATTRIBUTE_DIRECTORY ) ) )
			{
				if ( !(DeleteFile((LPCSTR)(strSafeDir+_wfd.cFileName))) )
				{  
					FindClose(h);
					return FALSE;
					
				}
			}
			//����ҵ�����Ŀ¼��ݹ�
			else
				if ( ((CString)_wfd.cFileName != ".")&&((CString)_wfd.cFileName != "..") )
				{
					if ( !(DeleteTree(strSafeDir+_wfd.cFileName)) )
					{
						FindClose(h);
						return FALSE;
						
					}
				}
				ZeroMemory(&_wfd, sizeof WIN32_FIND_DATA);
				flag = FindNextFile(h, &_wfd);
		}while(true);
	}
	//���Ŀ¼�����ڣ�Ҳ���سɹ�
	return TRUE;
}

BOOL GetFileSize(CString strFileName, __int64 *pfSize)  
{
	HANDLE h;
	WIN32_FIND_DATA _wfd;
	if ( !(PathFileExists(strFileName)) )
		return FALSE;
    
	ZeroMemory(&_wfd, sizeof WIN32_FIND_DATA);
	h = FindFirstFile((LPCSTR)strFileName, &_wfd);
	if ( h == INVALID_HANDLE_VALUE )
		return FALSE;
	
	*pfSize = _wfd.nFileSizeHigh;
	*pfSize <<= 32;
	*pfSize += _wfd.nFileSizeLow;
	FindClose(h);
	return TRUE;
}

CString ShowSpace(__int64 space)
{
	CString strSpace = "";
	if ( space < 1024 )
	{
		strSpace.Format("%d Byte", space);
		return strSpace;
	}
	else
		if ( space < 1048576 )
		{
			strSpace.Format("%2.2f KB", (float)(space/1024));
			return strSpace;
		}
		else
			if ( space<1073741824 )
			{
				strSpace.Format("%2.2f MB", (float)(space/(1024*1024)));
				return strSpace;
			}
			else
				if ( space<16979146571776 )
				{
					strSpace.Format("%2.2f GB", (float)(space/(1024*1024*1024)));
					return strSpace;
				}
				else
				{
					strSpace.Format("%2.2f TB", (float)(space/(1099511627776)));
					return strSpace;
				}	
}

BOOL RenameFile(HWND hWnd, CString strFrom, CString strTo)
{
	_SHFILEOPSTRUCTA fo;
	char caFrom[256], caTo[256];
	fo.hwnd = hWnd;
	fo.wFunc = FO_RENAME;
	
	ZeroMemory(caFrom, 256);
	ZeroMemory(caTo, 256);
	
	CString str = GetSafeFolder(strFrom, FALSE);
	strncpy(caFrom, str, 256);
	str = GetSafeFolder(strTo, FALSE);
	strncpy(caTo, str, 256);
	
	fo.pFrom = caFrom;
	fo.pTo = caTo;
	fo.fFlags = FOF_SILENT;
	fo.fAnyOperationsAborted = FALSE;
	fo.hNameMappings = NULL;
	fo.lpszProgressTitle = "Rename";
	if (SHFileOperation(&fo) == 0)
		return TRUE;
	else
		return FALSE;
}

BOOL IsContain( UINT uCode, const UINT uId )
{
	if ( ( uId & uCode ) == uId )
		return TRUE;
	else
		return FALSE;
}

BOOL IsEqual( UINT uCode, const UINT uId )
{
	if ( uCode == uId )
		return TRUE;
	else
		return FALSE;
}

void GuidToStr( GUID &guid, CString &str )
{
	CString strApp, strModule;
	GetGuidString( guid, str, strApp, strModule );
}

void GetGuidString( GUID& guid, CString& strAll, CString& strApp, CString& strModule )
{
	strAll.Empty();
	strApp.Empty();
	strModule.Empty();
	
	CString str;
	str.Format( "%X" , guid.Data1 );

	while( str.GetLength() < 8 )
	{
		str = "0" + str;
	}

	strAll = str + "-";
	str.MakeLower();
	strApp = "0x" + str + ", ";
	
	str.Format( "%X" , guid.Data2 );
	while( str.GetLength() < 4 )
	{
		str = "0" + str;
	}

	strAll = strAll + str + "-";
	str.MakeLower();
	strApp += "0x" + str + ", ";

	str.Format( "%X" , guid.Data3 );
	while( str.GetLength() < 4 )
	{
		str = "0" + str;
	}
	
	strAll = strAll + str + "-";
	str.MakeLower();
	strApp += "0x" + str + ", ";

	CString strTemp;
	strTemp.Empty();

	for( int i = 0 ; i < 8 ; i ++ )
	{
		str.Format( "%X" , guid.Data4[i] );

		while( str.GetLength() < 2 )
		{
			str = "0" + str;
		}

		strAll = strAll + str;
		str.MakeLower();

		strTemp = strTemp + "0x" + str;

		if( 7 != i )
		{
			strTemp += ", ";
		}

		if( 1 == i )
		{
			strAll += "-";
		}
	}

	strModule = strApp;
	strApp += "{ ";
	strApp += strTemp;
	strApp += " }";

	strModule += strTemp;

	strAll = "{" + strAll + "}";
}

void SelectSort( int *pnSrc, int nCount, BOOL bSmallFirst )
{
//	void SelectionSort(T arr[],int n) 
	//������СԪ�ص��±� 
	int smallIndex;   
	//����ɨ���ӱ���±� 
	int pass, j;       

	int temp = 0;

	//pass�ķ�Χ��0~n-2 
	for ( pass = 0; pass < nCount - 1; pass++ ) 
	{ 
	//���±�pass��ʼɨ���ӱ� 
		smallIndex = pass; 

	//j���������ӱ�arr[pass+1]��arr[n-1] 
		for ( j = pass + 1; j < nCount; j++ ) 
		{
			if ( bSmallFirst )
			{
				if ( pnSrc[j] < pnSrc[smallIndex] ) 
					smallIndex = j; 
			}
			else
			{
				if ( pnSrc[j] > pnSrc[smallIndex] ) 
					smallIndex = j; 
			}
		}
		//����ҵ���С��Ԫ��,�򽫸�λ�ø�ֵ��smallIndex 

	//���smallIndex��pass������ͬ��λ�� 
	//���ӱ��е���С����arr[pass]���� 

		if ( smallIndex != pass )
		{ 
			temp = pnSrc[pass]; 
			pnSrc[pass] = pnSrc[smallIndex]; 
			pnSrc[smallIndex] = temp; 
		} 
	}
}

int DichotomyFind( int *pnSrc, int nCount, int nValue )
{
	if ( ( !pnSrc )||( nCount <= 0 ) )
		return -1;

	int nMin = 0;
	int nMax = nCount;
	int nIndex = ( nMax - nMin ) / 2;

	if ( pnSrc[nMin] == nValue )
		return nMin;

	if ( pnSrc[nMax - 1] == nValue )
		return nMax - 1;

	do {
		if ( pnSrc[ nIndex ] == nValue )
			return nIndex;
		else
			if ( pnSrc[nIndex] < nValue )
			{
				nMin = nIndex;
			}
			else
			{
				nMax = nIndex;
			}

		nIndex = nMin + ( nMax - nMin ) / 2;

	}while( ( nIndex < nCount - 1 )&&( nMin != nMax ) );

	return -1;

}

void ClipBoard( RECT &rt, int &nDstX, int &nDstY, int &nWidth, int &nHeight, int &nSrcX, int &nSrcY )
{
	CRect rtBoard = rt;
	if ( ( rtBoard.left )||( rtBoard.top )||( rtBoard.right )||( rtBoard.bottom ) )
	{
		if ( nDstX < rtBoard.left )
		{
			nSrcX += ( rtBoard.left - nDstX );
			nWidth -= ( rtBoard.left - nDstX );
			nDstX = rtBoard.left;
		}
		if ( nDstY < rtBoard.top )
		{
			nSrcY += ( rtBoard.top - nDstY );
			nHeight -= ( rtBoard.top - nDstY );
			nDstY = rtBoard.top;
		}
		if ( nDstX + nWidth > rtBoard.right )
		{
			nWidth = rtBoard.right - nDstX;
		}
		if ( nDstY + nHeight > rtBoard.bottom )
		{
			nHeight = rtBoard.bottom - nDstY;
		}
		nHeight = max( 0, nHeight );
		nWidth = max( 0, nWidth );
		nSrcX = max( 0, nSrcX );
		nSrcY = max( 0, nSrcY );
	}
}

__int64 g_nRandSeed = 0;
void Randomize(__int64 nSeed)
{
	g_nRandSeed = nSeed;
}

unsigned long Random(long max)
{
	__int64 x ;
	double i ;
	unsigned long final ;
	x = 0xffffffff;
	x += 1 ;
	g_nRandSeed *= ((__int64)134775813);
	g_nRandSeed += 1 ;
	g_nRandSeed = g_nRandSeed % x ;
	i = ((double)g_nRandSeed) / (double)0xffffffff ;
	final = (long) (max * i) ;
	
	return (unsigned long)final;
}

unsigned long RandomEx(__int64 &nSeed, long max)
{
	__int64 x ;
	double i ;
	unsigned long final ;
	x = 0xffffffff;
	x += 1 ;
	nSeed *= ((__int64)134775813);
	nSeed += 1 ;
	nSeed = nSeed % x ;
	i = ((double)nSeed) / (double)0xffffffff ;
	final = (long) (max * i) ;
	return (unsigned long)final;
}

int FindFirstBracket(CString str, CString &strDst, CString &strRest, BRACKETTYPE type /* = BT_SMALL */)
{
	CString strSrc = str;
	strDst = "";
	int nIndex = 0;
	BOOL bFind = FALSE; 
	int nBlacket = 0;
	int nResult = 0;
	char cLeft, cRight;
	switch(type) {
	case BT_SMALL:
		cLeft = '(';
		cRight = ')';
		break;
	case BT_MID:
		cLeft = '[';
		cRight = ']';
		break;
	case BT_BIG:
		cLeft = '{';
		cRight = '}';
	}
	while((nIndex < strSrc.GetLength())&&
		  ((!bFind)||(nBlacket)))
	{
		if ((!bFind)&&(strSrc[nIndex] == cLeft))
		{
			bFind = TRUE;
			nBlacket++;
		}
		else
		{
			if (strSrc[nIndex] == cLeft)
			{
				nBlacket++;
			}
			else
				if ((bFind)&&(strSrc[nIndex] == cRight))
				{
					nBlacket--;
				}
			if ((bFind)&&(!nBlacket))
			{
				nResult++;
				if (nIndex < strSrc.GetLength())
				{
					strRest = strSrc.Right(strSrc.GetLength() - nIndex - 1);
					nResult++;
				}
				strRest.TrimLeft();
				strRest.TrimRight();
				strDst.TrimLeft();
				strDst.TrimRight();
			}
			else
			{
				if (bFind)
				{
					strDst += strSrc[nIndex];
				}
			}
		}
		nIndex++;
	}
	return nResult;
}

int FindFirstComma(CString str, CString &strDst, CString &strRest)
{
	CString strSrc = str;
	int nIndex = 0;
	BOOL bFind = FALSE;
	int nResult = 0;
	strDst = "";
	while((nIndex < strSrc.GetLength())&&(!bFind))
	{
		if (strSrc[nIndex] == ',')
		{
			bFind = TRUE;
			nResult++;
			if (nIndex < strSrc.GetLength())
			{
				strRest = strSrc.Right(strSrc.GetLength() - nIndex - 1);
				nResult++;
				strRest.TrimLeft();
				strRest.TrimRight();
				strDst.TrimLeft();
				strDst.TrimRight();
			}
		}
		else
		{
			strDst += strSrc[nIndex];
		}
		nIndex++;
	}
	return nResult;
}

int FindFirstBlank(CString str, CString &strDst, CString &strRest)
{
	CString strSrc = str;
	strSrc.TrimLeft();
	strSrc.TrimRight();
	int nIndex = 0;
	BOOL bFind = FALSE;
	int nResult = 0;
	strDst = "";
	while((nIndex < strSrc.GetLength())&&(!bFind))
	{
		if ((strSrc[nIndex] == ' ')||(strSrc[nIndex] == VK_TAB))
		{
			bFind = TRUE;
			nResult++;
			if (nIndex < strSrc.GetLength())
			{
				strRest = strSrc.Right(strSrc.GetLength() - nIndex - 1);
				strRest.TrimLeft();
				strRest.TrimRight();
				strDst.TrimLeft();
				strDst.TrimRight();
				nResult++;
			}
		}
		else
		{
			strDst += strSrc[nIndex];
		}
		nIndex++;
	}
	return nResult;
}

int StringBeforeBracket(CString str, CString &strDst, CString &strRest, BRACKETTYPE type /* = BT_SMALL */)
{
	CString strSrc = str;
	int nIndex = 0;
	BOOL bEnd = FALSE;
	int nResult = 0;
	strDst = "";
	char cLeft, cRight;
	switch(type) {
	case BT_SMALL:
		cLeft = '(';
		cRight = ')';
		break;
	case BT_MID:
		cLeft = '[';
		cRight = ']';
		break;
	case BT_BIG:
		cLeft = '{';
		cRight = '}';
	}
	while((nIndex < strSrc.GetLength())&&(!bEnd))
	{
		if (strSrc[nIndex] == cLeft)
		{
			nResult++;
			bEnd = TRUE;
			if (nIndex < strSrc.GetLength())
			{
				strRest = strSrc.Right(strSrc.GetLength() - nIndex);
			}
			strRest.TrimLeft();
			strRest.TrimRight();
			strDst.TrimLeft();
			strDst.TrimRight();
		}
		else
		{
			strDst += strSrc[nIndex];
		}
		nIndex++;
	}
	return nResult;
}

BOOL FindBracket(CString str, int nIndex, CString &strDst, BRACKETTYPE type /* = BT_SMALL */)
{
	CString strTmp;
	if (nIndex < 0)
	{
		if (StringBeforeBracket(str, strDst, strTmp, type))
			return TRUE;
		else
			return FALSE;
	}
	else
	{
		strTmp = str;
		for (int i = 0; i < nIndex + 1; i++)
		{
			if (!FindFirstBracket(strTmp, strDst, strTmp, type))
				return FALSE;
		}
		return TRUE;
	}
}

BOOL FindBracketContain(CString str, int nIndex, CString &strDst, BRACKETTYPE type /* = BT_SMALL */)
{
	CString strTmp;
	if (nIndex < 0)
	{
		if (StringBeforeBracket(str, strDst, strTmp, type))
			return TRUE;
		else
			return FALSE;
	}
	else
	{
		strTmp = str;
		for (int i = 0; i < nIndex + 1; i++)
		{
			if (!FindFirstBracket(strTmp, strDst, strTmp, type))
				return FALSE;
			strTmp = strDst;
		}
		return TRUE;
	}
}

BOOL FindComma(CString str, int nIndex, CString &strDst)
{
	BOOL bFind = FALSE;
	CString strTmp2;
	CString strTmp;
	if (nIndex < 0)
	{
		return FALSE;
	}
	else
	{
		strTmp = str;
		for (int i = 0; i < nIndex + 1; i++)
		{
			if (!FindFirstComma(strTmp, strDst, strTmp))
			{
				if (((bFind)&&(i == nIndex))||(!nIndex))
				{
					if (!nIndex)
						strDst = strTmp;
					else
						strDst = strTmp2;
					return TRUE;
				}
				else
					return FALSE;
			}
			else
			{
				strTmp2 = strTmp;
				bFind = TRUE;
			}
		}
		return TRUE;
	}
}

BOOL FindBlank(CString str, int nIndex, CString &strDst)
{
	BOOL bFind = FALSE;
	CString strTmp2;
	CString strTmp;
	if (nIndex < 0)
	{
		return FALSE;
	}
	else
	{
		strTmp = str;
		for (int i = 0; i < nIndex + 1; i++)
		{
			if (!FindFirstBlank(strTmp, strDst, strTmp))
			{
				if (((bFind)&&(i == nIndex))||(!nIndex))
				{
					if (!nIndex)
						strDst = strTmp;
					else
						strDst = strTmp2;
					return TRUE;
				}
				else
					return FALSE;
			}
			else
			{
				bFind = TRUE;
				strTmp2 = strTmp;
			}
		}
		return TRUE;
	}
}

int FindCommaCount(CString str)
{
	int nCount = 0;
	int nIndex = 0;
	CString strSrc = str;
	while(nIndex < strSrc.GetLength())
	{
		if (strSrc[nIndex] == ',')
		{
			nCount++;
		}
		nIndex++;
	}
	return nCount;
}

BOOL GetStrNum(CString &str, DWORD *pdw)
{
	int nVal = 0;
	if (GetStrNum(str, &nVal))
	{
		if (pdw)
		{
			*pdw = (DWORD)nVal;
		}
		return TRUE;
	}
	else
		return FALSE;
}

BOOL GetStrNum64(CString &str, __int64 *pInt64)
{
	str.TrimLeft();
	str.TrimRight();
	if (str == "")
	{
		if (pInt64)
			*pInt64 = 0;
		return TRUE;
	}
	
	str.MakeUpper();
	int nIndex = 0;
	BOOL bHex = FALSE;
	BOOL bNeg = FALSE;
	BOOL bNum = TRUE;
	int nNumLength = str.GetLength();
	__int64 nResult = 0;
	if ((str.GetLength() > 2)&&(str[0] == '0')&&(str[1] == 'X'))
	{
		nIndex = 2;
		nNumLength -= 2;
		bHex = TRUE;
	}
	else
	{
		if ((str.GetLength() > 1)&&(str[0] == '-'))
		{
			nIndex = 1;
			nNumLength--;
			bNeg = TRUE;
		}
	}
	for (int i = 0; i < nNumLength; i++)
	{
		char chr = str[i + nIndex];
		if ((chr >= '0')&&(chr <= '9'))
		{
			if (bHex)
				nResult += (chr - '0') * (__int64)pow(16.0, nNumLength - i - 1);
			else
				nResult += (chr - '0') * (__int64)pow(10.0, nNumLength - i - 1);
		}
		else
		{
			if ((bHex)&&(chr >= 'A')&&(chr <= 'F'))
			{
				nResult += (chr - 'A' + 10) * (__int64)pow(16.0, nNumLength - i - 1);
			}
			else
			{
				bNum = FALSE;
				break;
			}
		}
	}
	if (bNum)
	{
		if (bNeg)
		{
			nResult = -nResult;
		}
		if (pInt64)
		{
			*pInt64 = nResult;
		}
	}
	return bNum;
}

BOOL GetStrNum(CString &str, int *pInt)
{
	str.TrimLeft();
	str.TrimRight();
	if (str == "")
	{
		if (pInt)
			*pInt = 0;
		return TRUE;
	}

	str.MakeUpper();
	int nIndex = 0;
	BOOL bHex = FALSE;
	BOOL bNeg = FALSE;
	BOOL bNum = TRUE;
	int nNumLength = str.GetLength();
	int nResult = 0;
	if ((str.GetLength() > 2)&&(str[0] == '0')&&(str[1] == 'X'))
	{
		nIndex = 2;
		nNumLength -= 2;
		bHex = TRUE;
	}
	else
	{
		if ((str.GetLength() > 1)&&(str[0] == '-'))
		{
			nIndex = 1;
			nNumLength--;
			bNeg = TRUE;
		}
	}
	for (int i = 0; i < nNumLength; i++)
	{
		char chr = str[i + nIndex];
		if ((chr >= '0')&&(chr <= '9'))
		{
			if (bHex)
				nResult += (chr - '0') * (int)pow(16.0, nNumLength - i - 1);
			else
				nResult += (chr - '0') * (int)pow(10.0, nNumLength - i - 1);
		}
		else
		{
			if ((bHex)&&(chr >= 'A')&&(chr <= 'F'))
			{
				nResult += (chr - 'A' + 10) * (int)pow(16.0, nNumLength - i - 1);
			}
			else
			{
				bNum = FALSE;
				break;
			}
		}
	}
	if (bNum)
	{
		if (bNeg)
		{
			nResult = -nResult;
		}
		if (pInt)
		{
			*pInt = nResult;
		}
	}
	return bNum;
}

BOOL GetSafeStrPart(LPCSTR lpsz, int nPart1Count, CString &str1, CString &str2)
{
	if (!lpsz)
		return FALSE;

	CString str = lpsz;

	if (!nPart1Count)
	{
		str1 = "";
		str2 = str;
		return TRUE;
	}
	
	//���ֽ��ַ���ת��˫�ֽ��ַ���
	int nWideCharLen = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str, str.GetLength(), NULL, 0);	
	if (nPart1Count >= nWideCharLen)
	{
		str1 = str;
		str2 = "";
		return TRUE;
	}

	WCHAR *pwsz = new WCHAR[nWideCharLen + 1];
	ZeroMemory(pwsz, sizeof(WCHAR) * (nWideCharLen + 1));	
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str, str.GetLength(), pwsz, nWideCharLen);
	
	//������һ��
	PWCHAR pwszPart1 = new WCHAR[nPart1Count + 1];
	ZeroMemory(pwszPart1, (nPart1Count + 1) * sizeof(WCHAR));
	wcsncpy(pwszPart1, pwsz, nPart1Count);
	//�����ڶ���
	int nPart2Count = str.GetLength() - nPart1Count;
	PWCHAR pwszPart2 = new WCHAR[nPart2Count + 1];
	ZeroMemory(pwszPart2, (nPart2Count + 1) * sizeof(WCHAR));
	wcsncpy(pwszPart2, pwsz + nPart1Count, nPart2Count);
	
	//��һ��˫�ֽ��ַ���ת�ص��ֽ��ַ���
	int nStrPart1Count = WideCharToMultiByte(CP_ACP, 0, pwszPart1, nPart1Count, NULL, 0, NULL, NULL);
	PCHAR pszPart1 = new CHAR[nStrPart1Count + 1];
	ZeroMemory(pszPart1, nStrPart1Count + 1);
	WideCharToMultiByte(CP_ACP, 0, pwszPart1, nPart1Count, pszPart1, nStrPart1Count, NULL, NULL);
	//�ڶ���˫�ֽ��ַ���ת�ص��ֽ��ַ���
	int nStrPart2Count = WideCharToMultiByte(CP_ACP, 0, pwszPart2, nPart2Count, NULL, 0, NULL, NULL);
	PCHAR pszPart2 = new CHAR[nStrPart2Count + 1];
	ZeroMemory(pszPart2, nStrPart2Count + 1);
	WideCharToMultiByte(CP_ACP, 0, pwszPart2, nPart2Count, pszPart2, nStrPart2Count, NULL, NULL);
	
	//����
	str1 = pszPart1;
	str2 = pszPart2;

	//ɾ����ʱ����
	delete []pwsz;
	delete []pwszPart1;
	delete []pwszPart2;
	delete []pszPart1;
	delete []pszPart2;

	return TRUE;
}

BOOL GetSafeStrPartInCharCount(LPCSTR lpsz, int nPart1Count, CString &str1, CString &str2)
{
	if (!lpsz)
		return FALSE;
	
	CString str = lpsz;
	
	if (nPart1Count >= str.GetLength())
	{
		str1 = str;
		str2 = "";
		return TRUE;
	}
	
	if (nPart1Count == 0)
	{
		str1 = "";
		str2 = str;
		return TRUE;
	}

	int nRealPart1Count = 0;
	BOOL bWCHAR = FALSE;
	for (int i = 0; i < nPart1Count; i++)
	{	
		if (!bWCHAR)
		{
			char c = str[i];
			if ((BYTE)str[i] <= (BYTE)0xA0)
			{
				nRealPart1Count++;
				bWCHAR = FALSE;
			}
			else
			{
				bWCHAR = TRUE;
			}
		}
		else
		{
			nRealPart1Count++;
			bWCHAR = FALSE;
		}		
	}

	GetSafeStrPart(str, nRealPart1Count, str1, str2);

	return TRUE;
}

CString CutString(LPCSTR lpsz, int nCount, BOOL bByCharCount)
{
	CString strResult, strTemp;
	if (bByCharCount)
	{
		GetSafeStrPartInCharCount(lpsz, nCount, strResult, strTemp);
		if (strTemp.GetLength() > 0)
		{
			GetSafeStrPartInCharCount(lpsz, nCount - 2, strResult, strTemp);
			strResult += "..";
		}
	}
	else
	{
		GetSafeStrPart(lpsz, nCount, strResult, strTemp);
		if (strTemp.GetLength() > 0)
		{
			GetSafeStrPart(lpsz, nCount - 2, strResult, strTemp);
			strResult += "..";
		}
	}
	return strResult;
}

CString AutoIncStrNum(CString &str)
{
	CString strNum = "";
	CString strResult = "";

	int n = -1;
	int nIndex = -1;
	for (int i = str.GetLength() - 1; i >= 0; i--)
	{
		CString strN;
		strN.Format("%c",str[i]);				
		if (GetStrNum(strN, &n))
		{
			CString strTemp = strNum;
			strNum.Format("%d%s", n, strTemp);
		}
		else
		{
			if (i == str.GetLength())
			{
				strNum = "";						
			}
			nIndex = i;
			break;
		}			
	}
	if (!GetStrNum(strNum, &n))
	{
		n = 0;
	}
	else
	{
		n++;
	}

	strResult.Format("%s%d", str.Left(nIndex + 1), n);

	return strResult;
}

void LinkFile(HINSTANCE hInstance, LPCSTR lpszFileExt, int nIconIndex)
{
	CString str = lpszFileExt;
	LinkFileEx(hInstance, &str, 1, nIconIndex);
}

void LinkFileEx(HINSTANCE hInstance, CString *lpstrExt, int nExtCount, int nIconIndex)
{
	CString strAppFolder = GetModuleFolder(hInstance);
	CString strLinkFileModuleName;
	strLinkFileModuleName.Format("%s%s", strAppFolder, LINKFILE_MODULE_FILENAME);
	HMODULE hLinkFile = ::LoadLibrary(strLinkFileModuleName);
	typedef BOOL(__stdcall *LINKFILETOAPP)(LPCSTR lpszFileName, LPCSTR lpszAppName, LPCSTR lpszIcon, LPCSTR lpszParams);
	LINKFILETOAPP LinkFileToApp;
	LinkFileToApp = (LINKFILETOAPP)::GetProcAddress(hLinkFile, LINKFILE_PROC_NAME);
	if (LinkFileToApp)
	{
		CString strApp = GetModulePath(hInstance);
		for (int i = 0; i < nExtCount; i++)
		{
			CString strIconIndex;
			strIconIndex.Format(",%d", nIconIndex);
			LinkFileToApp(lpstrExt[i], strApp, strApp + strIconIndex, "-load");	
		}
	}
	::FreeLibrary(hLinkFile);
}

BOOL LinkFileGetOpenFileName(LPSTR lpCmdLine, CString &str)
{
	ASSERT( lpCmdLine != NULL );
	
	// If TRUE, don't loop.
	BOOL bOpen = FALSE ;
	
	// Read the command line.
	char szTokens[] = "-/" ;
	
	char* szToken = strtok( lpCmdLine , szTokens );
	
	CString strToken;
	CString strOld;
	
	while( szToken != NULL )
	{
		strToken.Format( "%s" , szToken );
		
		str = strOld;
		strOld = strToken;
		strOld.Replace("\"", "");
		
		if( 0 == strToken.CompareNoCase( "load" )  )
			bOpen = TRUE;
		
		szToken = strtok( NULL , szTokens );
	}
	
	return bOpen;
}

float GetAngle(POINT &pntSrc, POINT &pntDst)
{
	//////////////////////////////////////////////////////////////////////////
	//
	//	����Ƕ�
	//
	float fAngle = 0;
	
	double dRadin = atan2((double)(pntDst.y - pntSrc.y), (pntDst.x - pntSrc.x));		
	fAngle = (float)((dRadin * 180) / PI);
	
	if (fAngle < 0)
	{
		fAngle = 360 + fAngle;
	}
	if (fAngle >= 360)
	{
		fAngle = fAngle - 360;
	}
	
	return fAngle;
	//
	//////////////////////////////////////////////////////////////////////////
}

CString GetMoneyStr(__int64 nMoney)
{
	CString str = "";
	CString str1;
	//int nAbsMoney = abs(nMoney);

	__int64 nAbsMoney = nMoney;

	if (nMoney < 0)
		nAbsMoney = -nMoney;
				
	while (nAbsMoney >= NUMBER_BASE_1WAN)
	{
		str1.Format(",%04d", nAbsMoney % NUMBER_BASE_1WAN);
		str = str1 + str;
		nAbsMoney = nAbsMoney / NUMBER_BASE_1WAN;
	}
	
	str1.Format("%d", nAbsMoney);
	str = str1 + str;

	if (nMoney < 0)
		str = "-" + str;

	return str;
}

__int64 GetNowFileTime()
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	FILETIME ft;
	SystemTimeToFileTime(&st, &ft);
	__int64 nTime = (((__int64)ft.dwHighDateTime << 32) | ((__int64)ft.dwLowDateTime));
	return nTime;
}

RECT GetWorkArea()
{
	RECT rtWorkArea;
	memset(&rtWorkArea, 0, sizeof(rtWorkArea));
	SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID) &rtWorkArea, 0);
	return rtWorkArea;
}

RECT GetWindowRealRect(HWND hWnd)
{
	//-------------------------------------------------------------
	//	��ȡ��������
	/*
	WINDOWPLACEMENT wp;
	ZeroMemory(&wp, sizeof(wp));
	wp.length = sizeof(WINDOWPLACEMENT);

	GetWindowPlacement(hWnd, &wp);

	RECT rtWnd = wp.rcNormalPosition;
	return rtWnd;*/
	//-------------------------------------------------------------

	RECT rt;
	memset(&rt, 0, sizeof(rt));

	if (hWnd)
	{
		if (!IsIconic(hWnd))
		{
			GetWindowRect(hWnd, &rt);	//	��ȡ�����������Ļ���Ͻǵ�λ��
		}
		else
		{
			//-------------------------------------------------------------
			//	��ȡ��������ڹ������������������������Ͻǵ�λ��
			WINDOWPLACEMENT wp;
			ZeroMemory(&wp, sizeof(wp));
			wp.length = sizeof(WINDOWPLACEMENT);			
			GetWindowPlacement(hWnd, &wp);
			rt = wp.rcNormalPosition;
			//-------------------------------------------------------------

			//-------------------------------------------------------------
			//	�����������ڲ�ͬ��λ���������ƫ��
			RECT rtWorkArea = GetWorkArea();

			if (rtWorkArea.top != 0)
			{
				rt.top += rtWorkArea.top;
				rt.bottom += rtWorkArea.top;
			}

			if (rtWorkArea.left != 0)
			{
				rt.left += rtWorkArea.left;
				rt.right += rtWorkArea.left;
			}
			//-------------------------------------------------------------
		}
	}

	return rt;
}

DWORD GetConfigStr(LPCSTR lpszCfgFile, LPCSTR lpszSect, LPCSTR lpszID, CString &strValue)
{
	//-------------------------------------------------------------
	char szInfo[MAX_PATH + 1];
	ZeroMemory(szInfo, sizeof(szInfo));
	DWORD dwResult = GetPrivateProfileString(lpszSect, lpszID, strValue, szInfo, MAX_PATH, lpszCfgFile);
	if (dwResult)
	{
		strValue = szInfo;
	}
	return dwResult;
	//-------------------------------------------------------------
}

int GetConfigInt(LPCSTR lpszCfgFile, LPCSTR lpszSect, LPCSTR lpszID, int nDefaultValue)
{
	char szInfo[MAX_PATH + 1];
	ZeroMemory(szInfo, sizeof(szInfo));
	
	CString strDefault;
	strDefault.Format("0x%x", nDefaultValue);
	GetPrivateProfileString(lpszSect, lpszID, strDefault, szInfo, MAX_PATH, lpszCfgFile);
	strDefault = szInfo;
	
	int nNewValue = 0;
	if (GetStrNum(strDefault, &nNewValue))
	{
		return nNewValue;
	}
	
	return nDefaultValue;
}

DWORD GetConfigDW(LPCSTR lpszCfgFile, LPCSTR lpszSect, LPCSTR lpszID, DWORD dwDefaultValue)
{
	char szInfo[MAX_PATH + 1];
	ZeroMemory(szInfo, sizeof(szInfo));
	
	CString strDefault;
	strDefault.Format("0x%x", dwDefaultValue);
	GetPrivateProfileString(lpszSect, lpszID, strDefault, szInfo, MAX_PATH, lpszCfgFile);
	strDefault = szInfo;
	
	DWORD dwNewValue = 0;
	if (GetStrNum(strDefault, &dwNewValue))
	{
		return dwNewValue;
	}
	
	return dwDefaultValue;
}

BOOL SetConfigStr(LPCSTR lpszCfgFile, LPCSTR lpszSect, LPCSTR lpszID, CString strValue)
{
	return WritePrivateProfileString(lpszSect, lpszID, strValue, lpszCfgFile);
}

BOOL SetConfigInt(LPCSTR lpszCfgFile, LPCSTR lpszSect, LPCSTR lpszID, int nValue, BOOL bHex)
{
	CString str;
	if (bHex)
	{
		str.Format("0x%x", nValue);
	}
	else
	{
		str.Format("%d", nValue);
	}
	return SetConfigStr(lpszCfgFile, lpszSect, lpszID, str);
}

BOOL SetConfigDW(LPCSTR lpszCfgFile, LPCSTR lpszSect, LPCSTR lpszID, DWORD dwValue, BOOL bHex)
{
	CString str;
	if (bHex)
	{
		str.Format("0x%x", dwValue);
	}
	else
	{
		str.Format("%u", dwValue);
	}
	return SetConfigStr(lpszCfgFile, lpszSect, lpszID, str);
}

void CompareStr(LPCSTR lpsz1, LPCSTR lpsz2, BOOL bReverse, int &nResult)
{
	if (!nResult)
	{
		nResult = strcmp(lpsz1, lpsz2);
		if (bReverse)
		{
			nResult = -nResult;
		}
	}
}

#define _COMPARE_INT(a, b, bReverse, nResult)\
{\
	if (!nResult)\
	{\
		if (a > b)\
		{\
			nResult = 1;\
		}\
		if (a < b)\
		{\
			nResult = -1;\
		}\
		if (bReverse)\
		{\
			nResult = -nResult;\
		}\
	}\
}
void CompareInt(int n1, int n2, BOOL bReverse, int &nResult)
{
	_COMPARE_INT(n1, n2, bReverse, nResult);
}

void CompareDWORD(DWORD dw1, DWORD dw2, BOOL bReverse, int &nResult)
{
	_COMPARE_INT(dw1, dw2, bReverse, nResult);
}

void CompareInt64(__int64 n641, __int64 n642, BOOL bReverse, int &nResult)
{
	_COMPARE_INT(n641, n642, bReverse, nResult);
}

void CompareBOOL(BOOL b1, BOOL b2, BOOL bReverse, int &nResult)
{
	if (!nResult)
	{
		int nTemp1, nTemp2;
		if (b1)
			nTemp1 = 1;
		else
			nTemp1 = 0;
		if (b2)
			nTemp2 = 1;
		else
			nTemp2 = 0;
		_COMPARE_INT(nTemp1, nTemp2, bReverse, nResult);
	}
}

BOOL ValidMutexName(LPCSTR lpszMutex)
{
	CString strCommonMutex = MUTEX_COMMON;
	CString strMutexName = lpszMutex;
	CString strTemp = strMutexName.Left(strCommonMutex.GetLength());
	
	//-------------------------------------------------------------
	//	ǰ�벿������ͨ�û��������
	if (!strcmp(strTemp, strCommonMutex))
	{
		strTemp = "0x" + strMutexName.Right(strMutexName.GetLength() - strCommonMutex.GetLength());
		int nCode = 0;

		if (GetStrNum(strTemp, &nCode))
		{
			//-------------------------------------------------------------
			//	��벿����Ϊ���֣��ұ���ָ����Χ�����ӵ����ֵ
			for (int i = 1; i < MAX_MUTEXCOUNT + 1; i++)
			{
				__int64 nSeed64 = i;

				if (nCode == (int)RandomEx(nSeed64, 0x7FFFFFFF))
				{
					return TRUE;
				}
			}
			//-------------------------------------------------------------
		}
	}
	//-------------------------------------------------------------
	
	return FALSE;
}

MUTEXCHECKRESULT MutexCheck(HINSTANCE hInstance, HANDLE &hMutex, CString *pStrMutexName)
{
	MUTEXCHECKRESULT Result = MTCR_OK;

	//-------------------------------------------------------------
	//	��ȡ��������
	CString strMutex = DEFAULT_MUTEX;
	GetConfigStr(GetModuleFolder(hInstance) + MUTEX_FILENAME, CFG_SECT_MUTEX, CFG_MUTEX_ID_NAME, strMutex);
	//-------------------------------------------------------------

	if (pStrMutexName)
	{
		*pStrMutexName = strMutex;
	}
	
	//-------------------------------------------------------------
	//	�жϻ������Ƿ�Ϸ�
	if (ValidMutexName(strMutex))
	{
		//-------------------------------------------------------------
		//	����������
		hMutex = CreateMutex(NULL, TRUE, strMutex);
		
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			CloseHandle(hMutex);
			hMutex = 0;
			Result = MTCR_ALREADY;
		}
		else if (!hMutex)
		{
			Result = MTCR_ALREADY;
		}
		//-------------------------------------------------------------
	}
	//-------------------------------------------------------------
	
	//-------------------------------------------------------------
	//	������Ϸ������������
	else
	{
		Result = MTCR_ILLEGAL;
	}
	//-------------------------------------------------------------

	return Result;
}

HWND FindMutexWnd(LPCSTR lpszMutexName)
{
	CWnd *pPrevWnd = CWnd::GetDesktopWindow()->GetWindow(GW_CHILD);
	while(pPrevWnd)
	{
		if(::GetProp(pPrevWnd->GetSafeHwnd(), lpszMutexName))
		{
			return pPrevWnd->GetSafeHwnd();
			break;
		}
		
		// ��ȡ��һ������
		pPrevWnd = pPrevWnd->GetWindow(GW_HWNDNEXT);
	}
	return 0;
}

void SetMutexWnd(HWND hWnd, LPCSTR lpszMutexName)
{
	::SetProp(hWnd, lpszMutexName, (HANDLE)1);
}

CString MakeMutexName(int nSeed)
{
	CString str;
	__int64 nSeed64 = nSeed;
	str.Format("%s%x", MUTEX_COMMON, RandomEx(nSeed64, 0x7FFFFFFF));
	return str;
}

BOOL CopyToClipboard(CString &strData)
{
	int len = strData.GetLength();
	if(len < 1)
		return false;
	BOOL res  = false;
	if(OpenClipboard(NULL) == false)
		return false;
	if(EmptyClipboard() == false)
		return false;
	HGLOBAL simpleData  =  GlobalAlloc(GPTR,len+1);  
	LPBYTE  lpSmpData   =  (LPBYTE)GlobalLock(simpleData);  
	memcpy(lpSmpData,strData.GetBuffer(0),len+1);  
	
	SetClipboardData(CF_TEXT,(void*)lpSmpData);
	res = CloseClipboard();
	GlobalUnlock(simpleData);
	return res;
} 

void GetTileInfo(const CRect &rtDst, const CRect &rtSrc, const CRect &rtSrcTile, CRect *pDstRects, CRect *pSrcRects)
{
	int nWidth = rtDst.Width() - (rtSrcTile.left + (rtSrc.Width() - rtSrcTile.right));
	int nHeight = rtDst.Height() - (rtSrcTile.top + (rtSrc.Height() - rtSrcTile.bottom));
	CRect rtLayer = rtSrc;
	CRect rtTile = rtSrcTile;
	//-------------------------------------------------------------
	for (int H = 0; H < 3; H++)
	{
		for (int W = 0; W < 3; W++)
		{
			switch(H) {
			case 0:
				pSrcRects[H * 3 + W].top = 0;
				pSrcRects[H * 3 + W].bottom = rtTile.top;
				pDstRects[H * 3 + W].top = 0;
				pDstRects[H * 3 + W].bottom = rtTile.top;
				break;
			case 1:
				pSrcRects[H * 3 + W].top = rtTile.top;
				pSrcRects[H * 3 + W].bottom = rtTile.bottom;
				pDstRects[H * 3 + W].top = rtTile.top;
				pDstRects[H * 3 + W].bottom = pDstRects[H * 3 + W].top + nHeight;
				break;
			case 2:
				pSrcRects[H * 3 + W].top = rtTile.bottom;
				pSrcRects[H * 3 + W].bottom = rtLayer.bottom;
				pDstRects[H * 3 + W].top = rtTile.top + nHeight;
				pDstRects[H * 3 + W].bottom = pDstRects[H * 3 + W].top + pSrcRects[H * 3 + W].Height();
				break;
			}
			switch(W){
			case 0:
				pSrcRects[H * 3 + W].left = 0;
				pSrcRects[H * 3 + W].right = rtTile.left;
				pDstRects[H * 3 + W].left = 0;
				pDstRects[H * 3 + W].right = rtTile.left;
				break;
			case 1:
				pSrcRects[H * 3 + W].left = rtTile.left;
				pSrcRects[H * 3 + W].right = rtTile.right;
				pDstRects[H * 3 + W].left = rtTile.left;
				pDstRects[H * 3 + W].right = pDstRects[H * 3 + W].left + nWidth;
				break;
			case 2:
				pSrcRects[H * 3 + W].left = rtTile.right;
				pSrcRects[H * 3 + W].right = rtLayer.right;
				pDstRects[H * 3 + W].left = rtTile.left + nWidth;
				pDstRects[H * 3 + W].right = pDstRects[H * 3 + W].left + pSrcRects[H * 3 + W].Width();
				break;
			}
		}
	}
	//-------------------------------------------------------------
}

CString GetNumStr(int nNum)
{
	CString str;
	str.Format("%d", nNum);
	return str;
}

CString GetNumStr(UINT uNum)
{
	CString str;
	str.Format("%u", uNum);
	return str;
}

CString GetOmittedNum(__int64 nNum)
{
	CString str = "0", strS = "";
	
	if (nNum < 0)
	{
		strS = "-";
		nNum = nNum * -1;
	}

	if (nNum >= 100000000000)
	{
		str.Format("%dǧ��", (nNum / 100000000000));
	}
	else if (nNum >= 100000000)
	{
		str.Format("%.1f��", floor(nNum / 100000000.0));
	}else if (nNum >= 1000000)
	{
		str.Format("%d��", (nNum / 10000));
	}else if (nNum >= 10000)
	{
		str.Format("%.1f��", floor(nNum / 10000.0));
	}else
	{
		str.Format("%d", nNum);
	}

	str = strS + str;

	return str;
}

CString NumberToStr(__int64 nNumber, BOOL bPlus, BOOL bComma, BOOL bLong, BOOL bShort, int nMaxTailCount)
{
	__int64 nAbs = nNumber;
	CString strAbs = "";
	CString strSign = "";				//	�������ű��
	CString strResult = "";				//	��󷵻ؽ��

	if (nNumber < 0)
		nAbs = -nNumber;

	//-------------------------------------------------------------
	//	��������
	if (nNumber > 0)
	{
		if (bPlus)
			strSign = "+";
	}
	else if (nNumber < 0)
	{
		strSign = "-";
	}
	//-------------------------------------------------------------

	if (bComma)
	{
		//	�Զ��ŷָ�����
		strAbs = GetMoneyStr(nAbs);
	}
	else
	{
		if ((!bLong) && (!bShort))
		{
			strAbs.Format("%I64d", nAbs);
		}
		else if (bShort)
		{
			CString strUnit = "";			//	��λ
			CString strInteger = "";		//	����	
			CString strDecimal = "";		//	С��
			__int64 nRemainder = 0;
			__int64 nDigigCount = 0;
			__int64 nBase;

			if (nMaxTailCount < 0)
				nMaxTailCount = 0;

			//-------------------------------------------------------------
			//	�����������ּ���λ
			if (nAbs >= NUMBER_BASE_1YI)
			{
				strUnit = "��";
				strInteger.Format("%d", nAbs / NUMBER_BASE_1YI);

				//-------------------------------------------------------------
				//	�������β������ȥ������β��
				if (nMaxTailCount >= NUMBER_1YI_DIGIT)
					nMaxTailCount = 0;
				
				nRemainder = nAbs % NUMBER_BASE_1YI;
				nBase = pow(10.0, 8 - nMaxTailCount);
				nRemainder = nRemainder / nBase * nBase;
				//-------------------------------------------------------------

				nDigigCount = 7;
			}
			else
			{
				if (nAbs >= NUMBER_BASE_1WAN)
				{
					strUnit = "��";
					strInteger.Format("%d", nAbs / NUMBER_BASE_1WAN);

					if (nMaxTailCount >= NUMBER_1WAN_DIGIT)
						nMaxTailCount = 0;					
					
					nRemainder = nAbs % NUMBER_BASE_1WAN;
					nBase = pow(10.0, 4 - nMaxTailCount);
					nRemainder = nRemainder / nBase * nBase;
					nDigigCount = 3;
				}
				else
				{
					strUnit = "";
					strInteger.Format("%d", nAbs);
					nMaxTailCount = 0;
					nRemainder = 0;
					nDigigCount = 0;
				}
			}
			//-------------------------------------------------------------

			//-------------------------------------------------------------
			//	����С������
			if (nMaxTailCount > 0 && nRemainder > 0)
			{
				__int64 nValidTail = 0;
				__int64 nDigit;
				__int64 nInteger;
				CString strNumber = "";

				for (int i = 0; i < nDigigCount; i++)
				{
					//	�ﵽ���β������
					if (i >= nMaxTailCount)
						break;

					nDigit = (int)pow(10.0, (int)(nDigigCount - i));
					nInteger = nRemainder / nDigit;
					nRemainder %= nDigit;
					strNumber.Format("%d", nInteger);
					strDecimal += strNumber;

					if (nInteger != 0)
					{
						nValidTail++;
					}
					else
					{
						if (nValidTail > 0)
							nValidTail++;
					}

					//	ʣ������Ϊ0
					if (nRemainder == 0)
						break;
				}

				//	���β��ȫΪ0������ҪС������
				if (nValidTail <= 0)
					strDecimal = "";
			}
			//-------------------------------------------------------------

			//-------------------------------------------------------------
			//	�ϲ�������С��
			if (strDecimal.GetLength())
				strAbs = strInteger + "." + strDecimal + strUnit;
			else
				strAbs = strInteger + strUnit;
			//-------------------------------------------------------------
		}
		else if (bLong)
		{
			CString strYi = "";
			CString strWan = "";
			CString strOther = "";

			if (nAbs >= NUMBER_BASE_1YI)
			{
				strYi.Format("%d��", nAbs / NUMBER_BASE_1YI);
				nAbs %= NUMBER_BASE_1YI;
			}

			if (nAbs >= NUMBER_BASE_1WAN)
			{
				strWan.Format("%d��", nAbs / NUMBER_BASE_1WAN);
				nAbs %= NUMBER_BASE_1WAN;
			}

			if (nAbs > 0)
			{
				strOther.Format("%d", nAbs);
				nAbs = 0;
			}

			strAbs = strYi + strWan + strOther;
		}
	}

	strResult = strSign + strAbs;
	return strResult;
}

long FloatRound(float fNumber)
{
	return (long)(fNumber + (double)0.5);
}
