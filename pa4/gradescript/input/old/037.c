/*
 * Functions Test 3
 */

add(int a, int b) {
	return a + b;
}

sub(int a, int b) {
	return a - b;
}

/* A game changer */
double fmul(double a, double b) {
	return a * b;
}

main() {
	int ca, cb;
	double d; /* Edd ;) */
	ca = add(2, 2); /* Should be 5 */
	cb = sub(1, 2);

	d = fmul(ca, cb);
}
