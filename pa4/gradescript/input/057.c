/*
 * Do-While-Loop Continue Test
 */

int a[24];

main() {
	int i;
	i = 0;
	do {
		if (i >= 24)
			continue;
		a[i] = 0;
		i += 1;
	}
	while (i < 100);
}
