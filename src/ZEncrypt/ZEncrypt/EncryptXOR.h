#pragma once
#include "encryptbase.h"

class CEncryptXOR :
	public CEncryptBase
{
public:
	CEncryptXOR(void);
	virtual ~CEncryptXOR(void);

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

	HRESULT XorBuffer(
		__in PVOID inputbuf,
		__in size_t intputbuflen,
		__out PVOID outputbuf,
		__inout size_t* outputbuflen,
		__in PVOID password,
		__in size_t passwordlen
		) ;

};
