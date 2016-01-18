// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>



// TODO: 在此处引用程序需要的其他头文件
#include <assert.h>
#include "EncryptFile.h"

#include "../../common/include/ZEncrypt.h"

#pragma comment(lib,"../../common/lib/ZEncrypt.lib")

#define converlen(len) ((USHORT)len ^ 0x54)

size_t DefaultEncrpt(PVOID bufin,PVOID bufout,size_t lenin);
size_t DefaultDecrpt(PVOID bufin,PVOID bufout,size_t lenin);