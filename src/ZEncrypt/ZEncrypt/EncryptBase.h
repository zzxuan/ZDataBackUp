#pragma once

class CEncryptBase
{
public:
	CEncryptBase(void);
	virtual ~CEncryptBase(void);

	virtual HRESULT EncryptBuffer(
		__in PVOID inputbuf,
		__in size_t intputbuflen,
		__out PVOID outputbuf,
		__inout size_t* outputbuflen,
		__in PVOID password,
		__in size_t passwordlen
		) = 0;

	virtual HRESULT DecryptBuffer(
		__in PVOID inputbuf,
		__in size_t intputbuflen,
		__out PVOID outputbuf,
		__inout size_t* outputbuflen,
		__in PVOID password,
		__in size_t passwordlen
		) = 0;
};
