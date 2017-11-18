/* If Statements Section (CCNOT && CCAND && CCOR) */

main() {
	int a, b, c;
	a = 2;
	b = 3;
	c = 2;

	if (!a && b == c || a != c && !b) {
		printf("a, b, and c match (%d)!\n", a);
	}
}
