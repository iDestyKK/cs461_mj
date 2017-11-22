/*
 * For Loop Test 2
 */

main() {
	int i, j;
	for (i = 0; i < 10; i += 1) {

		/* Nested Lists... :) */
		for (j = 0; j < 10; j += 1) {
			printf("%d, %d\n", i, j);
		}
	}
}

