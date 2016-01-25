#include "StdAfx.h"
#include "EncryptNULL.h"

CEncryptNULL::CEncryptNULL(void)
{
	//printf("CEncryptNULL\n");
}

CEncryptNULL::~CEncryptNULL(void)
{
	//printf("~CEncryptNULL\n");
}

HRESULT CEncryptNULL::EncryptBuffer( 
									 __in PVOID inputbuf,
									 __in size_t intputbuflen,
									 __out PVOID outputbuf,
									 __inout size_t* outputbuflen, 
									 __in PVOID password, 
									 __in size_t passwordlen 
									 )
{
	assert(inputbuf);
	assert(outputbuf);
	assert(outputbuflen);
	assert(password);
	assert(passwordlen);

	if ((*outputbuflen) < intputbuflen)
	{
		(*outputbuflen) = intputbuflen;
		return ERROR_DS_USER_BUFFER_TO_SMALL;
	}

	memcpy(outputbuf,inputbuf,intputbuflen);

	return ERROR_SUCCESS;
}

HRESULT CEncryptNULL::DecryptBuffer( 
									 __in PVOID inputbuf,
									 __in size_t intputbuflen,
									 __out PVOID outputbuf,
									 __inout size_t* outputbuflen,
									 __in PVOID password,
									 __in size_t passwordlen
									 )
{
	assert(inputbuf);
	assert(outputbuf);
	assert(outputbuflen);
	assert(password);
	assert(passwordlen);

	if ((*outputbuflen) < intputbuflen)
	{
		(*outputbuflen) = intputbuflen;
		return ERROR_DS_USER_BUFFER_TO_SMALL;
	}

	memcpy(outputbuf,inputbuf,intputbuflen);

	return ERROR_SUCCESS;
}
