//Reverse engineering the solution to figure out how left shifts identify an
//overflow.

#include <stdio.h>
#include <stdlib.h>

main(int argc, char** argv) {
	unsigned int i = 0, j;
	char buf[65];
	buf[64] = '\0';
	char msb;
	long long val = atoi(argv[1]);
	unsigned int lv;
	char overflow;
	int rv;

	for (; i < 64; i++) {
		memset(&buf[0], '0', 64); //Empty the buffer
		overflow = 0;
		msb = (val >> 31) & 1;
		lv = (unsigned int)((val << i) >> 32) & 0xFFFFFFFF;
		rv = (int)(val << i) & 0xFFFFFFFF;
		if (lv > 0)
			rv |= (1 << 31);
		for (j = 0; j < 64; j++) {
			buf[j] = '0' + (((val<<i) >> (63 - j)) & 1);
		}
		overflow = (msb != (((val << i) >> 31) & 1) || (lv != 0 && val > 0) || (lv != -1 && val < 0));
		if (val << i == 0) overflow = 0;
		printf("%3d (%c) - %11d - %11d - %s\n", i, (overflow) ? 'Y' : ' ', (val<<i), lv, buf);
	}
}
