// ZShareMem.cpp : ���� DLL Ӧ�ó���ĵ���������
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
