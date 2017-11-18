/* If Statements Section (CCNOT && CCOR) */

main() {
	int a, b, c;
	a = 2;
	b = 3;
	c = 2;

	if (!a || b == c || a != c) {
		printf("a, b, and c match (%d)!\n", a);
	}
}
