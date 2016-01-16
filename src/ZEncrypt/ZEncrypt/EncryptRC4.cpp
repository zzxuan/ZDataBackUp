#include "StdAfx.h"
#include "EncryptRC4.h"

CEncryptRC4::CEncryptRC4(void)
{
}

CEncryptRC4::~CEncryptRC4(void)
{
}

HRESULT CEncryptRC4::EncryptBuffer( 
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

	arc4_context arc4;
	arc4_setup(&arc4, (const unsigned char *)password, passwordlen);
	arc4_crypt( &arc4, intputbuflen, (const unsigned char *)inputbuf, (unsigned char *)outputbuf );
	(*outputbuflen) = intputbuflen;

	return ERROR_SUCCESS;
}

HRESULT CEncryptRC4::DecryptBuffer( 
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

	arc4_context arc4;
	arc4_setup(&arc4, (const unsigned char *)password, passwordlen);
	arc4_crypt( &arc4, intputbuflen, (const unsigned char *)inputbuf, (unsigned char *)outputbuf );
	(*outputbuflen) = intputbuflen;

	return ERROR_SUCCESS;
}



/*
 * ARC4 key schedule
 */
void CEncryptRC4::arc4_setup( arc4_context *ctx, const unsigned char *key, int keylen )
{
    int i, j, k, a;
    unsigned char *m;

    ctx->x = 0;
    ctx->y = 0;
    m = ctx->m;

    for( i = 0; i < 256; i++ )
        m[i] = (unsigned char) i;

    j = k = 0;

    for( i = 0; i < 256; i++, k++ )
    {
        if( k >= keylen ) k = 0;

        a = m[i];
        j = ( j + a + key[k] ) & 0xFF;
        m[i] = m[j];
        m[j] = (unsigned char) a;
    }
}

/*
 * ARC4 cipher function
 */
int CEncryptRC4::arc4_crypt( arc4_context *ctx, int length, const unsigned char *input,
                unsigned char *output )
{
    int i, x, y, a, b;
    unsigned char *m;

    x = ctx->x;
    y = ctx->y;
    m = ctx->m;

    for( i = 0; i < length; i++ )
    {
        x = ( x + 1 ) & 0xFF; a = m[x];
        y = ( y + a ) & 0xFF; b = m[y];

        m[x] = (unsigned char) b;
        m[y] = (unsigned char) a;

        output[i] = (unsigned char)
            ( input[i] ^ m[(unsigned char)( a + b )] );
    }

    ctx->x = x;
    ctx->y = y;

    return( 0 );
}