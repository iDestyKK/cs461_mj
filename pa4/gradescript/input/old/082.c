/*
 * Goto Test 3
 */

add(int a, int b) {
	return a + b;
}

main() {
	int a[4];
	goto test2;
	test1:
		a[0] = 2;
		a[1] = 3;
		goto test3;

	test2:
		a[2] = add(a[0], a[1]);
		a[3] = a[0] * a[1];
		goto test1;

	test3:
		a[0] = 42;
}
