/*
 * Nested Function Calling Test 2
 */

double gl; /* Grenade Launcher */

cool(double x) {
	double gl;
	gl = x;
	return gl;
}

main() {
	int x;
	double y;
	x = 0;
	y = x + 1;
	y = gl(y);
	printf(
		"%d %f %d\n",
		x + y,
		gl(y) + 2,
		printf("Bet you didn't see this one coming... %d\n", x * y)
	);
}
