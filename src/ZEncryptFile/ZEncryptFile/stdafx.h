// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>
#include <tchar.h>


// TODO: 在此处引用程序需要的其他头文件
#include <assert.h>
#include "ZEncryptFile.h"

#include "../../common/include/ZEncrypt.h"
#include "../../common/include/ConverHelper.h"

#pragma comment(lib,"../../common/lib/ZEncrypt.lib")

#define converlen(len) ((USHORT)len ^ 0x54)
//#define converlen(len) ((USHORT)len)

size_t DefaultEncrpt(PVOID bufin,PVOID bufout,size_t lenin);
size_t DefaultDecrpt(PVOID bufin,PVOID bufout,size_t lenin);

#define FREAD_HEAD_SIZE	1024
#define FREAD_DATABLUK_SIZE	1024 * 56
#define MD5LEN	16