
#ifdef ESP8266

#include "inner.h"

/* see inner.h */
uint32_t
br_rsa_pkcs1_sig_pad(const unsigned char *hash_oid,
	const unsigned char *hash, size_t hash_len,
	uint32_t n_bitlen, unsigned char *x)
{
	size_t u, x3, xlen;

	/*
	 * Padded hash value has format:
	 *  00 01 FF .. FF 00 30 x1 30 x2 06 x3 OID 05 00 04 x4 HASH
	 *
	 * with the following rules:
	 *
	 *  -- Total length is equal to the modulus length (unsigned
	 *     encoding).
	 *
	 *  -- There must be at least eight bytes of value 0xFF.
	 *
	 *  -- x4 is equal to the hash length (hash_len).
	 *
	 *  -- x3 is equal to the encoded OID value length (hash_oid[0]).
	 *
	 *  -- x2 = x3 + 4.
	 *
	 *  -- x1 = x2 + x4 + 4 = x3 + x4 + 8.
	 *
	 * Note: the "05 00" is optional (signatures with and without
	 * that sequence exist in practice), but notes in PKCS#1 seem to
	 * indicate that the presence of that sequence (specifically,
	 * an ASN.1 NULL value for the hash parameters) may be slightly
	 * more "standard" than the opposite.
	 */
	xlen = (n_bitlen + 7) >> 3;

	if (hash_oid == NULL) {
		if (xlen < hash_len + 11) {
			return 0;
		}
		x[0] = 0x00;
		x[1] = 0x01;
		u = xlen - hash_len;
		memset(x + 2, 0xFF, u - 3);
		x[u - 1] = 0x00;
	} else {
		x3 = hash_oid[0];

		/*
		 * Check that there is enough room for all the elements,
		 * including at least eight bytes of value 0xFF.
		 */
		if (xlen < (x3 + hash_len + 21)) {
			return 0;
		}
		x[0] = 0x00;
		x[1] = 0x01;
		u = xlen - x3 - hash_len - 11;
		memset(x + 2, 0xFF, u - 2);
		x[u] = 0x00;
		x[u + 1] = 0x30;
		x[u + 2] = x3 + hash_len + 8;
		x[u + 3] = 0x30;
		x[u + 4] = x3 + 4;
		x[u + 5] = 0x06;
		memcpy(x + u + 6, hash_oid, x3 + 1);
		u += x3 + 7;
		x[u ++] = 0x05;
		x[u ++] = 0x00;
		x[u ++] = 0x04;
		x[u ++] = hash_len;
	}
	memcpy(x + u, hash, hash_len);
	return 1;
}

#endif