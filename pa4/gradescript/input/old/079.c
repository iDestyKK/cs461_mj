/*
 * All Binary Operations Test 2
 */

main() {
	int a, b, c, i;
	a = 1;
	b = 2;
	c = 3;

	for (i = 0; i | (a << 12) < (1 << 12); i += 1) {
		a += (~b | ~c) & (a ^ ~b);
		b += (~a | a) * (~b << 8);
		c += ((~c * ~c) | b & a >> 2) << 12;
	}

	printf("%d %d %d\n", a, b, c);
}
