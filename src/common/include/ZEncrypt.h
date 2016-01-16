#ifndef __ZENCRYPT__H__
#define __ZENCRYPT__H__


enum ENCRYPTTYPE
{
	ENCRYPT_NULL,
	ENCRYPT_XOR,
	ENCRYPT_RC4,
	//ENCRYPT_RES
};


HRESULT ZEncryptBuffer(
					   __in PVOID inputbuf,
					   __in size_t intputbuflen,
					   __out PVOID outputbuf,
					   __inout size_t* outputbuflen,
					   __in ULONG encrypttype,
					   __in PVOID password,
					   __in size_t passwordlen
					   );

HRESULT ZDecryptBuffer(
					   __in PVOID inputbuf,
					   __in size_t intputbuflen,
					   __out PVOID outputbuf,
					   __inout size_t* outputbuflen,
					   __in ULONG encrypttype,
					   __in PVOID password,
					   __in size_t passwordlen
					   );
#endif