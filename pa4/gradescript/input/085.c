/*
 * Goto Test 6
 */

main() {
	int a;
	test1:
		a += 1;
		if (a < 10) {
			goto test1;
		}
	
	printf("%d\n", a);
}
