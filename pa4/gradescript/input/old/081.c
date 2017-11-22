/*
 * Goto Test 2
 */

main() {
	int a;
	test1:
		a = 0;
		goto test2;

	test2:
		a += 1;

		/* Loop Infinitely */
		goto test2;
}
