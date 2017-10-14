#include <stdio.h>
#include <stdlib.h>

main() {
	unsigned int i = 0, j;
	char buf[65];
	buf[64] = '\0';
	long long val = 37489;
	unsigned int lv;
	int rv;

	for (; i < 64; i++) {
		memset(&buf[0], '0', 64); //Empty the buffer
		lv = (unsigned int)((val << -i) >> 32) & 0xFFFFFFFF;
		rv = (int)(val << -i) & 0xFFFFFFFF;
		if (lv > 0)
			rv |= (1 << 31);
		for (j = 0; j < 64; j++) {
			buf[j] = '0' + (((val<<-i) >> (63 - j)) & 1);
		}
		printf("%3d - %11d - %11d - %s\n", i, (val<<-i), rv, buf);
	}
}
