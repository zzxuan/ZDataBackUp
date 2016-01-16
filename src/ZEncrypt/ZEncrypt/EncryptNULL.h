#pragma once
#include "encryptbase.h"

class CEncryptNULL :
	public CEncryptBase
{
public:
	CEncryptNULL(void);
	~CEncryptNULL(void);

	HRESULT EncryptBuffer(
		__in PVOID inputbuf,
		__in size_t intputbuflen,
		__out PVOID outputbuf,
		__inout size_t* outputbuflen,
		__in PVOID password,
		__in size_t passwordlen
		) ;

	HRESULT DecryptBuffer(
		__in PVOID inputbuf,
		__in size_t intputbuflen,
		__out PVOID outputbuf,
		__inout size_t* outputbuflen,
		__in PVOID password,
		__in size_t passwordlen
		) ;
};
