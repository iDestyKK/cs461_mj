/*
 * While-Loop Break Test
 */

int a[24];

main() {
	int i;
	i = 0;
	while (i < 100) {
		if (i >= 24)
			break;
		a[i] = 0;
		i += 1;
	}
}
