// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <assert.h>
#include "ZEncryptFile.h"

#include "../../common/include/ZEncrypt.h"

#pragma comment(lib,"../../common/lib/ZEncrypt.lib")

#define converlen(len) ((USHORT)len ^ 0x54)

size_t DefaultEncrpt(PVOID bufin,PVOID bufout,size_t lenin);
size_t DefaultDecrpt(PVOID bufin,PVOID bufout,size_t lenin);

#define FREAD_HEAD_SIZE	512
#define FREAD_DATABLUK_SIZE	1024*4