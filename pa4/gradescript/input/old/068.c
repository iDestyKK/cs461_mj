/*
 * Do-While-Loop Break/Continue Test (Multiple)
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
		break;
	}
	while (i < 100);

	i = 0;
	do {
		if (i >= 24)
			continue;
		a[i] = 0;
		i += 1;
		break;
	}
	while (i < 100);

	i = 0;
	do {
		if (i >= 24)
			continue;
		a[i] = 0;
		i += 1;
		break;
	}
	while (i < 100);
}
