#include "StdAfx.h"
#include "EncryptXOR.h"

CEncryptXOR::CEncryptXOR(void)
{
}

CEncryptXOR::~CEncryptXOR(void)
{
}

HRESULT CEncryptXOR::EncryptBuffer( 
									__in PVOID inputbuf,
									__in size_t intputbuflen,
									__out PVOID outputbuf,
									__inout size_t* outputbuflen, 
									__in PVOID password, 
									__in size_t passwordlen 
									)
{
	return XorBuffer(inputbuf,intputbuflen,outputbuf,outputbuflen,password,passwordlen);
}

HRESULT CEncryptXOR::DecryptBuffer( 
									__in PVOID inputbuf,
									__in size_t intputbuflen,
									__out PVOID outputbuf,
									__inout size_t* outputbuflen,
									__in PVOID password,
									__in size_t passwordlen
									)
{
	return XorBuffer(inputbuf,intputbuflen,outputbuf,outputbuflen,password,passwordlen);
}


HRESULT CEncryptXOR::XorBuffer( 
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

	PUCHAR inbuf = (PUCHAR)inputbuf;
	PUCHAR outbuf = (PUCHAR)outputbuf;
	PUCHAR pass = (PUCHAR)password;
	
	UINT n = 0;
	for (UINT i=0;i<intputbuflen;i++)
	{
		outbuf[i] = inbuf[i]^pass[n];
		n++;
		if (n >= passwordlen)
		{
			n = 0;
		}
	}
	(*outputbuflen) = intputbuflen;

	return ERROR_SUCCESS;
}