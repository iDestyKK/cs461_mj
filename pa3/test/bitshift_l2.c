#include <stdio.h>
#include <stdlib.h>

main() {
	unsigned int i = 0, j;
	char buf[33];
	buf[32] = '\0';
	long long val = 96;
	unsigned int lv;
	int rv;

	for (; i < 64; i++) {
		memset(&buf[0], '0', 32); //Empty the buffer
		lv = (unsigned int)((val << -i) >> 32) & 0xFFFFFFFF;
		rv = (int)(val << -i) & 0xFFFFFFFF;
		//if (lv > 0)
		//	rv |= (1 << 31);
		for (j = 0; j < 32; j++) {
			buf[j] = '0' + (((int)(val<<-i) >> (31 - j)) & 1);
		}
		printf("%3d - %11d - %11d - %s\n", i, (val<<-i), rv, buf);
	}
}
