
#ifdef ESP8266

#include "inner.h"

/* see inner.h */
uint32_t
br_i15_bit_length(uint16_t *x, size_t xlen)
{
	uint32_t tw, twk;

	tw = 0;
	twk = 0;
	while (xlen -- > 0) {
		uint32_t w, c;
		delay(0);

		c = EQ(tw, 0);
		w = x[xlen];
		tw = MUX(c, w, tw);
		twk = MUX(c, (uint32_t)xlen, twk);
	}
	return (twk << 4) + BIT_LENGTH(tw);
}

#endif
