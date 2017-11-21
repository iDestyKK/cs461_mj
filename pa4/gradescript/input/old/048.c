/*
 * Do-While Loop Tests (Nested)
 *
 * Hint:
 *     This one may not auto-pass just because you implemented your dodo(). But
 *     make sure your set is correct, and make sure nesting is supported. Then
 *     you should be fine.
 */

main() {
	int i, j, k;
	i = 0;
	j = 10;

	do {
		i += 1;
		do {
			i += j;
		}
		while (k < j);
	}
	while ((rand() % 20000) < 10000);
}
