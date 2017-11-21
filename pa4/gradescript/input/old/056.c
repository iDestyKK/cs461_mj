/*
 * Do-While-Loop Break Test
 */

int a[24];

main() {
	int i;
	i = 0;
	do {
		if (i >= 24)
			break;
		a[i] = 0;
		i += 1;
	}
	while (i < 100);
}
