/*
 * For-Loop Break Test
 */

int a[24];

main() {
	int i;
	for (i = 0; i < 100; i += 1) {
		if (i >= 24)
			break;
		a[i] = 0;
	}
}
