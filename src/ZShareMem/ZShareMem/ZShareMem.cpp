// ZShareMem.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "ZShareMem.h"
#include "ShareClass.h"

CZShareMem::CZShareMem()
{

}

CZShareMem::~CZShareMem()
{

}

CZShareMem* WINAPI CreateZShareMem(void)
{
	return new CShareClass;
}
