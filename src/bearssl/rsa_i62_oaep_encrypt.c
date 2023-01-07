

#ifdef ESP8266

#include "inner.h"

#if BR_INT128 || BR_UMUL128

/* see bearssl_rsa.h */
size_t
br_rsa_i62_oaep_encrypt(
	const br_prng_class **rnd, const br_hash_class *dig,
	const void *label, size_t label_len,
	const br_rsa_public_key *pk,
	void *dst, size_t dst_max_len,
	const void *src, size_t src_len)
{
	size_t dlen;

	dlen = br_rsa_oaep_pad(rnd, dig, label, label_len,
		pk, dst, dst_max_len, src, src_len);
	if (dlen == 0) {
		return 0;
	}
	return dlen & -(size_t)br_rsa_i62_public(dst, dlen, pk);
}

/* see bearssl_rsa.h */
br_rsa_oaep_encrypt
br_rsa_i62_oaep_encrypt_get(void)
{
	return &br_rsa_i62_oaep_encrypt;
}

#else

/* see bearssl_rsa.h */
br_rsa_oaep_encrypt
br_rsa_i62_oaep_encrypt_get(void)
{
	return 0;
}

#endif

#endif