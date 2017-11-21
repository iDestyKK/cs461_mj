/*
 * Goto Test 4
 */

add(int a, int b) {
	return a + b;
}

main() {
	int a[4];
	test1:
		a[0] = 2;
		a[1] = 3;
		goto test2;

	test2:
		a[2] = add(a[0], a[1]);
		a[3] = a[0] * a[1];
		goto final;

	final:
		printf(
			"%d %d %d %d\n",
			a[0],
			a[1],
			a[2],
			a[3]
		);
}
