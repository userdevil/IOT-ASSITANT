
#ifdef ESP8266

#include "inner.h"

/* see bearssl_rsa.h */
uint32_t
br_rsa_ssl_decrypt(br_rsa_private core, const br_rsa_private_key *sk,
	unsigned char *data, size_t len)
{
	uint32_t x;
	size_t u;

	/*
	 * A first check on length. Since this test works only on the
	 * buffer length, it needs not (and cannot) be constant-time.
	 */
	if (len < 59 || len != (sk->n_bitlen + 7) >> 3) {
		return 0;
	}
	x = core(data, sk);

	x &= EQ(data[0], 0x00);
	x &= EQ(data[1], 0x02);
	for (u = 2; u < (len - 49); u ++) {
		x &= NEQ(data[u], 0);
	}
	x &= EQ(data[len - 49], 0x00);
	memmove(data, data + len - 48, 48);
	return x;
}

#endif