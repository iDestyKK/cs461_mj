#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	for (i = 0; i < 64; i++) {
		int f = 10, z = -55;
		f&=z>>=((864 + i) % 32);
		printf("%d - %d\n", i, f);
	}
}

