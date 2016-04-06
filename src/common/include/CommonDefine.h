#ifndef __COMMONDEFINE__H__
#define __COMMONDEFINE__H__

#include "ZEncrypt.h"

#define PATH_MAX_LEN 512

#define CONVERT_CMD_OPTION_ENCRPT_BYMEM		L"-bymem"
#define CONVERT_CMD_OPTION_ENCRPT_TOFILE		L"-enc"
#define CONVERT_CMD_OPTION_DECRPT_FROMFILE		L"-dec"
#define CONVERT_CMD_OPTION_ENCRPT_TOZIP		L"-ezip"
#define CONVERT_CMD_OPTION_DECRPT_FROMZIP		L"-dzip"

#define CONVERT_CMD_ENCRPTTYPE_RC4		L"rc4"

#define CONVERT_CMD_SHOWPROCDIALOG		L"1"
#define CONVERT_CMD_NOTSHOWPROCDIALOG	L"0"

#define CONVERT_OPTIONCODE_ENCRPT_TOFILE					1
#define CONVERT_OPTIONCODE_DECRPT_FROMFILE					2
#define CONVERT_OPTIONCODE_ENCRPT_TOZIP						3
#define CONVERT_OPTIONCODE_DECRPT_FROMZIP					4
#define CONVERT_OPTIONCODE_GETINFO_FROMFILE					5
#define CONVERT_OPTIONCODE_GETINFO_FROMZIP					6
#define CONVERT_OPTIONCODE_GETLIST_FROMZIP					7

#define CONVERT_MEM_CREATENAME_EXT L"_ConvertCreator"

#define MEM_MAXUSE_SIZE		3*1024

#define ERROR_SUCCESS_BUT_BUFFERTOOSMALL 0xFF000000

#pragma pack(1)

//定义转化数据结构
typedef struct __zconverdata__
{
	TCHAR dstpath[PATH_MAX_LEN];
	TCHAR srcpath[PATH_MAX_LEN];
	ULONG optionType;
	ULONG encyptType;
	BOOL showProcDialog;
	UCHAR passWord[PATH_MAX_LEN];
	ULONG passWorfLen;
	UCHAR extdata[PATH_MAX_LEN];
	ULONG extlen;
	UCHAR reserve[PATH_MAX_LEN];
}ZConvertData,*PZConvertData;

typedef struct __zfileinfo__
{
	WIN32_FIND_DATAA fileData;
	UCHAR extendData[PATH_MAX_LEN];
	size_t extendLen;
}ZFileinfo,*PZFileinfo;

typedef struct __ziplistinfo__
{
	CHAR listData[MEM_MAXUSE_SIZE];
	ULONG listcount;
}ZZipListInfo,*PZZipListInfo;

#pragma pack()


#define ENCYFILE_EXT _T(".zenc")

#endif