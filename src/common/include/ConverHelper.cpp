#include "stdafx.h"
#include "ConverHelper.h"

VOID ShowLastErrMsg()
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL
		);

	// Process any inserts in lpMsgBuf.
	// ...

	// Display the string.
	MessageBox(NULL,(LPCTSTR)lpMsgBuf, _T("Error"), MB_OK | MB_ICONINFORMATION );

	// Free the buffer.
	LocalFree( lpMsgBuf );
}

VOID ZDbgPrint(UINT level,TCHAR * szFormat, ...)
{
	TCHAR   szBuffer [1024] ;
	va_list pArgList ;

	// The va_start macro (defined in STDARG.H) is usually equivalent to:
	// pArgList = (char *) &szFormat + sizeof (szFormat) ;

	va_start (pArgList, szFormat) ;

	// The last argument to wvsprintf points to the arguments

	_vsntprintf (szBuffer, sizeof (szBuffer) / sizeof (TCHAR), 
		szFormat, pArgList) ;

	// The va_end macro just zeroes out pArgList for no good reason

	va_end (pArgList) ;

	return OutputDebugString ( szBuffer) ;
}