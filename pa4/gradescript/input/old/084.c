/*
 * Goto Test 5
 */

main() {
	int a;
	test1:
		a = 0;
		goto test2;

	test2:
		a += 1;
		printf("%d\n", a);
		goto test2;
	
	/* This line of code should never execute */
	printf("%d\n", a);
}
