#pragma once
#include "encryptbase.h"

/**
* \brief          ARC4 context structure
*/
typedef struct
{
	int x;                      /*!< permutation index */
	int y;                      /*!< permutation index */
	unsigned char m[256];       /*!< permutation table */
}
arc4_context;

class CEncryptRC4 :
	public CEncryptBase
{
public:
	CEncryptRC4(void);
	~CEncryptRC4(void);

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

	/**
	* \brief          ARC4 key schedule
	*
	* \param ctx      ARC4 context to be initialized
	* \param key      the secret key
	* \param keylen   length of the key
	*/
	void arc4_setup( arc4_context *ctx, const unsigned char *key, int keylen );

	/**
	* \brief          ARC4 cipher function
	*
	* \param ctx      ARC4 context
	* \param length   length of the input data
	* \param input    buffer holding the input data
	* \param output   buffer for the output data
	*
	* \return         0 if successful
	*/
	int arc4_crypt( arc4_context *ctx, int length, const unsigned char *input,
		unsigned char *output );
};
