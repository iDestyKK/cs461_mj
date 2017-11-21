/*
 * While Loop Test (Nested)
 *
 * Hint:
 *     Just support nested while loops... oh and also function calls.
 */

main() {
	int i, j, k;
	i = 0;
	j = 10;

	while (i < j) {
		i += 1;
		k = 0;
		while (k < i) {
			k += 1;
			printf("%d\n", k);
		}
	}
}
